#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

// Function prototypes
void button_init(uint16_t button_pin);    // Initialize the button
bool button_is_pressed(void);         // Check if the button is pressed

#endif // BUTTON_H
