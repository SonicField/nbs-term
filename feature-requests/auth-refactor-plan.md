# Auth Refactor: Move Cert Discovery into nbs-ssh

## Problem

nbs-term manually builds the SSH auth chain in `nbsterm.py:548-579`, duplicating logic from nbs-ssh's CLI (`__main__.py:958-988`). This creates three private API couplings:

1. `conn._conn.create_process()` — reaches into SSHConnection internals for PTY access
2. `from nbs_ssh.auth import get_agent_cert_key_pair` — imports non-public function
3. `cert_auth._agent_key_pair = key_pair` — sets private attribute on AuthConfig

When nbs-ssh changes internally, nbs-term breaks silently at runtime.

## Goal

After this refactor, nbs-term's `_ssh_session()` becomes:

```python
conn = SSHConnection(
    host,
    interaction_handler=TkInteractionHandler(root),
)
async with conn:
    process = await conn.create_process(
        term_type="xterm-256color", term_size=(cols, rows),
    )
```

No manual auth chain. No private imports. No `_conn` access.

## Stepwise Plan

Each step is independently shippable. Tests pass after every step. No step depends on a later step.

### Step 1: Public `create_process()` on SSHConnection

**What:** Add a public method that delegates to `self._conn.create_process()`.

```python
async def create_process(self, command=None, *, term_type=None, term_size=None):
    """Create a remote process with optional PTY."""
    return await self._conn.create_process(
        command, term_type=term_type, term_size=term_size,
    )
```

**Why first:** Smallest change, zero risk. nbs-term switches from `conn._conn.create_process()` to `conn.create_process()`. Eliminates coupling #1.

**Tests:**
- test_create_process_delegates — mock `_conn`, verify delegation
- test_create_process_passes_term_type — verify kwargs forwarded
- test_create_process_raises_before_connect — call before `async with`, expect error

**Migrate nbs-term:** Change one line: `conn._conn.create_process(...)` → `conn.create_process(...)`. Remove the `_conn` access.

### Step 2: Cert identity discovery in `_build_auth_configs()`

**What:** Move cert identity loading from nbs-term into `_build_auth_configs()`. When `self._host_config` has `identity_file` entries ending in `-cert.pub` and an `identity_agent`, load the agent-backed key pair and include it in the auth chain.

**Challenge:** `get_agent_cert_key_pair()` is async (needs agent communication). `_build_auth_configs()` is sync. Two options:

- **Option A:** Make `_build_auth_configs()` async. Cleanest, but changes the internal API.
- **Option B:** Defer cert discovery to `_connect()` (already async), calling `_build_auth_configs()` for the non-async portion and appending cert configs afterward.

**Recommendation:** Option B. Keep `_build_auth_configs()` sync. Add an `async _discover_cert_identities()` method called from `_connect()` that appends cert auth configs to `self._auth_configs` before the auth loop starts.

**Tests:**
- test_discover_cert_no_config — no identity_file in config → no cert auth added
- test_discover_cert_with_config — identity_file with -cert.pub → cert auth appended
- test_discover_cert_agent_missing — identity_agent not set → skip cert, log warning
- test_discover_cert_key_not_found — agent has no matching key → skip cert, log warning
- test_cert_before_kbdint — cert auth appears before kbdint in the chain

**Migrate nbs-term:** Remove lines 552-574 (`ssh_config.lookup`, cert_files loop, `get_agent_cert_key_pair` call). Remove lines 577-579 (manual kbdint append). Remove the `auth=auth` kwarg from `conn_kwargs`. The interaction_handler triggers auto-discovery with kbdint. Cert discovery happens inside SSHConnection.

### Step 3: Export `get_agent_cert_key_pair` as public API

**What:** Add `get_agent_cert_key_pair` to nbs-ssh's `__init__.py` exports. Or, if Step 2 fully internalises cert loading, this step is unnecessary.

**Decision point:** If Step 2 fully moves cert discovery into SSHConnection, this step is skipped. If some consumers need to build custom auth chains with cert keys, export the function.

**Recommendation:** Skip this step if Step 2 succeeds. The function is an implementation detail of cert discovery, not a consumer-facing API.

### Step 4: CLI migration (deferred from prior session)

**What:** Update nbs-ssh's CLI (`__main__.py`) to use `SSHInteractionHandler` with a `TerminalInteractionHandler` subclass, eliminating the manual auth chain construction at lines 1046-1079.

**Challenge:** The CLI has batch_mode, IdentitiesOnly, explicit auth flags, and lazy password — patterns not represented in the current 3-method handler interface. May require extending the interface.

**Approach:** 
1. Add `on_password_needed()` to the handler (already designed, not yet used)
2. Add a `batch_mode` flag to SSHConnection that disables interactive prompts
3. Migrate the CLI's auth chain to use auto-discovery + handler
4. Verify all existing CLI tests pass

**Tests:** All existing nbs-ssh CLI tests must pass. Add:
- test_cli_batch_mode_no_prompts — batch mode skips kbdint and password prompts
- test_cli_explicit_auth_overrides — -i flag overrides auto-discovery
- test_cli_handler_kbdint — interactive CLI gets Duo prompt through handler

### Step 5: Remove manual auth chain from nbs-term

**What:** Final cleanup. nbs-term's `_ssh_session()` reduces to:

```python
conn = SSHConnection(
    host,
    interaction_handler=self._interaction_handler,
    **({"port": self.port} if self.port else {}),
    **({"username": self.username} if self.username else {}),
)
async with conn:
    process = await conn.create_process(
        term_type="xterm-256color", term_size=(cols, rows),
    )
```

**Prerequisite:** Steps 1 + 2 complete and shipped.

**Tests:** nbs-term's existing 277 tests pass. Manual test: Duo auth on alexie's Mac.

## Risk Assessment

| Risk | Mitigation |
|------|-----------|
| Async cert loading breaks `_build_auth_configs()` | Option B: separate async method in `_connect()` |
| CLI migration reveals handler interface gaps | Step 4 is deferred and can extend the interface |
| Cert loading regresses on alexie's Mac | Each step is independently testable; manual Duo test after Step 2 |
| nbs-ssh version drift breaks nbs-term | Pin nbs-ssh to specific commits; update pin after each step |

## What Would Falsify This Plan

1. If `_connect()` cannot append to `self._auth_configs` between `_build_auth_configs()` and the auth loop — the cert discovery must happen inside `_build_auth_configs()` (forcing Option A).
2. If the CLI requires handler interface changes that break nbs-term's TkInteractionHandler — Steps 4 and 5 conflict.
3. If `create_process()` needs additional parameters beyond term_type/term_size for real-world use — the public API must be designed more carefully.
