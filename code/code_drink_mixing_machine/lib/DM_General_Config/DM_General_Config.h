#ifndef __DM_GENERAL_CONFIG__
#define __DM_GENERAL_CONFIG__


/*
Configuration file for Drinking Machine

I/O Pins, Constants, etc
*/

/* Display Pins */
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

/* Input Pins - Arduino Mega 2560 */
#define JOYSTICK_X_PIN A8
#define JOYSTICK_Y_PIN A9
#define JOYSTICK_BUTTON_PIN 14
#define BUTTON_OK_PIN 15
#define BUTTON_RETURN_PIN 16
#define RANDOMIZER_PIN A12

#define BUTTON_DEBOUNCE_TIME_MS 100

/* Joystick analog limits */
#define JOYSTICK_X_DECREASE_TRIGGER_LIMIT 400
#define JOYSTICK_X_INCREASE_TRIGGER_LIMIT 600
#define JOYSTICK_Y_DECREASE_TRIGGER_LIMIT 400
#define JOYSTICK_Y_INCREASE_TRIGGER_LIMIT 600

/* EEPROM memory adress(es) for Drink Machine (0 - 1023) */
/* Used to store key information of drink machine state between power cycles in non volatile memory */
#define EEPROM_ADR_NR_DRINKS 2 //integer variable -> 16 bit -> 2 bytes of data
#define EEPROM_ADR_NR_CL 8 //float variable -> 32 bit -> 4 bytes of data


#endif