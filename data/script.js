"use strict";

let lightOn = false;
let waterOn = false;
let feedOn = false;
let cleanOn = false;
let lastCheckedMinute = -1;

const ws = new WebSocket(`ws://${location.host}/ws`);

function changeState(state, type) {
  const nextState = !state;
  console.log(`[${type}] Changing state to:`, nextState);

  let btn, statusText, statusCard, statusCardText;

  if (type === "light") {
    ws.send(nextState ? "ON" : "OFF");
    lightOn = nextState;
    btn = document.getElementById("lightBtn");
    statusText = document.getElementById("lightStatus");
    statusCard = document.getElementById("lightStatusContainer");
    statusCardText = document.getElementById("lightStatusText");
  } else if (type === "water") {
    ws.send(nextState ? "FILL" : "DRAIN");
    waterOn = nextState;
    btn = document.getElementById("waterBtn");
    statusText = document.getElementById("waterStatus");
    statusCard = document.getElementById("waterStatusContainer");
    statusCardText = document.getElementById("waterStatusText");
  } else if (type === "feed") {
    ws.send(nextState ? "FEED" : "STOP_FEED");
    feedOn = nextState;
    btn = document.getElementById("feedBtn");
    statusText = document.getElementById("feedStatus");
    statusCard = document.getElementById("feedStatusContainer");
    statusCardText = document.getElementById("feedStatusText");
  } else if (type === "clean") {
    ws.send(nextState ? "CLEAN" : "STOP_CLEAN");
    cleanOn = nextState;
    btn = document.getElementById("cleanBtn");
    statusText = document.getElementById("cleanStatus");
    statusCard = document.getElementById("cleanStatusContainer");
    statusCardText = document.getElementById("cleanStatusText");
  }

  if (btn && statusText) {
    statusText.textContent = nextState ? "On" : "Off";
    statusText.style.color = nextState ? "white" : "gray";
    btn.style.backgroundColor = nextState ? "#4caf50" : "#5f3737";
  }

  if (statusCard && statusCardText) {
    statusCardText.textContent = nextState ? "ON" : "OFF";
    statusCardText.style.color = nextState ? "white" : "black";

    const onColors = {
      light: "#ffeb3b",
      water: "#2196f3",
      feed: "#ff9800",
      clean: "#9c27b0",
    };

    const offColor = "#f5f5f5";

    statusCard.style.backgroundColor = nextState ? onColors[type] : offColor;
  }

  updateStatusSectionBackground();
}

function updateStatusSectionBackground() {
  const section = document.getElementById("statusSection");
  if (!section) return;
  section.style.backgroundColor = lightOn ? "#e0ffe0" : "#ffffff";
}

document.getElementById("lightBtn").onclick = () =>
  changeState(lightOn, "light");
document.getElementById("waterBtn").onclick = () =>
  changeState(waterOn, "water");
document.getElementById("feedBtn").onclick = () => changeState(feedOn, "feed");
document.getElementById("cleanBtn").onclick = () =>
  changeState(cleanOn, "clean");

async function getRTCTime() {
  try {
    const res = await fetch("/api/time");
    const data = await res.json();
    console.log("RTC Time fetched:", data.time);
    return data.time;
  } catch (err) {
    console.error("RTC fetch error:", err);
    return null;
  }
}

function timeToMinutes(timeStr) {
  if (!timeStr) return -1;

  // Handle both "HH:MM" format and time input value format
  const timeParts = timeStr.includes(":")
    ? timeStr.split(":")
    : [timeStr.substr(0, 2), timeStr.substr(2, 2)];
  const hour = parseInt(timeParts[0], 10);
  const minute = parseInt(timeParts[1], 10);

  if (isNaN(hour)) return -1;
  if (isNaN(minute)) return hour * 60;

  return hour * 60 + minute;
}

async function checkScheduledTasks() {
  const rtcTime = await getRTCTime();
  if (!rtcTime) return;

  const currentMinutes = timeToMinutes(rtcTime);
  if (currentMinutes === -1 || currentMinutes === lastCheckedMinute) return;

  lastCheckedMinute = currentMinutes;
  console.log(`Checking schedules at ${rtcTime} (${currentMinutes} minutes)`);

  const checkAndToggle = (type, onTimeId, offTimeId) => {
    const onTime = document.getElementById(onTimeId)?.value;
    const offTime = document.getElementById(offTimeId)?.value;

    const onMinutes = timeToMinutes(onTime);
    const offMinutes = timeToMinutes(offTime);

    const currentState =
      type === "light"
        ? lightOn
        : type === "water"
        ? waterOn
        : type === "feed"
        ? feedOn
        : cleanOn;

    if (onMinutes === currentMinutes && !currentState) {
      console.log(`Auto ON triggered for ${type} at ${onTime}`);
      changeState(false, type);
    } else if (offMinutes === currentMinutes && currentState) {
      console.log(`Auto OFF triggered for ${type} at ${offTime}`);
      changeState(true, type);
    }
  };

  checkAndToggle("light", "lightOnTime", "lightOffTime");
  checkAndToggle("water", "waterOnTime", "waterOffTime");
  checkAndToggle("feed", "feedStartTime", "feedStopTime");
  checkAndToggle("clean", "cleanStartTime", "cleanStopTime");
}

// Check schedules every 10 seconds
setInterval(checkScheduledTasks, 10000);

function toggleEdit(element) {
  const type = element.getAttribute("data-type");

  const onTimeInput =
    document.getElementById(`${type}OnTime`) ||
    document.getElementById(`${type}StartTime`);
  const offTimeInput =
    document.getElementById(`${type}OffTime`) ||
    document.getElementById(`${type}StopTime`);

  if (!onTimeInput || !offTimeInput) return;

  const isDisabled = onTimeInput.disabled;

  onTimeInput.disabled = !isDisabled;
  offTimeInput.disabled = !isDisabled;

  const highlightColor = "#fff9c4";
  const normalColor = "";

  onTimeInput.style.backgroundColor = !isDisabled
    ? normalColor
    : highlightColor;
  offTimeInput.style.backgroundColor = !isDisabled
    ? normalColor
    : highlightColor;

  const textElement = element.querySelector("p");
  if (textElement) textElement.textContent = isDisabled ? "Save" : "Edit";
}
