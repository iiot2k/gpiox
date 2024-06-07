/*
 * example blinks output, blink period is switch with input
 *
 * run:
 * > node blink.js
 *
 * blink.js
 *
 */

"use strict";

const gpiox = require("../gpiox");

const INPUT_PIN = 21;
const OUTPUT_PIN = 20;
const DEBOUNCE_US = 1000; // us
const BLINK_TIME_MS_1 = 500; // ms
const BLINK_TIME_MS_2 = 2500; // ms

console.log("*** blink node.js example ***");
console.log("output pin is gpio", OUTPUT_PIN);
console.log("input pin is gpio", INPUT_PIN, "changes blink period on change");
console.log("stop program with Ctrl+C");

gpiox.init_gpio(OUTPUT_PIN, gpiox.GPIO_MODE_OUTPUT, 0);

gpiox.watch_gpio(INPUT_PIN, gpiox.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpiox.GPIO_EDGE_BOTH, 
    (state, edge, pin)=>{
        if (state == 0)
            gpiox.blink_gpio(OUTPUT_PIN, BLINK_TIME_MS_2);
        else
            gpiox.blink_gpio(OUTPUT_PIN, BLINK_TIME_MS_1);
    }
);

gpiox.blink_gpio(OUTPUT_PIN, BLINK_TIME_MS_1);

process.on('SIGINT', () => {
    gpiox.deinit_gpio(INPUT_PIN);
    gpiox.deinit_gpio(OUTPUT_PIN);
    console.log(" -> program stopped");
    process.exit();
});