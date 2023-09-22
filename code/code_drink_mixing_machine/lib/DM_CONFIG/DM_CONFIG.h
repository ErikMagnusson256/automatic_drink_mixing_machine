#pragma once
#ifndef __DM_CONFIG__
#define __DM_CONFIG__

#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/*

    PIN CONFIGURATION

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

/*

    EEPROM CONFIG

*/

/* EEPROM memory adress(es) for Drink Machine (0 - 1023) */
/* Used to store key information of drink machine state between power cycles in non volatile memory */
#define EEPROM_ADR_NR_DRINKS 2 //integer variable -> 16 bit -> 2 bytes of data
#define EEPROM_ADR_NR_CL 8 //float variable -> 32 bit -> 4 bytes of data

/*

    GRAPHICS CONFIGURATION

*/

/* 16 Bit HEX Colour definitions according to RGB 565 standard see https://rgbcolorpicker.com/565  */
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define DARK_GREEN 0x33A6
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x7BEF
#define DARK_GREY 0x632C
#define ORANGE  0xD586
#define DARK_ORANGE 0xDAA4

/* Screen Size Parameters */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480


 void lcd_background(MCUFRIEND_kbv *screen);

#endif