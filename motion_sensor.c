#include "motion_sensor.h"
#include "pico/stdlib.h"

static uint motion_sensor_pin;

void motion_sensor_init(uint16_t sensor_pin) {
    motion_sensor_pin = sensor_pin;

    gpio_init(motion_sensor_pin);
    gpio_set_dir(motion_sensor_pin, GPIO_IN);
}

bool motion_sensor_detected(void) {
    return gpio_get(motion_sensor_pin);
}
