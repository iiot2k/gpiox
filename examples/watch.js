"use strict";

const gpio = require("../gpiox");

const INPUT_PIN1 = 21;
const INPUT_PIN2 = 20;
const INPUT_PIN3 = 16;
const INPUT_PIN4 = 12;
const INPUT_PIN5 = 7;
const INPUT_PIN6 = 8;
const INPUT_PIN7 = 25;
const INPUT_PIN8 = 24;
const INPUT_PIN9 = 23;
const DEBOUNCE_US = 1000; // us

// init watch INPUT_PIN1
gpio.watch_gpio(INPUT_PIN1, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_BOTH,
    (state, edge) => {
        console.log("pin", INPUT_PIN1, "state", state, "edge", edge);
});

// init watch INPUT_PIN2
gpio.watch_gpio(INPUT_PIN2, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_RISING,
    (state, edge) => {
        console.log("pin", INPUT_PIN2, "state", state, "edge", edge);
});

// init watch INPUT_PIN3
gpio.watch_gpio(INPUT_PIN3, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_FALLING,
    (state, edge) => {
        console.log("pin", INPUT_PIN3, "state", state, "edge", edge);
});

// init watch INPUT_PIN4
gpio.watch_gpio(INPUT_PIN4, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_BOTH,
    (state, edge) => {
        console.log("pin", INPUT_PIN4, "state", state, "edge", edge);
});

// init watch INPUT_PIN5
gpio.watch_gpio(INPUT_PIN5, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_BOTH,
    (state, edge) => {
        console.log("pin", INPUT_PIN5, "state", state, "edge", edge);
});

// init watch INPUT_PIN6
gpio.watch_gpio(INPUT_PIN6, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_BOTH,
    (state, edge) => {
        console.log("pin", INPUT_PIN6, "state", state, "edge", edge);
});

// init watch INPUT_PIN7
gpio.watch_gpio(INPUT_PIN7, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_BOTH,
    (state, edge) => {
        console.log("pin", INPUT_PIN7, "state", state, "edge", edge);
});

// init watch INPUT_PIN8
gpio.watch_gpio(INPUT_PIN8, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_BOTH,
    (state, edge) => {
        console.log("pin", INPUT_PIN8, "state", state, "edge", edge);
});

// init watch INPUT_PIN9
gpio.watch_gpio(INPUT_PIN9, gpio.GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpio.GPIO_EDGE_BOTH,
    (state, edge) => {
        console.log("pin", INPUT_PIN9, "state", state, "edge", edge);
});

console.log("*** watch example ***");
console.log("stop program with Ctrl+C");

// handle Ctrl+C
process.on('SIGINT', () => {
    gpio.deinit_gpio(INPUT_PIN1);
    gpio.deinit_gpio(INPUT_PIN2);
    gpio.deinit_gpio(INPUT_PIN3);
    gpio.deinit_gpio(INPUT_PIN4);
    gpio.deinit_gpio(INPUT_PIN5);
    gpio.deinit_gpio(INPUT_PIN6);
    gpio.deinit_gpio(INPUT_PIN7);
    gpio.deinit_gpio(INPUT_PIN8);
    gpio.deinit_gpio(INPUT_PIN9);
    console.log(" -> program stopped");
    process.exit();
});