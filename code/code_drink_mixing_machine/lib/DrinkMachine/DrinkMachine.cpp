#include "DrinkMachine.h"


DrinkMachine::DrinkMachine() 
        : startup_screen(),
          main_screen(),
          pour_drink_screen()
{
    
}

bool DrinkMachine::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms) // Renders state of DrinkMachien
{
    if(startup_screen.IsSetupFinnished() == false)
    {
        startup_screen.Render(screen, dt_ms);
    }
    else if (!main_screen.IsReadyToPour())
    {
        main_screen.Render(screen, dt_ms);
    }
    else if (main_screen.IsReadyToPour())
    {
        /* Render pour glass window */
        pour_drink_screen.Render(screen, dt_ms);
    }
    else
    {
        

    }

    return true;
}
bool DrinkMachine::Update(const InputVector &user_input, uint32_t  dt_ms)
{

    if(startup_screen.IsSetupFinnished() == false)
    {
        startup_screen.Update(user_input, dt_ms);
    }
    else if (!main_screen.IsReadyToPour())
    {
        main_screen.Update(user_input, dt_ms);
    }
    else if (main_screen.IsReadyToPour())
    {
        /* Update logic pour glass window */
        pour_drink_screen.Update(user_input, dt_ms);
    }
}