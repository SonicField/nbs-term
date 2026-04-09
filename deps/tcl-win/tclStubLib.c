/*
 * Minimal Tcl stubs bootstrap for Windows.
 *
 * Provides Tcl_InitStubs() without requiring tclInt.h (internal header)
 * or a Tcl import library (.lib). At runtime, tcl86t.dll is already
 * loaded by Python's _tkinter module. We use GetProcAddress to find
 * Tcl_PkgRequireEx and bootstrap the stubs table.
 *
 * The official tclStubLib.c (Tcl 8.6) uses the internal Interp struct
 * to read the stubs table directly. We can't do that without tclInt.h,
 * so instead we use Tcl_PkgRequireEx (resolved via GetProcAddress) which
 * returns the stubs table through its clientData output parameter.
 *
 * Tcl license (BSD-like) applies to the stubs mechanism design.
 */

#include <windows.h>

/* Must NOT define USE_TCL_STUBS — we call Tcl_PkgRequireEx directly
 * via GetProcAddress, not through the stubs table (which doesn't
 * exist yet — that's what we're bootstrapping).
 */
#include "include/tcl.h"

/* The global stubs table pointer (non-const to match both Tcl 8 and 9 headers) */
TclStubs *tclStubsPtr = NULL;

/*
 * Tcl_InitStubs -- Initialize the stubs table from an interpreter.
 *
 * Finds Tcl_PkgRequireEx in the already-loaded Tcl DLL via
 * GetProcAddress (no import library needed), then uses it to
 * get the stubs table pointer from the interpreter.
 */
#undef Tcl_InitStubs
const char *
Tcl_InitStubs(Tcl_Interp *interp, const char *version, int exact)
{
    typedef const char *(*PkgRequireExProc)(Tcl_Interp *, const char *,
                                            const char *, int, void *);
    PkgRequireExProc pkgRequireEx;
    HMODULE hTcl;
    const char *actualVersion;
    void *clientData = NULL;
    TclStubs *stubsPtr;

    /* tcl86t.dll is already loaded by _tkinter */
    hTcl = GetModuleHandleA("tcl86t.dll");
    if (!hTcl) {
        /* Try Tcl 9.0 */
        hTcl = GetModuleHandleA("tcl90.dll");
    }
    if (!hTcl) {
        return NULL;
    }

    pkgRequireEx = (PkgRequireExProc)GetProcAddress(hTcl, "Tcl_PkgRequireEx");
    if (!pkgRequireEx) {
        return NULL;
    }

    actualVersion = pkgRequireEx(interp, "Tcl", version, exact, &clientData);
    if (actualVersion == NULL || clientData == NULL) {
        return NULL;
    }

    stubsPtr = (TclStubs *)clientData;
    if (stubsPtr->magic != TCL_STUB_MAGIC) {
        return NULL;
    }

    tclStubsPtr = stubsPtr;
    return actualVersion;
}
