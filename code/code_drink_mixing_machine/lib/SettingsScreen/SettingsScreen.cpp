 #include "SettingsScreen.h"


SettingsScreen::SettingsScreen() :
                            returnButton(SCREEN_WIDTH/2-70, 65, 140, 45, DARK_GREY, GREEN, DARK_GREEN, "Go back", 2, WHITE),
                            forcePumpOn_1(SCREEN_WIDTH/2-70, 100, 140, 45, DARK_GREY, GREEN, DARK_GREEN, "Pump 1 ON", 2, WHITE),
                            forcePumpOn_2(SCREEN_WIDTH/2-70, 150, 140, 45, DARK_GREY, GREEN, DARK_GREEN, "Pump 2 ON", 2, WHITE),
                            forcePumpOn_3(SCREEN_WIDTH/2-70, 200, 140, 45, DARK_GREY, GREEN, DARK_GREEN, "Pump 3 ON", 2, WHITE),
                            forcePumpOn_4(SCREEN_WIDTH/2-70, 250, 140, 45, DARK_GREY, GREEN, DARK_GREEN, "Pump 4 ON", 2, WHITE)
{
    this->reset_screen_gui = true;
    this->is_done = false;

    cursor_y_pos = 0;
}
bool SettingsScreen::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{
    if(reset_screen_gui)
    {
        // Reset screen elements

        lcd_background(screen);


        // reset value
        reset_screen_gui = false;
    }

    returnButton.Render(screen, dt_ms);
    forcePumpOn_1.Render(screen, dt_ms);
    forcePumpOn_2.Render(screen, dt_ms);
    forcePumpOn_3.Render(screen, dt_ms);
    forcePumpOn_4.Render(screen, dt_ms);

    return true;
} 
bool SettingsScreen::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    // Update any internal logic

    /* Update virtual cursor position */
    if(user_input.joystick_y < JOYSTICK_Y_DECREASE_TRIGGER_LIMIT)
        {
            cursor_y_pos--;

            if(cursor_y_pos < 0)
                cursor_y_pos = 0;
        }

        if(user_input.joystick_y > JOYSTICK_Y_INCREASE_TRIGGER_LIMIT)
        {
            cursor_y_pos++;
            
            if(cursor_y_pos > 10)
                cursor_y_pos = 10;
        }

    // Check where cursor is located at, highlight element at that index

    if(!user_input.button_confirm || !user_input.button_return)
    {
        // Button not pressed, still hovering

        switch(cursor_y_pos)
        {
            case 0: // "Go Back"
            if(!returnButton.GetIsHighlighted())
            {
                returnButton.SetIsHighlighted(true);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);
            }
            

            break;

            case 1: // "Pump 1 ON"
            if(!forcePumpOn_1.GetIsHighlighted())
            {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(true);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);
            }
            

            break;

            case 2: // "Pump 2 ON"
            if(!forcePumpOn_2.GetIsHighlighted())
            {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(true);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);
            }
            

            break;

            case 3: // "Pump 3 ON"
            if(!forcePumpOn_3.GetIsHighlighted())
            {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(true);
                forcePumpOn_4.SetIsHighlighted(false);
            }
            

            break;

            case 4: // "Pump 4 ON"
            if(!forcePumpOn_4.GetIsHighlighted())
            {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(true);
            }
            
            break;

            default:

            returnButton.SetIsHighlighted(false);
            forcePumpOn_1.SetIsHighlighted(false);
            forcePumpOn_2.SetIsHighlighted(false);
            forcePumpOn_3.SetIsHighlighted(false);
            forcePumpOn_4.SetIsHighlighted(false);

        }

    }

    // Temp exit condition
    if (user_input.button_confirm || user_input.button_return)
    {

        is_done = true;
    }

    return true;
}

bool SettingsScreen::ResetScreen()
{
    is_done = false;
    reset_screen_gui = true;

}

bool SettingsScreen::GetIsDone()
{
    return is_done;
}

