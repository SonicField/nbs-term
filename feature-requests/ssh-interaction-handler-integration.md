# Feature Request: SSHInteractionHandler Proper Integration

## Current State (Workaround)

nbs-term currently replicates the CLI's cert-backed agent key discovery
in `nbsterm.py:_ssh_session()`. This duplicates logic from nbs-ssh's
`__main__.py` lines 958-988 and uses three private APIs:

1. `conn._conn.create_process()` — PTY access through private attribute
2. `from nbs_ssh.auth import get_agent_cert_key_pair` — internal module import
3. `cert_auth._agent_key_pair = key_pair` — setting private attribute on AuthConfig

This works but creates fragile coupling that breaks on nbs-ssh internal changes.

## Proper Fix: Two Changes to nbs-ssh

### 1. Move cert/identity discovery into `_build_auth_configs()`

`SSHConnection._build_auth_configs()` should read `IdentityFile` and
`IdentityAgent` from SSH host config during auto-discovery, just as the
CLI does. When a cert identity file is found (ending in `-cert.pub`),
load the agent-backed key pair and include it in the auth chain.

This requires making `_build_auth_configs()` async (cert loading needs
agent communication) or deferring cert discovery to `_connect()`.

**After this change:** nbs-term removes all cert discovery code — 
`SSHConnection(host, interaction_handler=handler)` handles everything.

### 2. Add public `create_process()` method to SSHConnection

```python
async def create_process(self, command=None, *, term_type=None, term_size=None):
    """Create a remote process with optional PTY.

    Args:
        command: Command to run (None for shell).
        term_type: Terminal type (e.g. 'xterm-256color').
        term_size: Terminal size as (cols, rows) tuple.

    Returns:
        asyncssh.SSHClientProcess with stdin/stdout access.
    """
    return await self._conn.create_process(
        command, term_type=term_type, term_size=term_size,
    )
```

One method. Removes the `conn._conn` private attribute access from all
consumers.

## After Both Changes

nbs-term simplifies to:

```python
conn = SSHConnection(host, interaction_handler=TkInteractionHandler(root))
async with conn:
    process = await conn.create_process(
        term_type="xterm-256color", term_size=(cols, rows),
    )
    # ... read/write loop ...
```

No private API access. No duplicated auth logic. No internal imports.

## CLI Migration (Step 3 — Deferred)

The CLI (`__main__.py`) should also switch to `SSHInteractionHandler` with
a `TerminalInteractionHandler` subclass. This is more complex due to
batch_mode, IdentitiesOnly, explicit auth flags, and lazy password
prompting. Separate PR.

## Test Plan

1. Existing nbs-ssh tests must pass (no regressions)
2. Add test: `_build_auth_configs()` discovers cert identities from SSH config
3. Add test: `create_process()` delegates to `_conn.create_process()`
4. nbs-term integration: verify Duo auth still works after removing workaround
