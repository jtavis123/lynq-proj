$ErrorActionPreference = "Stop"
$Root = Resolve-Path "$PSScriptRoot\..\.."
Set-Location $Root
python -m pip install -r tools/bench-console/requirements.txt
python tools/bench-console/bench_console.py detect
Write-Host ""
Write-Host "Review the detected ports before continuing."
