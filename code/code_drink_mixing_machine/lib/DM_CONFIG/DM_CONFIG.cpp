#include "DM_CONFIG.h"


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
