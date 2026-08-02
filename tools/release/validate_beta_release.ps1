param([string]$RepoRoot = ".")
$ErrorActionPreference = "Stop"
python "$RepoRoot/tools/release/validate_beta_release.py" "$RepoRoot"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
