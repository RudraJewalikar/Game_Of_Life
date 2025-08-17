param(
  [string]$BuildDir = "build",
  [string]$BuildType = "Release",
  [int]$Width = 10,
  [int]$Height = 10,
#   [int]$Steps = 10,
  [bool]$Wrap = $true
#   [string]$Rules = "B3/S23"
)

if (!(Test-Path $BuildDir)) { New-Item -ItemType Directory -Path $BuildDir | Out-Null }

cmake -S cpp -B $BuildDir -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=$BuildType
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build $BuildDir -j
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

$exe = Join-Path $BuildDir "gol_cli.exe"
if (Test-Path $exe) {
  $argv = @(
    "--width",  $Width.ToString()
    "--height", $Height.ToString()
    # "--steps",  $Steps.ToString()
    "--wrap",   ($Wrap.ToString().ToLower())
    # "--rules",  $Rules
  )
  if ($Pattern -ne "") { $argv += @("--pattern", $Pattern) }
  & $exe @argv
}
