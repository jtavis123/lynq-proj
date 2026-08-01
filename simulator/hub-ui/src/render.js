const escapeHtml = value =>
  String(value)
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;");

const pageHeading = (title, subtitle) => `
  <div class="heading-row">
    <div>
      <h1>${escapeHtml(title)}</h1>
      <div class="muted">${escapeHtml(subtitle)}</div>
    </div>
  </div>`;

export function render(state) {
  switch (state.page) {
    case "devices": return renderDevices(state);
    case "scenes": return renderScenes(state);
    case "automations": return renderAutomations(state);
    case "settings": return renderSettings(state);
    default: return renderHome(state);
  }
}

function renderHome(state) {
  const favorites = state.devices.slice(0, 3).map(device => `
    <button class="card ${device.on ? "active" : ""} ${!device.online ? "warning" : ""}"
            data-action="toggle-device" data-id="${escapeHtml(device.id)}">
      <strong>${escapeHtml(device.name)}</strong>
      <span class="muted">${escapeHtml(device.room)} · ${device.online ? (device.on ? "On" : "Off") : "Offline"}</span>
    </button>`).join("");

  const scenes = state.scenes.slice(0, 3).map(scene => `
    <button class="card" data-action="run-scene" data-id="${escapeHtml(scene.id)}">
      <strong>${escapeHtml(scene.name)}</strong>
      <span class="muted">${escapeHtml(scene.subtitle)} · ${escapeHtml(scene.lastRun)}</span>
    </button>`).join("");

  const alerts = state.alerts.map(alert => `
    <div class="row">
      <div><strong>${escapeHtml(alert.title)}</strong><div class="muted">${escapeHtml(alert.subtitle)}</div></div>
      <span class="pill warning">Attention</span>
    </div>`).join("");

  return `
    ${pageHeading("Good afternoon", state.homeName)}
    <div class="grid">${favorites}</div>
    <div class="section-title">Scenes</div>
    <div class="grid">${scenes}</div>
    ${alerts ? `<div class="section-title">Alerts</div><div class="row-list">${alerts}</div>` : ""}
  `;
}

function renderDevices(state) {
  const rows = state.devices.map(device => `
    <div class="row">
      <div>
        <strong>${escapeHtml(device.name)}</strong>
        <div class="muted">${escapeHtml(device.room)} · ${escapeHtml(device.type)}${device.safety ? " · Safety-sensitive" : ""}</div>
      </div>
      <button class="toggle ${device.on ? "on" : ""}"
              data-action="toggle-device" data-id="${escapeHtml(device.id)}"
              aria-label="Toggle ${escapeHtml(device.name)}"
              ${device.online ? "" : "disabled"}></button>
    </div>`).join("");

  return `${pageHeading("Devices", `${state.devices.length} configured devices`)}<div class="row-list">${rows}</div>`;
}

function renderScenes(state) {
  const cards = state.scenes.map(scene => `
    <button class="card" data-action="run-scene" data-id="${escapeHtml(scene.id)}">
      <strong>${escapeHtml(scene.name)}</strong>
      <span class="muted">${escapeHtml(scene.subtitle)}</span>
      <div class="muted">Last run: ${escapeHtml(scene.lastRun)}</div>
    </button>`).join("");

  return `${pageHeading("Scenes", "One touch, multiple actions")}<div class="grid">${cards}</div>`;
}

function renderAutomations(state) {
  const rows = state.automations.map(rule => `
    <div class="row">
      <div>
        <strong>${escapeHtml(rule.name)}</strong>
        <div class="muted">${escapeHtml(rule.trigger)}</div>
      </div>
      <button class="toggle ${rule.enabled ? "on" : ""}"
              data-action="toggle-automation" data-id="${escapeHtml(rule.id)}"
              aria-label="Toggle ${escapeHtml(rule.name)}"></button>
    </div>`).join("");

  return `${pageHeading("Automations", "Runs locally on your Hub")}<div class="row-list">${rows}</div>`;
}

function renderSettings(state) {
  return `
    ${pageHeading("Settings", "System and connectivity")}
    <div class="row-list">
      <div class="row"><strong>Wi-Fi</strong><span class="pill success">Connected</span></div>
      <div class="row"><strong>Alexa</strong><span class="pill success">Linked</span></div>
      <div class="row"><strong>Cloud</strong><span class="pill success">Online</span></div>
      <div class="row"><strong>Nodes</strong><span class="pill warning">${state.status.onlineNodes} online · ${state.status.offlineNodes} offline</span></div>
      <div class="row"><strong>Firmware</strong><span class="pill">v0.9.1-alpha</span></div>
    </div>`;
}
