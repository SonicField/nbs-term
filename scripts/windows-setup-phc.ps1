# nbs-term Windows pure-phc Setup Script
#
# Builds the standalone phc binary (build/p3_pty.exe) on Windows. No Python
# at runtime; links Tcl/Tk + ConPTY (Win10 1809+).
#
# Self-contained: only assumes host C toolchain bootstrap (vs_BuildTools, admin
# elevation if absent) and Git. Tcl/Tk is built from vendored source under
# deps/tcl/ + deps/tk/ (8.6.15, BSD-licensed; pinned in repo per alexie
# 2026-05-05 D-1777978221, D-1777978497). No system Tcl/Tk dependency.
#
# Prerequisites:
#   - MSVC Build Tools (cl.exe, nmake.exe)  -- auto-installed if missing (admin)
#   - Git                                    -- assumed; nbs-term cloned via it
#
# Run from PowerShell:
#     .\scripts\windows-setup-phc.ps1
#
# Per supervisor 2026-05-01 12:47:39 (P4.5 GO; pure-phc binary on Windows so
# alexie can smoke 840b441 ConPTY path). Companion to scripts/windows-setup
# .ps1 (which builds the legacy Python C extension; both can coexist on the
# same machine).

$ErrorActionPreference = "Stop"

$RepoDir = if ($PSScriptRoot) { Split-Path -Parent $PSScriptRoot } else { (Get-Location).Path }
$BuildDir = Join-Path $RepoDir "build"
$SrcDir = Join-Path $RepoDir "src"
$DepsDir = Join-Path $RepoDir "deps"
$PhcDir = Join-Path $DepsDir "phc"
$PhcBuildDir = Join-Path $PhcDir "build"
$PhcExe = Join-Path $PhcBuildDir "phc.exe"
$TclSrcDir = Join-Path $DepsDir "tcl"
$TkSrcDir = Join-Path $DepsDir "tk"
$TclBuildDir = Join-Path $DepsDir "tcl-build"
$TclInclude = Join-Path $TclBuildDir "include"
$TclLib = Join-Path $TclBuildDir "lib"
$TclBin = Join-Path $TclBuildDir "bin"

Write-Host "=== nbs-term Windows pure-phc Setup ===" -ForegroundColor Cyan
Write-Host "Repo: $RepoDir"

# ---- Step 0: ensure MSVC Build Tools (mirrors scripts/windows-setup.ps1 pattern) ----
$VsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$VsPath = $null
if (Test-Path $VsWhere) {
    $VsPath = & $VsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2>$null
}
if (-not $VsPath) {
    Write-Host "MSVC Build Tools not found." -ForegroundColor Yellow
    $response = Read-Host "Install Visual Studio Build Tools? [Y]/n"
    if ($response -eq '' -or $response -eq 'Y' -or $response -eq 'y') {
        $isAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
        if (-not $isAdmin) {
            Write-Host "ERROR: Build Tools install requires admin rights." -ForegroundColor Red
            Write-Host "Re-run this script from an elevated PowerShell (Run as Administrator)." -ForegroundColor Yellow
            exit 1
        }
        $vsUrl = "https://aka.ms/vs/17/release/vs_BuildTools.exe"
        $vsInstaller = "$env:TEMP\vs_BuildTools.exe"
        Write-Host "Downloading Visual Studio Build Tools..." -ForegroundColor Yellow
        Invoke-WebRequest -Uri $vsUrl -OutFile $vsInstaller
        Write-Host "Installing Build Tools (this may take several minutes)..." -ForegroundColor Yellow
        Start-Process -Wait -FilePath $vsInstaller -ArgumentList @(
            "--quiet", "--wait", "--norestart",
            "--add", "Microsoft.VisualStudio.Workload.VCTools",
            "--includeRecommended"
        )
        Remove-Item $vsInstaller -ErrorAction SilentlyContinue
        Write-Host "Build Tools installed." -ForegroundColor Green
        if (Test-Path $VsWhere) {
            $VsPath = & $VsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2>$null
        }
    } else {
        Write-Host "ERROR: C compiler required. Install from: https://visualstudio.microsoft.com/visual-cpp-build-tools/" -ForegroundColor Red
        exit 1
    }
}
if (-not $VsPath) {
    Write-Host "ERROR: VC tools not detected after install attempt." -ForegroundColor Red
    exit 1
}
Write-Host "MSVC found at $VsPath" -ForegroundColor Green

