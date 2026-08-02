import test from "node:test";
import assert from "node:assert/strict";
import { RevANodeSimulator } from "../src/simulator.js";

test("announces the locked Rev A capability profile", () => {
  const node = new RevANodeSimulator({ nodeId: "node-1", name: "Garage Node" });
  const announcement = node.announce();
  assert.equal(announcement.hardwareProfile, "rev-a-m5stack");
  assert.ok(announcement.capabilities.includes("rf433"));
});

test("requires a valid pairing code", () => {
  const node = new RevANodeSimulator({ nodeId: "node-1", name: "Garage Node" });
  assert.throws(() => node.pair("123"));
  node.pair("123456");
  assert.equal(node.paired, true);
});

test("emits health heartbeats after pairing", () => {
  let now = 1000;
  const node = new RevANodeSimulator({ nodeId: "node-1", name: "Garage Node", clock: () => now });
  node.pair("123456");
  const heartbeat = node.heartbeat();
  assert.equal(heartbeat.observedAtEpochMs, 1000);
  assert.equal(heartbeat.rf433Ready, true);
});
