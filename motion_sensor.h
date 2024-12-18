#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include <stdbool.h>
#include <stdint.h>

// Function prototypes
void motion_sensor_init(uint16_t sensor_pin); // Initialize the motion sensor
bool motion_sensor_detected(void);        // Check if motion is detected

#endif // MOTION_SENSOR_H