# Import MSVC environment so cl.exe / link.exe / nmake.exe land on PATH for this session.
$VcVarsBat = Join-Path $VsPath "VC\Auxiliary\Build\vcvars64.bat"
if (-not (Test-Path $VcVarsBat)) {
    Write-Host "ERROR: vcvars64.bat not found at $VcVarsBat." -ForegroundColor Red
    exit 1
}
Write-Host "Importing MSVC environment..." -ForegroundColor Yellow
$EnvDump = & cmd /c "`"$VcVarsBat`" >nul 2>&1 && set"
foreach ($line in $EnvDump) {
    if ($line -match "^([^=]+)=(.*)$") {
        Set-Item -Path "Env:$($matches[1])" -Value $matches[2]
    }
}
& cl.exe /? 2>&1 | Select-Object -First 1

# ---- Step 1: build vendored Tcl/Tk from deps/{tcl,tk}/ ----
# Pinned at 8.6.15 (per deps/tcl/README.md, deps/tk/README.md; verifiable via
# upstream sourceforge.net SHA256 in commit e05c00c message).
if (-not (Test-Path $TclSrcDir) -or -not (Test-Path (Join-Path $TclSrcDir "win\makefile.vc"))) {
    Write-Host "ERROR: vendored Tcl source missing at $TclSrcDir." -ForegroundColor Red
    Write-Host "Re-clone the repo or run: git checkout deps/tcl deps/tk" -ForegroundColor Yellow
    exit 1
}
if (-not (Test-Path $TkSrcDir) -or -not (Test-Path (Join-Path $TkSrcDir "win\makefile.vc"))) {
    Write-Host "ERROR: vendored Tk source missing at $TkSrcDir." -ForegroundColor Red
    exit 1
}

$TclBuildMarker = Join-Path $TclLib "tcl86.lib"
if (-not (Test-Path $TclBuildMarker)) {
    Write-Host "Building vendored Tcl 8.6.15 -> $TclBuildDir ..." -ForegroundColor Yellow
    Push-Location (Join-Path $TclSrcDir "win")
    try {
        & nmake.exe -nologo -f makefile.vc release
        if ($LASTEXITCODE -ne 0) {
            Write-Host "ERROR: Tcl release build failed (nmake exit $LASTEXITCODE)" -ForegroundColor Red
            exit 1
        }
        & nmake.exe -nologo -f makefile.vc install "INSTALLDIR=$TclBuildDir"
        if ($LASTEXITCODE -ne 0) {
            Write-Host "ERROR: Tcl install failed (nmake exit $LASTEXITCODE)" -ForegroundColor Red
            exit 1
        }
    } finally {
        Pop-Location
    }
    Write-Host "Built Tcl 8.6.15 -> $TclBuildDir" -ForegroundColor Green
} else {
    Write-Host "Vendored Tcl 8.6.15 already built (delete deps/tcl-build to force rebuild)" -ForegroundColor Yellow
}

$TkBuildMarker = Join-Path $TclLib "tk86.lib"
if (-not (Test-Path $TkBuildMarker)) {
    Write-Host "Building vendored Tk 8.6.15 -> $TclBuildDir ..." -ForegroundColor Yellow
    Push-Location (Join-Path $TkSrcDir "win")
    try {
        & nmake.exe -nologo -f makefile.vc release "TCLDIR=$TclSrcDir"
        if ($LASTEXITCODE -ne 0) {
            Write-Host "ERROR: Tk release build failed (nmake exit $LASTEXITCODE)" -ForegroundColor Red
            exit 1
        }
        & nmake.exe -nologo -f makefile.vc install "INSTALLDIR=$TclBuildDir" "TCLDIR=$TclSrcDir"
        if ($LASTEXITCODE -ne 0) {
            Write-Host "ERROR: Tk install failed (nmake exit $LASTEXITCODE)" -ForegroundColor Red
            exit 1
        }
    } finally {
        Pop-Location
    }
    Write-Host "Built Tk 8.6.15 -> $TclBuildDir" -ForegroundColor Green
} else {
    Write-Host "Vendored Tk 8.6.15 already built" -ForegroundColor Yellow
}

# Locate the import libraries (tcl86.lib + tk86.lib) for linking.
$TclImport = Get-ChildItem -Path $TclLib -Filter "tcl*.lib" -ErrorAction SilentlyContinue |
    Where-Object { $_.Name -notmatch "stub" } | Select-Object -First 1
$TkImport = Get-ChildItem -Path $TclLib -Filter "tk*.lib" -ErrorAction SilentlyContinue |
    Where-Object { $_.Name -notmatch "stub" } | Select-Object -First 1
if (-not $TclImport -or -not $TkImport) {
    Write-Host "ERROR: tcl*.lib / tk*.lib not found under $TclLib after build." -ForegroundColor Red
    exit 1
}
Write-Host "Vendored Tcl/Tk ready at $TclBuildDir ($($TclImport.Name) + $($TkImport.Name))" -ForegroundColor Green

# ---- Step 2: build phc.exe ----
# phc lives at deps/phc as a git submodule. A `git clone --single-branch` does
# NOT init submodules, so deps/phc/src is empty until init. Idempotent re-run.
#
# Recovery: a prior failed run may have left deps/phc as a non-empty dir
# (e.g. with deps/phc/build/ created by an earlier script invocation that
# bombed before submodule init). git submodule update refuses to clone into
# a non-empty path. Deinit + rm + init is the canonical recovery (per
# supervisor 2026-05-05 12:15:05).
if (-not (Test-Path (Join-Path $PhcDir "src"))) {
    Push-Location $RepoDir
    try {
        if ((Test-Path $PhcDir) -and (Get-ChildItem -Path $PhcDir -Force -ErrorAction SilentlyContinue)) {
            Write-Host "Cleaning stale deps/phc before submodule init..." -ForegroundColor Yellow
            & git submodule deinit -f deps/phc 2>$null
            Remove-Item -Recurse -Force $PhcDir
        }
        Write-Host "Initializing phc submodule (deps/phc)..." -ForegroundColor Yellow
        & git submodule update --init deps/phc
        if ($LASTEXITCODE -ne 0) {
            Write-Host "ERROR: git submodule init failed for deps/phc." -ForegroundColor Red
            exit 1
        }
    } finally {
        Pop-Location
    }
}
if (-not (Test-Path $PhcBuildDir)) { New-Item -ItemType Directory -Path $PhcBuildDir | Out-Null }
if (-not (Test-Path $PhcExe)) {
    Write-Host "Building phc compiler from source..." -ForegroundColor Yellow
    $PhcSrcs = Get-ChildItem -Path (Join-Path $PhcDir "src") -Filter "*.c"
    $PhcObjs = @()
    foreach ($s in $PhcSrcs) {
        $obj = Join-Path $PhcBuildDir ($s.BaseName + ".obj")
        & cl.exe /c /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /Fo"$obj" $s.FullName | Out-Null
        if ($LASTEXITCODE -ne 0) {
            Write-Host "ERROR: phc build failed at $($s.Name)" -ForegroundColor Red
            exit 1
        }
        $PhcObjs += $obj
    }
    & cl.exe /nologo /Fe"$PhcExe" @PhcObjs | Out-Null
    if ($LASTEXITCODE -ne 0 -or -not (Test-Path $PhcExe)) {
        Write-Host "ERROR: phc link failed" -ForegroundColor Red
        exit 1
    }
    Write-Host "Built $PhcExe" -ForegroundColor Green
} else {
    Write-Host "phc.exe already built (delete to force rebuild)" -ForegroundColor Yellow
}

# ---- Step 3: build build/p3_pty.exe ----
if (-not (Test-Path $BuildDir)) { New-Item -ItemType Directory -Path $BuildDir | Out-Null }
$PtyPhc = Join-Path $SrcDir "p3_pty.phc"
$PtyC = Join-Path $BuildDir "p3_pty.c"
$PtyExe = Join-Path $BuildDir "p3_pty.exe"

# Preprocess .phc -> .c via cl.exe /P (preprocess to file) then phc transform.
# cl.exe /P writes p3_pty.i; rename to .c so phc accepts it on stdin.
Write-Host "Preprocessing $PtyPhc -> $PtyC ..." -ForegroundColor Yellow
$Pp = Join-Path $BuildDir "p3_pty.i"
& cl.exe /nologo /EP /TC /I"$SrcDir" /I"$TclInclude" $PtyPhc 2>$null | Out-File -Encoding ASCII -FilePath $Pp
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: cl /EP failed on $PtyPhc" -ForegroundColor Red
    exit 1
}
# Pipe preprocessed source through phc.exe.
$PreText = Get-Content -Raw $Pp
$PreText | & $PhcExe | Out-File -Encoding ASCII -FilePath $PtyC
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: phc transform failed" -ForegroundColor Red
    exit 1
}
Write-Host "Compiling $PtyC -> $PtyExe ..." -ForegroundColor Yellow
# Define _CRT_SECURE_NO_WARNINGS to silence MSVC's strncpy/sprintf nags.
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /I"$TclInclude" /Fe"$PtyExe" $PtyC `
    /link $($TclImport.FullName) $($TkImport.FullName) kernel32.lib user32.lib shell32.lib advapi32.lib | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $PtyExe)) {
    Write-Host "ERROR: cl link failed for p3_pty.exe" -ForegroundColor Red
    exit 1
}
Write-Host "Built $PtyExe" -ForegroundColor Green

