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

        if(main_screen.IsReadyToPour())
        {
            pour_drink_screen.ResetPourDrinkScreen();

            float amount1 = -1;
            float amount2 = -1;
            float amount3 = -1;
            float amount4 = -1;
            main_screen.GetDrinkAmounts(&amount1, &amount2, &amount3, &amount4);
            pour_drink_screen.InsertPumpAmounts(amount1, amount2, amount3, amount4);
        }
    }
    else if (!pour_drink_screen.IsDone() && main_screen.IsReadyToPour() )
    {
        /* Update logic pour glass window */
        pour_drink_screen.Update(user_input, dt_ms);

        // If pour drink screen has finnished, reset to main screen
        if (pour_drink_screen.IsDone())
        {
            main_screen.ResetReadyToPour();
        }
    }
}