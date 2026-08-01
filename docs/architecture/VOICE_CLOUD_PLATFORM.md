# Voice and Cloud Platform Architecture

```text
Alexa Voice Service
        |
Alexa Smart Home Skill
        |
AWS Lambda
        |
LYNQ Device Cloud API
        |
Authenticated outbound Hub connection
        |
LYNQ Hub Command Router
        |
Node One / Node Mini / Relay / Garage
```

The Hub remains the local authority. Cloud services expose selected devices to Alexa and route signed, authenticated command envelopes to the correct Hub. The Hub validates authorization, endpoint ownership, replay protection and device safety policy before forwarding a local command to a Node.

## Command lifecycle

1. Alexa sends a directive containing a linked-account access token.
2. Lambda validates the token and resolves the LYNQ user.
3. The endpoint cookie identifies the Hub, Node and learned command.
4. The cloud API records an idempotent command envelope.
5. The Hub receives the command over an authenticated outbound connection.
6. The Hub enforces device-class safety rules.
7. The Hub routes the command to the paired Node.
8. The Node transmits the learned RF/IR signal or actuates a relay.
9. Result and state are reported back to Alexa.
