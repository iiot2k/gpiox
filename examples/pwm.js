/*
 * example generate pwm on output, input selects duty cycle
 *
 * run:
 * > node pwm.js
 *
 * pwm.js
 *
 */

"use strict";

const gpiox = require("../gpiox");

const INPUT_PIN = 21;
const OUTPUT_PIN = 20;
const DEBOUNCE_US = 1000; // us
const PWM_FREQ = 200; // Hz
const PWM_DUTYC_1 = 10; // %
const PWM_DUTYC_2 = 25; // %
const PWM_DUTYC_3 = 75; // %

console.log("*** node.js pwm example ***");
console.log("pwm output is pin gpio", OUTPUT_PIN);
console.log("input pin", INPUT_PIN, "switches duty cycle");
console.log("stop program with Ctrl+C");

gpiox.init_pwm(OUTPUT_PIN, gpiox.GPIO_MODE_PWM, PWM_FREQ, PWM_DUTYC_1);

gpiox.watch_gpio(INPUT_PIN, gpiox.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpiox.GPIO_EDGE_BOTH,
    (state, edge, pin) => {
        if (state)
            gpiox.set_pwm(OUTPUT_PIN, PWM_FREQ, PWM_DUTYC_2);
        else
            gpiox.set_pwm(OUTPUT_PIN, PWM_FREQ, PWM_DUTYC_3);
});

process.on('SIGINT', () => {
    gpiox.deinit_gpio(OUTPUT_PIN);
    gpiox.deinit_gpio(INPUT_PIN);
    console.log(" -> program stopped");
    process.exit();
});