#include "PourDrink.h"

PourDrink::PourDrink() // Constructor
    : confirm_button(SCREEN_WIDTH/2 - 100, 320, 200, 55, DARK_GREY, GREEN, RED, "Confirm!", 3, WHITE),
      return_button(SCREEN_WIDTH/2 - 100, 400, 200, 55, DARK_GREY, RED, RED, "Go Back!", 3, WHITE )
{
    amount1 = 0;
    amount2 = 0;
    amount3 = 0;
    amount4 = 0;  

    screen_reset = true;
    is_screen_done = false;
    confirmed_placed_glass = false;

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
        screen->setTextSize(1);
        screen->setTextColor(BLACK);
        //screen->println("Pour drink screen!");

        String txt = "P1=" + String(amount1) + ", P2=" + String(amount2) + ", P3=" + String(amount3) + ", P4=" + String(amount4);
        screen->setCursor(25, 75);
        screen->setTextSize(1);
        screen->println(txt);
    }
    else if( confirmed_placed_glass == false )
    {

        confirm_button.Render(screen, dt_ms);
        return_button.Render(screen, dt_ms);

        screen->setCursor(25, 150);
        screen->setTextColor(BLACK);
        screen->setTextSize(3);
        screen->println("Place glass");
        screen->setCursor(25, 180);
        screen->println("below dispenser");
        screen->setCursor(25, 210);
        screen->println("and press");
        screen->setCursor(25, 240);
        screen->println("Confirm!");

        
    }
    else if ( confirmed_placed_glass == true)
    {
        // Render filled amount of glass so far
    }
    else
    {

    }

    return true;
} 
bool PourDrink::Update(const InputVector &user_input, uint32_t  dt_ms)
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
        
        if(screen_y_cursor > 1)
            screen_y_cursor = 1;
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

    if(screen_reset)
    {
        screen_x_cursor = 0;
        screen_y_cursor = 0;
    }
    else if (confirmed_placed_glass == false)
    {
        /*
            Is there a glass placed below dispenser?

                        [ Confirm  ] (-,0)

                        [ Go back! ] (-,1)
        
        */

       // Detect when cursor y value has changed
       static int last_y_cursor_pos = -1;

       // Logic for highlighting correct button
       if(screen_y_cursor == 0 && last_y_cursor_pos != 0)
       {
        confirm_button.SetIsSelected(false);
        confirm_button.SetIsHighlighted(true);
        return_button.SetIsSelected(false);
        return_button.SetIsHighlighted(false);
       }
       else if(screen_y_cursor == 1 && last_y_cursor_pos != 1)
       {
        confirm_button.SetIsSelected(false);
        confirm_button.SetIsHighlighted(false);
        return_button.SetIsSelected(false);
        return_button.SetIsHighlighted(true);
       }

       last_y_cursor_pos = screen_y_cursor;

       // Check user input, if user has clicked button
       if(user_input.button_confirm && screen_y_cursor == 0)
       {
        /*
            Save weight from loadcell when user presses confirm button. Used to zero out drink pouring in next step
            Go to next screen
        */

       empty_glass_weight = user_input.weight;

       confirm_button.SetIsSelected(true);
       confirm_button.SetIsHighlighted(false);
       return_button.SetIsSelected(false);
       return_button.SetIsHighlighted(false);

       screen_x_cursor = 0;
       screen_y_cursor = 0;

       confirmed_placed_glass = true;

        return true;
       }

       if(user_input.button_confirm && screen_y_cursor == 1)
       {
        /*
            Exit pour drink screen
        */

        confirm_button.SetIsSelected(false);
        confirm_button.SetIsHighlighted(false);
        return_button.SetIsSelected(true);
        return_button.SetIsHighlighted(false);

        is_screen_done = true;

        return true;
       }



    }
    else if (confirmed_placed_glass == true)
    {
        // Internmediate logic step, do something to go into pouring state ?
    }
    {

       /* ? */ 

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
    confirmed_placed_glass = false;

    screen_x_cursor = 0;
    screen_y_cursor = 0;

    empty_glass_weight = -1;
    
}

bool PourDrink::IsDone()
{
    return is_screen_done;
}