# ---- Step 3.5: build build/test_pty_burst.exe ----
# Programmatic byte-accounting test for pty.phc; isolates the PTY layer
# from Tk/render so a self-test failure can be diagnosed (PTY ring vs Tk
# render). Per testkeeper deferred spec D-1777640886.
$TestSrc = Join-Path (Join-Path $RepoDir "tests") "test_pty_burst.phc"
$TestC = Join-Path $BuildDir "test_pty_burst.c"
$TestExe = Join-Path $BuildDir "test_pty_burst.exe"

Write-Host "Preprocessing $TestSrc -> $TestC ..." -ForegroundColor Yellow
$TestPp = Join-Path $BuildDir "test_pty_burst.i"
& cl.exe /nologo /EP /TC /I"$SrcDir" /I"$TclInclude" $TestSrc 2>$null | Out-File -Encoding ASCII -FilePath $TestPp
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: cl /EP failed on $TestSrc" -ForegroundColor Red
    exit 1
}
$TestPreText = Get-Content -Raw $TestPp
$TestPreText | & $PhcExe | Out-File -Encoding ASCII -FilePath $TestC
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: phc transform failed on $TestSrc" -ForegroundColor Red
    exit 1
}
Write-Host "Compiling $TestC -> $TestExe ..." -ForegroundColor Yellow
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /I"$TclInclude" /Fe"$TestExe" $TestC `
    /link $($TclImport.FullName) $($TkImport.FullName) kernel32.lib user32.lib shell32.lib advapi32.lib | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $TestExe)) {
    Write-Host "ERROR: cl link failed for test_pty_burst.exe" -ForegroundColor Red
    exit 1
}
Write-Host "Built $TestExe" -ForegroundColor Green

# ---- Step 3.6: build build/test_pixel_to_cell.exe (F1 anchor, libc-only) ----
# Pure-spec discriminator for F1 e0665eb selection arithmetic per pythia
# #76 + supervisor 17:48:58. No Tcl/Tk link.
$ShimSrc1  = Join-Path (Join-Path $RepoDir "tests") "test_pixel_to_cell.phc"
$ShimC1    = Join-Path $BuildDir "test_pixel_to_cell.c"
$ShimExe1  = Join-Path $BuildDir "test_pixel_to_cell.exe"
$ShimPp1   = Join-Path $BuildDir "test_pixel_to_cell.i"
Write-Host "Preprocessing $ShimSrc1 -> $ShimC1 ..." -ForegroundColor Yellow
& cl.exe /nologo /EP /TC /I"$SrcDir" $ShimSrc1 2>$null | Out-File -Encoding ASCII -FilePath $ShimPp1
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: cl /EP failed on $ShimSrc1" -ForegroundColor Red; exit 1 }
Get-Content -Raw $ShimPp1 | & $PhcExe | Out-File -Encoding ASCII -FilePath $ShimC1
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: phc transform failed on $ShimSrc1" -ForegroundColor Red; exit 1 }
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /Fe"$ShimExe1" $ShimC1 | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $ShimExe1)) { Write-Host "ERROR: cl link failed for test_pixel_to_cell.exe" -ForegroundColor Red; exit 1 }
Write-Host "Built $ShimExe1" -ForegroundColor Green

# ---- Step 3.7: build build/test_extract_utf8.exe (F2 anchor, libc-only) ----
# Pure-spec discriminator for F2 f391992 byte-extract per pythia #77 +
# supervisor 18:26:48. No Tcl/Tk link.
$ShimSrc2  = Join-Path (Join-Path $RepoDir "tests") "test_extract_utf8.phc"
$ShimC2    = Join-Path $BuildDir "test_extract_utf8.c"
$ShimExe2  = Join-Path $BuildDir "test_extract_utf8.exe"
$ShimPp2   = Join-Path $BuildDir "test_extract_utf8.i"
Write-Host "Preprocessing $ShimSrc2 -> $ShimC2 ..." -ForegroundColor Yellow
& cl.exe /nologo /EP /TC /I"$SrcDir" $ShimSrc2 2>$null | Out-File -Encoding ASCII -FilePath $ShimPp2
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: cl /EP failed on $ShimSrc2" -ForegroundColor Red; exit 1 }
Get-Content -Raw $ShimPp2 | & $PhcExe | Out-File -Encoding ASCII -FilePath $ShimC2
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: phc transform failed on $ShimSrc2" -ForegroundColor Red; exit 1 }
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /Fe"$ShimExe2" $ShimC2 | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $ShimExe2)) { Write-Host "ERROR: cl link failed for test_extract_utf8.exe" -ForegroundColor Red; exit 1 }
Write-Host "Built $ShimExe2" -ForegroundColor Green

# ---- Step 3.8: build build/test_render_gamma.exe (T1 H gamma anchor, libc + math) ----
# Discriminator for H gamma transform (commit 17fe5dc) per testkeeper
# coverage 09:41:25 + alexie 09:46:53 automated-suite directive. Math in
# MSVC CRT (no separate libm needed on Win).
$T1Src  = Join-Path (Join-Path $RepoDir "tests") "test_render_gamma.phc"
$T1C    = Join-Path $BuildDir "test_render_gamma.c"
$T1Exe  = Join-Path $BuildDir "test_render_gamma.exe"
$T1Pp   = Join-Path $BuildDir "test_render_gamma.i"
Write-Host "Preprocessing $T1Src -> $T1C ..." -ForegroundColor Yellow
& cl.exe /nologo /EP /TC /I"$SrcDir" $T1Src 2>$null | Out-File -Encoding ASCII -FilePath $T1Pp
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: cl /EP failed on $T1Src" -ForegroundColor Red; exit 1 }
Get-Content -Raw $T1Pp | & $PhcExe | Out-File -Encoding ASCII -FilePath $T1C
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: phc transform failed on $T1Src" -ForegroundColor Red; exit 1 }
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /Fe"$T1Exe" $T1C | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $T1Exe)) { Write-Host "ERROR: cl link failed for test_render_gamma.exe" -ForegroundColor Red; exit 1 }
Write-Host "Built $T1Exe" -ForegroundColor Green

# ---- Step 3.9: build build/test_input_keys.exe (T2 D anchor, libc-only) ----
# Discriminator for D port (commit a592576) per testkeeper coverage
# 09:41:25. Direct-include of input.phc; transitive sgr/screen defs via
# cl /EP. No Tcl/Tk link.
$T2Src  = Join-Path (Join-Path $RepoDir "tests") "test_input_keys.phc"
$T2C    = Join-Path $BuildDir "test_input_keys.c"
$T2Exe  = Join-Path $BuildDir "test_input_keys.exe"
$T2Pp   = Join-Path $BuildDir "test_input_keys.i"
Write-Host "Preprocessing $T2Src -> $T2C ..." -ForegroundColor Yellow
& cl.exe /nologo /EP /TC /I"$SrcDir" $T2Src 2>$null | Out-File -Encoding ASCII -FilePath $T2Pp
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: cl /EP failed on $T2Src" -ForegroundColor Red; exit 1 }
Get-Content -Raw $T2Pp | & $PhcExe | Out-File -Encoding ASCII -FilePath $T2C
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: phc transform failed on $T2Src" -ForegroundColor Red; exit 1 }
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /Fe"$T2Exe" $T2C | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $T2Exe)) { Write-Host "ERROR: cl link failed for test_input_keys.exe" -ForegroundColor Red; exit 1 }
Write-Host "Built $T2Exe" -ForegroundColor Green

# ---- Step 3.10: build build/test_compute_layout.exe (T3 A2 anchor, libc-only) ----
# Discriminator for A2 port (commit b37fcd1) per testkeeper coverage
# 09:41:25. SPEC COPY of p3_pty.phc:466-477 + 506-510. No Tcl/Tk link.
$T3Src  = Join-Path (Join-Path $RepoDir "tests") "test_compute_layout.phc"
$T3C    = Join-Path $BuildDir "test_compute_layout.c"
$T3Exe  = Join-Path $BuildDir "test_compute_layout.exe"
$T3Pp   = Join-Path $BuildDir "test_compute_layout.i"
Write-Host "Preprocessing $T3Src -> $T3C ..." -ForegroundColor Yellow
& cl.exe /nologo /EP /TC /I"$SrcDir" $T3Src 2>$null | Out-File -Encoding ASCII -FilePath $T3Pp
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: cl /EP failed on $T3Src" -ForegroundColor Red; exit 1 }
Get-Content -Raw $T3Pp | & $PhcExe | Out-File -Encoding ASCII -FilePath $T3C
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: phc transform failed on $T3Src" -ForegroundColor Red; exit 1 }
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /Fe"$T3Exe" $T3C | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $T3Exe)) { Write-Host "ERROR: cl link failed for test_compute_layout.exe" -ForegroundColor Red; exit 1 }
Write-Host "Built $T3Exe" -ForegroundColor Green

# ---- Step 3.11: build build/test_pty_resize.exe (T4 J-resize anchor, libc-only) ----
# Discriminator for pty_resize POSIX (pty.phc:255-261) per testkeeper
# coverage 09:41:25. On Win the source compiles to a SKIP banner main()
# under #if defined(_WIN32) (ConPTY ResizePseudoConsole needs spawned-child
# harness, out of unit-test scope).
$T4Src  = Join-Path (Join-Path $RepoDir "tests") "test_pty_resize.phc"
$T4C    = Join-Path $BuildDir "test_pty_resize.c"
$T4Exe  = Join-Path $BuildDir "test_pty_resize.exe"
$T4Pp   = Join-Path $BuildDir "test_pty_resize.i"
Write-Host "Preprocessing $T4Src -> $T4C ..." -ForegroundColor Yellow
& cl.exe /nologo /EP /TC /I"$SrcDir" $T4Src 2>$null | Out-File -Encoding ASCII -FilePath $T4Pp
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: cl /EP failed on $T4Src" -ForegroundColor Red; exit 1 }
Get-Content -Raw $T4Pp | & $PhcExe | Out-File -Encoding ASCII -FilePath $T4C
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: phc transform failed on $T4Src" -ForegroundColor Red; exit 1 }
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /Fe"$T4Exe" $T4C | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $T4Exe)) { Write-Host "ERROR: cl link failed for test_pty_resize.exe" -ForegroundColor Red; exit 1 }
Write-Host "Built $T4Exe" -ForegroundColor Green

# ---- Step 3.12: build build/test_render_state.exe (T0 harness, Tcl/Tk linked) ----
# Bucket B state-dump harness per d9bba41 (theologian harness + footgun
# guard). #defines NBS_TEST_MODE then #includes p3_pty.phc — pulls
# render_screen / render_cursor / flush_span / compute_layout / etc into
# the test TU. Same Tcl/Tk import-lib link as p3_pty.exe. First Win CI
# result on this binary = empirical confirm of windows-latest window-
# station availability per testkeeper 09:52:11 b-pattern.
$T0Src  = Join-Path (Join-Path $RepoDir "tests") "test_render_state.phc"
$T0C    = Join-Path $BuildDir "test_render_state.c"
$T0Exe  = Join-Path $BuildDir "test_render_state.exe"
$T0Pp   = Join-Path $BuildDir "test_render_state.i"
Write-Host "Preprocessing $T0Src -> $T0C ..." -ForegroundColor Yellow
& cl.exe /nologo /EP /TC /I"$SrcDir" /I"$TclInclude" $T0Src 2>$null | Out-File -Encoding ASCII -FilePath $T0Pp
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: cl /EP failed on $T0Src" -ForegroundColor Red; exit 1 }
Get-Content -Raw $T0Pp | & $PhcExe | Out-File -Encoding ASCII -FilePath $T0C
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: phc transform failed on $T0Src" -ForegroundColor Red; exit 1 }
& cl.exe /nologo /std:c11 /W3 /D_CRT_SECURE_NO_WARNINGS /I"$TclInclude" /Fe"$T0Exe" $T0C `
    /link $($TclImport.FullName) $($TkImport.FullName) kernel32.lib user32.lib shell32.lib advapi32.lib | Out-Null
