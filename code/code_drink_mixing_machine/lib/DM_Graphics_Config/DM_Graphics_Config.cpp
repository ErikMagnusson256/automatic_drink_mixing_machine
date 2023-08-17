#include "DM_Graphics_Config.h"

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