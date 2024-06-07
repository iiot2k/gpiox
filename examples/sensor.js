/*
 * example list and reads all sensors
 *
 * run:
 * > node sensor.js
 *
 * sensor.js
 *
 */

"use strict";

const gpiox = require("../gpiox");

const SENSOR_PIN = 21;

console.log("*** node.js sensor example***");
console.log("sensors are connected to pin", SENSOR_PIN);

gpiox.init_sensor(SENSOR_PIN, gpiox.RES_SENSOR_11);

gpiox.scan_sensor_sync(SENSOR_PIN);
    
var sensor_list = gpiox.list_sensor(SENSOR_PIN);
var sensor_data = gpiox.read_sensor_sync(SENSOR_PIN, false);

for(var i=0; i < sensor_data.length; i++)
    console.log(sensor_list[i], sensor_data[i], "°C");
