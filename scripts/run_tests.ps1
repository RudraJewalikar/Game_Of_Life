param(
[string]$BuildDir = "build-tests",
[string]$BuildType = "Debug"
)

if (!(Test-Path $BuildDir)) { New-Item -ItemType Directory -Path $BuildDir | Out-Null }

cmake -S cpp -B $BuildDir -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=$BuildType

if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build $BuildDir -j

if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

if (Test-Path "$BuildDir/gol_tests.exe") {
& "$BuildDir/gol_tests.exe"
exit $LASTEXITCODE
} else {
Write-Error "gol_tests.exe not found in $BuildDir"
exit 1
}