if ($LASTEXITCODE -ne 0 -or -not (Test-Path $T0Exe)) { Write-Host "ERROR: cl link failed for test_render_state.exe" -ForegroundColor Red; exit 1 }
Write-Host "Built $T0Exe" -ForegroundColor Green

# ---- Static guard: no Python DLL import (mirrors POSIX verify-no-python-link) ----
Write-Host "Verifying zero Python linkage..." -ForegroundColor Yellow
$Deps = & dumpbin.exe /dependents $PtyExe 2>$null
$PyImport = $Deps | Select-String -Pattern "python" -CaseSensitive:$false
if ($PyImport) {
    Write-Host "FAIL: $PtyExe imports Python DLL (B-shape requires zero Python linkage)" -ForegroundColor Red
    $PyImport | ForEach-Object { Write-Host "  $_" }
    exit 1
}
Write-Host "PASS: phc binary has zero Python linkage" -ForegroundColor Green

# ---- Step 4: self-tests ----
# Tcl/Tk runtime DLLs need to be on PATH; they live in deps/tcl-build/bin.
$env:PATH = "$TclBin;$env:PATH"

# Run the libc-only F1+F2 regression-anchor shims FIRST so their pass/fail
# signal is observed in CI even when the burst step (Win-CI longstanding
# fail since 2026-05-05) exits the script via the rc cascade. Order:
# shim1 -> shim2 -> burst -> selftest. Each captures its own rc; cascade
# below preserves shim signals before burst/selftest exits.
Write-Host "Running F1 selection-arithmetic shim (build/test_pixel_to_cell.exe)..." -ForegroundColor Yellow
& $ShimExe1
$shim1_rc = $LASTEXITCODE
if ($shim1_rc -eq 0) { Write-Host "F1 SHIM OK: pixel_to_cell arithmetic" -ForegroundColor Green }
else                  { Write-Host "F1 SHIM FAILED (exit $shim1_rc)." -ForegroundColor Red }

