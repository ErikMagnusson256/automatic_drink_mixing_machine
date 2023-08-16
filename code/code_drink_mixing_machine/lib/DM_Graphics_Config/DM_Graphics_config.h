#ifndef __DM_GRAPHICS_CONFIG__
#define __DM_GRAPHICS_CONFIG__

/*
Header file containing configuration settings, defined colours
and useful helper functions related to the MCUFRIEND_kbv graphics library
*/


/* Include Headers */
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/* 16 Bit HEX Colour definitions according to RGB 565 standard see https://rgbcolorpicker.com/565  */
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x7BEF

/* Screen Size Parameters */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

/* Helper Function Defintitions */
void center_text_box(MCUFRIEND_kbv *screen, int center_x, int center_y, String text, int16_t text_colour, int16_t outline_colour, int16_t infill_colour, int* width, int* height);
void lcd_background(MCUFRIEND_kbv *screen);

/* Helper Function Implementations */
void center_text_box(MCUFRIEND_kbv *screen, int center_x, int center_y, String text, int16_t text_colour, int16_t outline_colour, int16_t infill_colour, int* width, int* height)
{
    int cursor_x = 0, cursor_y = 0;

    int16_t x0, y0;
    uint16_t w, h;
   
    screen->getTextBounds(text.c_str(), cursor_x, cursor_y, &x0, &y0, &w, &h);
    
    float outline_scale = 1.25;
    int radius = 5;
    screen->fillRoundRect((center_x - w/2), (center_y - h/2), w*outline_scale, h*outline_scale, radius, outline_colour); //background box
    screen->fillRoundRect((center_x - w/2), (center_y - h/2), w, h, radius, infill_colour); //foreground box
    screen->setCursor(center_x - w/2, center_y - h/2);
    screen->setTextColor(text_colour);
    screen->println(text);

}

void lcd_background(MCUFRIEND_kbv *screen)
{
    screen->fillScreen(WHITE);

    screen->fillRoundRect(20, 5, SCREEN_WIDTH - 2 *20, 60, 5, GREY);
    screen->fillRoundRect(25, 10, SCREEN_WIDTH - 2*25, 50, 5, BLACK);
    screen->setCursor(65, 23);
    screen->setTextSize(3);
    screen->setTextColor(WHITE);
    screen->print("Groggbot 3!!");
}
#endif