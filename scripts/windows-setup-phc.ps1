# nbs-term Windows pure-phc Setup Script
#
# Builds the standalone phc binary (build/p3_pty.exe) on Windows. No Python
# at runtime; links Tcl/Tk + ConPTY (Win10 1809+).
#
# Prerequisites checked / installed by this script:
#   - MSVC Build Tools (cl.exe)            -- offers install if missing
#   - Magicsplat Tcl/Tk Windows kit         -- prompts for download path
#   - Git                                   -- assumed; nbs-term cloned via it
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
$PhcDir = Join-Path $RepoDir "deps\phc"
$PhcBuildDir = Join-Path $PhcDir "build"
$PhcExe = Join-Path $PhcBuildDir "phc.exe"

Write-Host "=== nbs-term Windows pure-phc Setup ===" -ForegroundColor Cyan
Write-Host "Repo: $RepoDir"

# ---- Step 1: locate MSVC ----
$VsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $VsWhere)) {
    Write-Host "ERROR: Visual Studio Installer not present." -ForegroundColor Red
    Write-Host "Install MSVC Build Tools first (https://visualstudio.microsoft.com/visual-cpp-build-tools/)." -ForegroundColor Yellow
    Write-Host "Or run scripts\windows-setup.ps1 -- it offers MSVC install." -ForegroundColor Yellow
    exit 1
}
$VsPath = & $VsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $VsPath) {
    Write-Host "ERROR: VC tools not detected. Install via Visual Studio Installer." -ForegroundColor Red
    exit 1
}
Write-Host "MSVC found at $VsPath" -ForegroundColor Green

# Import MSVC environment so cl.exe / link.exe land on PATH for this session.
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

# ---- Step 2: locate Tcl/Tk Windows kit ----
# Order: $env:TCL_HOME / $env:TK_HOME -> Magicsplat default -> ActiveTcl default.
$TclHome = $env:TCL_HOME
if (-not $TclHome) {
    foreach ($candidate in @("C:\Tcl", "C:\ActiveTcl", "C:\tcl86")) {
        if (Test-Path (Join-Path $candidate "include\tcl.h")) {
            $TclHome = $candidate; break
        }
    }
}
if (-not $TclHome -or -not (Test-Path (Join-Path $TclHome "include\tcl.h"))) {
    Write-Host "ERROR: Tcl/Tk Windows kit not found." -ForegroundColor Red
    Write-Host "" -ForegroundColor Yellow
    Write-Host "Install Magicsplat Tcl/Tk for Windows (recommended):" -ForegroundColor Yellow
    Write-Host "  https://www.magicsplat.com/tcl-installer/" -ForegroundColor White
    Write-Host "Default install path: C:\Tcl  (auto-detected)." -ForegroundColor White
    Write-Host "Or set `$env:TCL_HOME to the install root and re-run." -ForegroundColor White
    exit 1
}
$TclInclude = Join-Path $TclHome "include"
$TclLib = Join-Path $TclHome "lib"
# Find the import library (tcl86.lib / tcl90.lib varies by version).
$TclImport = Get-ChildItem -Path $TclLib -Filter "tcl*.lib" -ErrorAction SilentlyContinue |
    Where-Object { $_.Name -notmatch "stub" } | Select-Object -First 1
$TkImport = Get-ChildItem -Path $TclLib -Filter "tk*.lib" -ErrorAction SilentlyContinue |
    Where-Object { $_.Name -notmatch "stub" } | Select-Object -First 1
if (-not $TclImport -or -not $TkImport) {
    Write-Host "ERROR: tcl*.lib / tk*.lib not found under $TclLib." -ForegroundColor Red
    Write-Host "Magicsplat ships these in lib\; check your install." -ForegroundColor Yellow
    exit 1
}
Write-Host "Tcl/Tk found at $TclHome ($($TclImport.Name) + $($TkImport.Name))" -ForegroundColor Green

# ---- Step 3: build phc.exe ----
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

# ---- Step 4: build build/p3_pty.exe ----
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

# ---- Step 5: self-test ----
Write-Host "Running self-test (build/p3_pty.exe -test)..." -ForegroundColor Yellow
# Tcl/Tk runtime DLLs need to be on PATH; Magicsplat default puts them in bin\.
$TclBin = Join-Path $TclHome "bin"
$env:PATH = "$TclBin;$env:PATH"
& $PtyExe -test
$rc = $LASTEXITCODE
if ($rc -eq 0) {
    Write-Host "SELF-TEST OK: ConPTY -> render round-trip" -ForegroundColor Green
} else {
    Write-Host "SELF-TEST FAILED (exit $rc). See stderr above." -ForegroundColor Red
    Write-Host "Common causes:" -ForegroundColor Yellow
    Write-Host "  * Tcl/Tk runtime DLLs not on PATH (check $TclBin)." -ForegroundColor Yellow
    Write-Host "  * cmd.exe child not found (CreateProcess error)." -ForegroundColor Yellow
    Write-Host "  * ConPTY not supported (Windows 10 < 1809)." -ForegroundColor Yellow
    exit $rc
}

Write-Host ""
Write-Host "=== Build Complete ===" -ForegroundColor Green
Write-Host "Run interactively:" -ForegroundColor Cyan
Write-Host "  $PtyExe                          (local cmd.exe)" -ForegroundColor White
Write-Host "  $PtyExe --ssh ssh user@host      (live SSH)" -ForegroundColor White
