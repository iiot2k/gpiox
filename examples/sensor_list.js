/*
 * example list all sensors
 *
 * run:
 * > node sensor_list.js
 *
 * sensor_list.js
 *
 */

"use strict";

const gpiox = require("../gpiox");

const SENSOR_PIN = 21;

console.log("*** node.js sensor list example***");
console.log("sensors are connected to pin", SENSOR_PIN);

gpiox.init_sensor(SENSOR_PIN, gpiox.RES_SENSOR_9);

gpiox.scan_sensor_sync(SENSOR_PIN);
    
var sensor_list = gpiox.list_sensor(SENSOR_PIN);

sensor_list.forEach((sensor) => {
    console.log(sensor);
});
