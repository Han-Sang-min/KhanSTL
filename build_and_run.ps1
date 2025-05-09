param(
    [switch]$Clean
)

# 1) Create separate Debug build dir
if ($Clean) {
    Write-Host "Cleaning build directory..."
    if (Test-Path "build") {
        Remove-Item -Recurse -Force "build"
    }
}

if (!(Test-Path "build")) {
    Write-Host "Creating build directory..."
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# 2) Configure CMake in Debug mode
Write-Host "Configuring CMake (Debug)..."
Push-Location "build"
cmake -G "MinGW Makefiles" `
      -DCMAKE_C_COMPILER=gcc `
      -DCMAKE_CXX_COMPILER=g++ `
      -DCMAKE_BUILD_TYPE=Debug `
      ..

if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake (Debug) failed."
    exit $LASTEXITCODE
}

# 3) Build the Debug target
Write-Host "Building Debug..."
cmake --build . --config Debug

if ($LASTEXITCODE -ne 0) {
    Write-Host "Debug build failed."
    Exit $LASTEXITCODE
}

# 4) Run your debug exe
Write-Host "Running Debug executable..."
& .\unit_tests.exe

Pop-Location