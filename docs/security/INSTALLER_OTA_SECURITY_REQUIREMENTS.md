# Installer and OTA Security Requirements

1. Installer access shall require a one-time setup credential.
2. Setup credentials shall expire after successful use or a short timeout.
3. Production remote access shall require mutually authenticated TLS or an
   equivalent authenticated tunnel.
4. Firmware artifacts shall be signed by an offline-controlled release key.
5. Devices shall contain only the public verification key.
6. Firmware SHA-256 shall be checked before installation.
7. Downgrades shall be denied unless an authorized recovery policy permits one.
8. Hub firmware shall use A/B partitions and automatic rollback.
9. Node updates shall validate hardware profile and available power.
10. Configuration exports shall use authenticated encryption in production.
11. Secrets shall never appear in logs, crash records or support bundles.
12. Service sessions shall expire automatically.
13. Technician actions shall be auditable.
14. Crash uploads shall be opt-in and privacy reviewed.
15. Factory firmware backups shall be preserved before the first LYNQ flash.
