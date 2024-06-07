/*
 * example reads one sensor
 *
 * build:
 * > make
 *
  * run:
 * > ./sensor_one
 *
 * sensor_one.cpp
 *
 */

#include <stdio.h>

#include "gpiox_lib.h"

#define SENSOR_PIN 21
#define SENSOR_ID "28-020198430BF2" // change id for your sensor

int main()
{
    puts("*** c++ one sensor example***");
    printf("sensors are connected to gpio%d\n", SENSOR_PIN);
    puts("change SENSOR_ID for your sensor");

    gpiox::init_sensor(SENSOR_PIN, gpiox::RES_SENSOR_11);

    double temp_data;

    gpiox::read_one_sensor(SENSOR_PIN, SENSOR_ID, false, temp_data);

    printf("%s %.1f°C\n", SENSOR_ID, temp_data);

	return 0;
}



