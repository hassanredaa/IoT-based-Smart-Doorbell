#include "lcd.h"
#include "pico/stdlib.h"

// Pin configuration
static uint16_t rs_pin, en_pin;
static uint16_t data_pins[4];

// Helper function: Pulse the enable pin
static void lcd_pulse_enable(void) {
    gpio_put(en_pin, 1);
    sleep_us(1); // Enable pulse >450ns
    gpio_put(en_pin, 0);
    sleep_us(40); // Commands need >37us to settle
}

// Send 4 bits to the LCD
static void lcd_send_nibble(uint8_t nibble) {
    for (int i = 0; i < 4; i++) {
        gpio_put(data_pins[i], (nibble >> i) & 0x01);
    }
    lcd_pulse_enable();
}

// Send a byte to the LCD
static void lcd_send_byte(uint8_t value, bool is_data) {
    gpio_put(rs_pin, is_data); // RS: 1 for data, 0 for command

    // Send upper nibble first
    lcd_send_nibble(value >> 4);
    // Send lower nibble
    lcd_send_nibble(value & 0x0F);
}

// LCD API functions
void lcd_init(uint16_t rs, uint16_t en, uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7) {
    rs_pin = rs;
    en_pin = en;
    data_pins[0] = d4;
    data_pins[1] = d5;
    data_pins[2] = d6;
    data_pins[3] = d7;

    // Configure pins as outputs
    gpio_init(rs_pin);
    gpio_init(en_pin);
    gpio_set_dir(rs_pin, GPIO_OUT);
    gpio_set_dir(en_pin, GPIO_OUT);

    for (int i = 0; i < 4; i++) {
        gpio_init(data_pins[i]);
        gpio_set_dir(data_pins[i], GPIO_OUT);
    }

    // Initial delay for power-on
    sleep_ms(50);

    // Initialization sequence for 4-bit mode
    lcd_send_nibble(0x03); // Function set in 8-bit mode
    sleep_ms(5);
    lcd_send_nibble(0x03);
    sleep_us(150);
    lcd_send_nibble(0x03);
    sleep_us(150);
    lcd_send_nibble(0x02); // Switch to 4-bit mode

    // Function set: 4-bit mode, 2-line display, 5x8 dots
    lcd_send_byte(0x28, false);

    // Display control: Display on, cursor off, blink off
    lcd_send_byte(0x0C, false);

    // Clear display
    lcd_clear();

    // Entry mode set: Increment cursor, no display shift
    lcd_send_byte(0x06, false);
}

void lcd_clear(void) {
    lcd_send_byte(0x01, false); // Clear display command
    sleep_ms(2); // Clearing takes >1.52ms
}

void lcd_set_cursor(uint16_t row, uint16_t col) {
    uint8_t address = col + (row == 0 ? 0x00 : 0x40);
    lcd_send_byte(0x80 | address, false); // Set DDRAM address command
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_write_char(*str++);
    }
}

void lcd_write_char(char c) {
    lcd_send_byte(c, true); // Send character as data
}
