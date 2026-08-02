#!/usr/bin/env bash
set -euo pipefail
TARGET=${1:?hub or node}
PORT=${2:?serial port required}
cd "$(dirname "$0")/../../${TARGET}/firmware"
idf.py set-target esp32s3
idf.py build
idf.py -p "$PORT" flash monitor
