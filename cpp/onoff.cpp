/*
 * example turns output on and after 3s off
 *
 * build:
 * > make
 *
  * run:
 * > ./onoff
 *
 * onoff.cpp
 *
 */

#include <stdio.h>

#include "gpiox_lib.h"

#define OUTPUT_PIN 20

void timeout_callback()
{
	gpiox::set_gpio(OUTPUT_PIN, 0);
	gpiox::deinit_gpio(OUTPUT_PIN);
}

int main()
{
    puts("*** on/off C++ example ***");
    printf("output pin is gpio%d\n", OUTPUT_PIN);
    puts("led turns after 3000 ms off");

    gpiox::init_gpio(OUTPUT_PIN, gpiox::GPIO_MODE_OUTPUT, 1);
    gpiox::set_timeout(timeout_callback, 3000);

	return 0;
}



