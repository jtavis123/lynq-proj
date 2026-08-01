# Alexa Integration Requirements

1. LYNQ shall implement an Alexa Smart Home skill using API v3 directives.
2. Every customer shall link an Alexa identity to a LYNQ account using OAuth 2.0 authorization-code grant.
3. Discovery shall return only devices owned by the linked account.
4. Endpoint IDs shall be stable and opaque.
5. Lambda shall validate the bearer token on every directive.
6. Commands shall be idempotent by message ID.
7. The cloud shall route commands only to the authenticated customer's Hub.
8. The Hub shall enforce local device-class safety policy before execution.
9. Offline Hubs or Nodes shall return an Alexa endpoint-unreachable response.
10. Event Gateway support shall be added for proactive state and health reporting.
11. Account unlinking shall revoke cloud and Event Gateway tokens.
12. Alexa integration shall not be required for local touchscreen, app or automation operation.
