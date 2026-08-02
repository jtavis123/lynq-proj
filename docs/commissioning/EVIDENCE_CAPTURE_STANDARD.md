# Evidence Capture Standard

Every important commissioning result should have objective evidence.

## Acceptable evidence

- Clear photographs showing the complete unit and relevant detail
- Serial console logs saved as text
- Flash backup file and SHA-256
- Firmware artifact and SHA-256
- Screen capture of display/touch tests
- RF/IR capture summary
- Network diagnostics with credentials removed
- Measurement records with equipment identifier

## Photograph naming

```text
SESSION_ARTICLE_TESTID_SEQUENCE_DESCRIPTION.jpg
```

Example:

```text
SESSION-001_FAI-0001_NODE-RF-TX_01_target-response.jpg
```

## Privacy and security

Do not capture or attach Wi-Fi passwords, private keys, access tokens, personal
account details, or unrestricted memory dumps. Redact screenshots before adding
them to the evidence package.
