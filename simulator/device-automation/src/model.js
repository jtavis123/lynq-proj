export function createState() {
  return {
    devices: [{
      id: "tv-living-room",
      name: "Living Room TV",
      room: "Living Room",
      commands: [
        { name: "Power", learnedCommandId: "ir-power", nodeId: "node-1" },
        { name: "Volume Up", learnedCommandId: "ir-vol-up", nodeId: "node-1" }
      ]
    }],
    scenes: [{
      id: "movie-night",
      name: "Movie Night",
      actions: [
        { deviceId: "tv-living-room", commandName: "Power" }
      ]
    }],
    history: []
  };
}

export function dispatch(state, deviceId, commandName) {
  const device = state.devices.find(d => d.id === deviceId);
  const command = device?.commands.find(c => c.name === commandName);
  const entry = command
    ? {
        deviceId,
        commandName,
        nodeId: command.nodeId,
        learnedCommandId: command.learnedCommandId,
        success: true
      }
    : { deviceId, commandName, success: false };

  return { ...state, history: [...state.history, entry] };
}

export function runScene(state, sceneId) {
  const scene = state.scenes.find(s => s.id === sceneId);
  if (!scene) return state;

  return scene.actions.reduce(
    (next, action) =>
      dispatch(next, action.deviceId, action.commandName),
    state
  );
}
