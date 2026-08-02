#!/usr/bin/env python3
from pathlib import Path
import sys

required = [
    "sdk/include/lynq/service/DeploymentModels.h",
    "sdk/include/lynq/service/UpdateCoordinator.h",
    "sdk/src/UpdateCoordinator.cpp",
    "sdk/include/lynq/service/ServiceSessionManager.h",
    "tools/web-installer/src/server.js",
    "tools/config/backup_config.py",
    "tools/config/restore_config.py",
    "tools/support/create_support_bundle.py",
    "docs/architecture/DEPLOYMENT_SERVICE_PLATFORM.md",
    "docs/integration/DEPLOYMENT_AND_SERVICE_INTEGRATION_GUIDE.md",
    "docs/security/INSTALLER_OTA_SECURITY_REQUIREMENTS.md",
]

root = Path(__file__).resolve().parents[1]
missing = [item for item in required if not (root / item).exists()]
if missing:
    print("Missing required files:")
    for item in missing:
        print(" -", item)
    sys.exit(1)

print("PASS: LYNQ v2.1.0-beta.1 deployment/service package is valid.")
