#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

// Function prototypes
void buzzer_init(uint16_t buzzer_pin);          // Initialize the buzzer on a specific pin
void buzzer_set_frequency(uint16_t frequency); // Set PWM frequency for the buzzer
void buzzer_on(void);                       // Turn the buzzer on
void buzzer_off(void);                      // Turn the buzzer off

#endif // BUZZER_H
