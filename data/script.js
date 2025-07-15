"use strict";

let lightOn = false;
let waterOn = false;
let feedOn = false;
let cleanOn = false;

const ws = new WebSocket(`ws://${location.host}/ws`);

function changeState(state, type) {
  const nextState = !state;

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
    return data.time; // "HH:MM:SS"
  } catch (err) {
    console.error("RTC error:", err);
    return null;
  }
}

function timeToMinutes(timeStr) {
  const [hour, minute] = timeStr.split(":").map(Number);
  return hour * 60 + minute;
}

let lastCheckedMinute = -1;

setInterval(async () => {
  const rtcTime = await getRTCTime();
  if (!rtcTime) return;

  const [hour, minute] = rtcTime.split(":").map(Number);
  const currentMinutes = hour * 60 + minute;

  if (currentMinutes === lastCheckedMinute) return;
  lastCheckedMinute = currentMinutes;

  // Actions
  if (
    timeToMinutes(document.getElementById("lightOnTime")?.value) ===
    currentMinutes
  )
    changeState(false, "light");
  if (
    timeToMinutes(document.getElementById("lightOffTime")?.value) ===
    currentMinutes
  )
    changeState(true, "light");

  if (
    timeToMinutes(document.getElementById("feedStartTime")?.value) ===
    currentMinutes
  )
    changeState(false, "feed");
  if (
    timeToMinutes(document.getElementById("feedStopTime")?.value) ===
    currentMinutes
  )
    changeState(true, "feed");

  if (
    timeToMinutes(document.getElementById("waterOnTime")?.value) ===
    currentMinutes
  )
    changeState(false, "water");
  if (
    timeToMinutes(document.getElementById("waterOffTime")?.value) ===
    currentMinutes
  )
    changeState(true, "water");

  if (
    timeToMinutes(document.getElementById("cleanStartTime")?.value) ===
    currentMinutes
  )
    changeState(false, "clean");
  if (
    timeToMinutes(document.getElementById("cleanStopTime")?.value) ===
    currentMinutes
  )
    changeState(true, "clean");
}, 10000);
