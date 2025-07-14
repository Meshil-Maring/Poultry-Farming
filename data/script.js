"use strict";

let lightOn = false;
let waterOn = false;
let feedOn = false;

const ws = new WebSocket(`ws://${location.host}/ws`);

function changeState(state, type) {
  const nextState = !state;
  const isOff = state;
  const statusText = isOff ? "off" : "on";
  const statusValue = isOff ? "OFF" : "ON";
  const backgroundColor = isOff ? "#5f3737" : "#72a8ce";
  const backgroundImage = isOff
    ? "linear-gradient(to bottom right, #e1eafb, white)"
    : "linear-gradient(to bottom right, #72a8ce, white)";

  // Send WebSocket command
  if (type === "light") {
    ws.send(nextState ? "ON" : "OFF");
    lightOn = nextState;
  } else if (type === "water") {
    ws.send(nextState ? "FILL" : "DRAIN");
    waterOn = nextState;
  } else if (type === "feed") {
    ws.send(nextState ? "FEED" : "STOP_FEED");
    feedOn = nextState;
  }

  // Update UI safely
  const statusEl = document.getElementById(`${type}Status`);
  const statusTextEl = document.getElementById(`${type}StatusText`);
  const statusContainerEl = document.getElementById(`${type}StatusContainer`);
  const btnEl = document.getElementById(`${type}Btn`);

  if (statusEl) statusEl.innerHTML = statusText;
  if (statusTextEl) statusTextEl.innerHTML = statusValue;
  if (btnEl) btnEl.style.backgroundColor = backgroundColor;
  if (statusContainerEl)
    statusContainerEl.style.backgroundImage = backgroundImage;
}

// Button click handlers
document.getElementById("lightBtn").onclick = () =>
  changeState(lightOn, "light");
document.getElementById("waterBtn").onclick = () =>
  changeState(waterOn, "water");
document.getElementById("feedBtn").onclick = () => changeState(feedOn, "feed");

// Listen for water level from sensor
ws.onmessage = (event) => {
  const levelEl = document.getElementById("waterLvl");
  // if (levelEl) levelEl.innerHTML = event.data + "%";
};