Write-Host "Running F2 byte-extract shim (build/test_extract_utf8.exe)..." -ForegroundColor Yellow
& $ShimExe2
$shim2_rc = $LASTEXITCODE
if ($shim2_rc -eq 0) { Write-Host "F2 SHIM OK: utf8_emit + row_sel_range + extract walk" -ForegroundColor Green }
else                  { Write-Host "F2 SHIM FAILED (exit $shim2_rc)." -ForegroundColor Red }

# Run the new T1-T4 + T0 shims BEFORE burst/selftest so their pass/fail
# signal is observed in CI even when the burst step exits the script via
# the rc cascade (Win-CI burst longstanding fail per testkeeper 2026-05-12
# 20:23:30 audit; path-c posture). Each shim captures its own rc.
Write-Host "Running T1 H gamma + dim shim (build/test_render_gamma.exe)..." -ForegroundColor Yellow
& $T1Exe
$t1_rc = $LASTEXITCODE
if ($t1_rc -eq 0) { Write-Host "T1 SHIM OK: render_gamma + render_dim" -ForegroundColor Green }
else              { Write-Host "T1 SHIM FAILED (exit $t1_rc)." -ForegroundColor Red }

Write-Host "Running T2 D special-keys + modifiers shim (build/test_input_keys.exe)..." -ForegroundColor Yellow
& $T2Exe
$t2_rc = $LASTEXITCODE
if ($t2_rc -eq 0) { Write-Host "T2 SHIM OK: encode_special_key + encode_key_event" -ForegroundColor Green }
else              { Write-Host "T2 SHIM FAILED (exit $t2_rc)." -ForegroundColor Red }

