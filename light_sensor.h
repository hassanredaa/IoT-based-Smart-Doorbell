#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <stdbool.h>
#include <stdint.h>

// Function prototypes
void light_sensor_init(uint16_t sensor_pin); // Initialize the light sensor
uint16_t light_sensor_read(void);        // Check if light is detected

#endif // LIGHT_SENSOR_H
