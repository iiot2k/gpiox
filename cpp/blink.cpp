/*
 * example blinks output, blink period is switch with input
 *
 * build:
 * > make
 *
 * run:
 * > ./blink
 *
 * blink.cpp
 *
 */

#include <stdio.h>
#include <csignal>
#include <cstdlib>

#include "gpiox_lib.h"

#define INPUT_PIN  21
#define OUTPUT_PIN 20

#define DEBOUNCE_US 10000 // us
#define BLINK_TIME_MS_1 500 // ms
#define BLINK_TIME_MS_2 2500 // ms

// signal handler
void onCtrlC(int signum)
{
    gpiox::deinit_gpio(INPUT_PIN);
    gpiox::deinit_gpio(OUTPUT_PIN);

    puts("\nprogram stopped");
    exit(signum);
}

// watch callback
void watch_callback(uint32_t state, uint32_t edge, uint32_t pin)
{
    if (state)
        gpiox::blink_gpio(OUTPUT_PIN, BLINK_TIME_MS_1);
    else
        gpiox::blink_gpio(OUTPUT_PIN, BLINK_TIME_MS_2);
}

int main()
{
    signal(SIGINT, onCtrlC);

    puts("*** blink C++ example ***");
    printf("output pin is gpio%d\n", OUTPUT_PIN);
    printf("input pin gpio%d changes blink period\n", INPUT_PIN);
    puts("stop program with Ctrl+C");

    gpiox::init_gpio(OUTPUT_PIN, gpiox::GPIO_MODE_OUTPUT, 0);
    gpiox::blink_gpio(OUTPUT_PIN, BLINK_TIME_MS_1);

    watch_gpio(INPUT_PIN, gpiox::GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpiox::GPIO_EDGE_BOTH, watch_callback);

    while(1)
    {

    }
}

