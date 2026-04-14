#!/usr/bin/env python3
"""
Headless integration test for the nbs-term orchestration layer.

Tests the data flow: MockSSHServer → SSHTransport → Terminal.feed() → screen state,
without requiring a Tk display.

Uses nbs-ssh's MockSSHServer for the SSH endpoint.
"""
import sys
import os
import asyncio
import threading
import time

# Ensure project root is on path for _nbsterm
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import _nbsterm

try:
    from nbs_ssh import SSHConnection, HostKeyPolicy
    from nbs_ssh.testing.mock_server import MockSSHServer, MockServerConfig
    HAS_NBS_SSH = True
except ImportError:
    HAS_NBS_SSH = False

# --- Test infrastructure ---

tests_run = 0
tests_passed = 0
tests_failed = 0


def _named(name):
    """Decorator to attach a display name to test functions."""
    def decorator(func):
        func._test_name = name
        return func
    return decorator


def run_test(func):
    global tests_run, tests_passed, tests_failed
    tests_run += 1
    name = getattr(func, '_test_name', func.__name__)
    try:
        func()
        tests_passed += 1
        print(f"  {name:50s} PASS")
    except Exception as e:
        tests_failed += 1
        print(f"  {name:50s} FAIL")
        print(f"    {e}")


def run_async_test(func):
    global tests_run, tests_passed, tests_failed
    tests_run += 1
    name = getattr(func, '_test_name', func.__name__)
    try:
        asyncio.run(func())
        tests_passed += 1
        print(f"  {name:50s} PASS")
    except Exception as e:
        tests_failed += 1
        print(f"  {name:50s} FAIL")
        print(f"    {e}")


# --- Tests ---

@_named("terminal_creation")
def test_terminal_creation():
    """Terminal can be created and used without Tk."""
    term = _nbsterm.Terminal(24, 80)
    assert term.get_size() == (24, 80)
    term.feed(b"Hello")
    row, col = term.get_cursor()
    assert row == 0 and col == 5, f"Expected (0,5), got ({row},{col})"


@_named("terminal_feed_escape_sequences")
def test_terminal_feed_escapes():
    """Terminal processes escape sequences correctly."""
    term = _nbsterm.Terminal(24, 80)
    term.feed(b"\x1b[31mRed\x1b[32mGreen\x1b[0m Normal")
    screen = term.get_screen()
    # Row 0 should have multiple spans
    assert len(screen[0]) >= 3, f"Expected >=3 spans, got {len(screen[0])}"
    # First span should be red
    text, fg, bg, attrs = screen[0][0][:4]
    assert "Red" in text, f"Expected 'Red' in span, got {text!r}"
    assert fg == "#cd0000", f"Expected red fg, got {fg}"


@_named("terminal_key_encoding")
def test_key_encoding():
    """Key encoding produces correct byte sequences."""
    term = _nbsterm.Terminal(24, 80)
    assert term.encode_key(ord('a')) == b'a'
    assert term.encode_key(ord('c'), _nbsterm.MOD_CTRL) == b'\x03'
    assert term.encode_special(_nbsterm.KEY_UP) == b'\x1b[A'
    assert term.encode_special(_nbsterm.KEY_UP, _nbsterm.MOD_SHIFT) == b'\x1b[1;2A'


@_named("terminal_scrollback")
def test_scrollback():
    """Scrollback captures lines that scroll off screen."""
    term = _nbsterm.Terminal(3, 10)
    term.feed(b"AAA\r\nBBB\r\nCCC\r\nDDD\r\nEEE")
    assert term.get_scrollback_count() == 2
    line = term.get_scrollback_line(0)
    assert line is not None
    assert "AAA" in line[0][0]


@_named("terminal_resize")
def test_resize():
    """Terminal resize works correctly."""
    term = _nbsterm.Terminal(24, 80)
    term.feed(b"Hello")
    term.resize(40, 120)
    assert term.get_size() == (40, 120)


@_named("terminal_dec_charset")
def test_dec_charset():
    """DEC line-drawing charset translates correctly."""
    term = _nbsterm.Terminal(24, 80)
    term.feed(b"\x1b(0qqqqq\x1b(B")
    cp = term.get_cell(0, 0)[0]
    assert cp == 0x2500, f"Expected U+2500 (─), got U+{cp:04X}"


