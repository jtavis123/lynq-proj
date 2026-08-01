# Hub Command Router Requirements

1. All local and remote commands shall pass through one routing boundary.
2. Every command shall include a unique command ID and endpoint ID.
3. Expired commands shall not execute.
4. Completed command IDs shall not execute more than once.
5. Unknown endpoints shall fail without contacting a Node.
6. Learned commands shall route to the assigned Node and signal ID.
7. Relay commands shall route to the assigned Node and relay ID.
8. Scene commands shall execute through the Hub scene engine.
9. Remote commands shall pass a safety-policy check.
10. Safety-sensitive endpoints shall be denied remotely by default.
11. Every routed cloud command shall produce an acknowledgement.
12. Local control shall remain available without cloud connectivity.
