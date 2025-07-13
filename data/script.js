"use strict";
let lightOn = false;

const ws = new WebSocket(`ws://${location.host}/ws`);

function changeState(state) {
  state ? ws.send("OFF") : ws.send("ON");

  document.getElementById("lightStatus").innerHTML = state ? "off" : "on";

  document.getElementById("lightBtn").style.backgroundColor = state
    ? "#5f3737"
    : "#72a8ce";

  lightOn = state ? false : true;

  document.getElementById("lightStatusText").innerHTML = state ? "OFF" : "ON";
  document.getElementById("lightStatusContainer").style.backgroundImage = state
    ? "linear-gradient(to bottom right, #e1eafb, white)"
    : "linear-gradient(to bottom right,#72a8ce, white";
}

document.getElementById("lightBtn").onclick = () => {
  if (lightOn) {
    changeState(lightOn);
  } else {
    changeState(lightOn);
  }
};

// Recieving from ultrasonic sensor
ws.onmessage = (even) => {
  document.getElementById("waterLevel").innerHTML = even.data + "%";
};
