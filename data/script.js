"use strict";

let lightOn = false;
let waterOn = false;
let feedOn = false;
let cleanOn = false; // Added clean state

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
  } else if (type === "clean") {
    ws.send(nextState ? "CLEAN" : "STOP_CLEAN");
    cleanOn = nextState;
  }

  // Update UI
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

///////////////////////
// Button click handlers
///////////////////////

document.getElementById("lightBtn").onclick = () =>
  changeState(lightOn, "light");
document.getElementById("waterBtn").onclick = () =>
  changeState(waterOn, "water");
document.getElementById("feedBtn").onclick = () => changeState(feedOn, "feed");
document.getElementById("cleanBtn").onclick = () =>
  changeState(cleanOn, "clean");

// WebSocket listener for sensor updates (example: water level)
ws.onmessage = (event) => {
  const levelEl = document.getElementById("waterLvl");
  // Uncomment if needed:
  // if (levelEl) levelEl.innerHTML = event.data + "%";
};

function toggleEdit(calenderElement) {
  const scheduleBox = calenderElement.closest(".schedulebox");
  const timeContainer = scheduleBox.nextElementSibling;

  if (!timeContainer) return;

  const inputs = timeContainer.querySelectorAll("input[type='time']");
  inputs.forEach((input) => {
    input.disabled = !input.disabled;
  });

  const text = calenderElement.querySelector("p");
  if (text) {
    text.textContent = inputs[0].disabled ? "Edit" : "Done";
  }
}

//////////////////////////////
// Automic working machine
//////////////////////////////

function timeToMinutes(timeStr) {
  const [hour, minute] = timeStr.split(":").map(Number);
  return hour * 60 + minute;
}

// Trigger only once per minute
let lastCheckedMinute = -1;

// Check schedule every 10 seconds
setInterval(() => {
  const now = new Date();
  const currentMinutes = now.getHours() * 60 + now.getMinutes();

  if (currentMinutes === lastCheckedMinute) return;
  lastCheckedMinute = currentMinutes;

  // Light
  const lightOnTime = document.getElementById("lightOnTime")?.value;
  const lightOffTime = document.getElementById("lightOffTime")?.value;
  if (lightOnTime && timeToMinutes(lightOnTime) === currentMinutes) {
    changeState(false, "light"); // Turn ON
  }
  if (lightOffTime && timeToMinutes(lightOffTime) === currentMinutes) {
    changeState(true, "light"); // Turn OFF
  }

  // Feed
  const feedStart = document.getElementById("feedStartTime")?.value;
  const feedStop = document.getElementById("feedStopTime")?.value;
  if (feedStart && timeToMinutes(feedStart) === currentMinutes) {
    changeState(false, "feed"); // FEED
  }
  if (feedStop && timeToMinutes(feedStop) === currentMinutes) {
    changeState(true, "feed"); // STOP_FEED
  }

  // Water
  const waterOn = document.getElementById("waterOnTime")?.value;
  const waterOff = document.getElementById("waterOffTime")?.value;
  if (waterOn && timeToMinutes(waterOn) === currentMinutes) {
    changeState(false, "water"); // FILL
  }
  if (waterOff && timeToMinutes(waterOff) === currentMinutes) {
    changeState(true, "water"); // DRAIN
  }

  // Clean
  const cleanStart = document.getElementById("cleanStartTime")?.value;
  const cleanStop = document.getElementById("cleanStopTime")?.value;
  if (cleanStart && timeToMinutes(cleanStart) === currentMinutes) {
    changeState(false, "clean"); // CLEAN
  }
  if (cleanStop && timeToMinutes(cleanStop) === currentMinutes) {
    changeState(true, "clean"); // STOP_CLEAN
  }
}, 10000);
