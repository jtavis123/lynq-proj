import test from "node:test";
import assert from "node:assert/strict";
import {
  createState,
  dispatch,
  runScene
} from "../src/model.js";

test("dispatches a bound learned command", () => {
  const updated = dispatch(
    createState(),
    "tv-living-room",
    "Power"
  );

  assert.equal(updated.history.length, 1);
  assert.equal(updated.history[0].success, true);
  assert.equal(updated.history[0].nodeId, "node-1");
});

test("records missing command failure", () => {
  const updated = dispatch(
    createState(),
    "tv-living-room",
    "Mute"
  );

  assert.equal(updated.history[0].success, false);
});

test("runs a scene through device command bindings", () => {
  const updated = runScene(createState(), "movie-night");
  assert.equal(updated.history.length, 1);
  assert.equal(updated.history[0].commandName, "Power");
});
