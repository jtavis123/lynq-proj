import hashlib
import json
import subprocess
import sys
from pathlib import Path

SCRIPT = Path(__file__).parents[1] / "bench_console.py"

def run(*args):
    return subprocess.run(
        [sys.executable, str(SCRIPT), *args],
        capture_output=True, text=True
    )

def test_verify_artifact_passes(tmp_path):
    artifact = tmp_path / "image.bin"
    artifact.write_bytes(b"LYNQ")
    expected = hashlib.sha256(b"LYNQ").hexdigest()
    result = run("verify-artifact", str(artifact), expected)
    assert result.returncode == 0
    assert json.loads(result.stdout)["match"] is True

def test_verify_artifact_rejects_bad_digest(tmp_path):
    artifact = tmp_path / "image.bin"
    artifact.write_bytes(b"LYNQ")
    result = run("verify-artifact", str(artifact), "0" * 64)
    assert result.returncode == 1
