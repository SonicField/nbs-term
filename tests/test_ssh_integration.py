"""
test_ssh_integration.py — Headless integration test using nbs-ssh MockSSHServer.

Tests the full data flow: MockSSHServer → SSHTransport → Terminal.feed() → screen state.
No Tk display required. Verifies the threading model and byte transport work correctly.
"""
import sys
import os
import asyncio
import threading
import time
import unittest

# Ensure project root is on path for _nbsterm
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import _nbsterm
from nbs_ssh import SSHConnection, HostKeyPolicy
from nbs_ssh.testing.mock_server import MockSSHServer, MockServerConfig


class TestSSHDataFlow(unittest.TestCase):
    """Test data flow through the threading model without Tk."""

    def test_connect_and_receive_prompt(self):
        """Connect to mock server, verify prompt appears in terminal screen."""
        asyncio.run(self._async_connect_and_receive_prompt())

    async def _async_connect_and_receive_prompt(self):
        config = MockServerConfig(username="test", password="test")
        async with MockSSHServer(config) as server:
            term = _nbsterm.Terminal(24, 80)
            received_data = []

            # Connect via SSHConnection
            conn = SSHConnection(
                host="localhost",
                port=server.port,
                username="test",
                password="test",
                known_hosts=None,
                host_key_policy=HostKeyPolicy.ACCEPT_NEW,
            )
            async with conn:
                process = await conn._conn.create_process(
                    None,  # shell
                    term_type="xterm-256color",
                    term_size=(80, 24),
                )

                # Read data until we see the prompt (with timeout)
                deadline = time.monotonic() + 5.0
                prompt_found = False
                while time.monotonic() < deadline:
                    try:
                        data = await asyncio.wait_for(
                            process.stdout.read(4096), timeout=0.5
                        )
                        if not data:
                            break
                        raw = data.encode() if isinstance(data, str) else data
                        term.feed(raw)
                        received_data.append(raw)

                        # Check if prompt is on screen
                        cell = term.get_cell(0, 0)
                        if cell and cell[0] == ord('t'):  # 'test@mockhost'
                            prompt_found = True
                            break
                    except asyncio.TimeoutError:
                        continue

                # Verify prompt appeared in terminal
                self.assertTrue(prompt_found,
                    f"Prompt not found. Received {len(received_data)} chunks, "
                    f"total {sum(len(d) for d in received_data)} bytes. "
                    f"Cell(0,0) = {term.get_cell(0, 0)}")

                # Verify terminal state is sane
                rows, cols = term.get_size()
                self.assertEqual(rows, 24)
                self.assertEqual(cols, 80)

                # Clean shutdown
                process.stdin.write_eof()

    def test_send_input_and_receive_echo(self):
        """Send keystrokes to mock server, verify echo in terminal."""
        asyncio.run(self._async_send_input())

    async def _async_send_input(self):
        config = MockServerConfig(username="test", password="test")
        async with MockSSHServer(config) as server:
            term = _nbsterm.Terminal(24, 80)

            conn = SSHConnection(
                host="localhost",
                port=server.port,
                username="test",
                password="test",
                known_hosts=None,
                host_key_policy=HostKeyPolicy.ACCEPT_NEW,
            )
            async with conn:
                process = await conn._conn.create_process(
                    None,
                    term_type="xterm-256color",
                    term_size=(80, 24),
                )

                # Wait for initial prompt
                deadline = time.monotonic() + 5.0
                while time.monotonic() < deadline:
                    try:
                        data = await asyncio.wait_for(
                            process.stdout.read(4096), timeout=0.5
                        )
                        if not data:
                            break
                        raw = data.encode() if isinstance(data, str) else data
                        term.feed(raw)
                        if term.get_cell(0, 0) and term.get_cell(0, 0)[0] != 0:
                            break
                    except asyncio.TimeoutError:
                        continue

                # Send a character
                process.stdin.write("A")

                # Wait for echo
                deadline = time.monotonic() + 3.0
                echo_found = False
                while time.monotonic() < deadline:
                    try:
                        data = await asyncio.wait_for(
                            process.stdout.read(4096), timeout=0.5
                        )
                        if not data:
                            break
                        raw = data.encode() if isinstance(data, str) else data
                        term.feed(raw)

                        # Search for 'A' on the screen (after prompt)
                        for col in range(80):
                            cell = term.get_cell(0, col)
                            if cell and cell[0] == ord('A'):
                                echo_found = True
                                break
                        if echo_found:
                            break
                    except asyncio.TimeoutError:
                        continue

                self.assertTrue(echo_found, "Echo of 'A' not found on screen")

                process.stdin.write_eof()

    def test_terminal_resize(self):
        """Verify terminal resize updates dimensions correctly."""
        term = _nbsterm.Terminal(24, 80)
        self.assertEqual(term.get_size(), (24, 80))
        term.resize(40, 120)
        self.assertEqual(term.get_size(), (40, 120))
        # Feed some data after resize — must not crash
        term.feed(b"Hello after resize")
        cell = term.get_cell(0, 0)
        self.assertEqual(cell[0], ord('H'))


if __name__ == '__main__':
    result = unittest.main(verbosity=2, exit=False)
    total = result.result.testsRun
    failures = len(result.result.failures) + len(result.result.errors)
    skipped = len(result.result.skipped)
    passed = total - failures - skipped
    print(f"\n  Pass: {passed} | Fail: {failures} | Skip: {skipped} | Total: {total}")
    gate = "OPEN" if failures == 0 and skipped == 0 else "BLOCKED"
    print(f"  Gate: {gate} (full_suite: no)")
    sys.exit(0 if failures == 0 else 1)
