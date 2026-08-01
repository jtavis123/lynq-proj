import {
  createInitialState,
  navigate,
  runScene,
  toggleAutomation,
  toggleDevice
} from "./model.js";
import { render } from "./render.js";

let state = createInitialState();

const content = document.querySelector("#content");
const navButtons = [...document.querySelectorAll("[data-page]")];

function refresh() {
  content.innerHTML = render(state);
  navButtons.forEach(button =>
    button.classList.toggle("active", button.dataset.page === state.page)
  );

  document.querySelector("#home-name").textContent = state.homeName;
  document.querySelector("#wifi-status").textContent =
    state.status.wifi ? "Wi-Fi ✓" : "Wi-Fi —";
  document.querySelector("#cloud-status").textContent =
    state.status.cloud ? "Cloud ✓" : "Cloud —";
  document.querySelector("#alexa-status").textContent =
    state.status.alexa ? "Alexa ✓" : "Alexa —";
}

navButtons.forEach(button => {
  button.addEventListener("click", () => {
    state = navigate(state, button.dataset.page);
    refresh();
  });
});

content.addEventListener("click", event => {
  const target = event.target.closest("[data-action]");
  if (!target) return;

  const { action, id } = target.dataset;
  if (action === "toggle-device") state = toggleDevice(state, id);
  if (action === "run-scene") state = runScene(state, id);
  if (action === "toggle-automation") state = toggleAutomation(state, id);
  refresh();
});

setInterval(() => {
  document.querySelector("#time").textContent =
    new Date().toLocaleTimeString([], { hour: "numeric", minute: "2-digit" });
}, 1000);

refresh();