Write-Host "Running T3 A2 origin + bbox-calibration shim (build/test_compute_layout.exe)..." -ForegroundColor Yellow
& $T3Exe
$t3_rc = $LASTEXITCODE
if ($t3_rc -eq 0) { Write-Host "T3 SHIM OK: compute_layout clamp + bbox_calibrate WIDEN" -ForegroundColor Green }
else              { Write-Host "T3 SHIM FAILED (exit $t3_rc)." -ForegroundColor Red }

Write-Host "Running T4 J-resize TIOCSWINSZ shim (build/test_pty_resize.exe)..." -ForegroundColor Yellow
& $T4Exe
$t4_rc = $LASTEXITCODE
if ($t4_rc -eq 0) { Write-Host "T4 SHIM OK: pty_resize POSIX (Win SKIP banner expected)" -ForegroundColor Green }
else              { Write-Host "T4 SHIM FAILED (exit $t4_rc)." -ForegroundColor Red }

# T0 harness smoke — Tk-linked binary; needs windows-latest window-station.
# First-run = empirical confirm of Win Tk availability per testkeeper
# 09:52:11 b-pattern + supervisor 09:53:13 GO. If exit non-zero on a
# no-display ground, escalate per testkeeper 09:54:34 fallback gate
# (drop to Linux+Mac CI + named alexie-Win-smoke gate, NOT silent skip).
Write-Host "Running T0 state-dump harness smoke (build/test_render_state.exe + smoke_hello.tcl)..." -ForegroundColor Yellow
$T0Script = Join-Path (Join-Path $RepoDir "tests") "scripts\smoke_hello.tcl"
$T0Golden = Join-Path (Join-Path $RepoDir "tests") "goldens\smoke_hello.golden.txt"
& $T0Exe $T0Script $T0Golden
$t0_rc = $LASTEXITCODE
if ($t0_rc -eq 0) { Write-Host "T0 HARNESS OK: render_screen round-trip + golden compare" -ForegroundColor Green }
else              { Write-Host "T0 HARNESS FAILED (exit $t0_rc). If Win window-station unavailable, escalate per testkeeper 09:54:34 fallback gate." -ForegroundColor Red }

