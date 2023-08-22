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
        main_screen.Render(screen, dt_ms);

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
        main_screen.Update(user_input, dt_ms);
    }
}