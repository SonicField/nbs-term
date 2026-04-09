# nbs-term Windows Setup Script
# Downloads Python with Tk, creates a venv, clones repo, installs, runs tests.
# Run from PowerShell: .\scripts\windows-setup.ps1
#
# No admin rights needed. Installs Python per-user.

$ErrorActionPreference = "Stop"

$PythonVersion = "3.12.8"
$PythonMajorMinor = "312"
$InstallDir = "$env:LOCALAPPDATA\Programs\Python\Python$PythonMajorMinor"
$VenvDir = "$env:USERPROFILE\nbsterm-venv"
$RepoDir = "$env:USERPROFILE\nbs-term"
$InstallerUrl = "https://www.python.org/ftp/python/$PythonVersion/python-$PythonVersion-amd64.exe"
$InstallerPath = "$env:TEMP\python-$PythonVersion-amd64.exe"

Write-Host "=== nbs-term Windows Setup ===" -ForegroundColor Cyan

# Step 1: Check if Python with Tk is already available
$existingPython = "$InstallDir\python.exe"
if (Test-Path $existingPython) {
    Write-Host "Python found at $existingPython" -ForegroundColor Green
} else {
    # Download Python installer
    Write-Host "Downloading Python $PythonVersion..." -ForegroundColor Yellow
    Invoke-WebRequest -Uri $InstallerUrl -OutFile $InstallerPath

    # Install per-user with tcl/tk, pip, no PATH modification
    Write-Host "Installing Python $PythonVersion (per-user, with Tk)..." -ForegroundColor Yellow
    Start-Process -Wait -FilePath $InstallerPath -ArgumentList @(
        "/quiet",
        "InstallAllUsers=0",
        "Include_tcltk=1",
        "Include_pip=1",
        "Include_test=0",
        "PrependPath=0",
        "DefaultJustForMeTargetDir=$InstallDir"
    )

    if (-not (Test-Path "$InstallDir\python.exe")) {
        Write-Host "ERROR: Python installation failed." -ForegroundColor Red
        exit 1
    }
    Write-Host "Python installed at $InstallDir" -ForegroundColor Green

    # Clean up installer
    Remove-Item $InstallerPath -ErrorAction SilentlyContinue
}

# Step 2: Verify Tk
Write-Host "Verifying Tk..." -ForegroundColor Yellow
& "$InstallDir\python.exe" -c "import tkinter; print(f'Tcl/Tk version: {tkinter.TclVersion}')"
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: tkinter not available. Reinstall Python with Tk enabled." -ForegroundColor Red
    exit 1
}

# Step 3: Check for C compiler (MSVC Build Tools)
$hasCompiler = $false
try {
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        $vsPath = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2>$null
        if ($vsPath) { $hasCompiler = $true }
    }
} catch {}

if (-not $hasCompiler) {
    Write-Host "C compiler (MSVC Build Tools) not found." -ForegroundColor Yellow
    $response = Read-Host "Install Visual Studio Build Tools? [Y]/n"
    if ($response -eq '' -or $response -eq 'Y' -or $response -eq 'y') {
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
    } else {
        Write-Host "ERROR: C compiler required. Install from: https://visualstudio.microsoft.com/visual-cpp-build-tools/" -ForegroundColor Red
        exit 1
    }
}
Write-Host "C compiler available." -ForegroundColor Green

# Step 4: Create venv
if (Test-Path $VenvDir) {
    Write-Host "Venv exists at $VenvDir — reusing." -ForegroundColor Yellow
} else {
    Write-Host "Creating venv at $VenvDir..." -ForegroundColor Yellow
    & "$InstallDir\python.exe" -m venv $VenvDir
}

# Activate venv
$VenvPython = "$VenvDir\Scripts\python.exe"
$VenvPip = "$VenvDir\Scripts\pip.exe"

# Step 5: Clone repo (if not already cloned)
if (Test-Path "$RepoDir\.git") {
    Write-Host "Repo exists at $RepoDir — pulling latest..." -ForegroundColor Yellow
    Push-Location $RepoDir
    git pull
    Pop-Location
} else {
    Write-Host "Cloning nbs-term..." -ForegroundColor Yellow
    git clone https://github.com/SonicField/nbs-term.git $RepoDir
}

# Step 6: Install nbs-term
Write-Host "Installing nbs-term (compiling C extension)..." -ForegroundColor Yellow
Push-Location $RepoDir
& $VenvPip install -e .
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: pip install failed. Check the error output above." -ForegroundColor Red
    Pop-Location
    exit 1
}

# Step 7: Run tests
Write-Host "Running tests..." -ForegroundColor Yellow
& $VenvPip install pytest
& "$VenvDir\Scripts\pytest.exe" --tb=short
Pop-Location

Write-Host ""
Write-Host "=== Setup Complete ===" -ForegroundColor Green
Write-Host "To use nbs-term:" -ForegroundColor Cyan
Write-Host "  $VenvDir\Scripts\Activate.ps1" -ForegroundColor White
Write-Host "  nbs-term user@host" -ForegroundColor White
