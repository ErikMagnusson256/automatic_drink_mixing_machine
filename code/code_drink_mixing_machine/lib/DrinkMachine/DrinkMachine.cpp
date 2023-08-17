#include "DrinkMachine.h"


DrinkMachine::DrinkMachine() // Constructor
{

}

bool DrinkMachine::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms) // Renders state of DrinkMachien
{
    if(startup_screen.IsSetupFinnished() == false)
    {
        startup_screen.Render(screen, dt_ms);
    }
    else
    {
        screen->fillScreen(WHITE);
        screen->setCursor(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        screen->setTextColor(BLACK);
        screen->setTextSize(2);
        screen->println("Successfully exited startup screen, glas size is=" + String(startup_screen.GetGlasSize()));

    }

    return true;
}
bool DrinkMachine::Update(const InputVector &user_input, uint32_t  dt_ms)
{

    if(startup_screen.IsSetupFinnished() == false)
    {
        startup_screen.Update(user_input, dt_ms);
    }
    else {
        Serial1.println("Great success!");
    }
}