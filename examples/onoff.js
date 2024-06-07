/*
 * example turns output on and after 3s off
 *
* run:
 * > node onoff.js
 *
 * onoff.js
 *
 */

"use strict";

const gpiox = require("../gpiox");

const OUTPUT_PIN = 20;

console.log("*** on/off node.js example ***");
console.log("output pin is gpio", OUTPUT_PIN);
console.log("led turns after 3000 ms off");

gpiox.init_gpio(OUTPUT_PIN, gpiox.GPIO_MODE_OUTPUT, 1);

setTimeout(() => {
    gpiox.set_gpio(OUTPUT_PIN, 0);
    gpiox.deinit_gpio(OUTPUT_PIN);
}, 3000);

