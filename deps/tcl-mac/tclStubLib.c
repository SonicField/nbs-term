/*
 * Minimal Tcl stubs bootstrap for macOS.
 *
 * Same approach as the Windows version (deps/tcl-win/tclStubLib.c) but
 * uses dlsym(RTLD_DEFAULT) instead of GetProcAddress. At runtime,
 * libtcl9.0.dylib (or libtcl8.6.dylib) is already loaded by Python's
 * _tkinter module. We use dlsym to find Tcl_PkgRequireEx and bootstrap
 * the stubs table.
 *
 * This avoids linking ANY Tcl library at build time — no libtclstub.a,
 * no -framework Tcl, no version detection. The only build-time
 * requirement is tcl.h (for type definitions).
 */

#include <dlfcn.h>

/* Must NOT define USE_TCL_STUBS here — we resolve Tcl_PkgRequireEx
 * via dlsym, not through the stubs table. */
#include <tcl.h>

/* The global stubs table pointer */
const TclStubs *tclStubsPtr = NULL;

#undef Tcl_InitStubs
const char *
Tcl_InitStubs(Tcl_Interp *interp, const char *version, int exact)
{
    typedef const char *(*PkgRequireExProc)(Tcl_Interp *, const char *,
                                            const char *, int, void *);

    /* Find Tcl_PkgRequireEx in whatever Tcl _tkinter already loaded */
    PkgRequireExProc pkgRequireEx = (PkgRequireExProc)dlsym(
        RTLD_DEFAULT, "Tcl_PkgRequireEx");
    if (!pkgRequireEx) {
        return NULL;
    }

    void *clientData = NULL;
    const char *actualVersion = pkgRequireEx(
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
