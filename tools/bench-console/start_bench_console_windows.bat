@echo off
setlocal
cd /d "%~dp0\..\.."
python -m pip install -r tools\bench-console\requirements.txt
python tools\bench-console\bench_console.py detect
echo.
echo Review the detected ports before continuing.
pause
