#ifndef LCD_H
#define LCD_H

#include <stdint.h>

// Function prototypes
void lcd_init(uint16_t rs, uint16_t en, uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7);
void lcd_clear(void);
void lcd_set_cursor(uint16_t row, uint16_t col);
void lcd_print(const char *str);
void lcd_write_char(char c);

#endif // LCD_H
