#!/usr/bin/env python3
import argparse, html, json
from pathlib import Path

def esc(value):
    return html.escape(str(value or ""))

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("session", type=Path)
    ap.add_argument("output", type=Path)
    args = ap.parse_args()
    data = json.loads(args.session.read_text())

    rows = "".join(
        f"<tr><td>{esc(t['testId'])}</td><td>{esc(t['name'])}</td>"
        f"<td class='{esc(t['result'].lower())}'>{esc(t['result'])}</td>"
        f"<td>{esc(t['measurement'])}</td><td>{esc(t['notes'])}</td>"
        f"<td>{len(t['evidence'])}</td></tr>"
        for t in data["tests"]
    )
    defects = "".join(
        f"<li><b>{esc(d['defectId'])}</b> — {esc(d['severity'])}: "
        f"{esc(d['description'])} ({esc(d['status'])})</li>"
        for d in data["defects"]
    ) or "<li>None recorded</li>"

    document = f"""<!doctype html>
<html><head><meta charset='utf-8'><title>LYNQ Commissioning Report</title>
<style>
body{{font-family:Arial,sans-serif;margin:32px;color:#1b2430}}
h1{{border-bottom:4px solid #297ec0;padding-bottom:10px}}
table{{border-collapse:collapse;width:100%;font-size:13px}}
th,td{{border:1px solid #cfd5dc;padding:8px;text-align:left}}
th{{background:#eef2f6}} .pass{{color:#08783e;font-weight:bold}}
.fail{{color:#b42318;font-weight:bold}} .blocked{{color:#8a4b00;font-weight:bold}}
.meta{{display:grid;grid-template-columns:repeat(3,1fr);gap:10px}}
.card{{background:#f4f6f8;padding:12px;border-radius:8px}}
</style></head><body>
<h1>LYNQ Commissioning Report</h1>
<div class='meta'>
<div class='card'><b>Session</b><br>{esc(data['sessionId'])}</div>
<div class='card'><b>Article</b><br>{esc(data['articleId'])}</div>
<div class='card'><b>Status</b><br>{esc(data['status'])}</div>
<div class='card'><b>Operator</b><br>{esc(data['operator'])}</div>
<div class='card'><b>Started</b><br>{esc(data['startedAt'])}</div>
<div class='card'><b>Completed</b><br>{esc(data['completedAt'])}</div>
</div>
<h2>Test Results</h2>
<table><thead><tr><th>ID</th><th>Test</th><th>Result</th>
<th>Measurement</th><th>Notes</th><th>Evidence</th></tr></thead>
<tbody>{rows}</tbody></table>
<h2>Defects</h2><ul>{defects}</ul>
<p><small>Generated from the controlled LYNQ commissioning record.
This report does not replace regulatory or laboratory certification.</small></p>
</body></html>"""
    args.output.write_text(document)
    print(args.output)

if __name__ == "__main__":
    main()
