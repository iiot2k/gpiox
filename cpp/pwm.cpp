/*
 * example generate pwm on output, input selects duty cycle
 *
 * build:
 * > make
 *
 * run:
 * > ./pwm
 *
 * pwm.cpp
 *
 */

#include <stdio.h>
#include <csignal>
#include <cstdlib>

#include "gpiox_lib.h"

#define INPUT_PIN 21
#define PWM_PIN   20

#define DEBOUNCE_US 10000 // us
#define BLINK_TIME_MS_1 500 // ms
#define BLINK_TIME_MS_2 2500 // ms

#define PWM_FREQ 200 // Hz
#define PWM_DUTYC_1 10 // %
#define PWM_DUTYC_2 25 // %
#define PWM_DUTYC_3 75 // %

// signal handler
void onCtrlC(int signum)
{
    gpiox::deinit_gpio(PWM_PIN);
    gpiox::deinit_gpio(INPUT_PIN);

    puts("\nprogram stopped");
    exit(signum);
}

// watch callback
void watch_callback(uint32_t state, uint32_t edge, uint32_t pin)
{
    if (state)
        gpiox::set_pwm(PWM_PIN, PWM_FREQ, PWM_DUTYC_2);
    else
        gpiox::set_pwm(PWM_PIN, PWM_FREQ, PWM_DUTYC_3);
}

int main()
{
    signal(SIGINT, onCtrlC);

    puts("*** pwm C++ example ***");
    printf("pwm output pin is gpio%d\n", PWM_PIN);
    printf("input pin gpio%d switches duty cycle\n", INPUT_PIN);
    puts("stop program with Ctrl+C");

    gpiox::init_pwm(PWM_PIN, gpiox::GPIO_MODE_PWM, PWM_FREQ, PWM_DUTYC_1);
    gpiox::watch_gpio(INPUT_PIN, gpiox::GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US, gpiox::GPIO_EDGE_BOTH, watch_callback);

    while(1)
    {

    }
}