# Bucket B per-surface T0 scripts (testkeeper 12:38:19 Option 1 + supervisor
# 12:20:28 GO + 09:52:11 start order). a1_color: A1 span renderer per-attr
# fg/bg/font emission discriminator. Win artifact upload via .yml is atomic
# (catches any tests/goldens/*.actual via wildcard) — no per-surface upload
# needed in .ps1.
Write-Host "Running T0 A1 color (build/test_render_state.exe + a1_color.tcl)..." -ForegroundColor Yellow
$T0A1Script = Join-Path (Join-Path $RepoDir "tests") "scripts\a1_color.tcl"
$T0A1Golden = Join-Path (Join-Path $RepoDir "tests") "goldens\a1_color.golden.txt"
& $T0Exe $T0A1Script $T0A1Golden
$t0_a1_color_rc = $LASTEXITCODE
if ($t0_a1_color_rc -eq 0) { Write-Host "T0 A1 COLOR OK: per-span fg emission verified" -ForegroundColor Green }
else                       { Write-Host "T0 A1 COLOR FAILED (exit $t0_a1_color_rc). Inspect a1_color.win.golden.txt.actual artifact." -ForegroundColor Red }

# Bucket B A3a (theologian 12:53:01 Option 1 + commit 2e57d0d):
# PreferencesDialog construction + var-binding inline assertions.
Write-Host "Running T0 A3a Prefs (build/test_render_state.exe + a3a_prefs.tcl)..." -ForegroundColor Yellow
$T0A3aScript = Join-Path (Join-Path $RepoDir "tests") "scripts\a3a_prefs.tcl"
$T0A3aGolden = Join-Path (Join-Path $RepoDir "tests") "goldens\a3a_prefs.golden.txt"
& $T0Exe $T0A3aScript $T0A3aGolden
$t0_a3a_prefs_rc = $LASTEXITCODE
if ($t0_a3a_prefs_rc -eq 0) { Write-Host "T0 A3a PREFS OK: dialog construction + var bindings verified" -ForegroundColor Green }
else                        { Write-Host "T0 A3a PREFS FAILED (exit $t0_a3a_prefs_rc). Inspect a3a_prefs.win.golden.txt.actual artifact." -ForegroundColor Red }

