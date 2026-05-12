# deps/tcl/pkgs — Removed Packages (build-time trim)

The following packages from upstream Tcl 8.6.15 were removed from the
vendored source tree to cut Linux build wall-clock by ~46% (48.49s →
26.26s on devgpu, single-threaded). p3_pty.exe / build/p3_pty never
`package require` these; Tcl auto-detects subdirs of `pkgs/` at
configure time, so deletion = automatic skip during the inner Tcl
make.

| Package          | Size  | Why removed                                                   |
|------------------|-------|---------------------------------------------------------------|
| `itcl4.3.0`      | 3.9MB | [incr Tcl] OO extension; no `package require Itcl` in p3_pty  |
| `sqlite3.45.3`   | 11MB  | Tcl SQLite driver; no DB consumer in p3_pty                   |
| `tdbc1.1.9`      | 880K  | TDBC core; no DB consumer                                     |
| `tdbcmysql1.1.9` | 884K  | TDBC MySQL driver; no DB consumer                             |
| `tdbcodbc1.1.9`  | 1.1MB | TDBC ODBC driver; no DB consumer                              |
| `tdbcpostgres1.1.9` | 864K  | TDBC PostgreSQL driver; no DB consumer                     |
| `tdbcsqlite3-1.1.9` | 652K  | TDBC SQLite driver; no DB consumer                         |
| `thread2.8.10`   | 1.7MB | Tcl Thread *script* package; pty.phc uses Tcl core threads (`Tcl_AsyncMark`), which is independent — flag `--enable-threads` in Tcl `./configure` is what we need, not this package |

Total: ~21MB of C source no longer compiled or copied during install.
Lazy-load semantics mean even if a downstream consumer ever issued
`package require Itcl` it would now fail with a clean
`can't find package Itcl` rather than silently loading; consumers of
the pure-phc binary never request these packages.

## Restore one or all

```bash
# All packages in this manifest:
git checkout HEAD -- deps/tcl/pkgs

# Single package:
git checkout HEAD -- deps/tcl/pkgs/sqlite3.45.3
```

(Both restore from the most recent commit that still carried the
package; if a Tcl version bump landed since the trim, restore from
that bump's parent commit instead.)

## On the next Tcl version bump

When `deps/tcl` is replaced with a newer upstream tarball, the new
tree will reintroduce these subdirs. Re-apply the same removals
post-bump (or fold the rm into the bump commit) to keep the
build-time savings.

Decision trail: theologian build-time analysis (D-1778594407 +
re-analysis after alexie 2026-05-12 13:57:36 'buildtime not runtime'
clarification); supervisor commit-rm mechanism choice
(D-1778595053).
