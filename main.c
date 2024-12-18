#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "lcd.h"
#include "led.h"
#include "light_sensor.h"
#include "motion_sensor.h"
#include "button.h"
#include "buzzer.h"



#define LCD_RS_PIN 19  // GPIO pin for LCD RS
#define LCD_EN_PIN 18  // GPIO pin for LCD D3
#define LCD_D4_PIN 17  // GPIO pin for LCD D4
#define LCD_D5_PIN 16 // GPIO pin for LCD D5
#define LCD_D6_PIN 15 // GPIO pin for LCD D6
#define LCD_D7_PIN 25 // GPIO pin for LCD D7

#define BUTTON_PIN 5
#define BUZZER_PIN 4


#define MOTION_SENSOR_PIN 21 // GPIO pin for the motion sensor (PIR)
#define LED1_PIN 20          // GPIO pin for the LED
#define LIGHT_SENSOR_PIN 26  // GPIO pin for the light sensor (digital)

void lcdTask(void *pvParameters)
{
    while (1)
    {
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("AMIRAA");
        lcd_set_cursor(1, 0);
        lcd_print("Success!");
        vTaskDelay(pdMS_TO_TICKS(1000));  // Add a 1-second delay
    }
}

void motionTask(void *pvParameters)
{
    while (1)
    {
        bool motion_detected = motion_sensor_detected();

        lcd_clear();
        if (motion_detected)
        {
            lcd_print("Welcome");
        }
        else
        {
            lcd_print("No Motion");
        }
        lcd_set_cursor(1, 0);

        vTaskDelay(pdMS_TO_TICKS(3000)); // Delay for 500ms
    }
}

void buttonTask(void *pvParameters)
{
    while (1)
    {
        if (button_is_pressed())
        {
            buzzer_set_frequency(1000); // 1 kHz tone
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(100)); // Beep for 100ms
            buzzer_off();
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // Check button state every 100ms
    }
}

void lightTask(void *pvParameters)
{
    while (1)
    {
        // Read the light sensor
        uint16_t light_detected = light_sensor_read();

        if (light_detected > 400)
        {
            led_on(LED1_PIN);
        }
        else
        {
            led_off(LED1_PIN);
        }

        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500ms
    }
}

int main()
{
    stdio_init_all();
    led_init(LED1_PIN);
    button_init(BUTTON_PIN);
    buzzer_init(BUZZER_PIN);
    motion_sensor_init(MOTION_SENSOR_PIN);
    light_sensor_init(LIGHT_SENSOR_PIN);

    lcd_init(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
    
    xTaskCreate(buttonTask, "Button Task", 256, NULL, 1, NULL);
    xTaskCreate(lightTask, "Light Task", 256, NULL, 1, NULL);
    xTaskCreate(motionTask, "motion_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}