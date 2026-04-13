/*
 * Minimal Tcl stubs bootstrap for macOS.
 *
 * Calls Tcl_PkgRequireEx directly (resolved from linked libtcl).
 * Sets up tclStubsPtr so stubs macros (including TclFreeObj via
 * Tcl_DecrRefCount) work correctly.
 *
 * Must NOT define USE_TCL_STUBS — we call Tcl_PkgRequireEx as a
 * direct function, not through tclStubsPtr.
 */

#include <tcl.h>

/* The global stubs table pointer — const to match Tcl 9 headers */
const TclStubs *tclStubsPtr = NULL;

/*
 * Our Tcl_InitStubs: calls Tcl_PkgRequireEx (resolved from linked
 * libtcl) to bootstrap the stubs table. The #undef removes the
 * Tcl_PkgInitStubsCheck macro redirect from tcl.h.
 */
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

    const TclStubs *stubsPtr = (const TclStubs *)clientData;
    if (stubsPtr->magic != TCL_STUB_MAGIC) {
        return NULL;
    }

    tclStubsPtr = stubsPtr;
    return actualVersion;
}
