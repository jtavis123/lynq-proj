# Device Database and Automation Requirements

1. Every device shall have a stable device ID.
2. Every visible command shall bind to one learned-command ID and one Node ID.
3. Disabled devices and disabled bindings shall not execute.
4. Scenes shall reference device IDs and friendly command names.
5. Scheduled automations shall use the same dispatch engine as manual control.
6. Expired command requests shall not execute.
7. Missing bindings shall fail without contacting a Node.
8. Device configuration shall persist through Hub restart.
9. Configuration writes shall be versioned and recoverable.
10. Relearning a command shall not require recreating scenes or automations.
11. Command results shall be available for activity history and diagnostics.
12. Safety-sensitive devices shall still pass the existing safety-policy layer.
