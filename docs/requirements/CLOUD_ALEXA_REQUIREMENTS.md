# Cloud and Alexa Requirements

1. Every Hub belongs to one authorized household.
2. Every remote command has a stable ID and expiration time.
3. Offline Hubs do not report false success.
4. Alexa endpoints derive from enabled Device Database records.
5. Remote commands use the same Hub dispatch path as local commands.
6. The Hub reports executing and final acknowledgement states.
7. Cloud loss does not stop local control or local automation.
8. Existing safety policies remain authoritative.
9. Tokens and private keys are never written to logs.
10. Alexa support is not production-ready until OAuth and certification are complete.
