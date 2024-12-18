#include "button.h"
#include "pico/stdlib.h"
#include <stdbool.h>

static uint16_t button_pin;

void button_init(uint16_t pin) {
    button_pin = pin;

    // Configure the button pin as input with a pull-up resistor
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_pull_up(button_pin);
}

bool button_is_pressed(void) {
    return gpio_get(button_pin) == 0;
}