@_named("terminal_alt_screen")
def test_alt_screen():
    """Alternate screen buffer works correctly."""
    term = _nbsterm.Terminal(24, 80)
    term.feed(b"Main")
    term.feed(b"\x1b[?1049h")  # switch to alt
    term.feed(b"Alt")
    assert term.get_cell(0, 0)[0] == ord('A')
    term.feed(b"\x1b[?1049l")  # switch back
    assert term.get_cell(0, 0)[0] == ord('M')


@_named("ssh_mock_server_data_flow")
def test_ssh_data_flow():
    """Data flows correctly from mock SSH server to terminal."""
    if not HAS_NBS_SSH:
        import pytest
        pytest.skip("nbs-ssh not installed")
    asyncio.run(_ssh_data_flow_async())


async def _ssh_data_flow_async():
    config = MockServerConfig(username="test", password="test")

    async with MockSSHServer(config) as server:
        # Connect
        conn = SSHConnection(
            host="localhost",
            port=server.port,
            username="test",
            password="test",
            host_key_policy=HostKeyPolicy.ACCEPT_NEW,
        )
        async with conn:
            # Open shell with PTY
            process = await conn._conn.create_process(
                None,
                term_type="xterm-256color",
                term_size=(80, 24),
            )

            # Read the initial prompt
            received = b""
            for _ in range(20):  # poll up to 2 seconds
                try:
                    data = await asyncio.wait_for(
                        process.stdout.read(4096), timeout=0.1
                    )
                    if data:
                        if isinstance(data, str):
                            data = data.encode()
                        received += data
                        if b"$" in received:
                            break
                except asyncio.TimeoutError:
                    continue

            assert len(received) > 0, "No data received from mock server"

            # Feed into terminal
            term = _nbsterm.Terminal(24, 80)
            term.feed(received)

            # Verify something is on screen
            row, col = term.get_cursor()
            assert col > 0, f"Expected cursor to advance, got col={col}"

            # Send a command
            process.stdin.write("echo hello\n")

            # Read response
            response = b""
            for _ in range(20):
                try:
                    data = await asyncio.wait_for(
                        process.stdout.read(4096), timeout=0.1
                    )
                    if data:
                        if isinstance(data, str):
                            data = data.encode()
                        response += data
                except asyncio.TimeoutError:
                    continue

            # Feed response
            if response:
                term.feed(response)

            process.stdin.write_eof()


@_named("cross_thread_data_delivery")
def test_cross_thread_data_delivery():
    """Data produced on a background thread can feed the terminal on the main thread."""
    # Simulates the threading pattern without needing SSH:
    # Background thread produces bytes, main thread feeds them to terminal
    term = _nbsterm.Terminal(24, 80)
    received = []
    event = threading.Event()

    def background_producer():
        # Simulate SSH data arriving on background thread
        data = b"\x1b[31mHello from background\x1b[0m\r\n"
        received.append(data)
        event.set()

    thread = threading.Thread(target=background_producer, daemon=True)
    thread.start()
    event.wait(timeout=2.0)
    thread.join(timeout=2.0)

    assert len(received) > 0, "No data from background thread"

    # Feed on main thread (the invariant: C extension only called from main thread)
    for chunk in received:
        term.feed(chunk)

    # Verify screen state
    screen = term.get_screen()
    assert len(screen[0]) >= 1
    assert "Hello" in screen[0][0][0], f"Expected 'Hello' in output, got {screen[0][0][0]!r}"


# --- Main ---

def main():
    print("Orchestration Integration Tests:")
    print()

    # Synchronous tests
    run_test(test_terminal_creation)
    run_test(test_terminal_feed_escapes)
    run_test(test_key_encoding)
    run_test(test_scrollback)
    run_test(test_resize)
    run_test(test_dec_charset)
    run_test(test_alt_screen)

    # Async tests (SSH) — skip if nbs-ssh not available
    if HAS_NBS_SSH:
        run_async_test(test_ssh_data_flow)
    else:
        print(f"  {'ssh_mock_server_data_flow':50s} SKIP (nbs-ssh not installed)")
    run_test(test_cross_thread_data_delivery)

    print()
    print(f"  Pass: {tests_passed} | Fail: {tests_failed} | Total: {tests_run}")
    print(f"  Gate: {'OPEN' if tests_failed == 0 else 'BLOCKED'}")

    return 0 if tests_failed == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
