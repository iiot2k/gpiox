/*
 * example creates a counter with reset and output pin and shows changes
 *
 * run:
 * > node counter.js
 *
 * counter.js
 *
 */

"use strict";

const gpiox = require("../gpiox");

const COUNTER_PIN = 21;
const RESET_PIN = 16;
const OUTPUT_PIN = 20;
const DEBOUNCE_US = 1000; // us
const COUNTER_HIGH = 20;

console.log("*** counter node.js example ***");
console.log("counts if pin", COUNTER_PIN, "is connected to ground");
console.log("counter is reset if pin", RESET_PIN, "is connected to ground");
console.log("output pin", OUTPUT_PIN, "is true if counter set to ", COUNTER_HIGH);
console.log("stop program with Ctrl+C");

// init counter pins
gpiox.init_counter_pin(COUNTER_PIN, gpiox.GPIO_MODE_COUNTER_PULLUP, DEBOUNCE_US, gpiox.GPIO_EDGE_RISING);
gpiox.init_counter_reset_pin(COUNTER_PIN, RESET_PIN, gpiox.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpiox.GPIO_EDGE_RISING);
gpiox.init_counter_output_pin(COUNTER_PIN, OUTPUT_PIN, gpiox.GPIO_MODE_OUTPUT);

// init counter
gpiox.init_counter(COUNTER_PIN, COUNTER_HIGH, gpiox.C_UP,
    (counter, on_limit, cnt_mode, counter_high, pin) => {
        if (on_limit)
            console.log("counter on limit:", counter, "high:", counter_high, "mode:", (cnt_mode == gpiox.C_UP) ? "up" : "down");
        else
            console.log("counter:", counter);
});

// handle Ctrl+C
process.on('SIGINT', () => {
    gpiox.deinit_gpio(COUNTER_PIN);
    gpiox.deinit_gpio(RESET_PIN);
    gpiox.deinit_gpio(OUTPUT_PIN);
    process.exit();
});
