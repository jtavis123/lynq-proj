# Automation Requirements

1. Automations shall execute locally on the Hub.
2. Automations shall support time-of-day triggers.
3. Automations shall support sunrise and sunset offsets.
4. Automations shall support future device-event triggers.
5. Automations shall activate Scenes through the Scene Engine.
6. A rule shall run no more than once for the same scheduled minute.
7. Disabled rules shall not execute.
8. Configuration shall survive Hub restart.
9. Configuration documents shall carry schema versions.
10. Invalid configuration shall not replace the last known good configuration.
11. Cloud loss shall not stop local schedules.
12. Safety-sensitive Scene actions shall still pass command safety policies.
