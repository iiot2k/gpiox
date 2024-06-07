/*
 * example creates a counter with reset and output pin and shows changes
 *
 * build:
 * > make
 *
 * run:
 * > ./counter
 *
 * counter.cpp
 *
 */

#include <stdio.h>
#include <csignal>
#include <cstdlib>

#include "gpiox_lib.h"

#define INPUT_PIN  21
#define OUTPUT_PIN 20

#define COUNTER_PIN 21
#define RESET_PIN 16
#define OUTPUT_PIN 20
#define DEBOUNCE_US 1000 // us
#define COUNTER_HIGH 20

// signal handler
void onCtrlC(int signum)
{
    gpiox::deinit_gpio(COUNTER_PIN);
    gpiox::deinit_gpio(RESET_PIN);
    gpiox::deinit_gpio(OUTPUT_PIN);

    puts("\nprogram stopped");
    exit(signum);
}

void counter_callback(uint32_t counter, bool onlimit, uint32_t mode, uint32_t high, uint32_t pin)
{
	if (onlimit)
		printf("counter on limit: %d high: %d mode: %s\n", counter, high, (mode == gpiox::C_UP) ? "up" : "down");
	else
		printf("counter: %d\n", counter);
}

int main()
{
    signal(SIGINT, onCtrlC);

    puts("*** counter C++ example ***");
    printf("counts if pin%d is connected to ground\n", COUNTER_PIN);
    printf("counter is reset if pin%d is connected to ground\n", RESET_PIN);
    printf("output pin%d is true if counter set to %d\n", OUTPUT_PIN, COUNTER_HIGH);
    puts("stop program with Ctrl+C");

    gpiox::init_counter_pin(COUNTER_PIN, gpiox::GPIO_MODE_COUNTER_PULLUP, DEBOUNCE_US, gpiox::GPIO_EDGE_RISING);
    gpiox::init_counter_reset_pin(COUNTER_PIN, RESET_PIN, gpiox::GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpiox::GPIO_EDGE_RISING);
    gpiox::init_counter_output_pin(COUNTER_PIN, OUTPUT_PIN, gpiox::GPIO_MODE_OUTPUT);

    gpiox::init_counter(COUNTER_PIN, COUNTER_HIGH, gpiox::C_UP, counter_callback);

    while(1)
    {

    }
}

