export function createInitialState() {
  return {
    page: "home",
    homeName: "Tavis Home",
    status: {
      wifi: true,
      cloud: true,
      alexa: true,
      onlineNodes: 3,
      offlineNodes: 1
    },
    devices: [
      { id: "pool-lights", name: "Pool Lights", room: "Backyard", type: "Light", on: false, online: true },
      { id: "living-room-fan", name: "Living Room Fan", room: "Living Room", type: "Fan", on: true, online: true },
      { id: "garage-door", name: "Garage Door", room: "Garage", type: "Garage", on: false, online: true, safety: true },
      { id: "patio-shades", name: "Patio Shades", room: "Patio", type: "Shade", on: false, online: false }
    ],
    scenes: [
      { id: "movie-night", name: "Movie Night", subtitle: "4 actions", lastRun: "Never" },
      { id: "good-morning", name: "Good Morning", subtitle: "3 actions", lastRun: "Today 7:30 AM" },
      { id: "all-off", name: "All Off", subtitle: "6 actions", lastRun: "Yesterday 10:42 PM" }
    ],
    automations: [
      { id: "morning", name: "Good Morning", trigger: "Daily at 7:30 AM", enabled: true },
      { id: "patio-sunset", name: "Patio at Sunset", trigger: "10 min before sunset", enabled: true },
      { id: "vacation", name: "Vacation Lights", trigger: "Daily at 8:15 PM", enabled: false }
    ],
    alerts: [
      { id: "node-patio", title: "Patio Node Offline", subtitle: "Last seen 18 minutes ago" }
    ]
  };
}

export function navigate(state, page) {
  return { ...state, page };
}

export function toggleDevice(state, deviceId) {
  return {
    ...state,
    devices: state.devices.map(device =>
      device.id === deviceId && device.online
        ? { ...device, on: !device.on }
        : device
    )
  };
}

export function runScene(state, sceneId, now = "Just now") {
  return {
    ...state,
    scenes: state.scenes.map(scene =>
      scene.id === sceneId ? { ...scene, lastRun: now } : scene
    )
  };
}

export function toggleAutomation(state, automationId) {
  return {
    ...state,
    automations: state.automations.map(rule =>
      rule.id === automationId ? { ...rule, enabled: !rule.enabled } : rule
    )
  };
}