# Bucket B F1 (commit e0665eb): mouse selection split-render
# (3 sub-spans with fg<->bg swap on selected segment).
Write-Host "Running T0 F mouse (build/test_render_state.exe + f_mouse.tcl)..." -ForegroundColor Yellow
$T0FmScript = Join-Path (Join-Path $RepoDir "tests") "scripts\f_mouse.tcl"
$T0FmGolden = Join-Path (Join-Path $RepoDir "tests") "goldens\f_mouse.golden.txt"
& $T0Exe $T0FmScript $T0FmGolden
$t0_f_mouse_rc = $LASTEXITCODE
if ($t0_f_mouse_rc -eq 0) { Write-Host "T0 F MOUSE OK: split-render selection highlight verified" -ForegroundColor Green }
else                      { Write-Host "T0 F MOUSE FAILED (exit $t0_f_mouse_rc). Inspect f_mouse.win.golden.txt.actual artifact." -ForegroundColor Red }

# Run the burst test (PTY layer only, direct-exec producer) AND p3_pty.exe
# -test (whole stack including Tk render) unconditionally, capturing both
# exit codes. Burst PASS + self-test FAIL isolates fault to the Tk/render
# layer; burst FAIL isolates to the PTY/ConPTY layer (producer choice is no
# longer a confound — direct-exec self-spawn replaced the prior powershell
# wrapper after the (iii) probe 1f2e33a confirmed powershell-startup as
# the Win bottleneck).
Write-Host "Running burst test (build/test_pty_burst.exe — PTY layer, direct-exec producer)..." -ForegroundColor Yellow
& $TestExe
$burst_rc = $LASTEXITCODE
if ($burst_rc -eq 0) {
    Write-Host "BURST TEST OK: ConPTY ring-backpressure drain" -ForegroundColor Green
} else {
    Write-Host "BURST TEST FAILED (exit $burst_rc). See stderr above." -ForegroundColor Red
}

Write-Host "Running self-test (build/p3_pty.exe -test)..." -ForegroundColor Yellow
& $PtyExe -test
$selftest_rc = $LASTEXITCODE
if ($selftest_rc -eq 0) {
    Write-Host "SELF-TEST OK: ConPTY -> render round-trip" -ForegroundColor Green
} else {
    Write-Host "SELF-TEST FAILED (exit $selftest_rc). See stderr above." -ForegroundColor Red
    Write-Host "Common causes:" -ForegroundColor Yellow
    Write-Host "  * Tcl/Tk runtime DLLs not on PATH (check $TclBin)." -ForegroundColor Yellow
    Write-Host "  * cmd.exe child not found (CreateProcess error)." -ForegroundColor Yellow
    Write-Host "  * ConPTY not supported (Windows 10 < 1809)." -ForegroundColor Yellow
}

# Exit codes: 0 = ok; 1 = setup fail; 2 = timeout (no marker); 3 = short read.
if ($burst_rc -eq 0 -and $selftest_rc -ne 0) {
    Write-Host "DIAGNOSIS: burst PASS, self-test FAIL -> fault is in Tk-render layer (separable from PTY)." -ForegroundColor Yellow
} elseif ($burst_rc -ne 0) {
    Write-Host "DIAGNOSIS: burst FAIL (exit $burst_rc) -> fault is in PTY/ConPTY layer. Investigate ring backpressure (exit 3) or pty_open / Tcl integration (exit 1/2)." -ForegroundColor Yellow
}

# Cascade: shims first (libc-only spec, must be observable on every CI run);
# burst + selftest after (PTY/Tk layers, longstanding Win-CI burst fail per
# testkeeper 2026-05-12 20:23:30 audit).
if ($shim1_rc -ne 0)    { exit $shim1_rc }
if ($shim2_rc -ne 0)    { exit $shim2_rc }
if ($t1_rc -ne 0)       { exit $t1_rc }
if ($t2_rc -ne 0)       { exit $t2_rc }
if ($t3_rc -ne 0)       { exit $t3_rc }
if ($t4_rc -ne 0)       { exit $t4_rc }
if ($t0_rc -ne 0)       { exit $t0_rc }
if ($t0_a1_color_rc -ne 0) { exit $t0_a1_color_rc }
if ($t0_a3a_prefs_rc -ne 0) { exit $t0_a3a_prefs_rc }
if ($t0_f_mouse_rc -ne 0) { exit $t0_f_mouse_rc }
if ($burst_rc -ne 0) { exit $burst_rc }
if ($selftest_rc -ne 0) { exit $selftest_rc }

Write-Host ""
Write-Host "=== Build Complete ===" -ForegroundColor Green
Write-Host "Run interactively:" -ForegroundColor Cyan
Write-Host "  $PtyExe                          (local cmd.exe)" -ForegroundColor White
Write-Host "  $PtyExe --ssh ssh user@host      (live SSH)" -ForegroundColor White
