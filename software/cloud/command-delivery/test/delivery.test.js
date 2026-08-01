import test from "node:test";
import assert from "node:assert/strict";
import { CommandQueue } from "../src/commandQueue.js";
import { HubSessionRegistry } from "../src/hubSessionRegistry.js";
import { DeliveryService } from "../src/deliveryService.js";

test("delivers a command to an online Hub and records an acknowledgement", async () => {
  let now = 1_000;
  const messages = [];
  const queue = new CommandQueue({ clock: () => now });
  const sessions = new HubSessionRegistry({ clock: () => now });
  sessions.connect({
    hubId: "hub-1",
    sessionId: "session-1",
    send: async message => messages.push(message)
  });

  const service = new DeliveryService({ queue, sessions });
  const result = await service.submit({
    commandId: "cmd-1",
    hubId: "hub-1",
    endpointId: "pool-light",
    action: "TurnOn"
  });

  assert.equal(messages.length, 1);
  assert.equal(messages[0].payload.commandId, "cmd-1");
  assert.equal(result.state, "delivering");

  now += 20;
  const completed = service.acknowledge({
    commandId: "cmd-1",
    status: "success"
  });
  assert.equal(completed.state, "completed");
});

test("retains a command while the Hub is offline", async () => {
  const queue = new CommandQueue();
  const sessions = new HubSessionRegistry();
  const service = new DeliveryService({ queue, sessions });

  const result = await service.submit({
    commandId: "cmd-offline",
    hubId: "hub-offline",
    endpointId: "garage",
    action: "Activate"
  });

  assert.equal(result.state, "queued");
});

test("deduplicates repeated command IDs", () => {
  const queue = new CommandQueue();
  const first = queue.enqueue({
    commandId: "same-id",
    hubId: "hub-1",
    endpointId: "fan",
    action: "TurnOn"
  });
  const second = queue.enqueue({
    commandId: "same-id",
    hubId: "hub-1",
    endpointId: "fan",
    action: "TurnOff"
  });
  assert.equal(first.action, "TurnOn");
  assert.equal(second.action, "TurnOn");
});

test("expires stale commands before delivery", () => {
  let now = 0;
  const queue = new CommandQueue({ clock: () => now, ttlMs: 100 });
  queue.enqueue({
    commandId: "expiring",
    hubId: "hub-1",
    endpointId: "light",
    action: "TurnOn"
  });
  now = 101;
  assert.equal(queue.nextForHub("hub-1"), null);
  assert.equal(queue.get("expiring").state, "expired");
});
