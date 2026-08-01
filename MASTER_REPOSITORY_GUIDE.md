# LYNQ Master Repository Guide

This repository is the digital product vault for the LYNQ platform.

## Source of truth

- `firmware/` contains normalized firmware projects and the shared SDK.
- Existing `hub/`, `node/`, and `sdk/` paths are retained for compatibility with prior commits.
- `hardware/`, `manufacturing/`, `software/`, `marketing/`, and `docs/` store the complete commercial product record.

## Asset migration from the HOMEHUB PC folder

Add existing files from the local HOMEHUB folder to the matching locations:

- BOM spreadsheets -> `manufacturing/bom/`
- Work instructions -> `manufacturing/work-instructions/`
- Assembly instructions -> `manufacturing/assembly-instructions/`
- PCB images and layouts -> `hardware/pcb/`
- Enclosure and exploded views -> `hardware/enclosures/`
- Wiring harness documentation -> `hardware/wiring-harnesses/`
- Marketing datasheets -> `marketing/datasheets/`
- Logos -> `marketing/logos/`
- Product renders and photos -> `marketing/photos/`
- Architecture and requirements documents -> `docs/product/`
- Certification files -> `docs/certification/`

Do not commit passwords, API secrets, Wi-Fi credentials, signing keys, or private certificates.
