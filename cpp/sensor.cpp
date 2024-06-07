/*
 * example list and reads all sensors
 *
 * build:
 * > make
 *
  * run:
 * > ./sensor
 *
 * sensor.cpp
 *
 */

#include <stdio.h>

#include "gpiox_lib.h"

#define SENSOR_PIN 21

int main()
{
    puts("*** c++ sensor example***");
    printf("sensors are connected to gpio%d\n", SENSOR_PIN);

    gpiox::init_sensor(SENSOR_PIN, gpiox::RES_SENSOR_11);
    gpiox::scan_sensor(SENSOR_PIN);

    vector<string> sensor_list;
    vector<double> sensor_data;

    gpiox::list_sensor(SENSOR_PIN, sensor_list);
    gpiox::read_sensor(SENSOR_PIN, false, sensor_data);

    for(uint32_t i=0; i < sensor_list.size(); i++)
    	printf("%s %.1f°C\n", sensor_list[i].c_str(), sensor_data[i]);

	return 0;
}



