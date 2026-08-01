import test from "node:test";
import assert from "node:assert/strict";
import {
  createInitialState,
  navigate,
  runScene,
  toggleAutomation,
  toggleDevice
} from "../src/model.js";

test("navigates between primary pages", () => {
  const state = navigate(createInitialState(), "devices");
  assert.equal(state.page, "devices");
});

test("toggles an online device", () => {
  const initial = createInitialState();
  const updated = toggleDevice(initial, "pool-lights");
  assert.equal(updated.devices.find(d => d.id === "pool-lights").on, true);
});

test("does not toggle an offline device", () => {
  const initial = createInitialState();
  const updated = toggleDevice(initial, "patio-shades");
  assert.equal(updated.devices.find(d => d.id === "patio-shades").on, false);
});

test("records scene execution", () => {
  const updated = runScene(createInitialState(), "movie-night", "Just now");
  assert.equal(updated.scenes.find(s => s.id === "movie-night").lastRun, "Just now");
});

test("toggles an automation", () => {
  const updated = toggleAutomation(createInitialState(), "vacation");
  assert.equal(updated.automations.find(a => a.id === "vacation").enabled, true);
});
