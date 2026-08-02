param([Parameter(Mandatory=$true)][string]$Port)
$ErrorActionPreference = "Stop"
Set-Location "$PSScriptRoot\..\..\node\firmware"
idf.py set-target esp32s3
idf.py build
idf.py -p $Port flash monitor
