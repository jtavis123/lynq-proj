$ErrorActionPreference = "Stop"
Write-Host "LYNQ ESP-IDF environment check"
$required = @("idf.py", "python", "git")
foreach ($command in $required) {
  if (-not (Get-Command $command -ErrorAction SilentlyContinue)) {
    throw "$command was not found. Open an ESP-IDF PowerShell terminal."
  }
}
idf.py --version
python --version
git --version
Write-Host "Environment check passed."
