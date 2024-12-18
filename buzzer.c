#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "buzzer.h"

// Static variables for tracking state
static uint buzzer_slice_num;  // PWM slice number
static uint buzzer_channel;    // PWM channel
static uint buzzer_pin;        // Pin used for the buzzer

void buzzer_init(uint16_t pin) {
    buzzer_pin = pin;

    // Initialize the GPIO pin for PWM
    gpio_set_function(buzzer_pin, GPIO_FUNC_PWM);

    // Get the PWM slice and channel for the specified pin
    buzzer_slice_num = pwm_gpio_to_slice_num(buzzer_pin);
    buzzer_channel = pwm_gpio_to_channel(buzzer_pin);

    // Disable the PWM output initially
    buzzer_off();
}

void buzzer_set_frequency(uint16_t frequency) {
    // Get the system clock frequency
    uint32_t clock_freq = clock_get_hz(clk_sys);

    // Calculate the PWM frequency divider and top value
    uint16_t top = clock_freq / frequency - 1;

    // Set the PWM configuration
    pwm_set_wrap(buzzer_slice_num, top);         // Set top value
    pwm_set_chan_level(buzzer_slice_num, buzzer_channel, top / 2); // 50% duty cycle
}

void buzzer_on(void) {
    // Enable the PWM output
    pwm_set_enabled(buzzer_slice_num, true);
}

void buzzer_off(void) {
    // Disable the PWM output
    pwm_set_enabled(buzzer_slice_num, false);
}
