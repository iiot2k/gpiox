/*
 * example list all sensors
 *
 * build:
 * > make
 *
  * run:
 * > ./sensor_list
 *
 * sensor_list.cpp
 *
 */

#include <stdio.h>

#include "gpiox_lib.h"

#define SENSOR_PIN 21

int main()
{
    puts("*** c++ sensor list example***");
    printf("sensors are connected to gpio%d\n", SENSOR_PIN);

    gpiox::init_sensor(SENSOR_PIN, gpiox::RES_SENSOR_9);
    gpiox::scan_sensor(SENSOR_PIN);

    vector<string> sensor_list;

    gpiox::list_sensor(SENSOR_PIN, sensor_list);

    for(string id: sensor_list)
    	puts(id.c_str());

	return 0;
}



