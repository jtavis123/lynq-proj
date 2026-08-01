# Cloud Command Delivery Requirements

1. The service shall queue commands for an offline Hub only until command expiry.
2. The service shall deduplicate identical command IDs.
3. The Hub shall maintain an outbound authenticated session.
4. The service shall deliver only commands owned by the authenticated Hub account.
5. The Hub shall acknowledge every accepted command.
6. Acknowledgements shall include command ID, result and optional diagnostic detail.
7. The service shall record delivery attempts without recording sensitive credentials.
8. A command shall not be executed after its expiration time.
9. Loss of cloud connectivity shall not disable local Hub and Node control.
10. Safety-sensitive commands shall pass local policy checks before execution.
