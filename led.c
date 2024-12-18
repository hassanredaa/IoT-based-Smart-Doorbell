#include "led.h"
#include "pico/stdlib.h"

void led_init(uint16_t pin) {
    // Initialize the LED pin as output
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 0); // Ensure the LED is off initially
}

void led_on(uint16_t pin) {
    // Set the pin high to turn on the LED
    gpio_put(pin, 1);
}

void led_off(uint16_t pin) {
    // Set the pin low to turn off the LED
    gpio_put(pin, 0);
}

void led_toggle(uint16_t pin) {
    // Toggle the state of the LED
    gpio_put(pin, !gpio_get(pin));
}
