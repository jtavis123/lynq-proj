# LYNQ Alexa Smart Home Skill

AWS Lambda scaffold for Alexa Smart Home API v3.

## Implemented

- Discovery
- PowerController
- SceneController routing
- Access-token validation boundary
- AcceptGrant response boundary
- LYNQ cloud command routing
- Automated tests

## Runtime

Node.js 22 (`nodejs22.x`).

## Test

```bash
npm test
```

## Deployment

Use AWS SAM after replacing `LYNQ_API_BASE_URL` and implementing production token introspection, persistence, Event Gateway token exchange, observability and secrets management.
