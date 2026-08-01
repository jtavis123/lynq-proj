# Automation Scheduler

The Automation Scheduler runs locally on the LYNQ Hub.

Supported foundation triggers:

- Time of day
- Sunrise with minute offset
- Sunset with minute offset
- Device events

Each automation activates a Scene. This keeps multi-device orchestration inside
the Scene Engine rather than duplicating command lists in every trigger.

## Reliability rules

- Disabled automations do not run.
- One rule runs at most once per epoch minute.
- Failed scene executions do not update the last-run marker.
- Local schedules continue without cloud connectivity.
- Timezone and daylight-saving changes are handled by the Hub time service.
