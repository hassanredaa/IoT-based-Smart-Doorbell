#ifndef LED_H
#define LED_H

#include <stdint.h>

// Function prototypes
void led_init(uint16_t pin);         // Initialize an LED on a specific pin
void led_on(uint16_t pin);           // Turn on the LED on the specified pin
void led_off(uint16_t pin);          // Turn off the LED on the specified pin
void led_toggle(uint16_t pin);       // Toggle the LED on the specified pin

#endif // LED_H
