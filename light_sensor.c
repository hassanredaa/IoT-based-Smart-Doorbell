#include "light_sensor.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

static uint light_sensor_adc_channel; 

void light_sensor_init(uint16_t sensor_pin) {
    adc_init();
    if (sensor_pin >= 26 && sensor_pin <= 29) {
        light_sensor_adc_channel = sensor_pin - 26; 
        adc_gpio_init(sensor_pin); 
    } else {
        while (true) {
        }
    }
}
uint16_t light_sensor_read(void) {
    adc_select_input(light_sensor_adc_channel); 
    return adc_read(); 
}
