#pragma once
#ifndef __DM_GRAPHICS_CONFIG__
#define __DM_GRAPHICS_CONFIG__

/*
Header file containing configuration settings, defined colours
and useful helper functions related to the MCUFRIEND_kbv graphics library
*/


/* Include Headers */
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include "Arduino.h"

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

/* Helper Function Defintitions */
void center_text_box(MCUFRIEND_kbv *screen, int center_x, int center_y, String text, int16_t text_colour, int16_t outline_colour, int16_t infill_colour, int* width, int* height);
void lcd_background(MCUFRIEND_kbv *screen);






#endif