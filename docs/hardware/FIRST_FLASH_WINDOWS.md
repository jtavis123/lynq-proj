# First Flash on Windows

1. Install the Espressif ESP-IDF Tools Installer.
2. Open **ESP-IDF PowerShell**, not ordinary PowerShell.
3. Connect only one LYNQ device by USB.
4. Open Device Manager and record its COM port.
5. Run `tools/windows/check-esp-idf.ps1`.
6. For the Hub, run `tools/windows/first-flash-hub.ps1 -Port COM7`.
7. For a Node, run `tools/windows/first-flash-node.ps1 -Port COM8`.
8. Replace the sample COM numbers with the ports shown on your PC.

Do not erase the Hub until its factory firmware has been backed up.
