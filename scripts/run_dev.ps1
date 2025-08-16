param(
[string]$BuildDir = "build",
[string]$BuildType = "Release"
)

if (!(Test-Path $BuildDir)) { New-Item -ItemType Directory -Path $BuildDir | Out-Null }

cmake -S cpp -B $BuildDir -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=$BuildType

if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build $BuildDir -j

if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

if (Test-Path "$BuildDir/gol_cli.exe") { & "$BuildDir/gol_cli.exe" }