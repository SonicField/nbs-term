/*
 * Minimal Tcl stubs bootstrap for macOS.
 *
 * Calls Tcl_PkgRequireEx directly (resolved from linked libtcl).
 * Sets up tclStubsPtr so stubs macros (including TclFreeObj via
 * Tcl_DecrRefCount) work correctly.
 *
 * This is the same pattern as Tcl's own tclStubLib.c but simplified
 * for our use case.
 */

/* Must NOT define USE_TCL_STUBS here — we call Tcl_PkgRequireEx as a
 * direct function (resolved from linked libtcl), not through tclStubsPtr. */
#include <tcl.h>

/* The global stubs table pointer (non-const for Tcl 8/9 compat) */
TclStubs *tclStubsPtr = NULL;

#undef Tcl_InitStubs
const char *
Tcl_InitStubs(Tcl_Interp *interp, const char *version, int exact)
{
    void *clientData = NULL;
    const char *actualVersion = Tcl_PkgRequireEx(
        interp, "Tcl", version, exact, &clientData);
    if (actualVersion == NULL || clientData == NULL) {
        return NULL;
    }

    TclStubs *stubsPtr = (TclStubs *)clientData;
    if (stubsPtr->magic != TCL_STUB_MAGIC) {
        return NULL;
    }

    tclStubsPtr = stubsPtr;
    return actualVersion;
}
