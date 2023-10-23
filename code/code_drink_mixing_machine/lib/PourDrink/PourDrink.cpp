#include "PourDrink.h"

PourDrink::PourDrink() // Constructor
{
    amount1 = 0;
    amount2 = 0;
    amount3 = 0;
    amount4 = 0;  

    screen_reset = true;
    is_screen_done = false;

    screen_x_cursor = 0;
    screen_y_cursor = 0;

    empty_glass_weight = -1;
}
bool PourDrink::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{

    if(screen_reset)
    {
        lcd_background(screen);
        screen_reset = false;

        screen->setCursor(150, 200);
        screen->setTextColor(BLACK);
        screen->println("Pour drink screen!");
    }
    else 
    {

    }

    return true;
} 
bool PourDrink::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    if(!screen_reset)
    {
        // Move cursor around
        if(user_input.joystick_y < JOYSTICK_Y_DECREASE_TRIGGER_LIMIT)
        {
            screen_y_cursor--;

            if(screen_y_cursor < 0)
                screen_y_cursor = 0;
        }

        if(user_input.joystick_y > JOYSTICK_Y_INCREASE_TRIGGER_LIMIT)
        {
            screen_y_cursor++;
            
            if(screen_y_cursor > 4)
                screen_y_cursor = 4;
        }

        if(user_input.joystick_x < JOYSTICK_X_DECREASE_TRIGGER_LIMIT)
        {
            screen_x_cursor--;

            if(screen_x_cursor < 0)
                screen_x_cursor = 0;
        }

        if(user_input.joystick_x > JOYSTICK_X_INCREASE_TRIGGER_LIMIT)
        {
            screen_x_cursor++;

            if(screen_x_cursor > 1)
                screen_x_cursor = 1;
        }

    }

    return true;
}

// Interface to set how many cl of liquid to pour from each pump
bool PourDrink::InsertPumpAmounts(float amount1_, float amount2_, float amount3_, float amount4_)
{
    amount1 = amount1_;
    amount2 = amount2_;
    amount3 = amount3_;
    amount4 = amount4_;
}

bool PourDrink::ResetPourDrinkScreen()
{
    amount1 = 0;
    amount2 = 0;
    amount3 = 0;
    amount4 = 0; 

    screen_reset = true; 
    is_screen_done = false;

    screen_x_cursor = 0;
    screen_y_cursor = 0;

    empty_glass_weight = -1;
}

bool PourDrink::IsDone()
{
    return is_screen_done;
}