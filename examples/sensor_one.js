/*
 * example reads one sensor
 *
 * run:
 * > node sensor_one.js
 *
 * sensor_one.js
 *
 */

"use strict";

const gpiox = require("../gpiox");

const SENSOR_PIN = 21;
const SENSOR_ID = "28-020198430BF2"; // change id for your sensor

console.log("*** node.js one sensor example***");
console.log("sensors are connected to pin", SENSOR_PIN);
console.log("change SENSOR_ID for your sensor");

gpiox.init_sensor(SENSOR_PIN, gpiox.RES_SENSOR_11);

var sensor_data = gpiox.read_one_sensor_sync(SENSOR_PIN, SENSOR_ID, false);

console.log(SENSOR_ID, sensor_data, "°C");
