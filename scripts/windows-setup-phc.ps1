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

# Run BOTH the burst test (PTY layer only) AND p3_pty.exe -test (whole stack
# including Tk render) unconditionally, capturing both exit codes. This
# preserves the diagnostic comparison even when one fails — burst PASS +
# self-test FAIL isolates the fault to the Tk/render layer; both FAIL
# isolates it to the PTY/ConPTY layer (per testkeeper deferred spec
# D-1777640886, generalist 18:04:57 ordering note).
Write-Host "Running burst test (build/test_pty_burst.exe — PTY layer)..." -ForegroundColor Yellow
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

# Diagnostic summary: which layer is faulty. The burst exit code further
# discriminates the failure mode (per pythia #48: collapsing exit 2 timeout
# vs exit 3 short-read into "burst FAIL" misattributes runner-environment
# latency as a PTY/ConPTY layer fault). Exit 1 = setup; 2 = timeout (no
# marker); 3 = short read (bytes dropped).
if ($burst_rc -eq 0 -and $selftest_rc -ne 0) {
    Write-Host "DIAGNOSIS: burst PASS, self-test FAIL -> fault is in Tk-render layer (separable from PTY)." -ForegroundColor Yellow
} elseif ($burst_rc -eq 3 -and $selftest_rc -ne 0) {
    Write-Host "DIAGNOSIS: burst SHORT-READ (exit 3), self-test FAIL -> ConPTY ring backpressure regression (c8d5378 fix #4 may have regressed)." -ForegroundColor Yellow
} elseif ($burst_rc -eq 2 -and $selftest_rc -ne 0) {
    Write-Host "DIAGNOSIS: burst TIMEOUT (exit 2), self-test FAIL -> child never produced marker; likely runner-environment latency or producer-side issue. Cannot distinguish PTY vs Tk from these exit codes alone." -ForegroundColor Yellow
} elseif ($burst_rc -eq 1 -and $selftest_rc -ne 0) {
    Write-Host "DIAGNOSIS: burst SETUP-FAIL (exit 1), self-test FAIL -> Tcl/PTY setup failed before drain; investigate stderr." -ForegroundColor Yellow
} elseif ($burst_rc -ne 0 -and $selftest_rc -eq 0) {
    Write-Host "DIAGNOSIS: burst FAIL (exit $burst_rc), self-test PASS -> burst exercised a path not reached by the Tk-driven self-test (rare; investigate)." -ForegroundColor Yellow
}

if ($burst_rc -ne 0) { exit $burst_rc }
if ($selftest_rc -ne 0) { exit $selftest_rc }

Write-Host ""
Write-Host "=== Build Complete ===" -ForegroundColor Green
Write-Host "Run interactively:" -ForegroundColor Cyan
Write-Host "  $PtyExe                          (local cmd.exe)" -ForegroundColor White
Write-Host "  $PtyExe --ssh ssh user@host      (live SSH)" -ForegroundColor White
