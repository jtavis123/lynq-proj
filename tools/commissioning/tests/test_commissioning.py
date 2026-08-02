import json
import subprocess
import sys
from pathlib import Path

SCRIPT = Path(__file__).parents[1] / "commission.py"

def run(*args):
    return subprocess.run([sys.executable, str(SCRIPT), *args],
                          capture_output=True, text=True)

def test_new_session_and_record(tmp_path):
    session = tmp_path / "session.json"
    result = run("new", "--session-id", "S-1", "--article-id", "FAI-1",
                 "--operator", "tech", "--hub-serial", "HUB-1",
                 "--node-serial", "NODE-1", "--output", str(session))
    assert result.returncode == 0
    data = json.loads(session.read_text())
    assert data["status"] == "IN_PROGRESS"

    result = run("record-test", str(session), "HUB-USB", "PASS",
                 "--operator", "tech", "--notes", "COM5")
    assert result.returncode == 0
    data = json.loads(session.read_text())
    test = next(t for t in data["tests"] if t["testId"] == "HUB-USB")
    assert test["result"] == "PASS"

def test_finalize_rejects_incomplete(tmp_path):
    session = tmp_path / "session.json"
    run("new", "--session-id", "S-2", "--article-id", "FAI-2",
        "--operator", "tech", "--hub-serial", "HUB-2",
        "--output", str(session))
    result = run("finalize", str(session), "--approver", "quality")
    assert result.returncode != 0
