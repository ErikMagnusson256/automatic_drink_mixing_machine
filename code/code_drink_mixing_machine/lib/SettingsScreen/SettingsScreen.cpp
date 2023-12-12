 #include "SettingsScreen.h"


SettingsScreen::SettingsScreen() :
                            returnButton(SCREEN_WIDTH/2-70, 65, 140, 45, DARK_GREY, GREEN, YELLOW, "Go back", 2, WHITE),
                            forcePumpOn_1(SCREEN_WIDTH/2-70, 100, 140, 45, DARK_GREY, GREEN, YELLOW, "Pump 1 OFF", 2, WHITE),
                            forcePumpOn_2(SCREEN_WIDTH/2-70, 150, 140, 45, DARK_GREY, GREEN, YELLOW, "Pump 2 OFF", 2, WHITE),
                            forcePumpOn_3(SCREEN_WIDTH/2-70, 200, 140, 45, DARK_GREY, GREEN, YELLOW, "Pump 3 OFF", 2, WHITE),
                            forcePumpOn_4(SCREEN_WIDTH/2-70, 250, 140, 45, DARK_GREY, GREEN, YELLOW, "Pump 4 OFF", 2, WHITE),
                            testFloatInput1(SCREEN_WIDTH/2-130, 350, 260, 60, DARK_GREY, GREEN, YELLOW, 2, WHITE, "Test123", "kr/kg", 2.0f)
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

        //lcd_background(screen);

        screen->fillScreen(WHITE);

        screen->fillRoundRect(20, 5, SCREEN_WIDTH - 2 *20, 60, 5, GREY);
        screen->fillRoundRect(25, 10, SCREEN_WIDTH - 2*25, 50, 5, BLACK);
        screen->setCursor(45, 23);
        screen->setTextSize(3);
        screen->setTextColor(WHITE);
        screen->print("Settings Menu!");


        // reset value
        reset_screen_gui = false;
    }

    returnButton.Render(screen, dt_ms);
    forcePumpOn_1.Render(screen, dt_ms);
    forcePumpOn_2.Render(screen, dt_ms);
    forcePumpOn_3.Render(screen, dt_ms);
    forcePumpOn_4.Render(screen, dt_ms);

    testFloatInput1.Render(screen, dt_ms);

    return true;
} 
bool SettingsScreen::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    // Update any internal logic
    
     /* Update virtual cursor position */
     if(user_input.joystick_y < JOYSTICK_Y_DECREASE_TRIGGER_LIMIT && !testFloatInput1.GetIsSelected() )
        {
            cursor_y_pos--;

            if(cursor_y_pos < 0)
                cursor_y_pos = 0;
        }

    else if(user_input.joystick_y > JOYSTICK_Y_INCREASE_TRIGGER_LIMIT && !testFloatInput1.GetIsSelected())
    {
        cursor_y_pos++;
        
        if(cursor_y_pos > 5)
            cursor_y_pos = 5;
    }


    //String test123 = "Selected?" + String(testFloatInput1.GetIsSelected()) + " exit condition?" + String(!testFloatInput1.GetExitCondition()) + " ypos?" + String(cursor_y_pos);
    //Serial.println(test123);
    
    // Handle any logic for float input boxes
    if (testFloatInput1.GetIsSelected() && !testFloatInput1.GetExitCondition() )
    {
        testFloatInput1.Update(user_input, dt_ms);

        if (testFloatInput1.GetExitCondition())
            testFloatInput1.SetIsSelected(false);
        

        Serial.println("Updating float element");
    }
    
    // Check where cursor is located at, highlight element at that index
    else if( !user_input.button_confirm )//!user_input.button_confirm || !user_input.button_return)
    {
        // Button not pressed, still hovering

        switch(cursor_y_pos)
        {
            case 0: // "Go Back"
            if(!returnButton.GetIsHighlighted() )
            {
                returnButton.SetIsHighlighted(true);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);

                testFloatInput1.SetIsHighlighted(false);
            }
            

            break;

            case 1: // "Pump 1 ON"
            if(!forcePumpOn_1.GetIsHighlighted() )
            {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(true);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);

                testFloatInput1.SetIsHighlighted(false);
            }
            

            break;

            case 2: // "Pump 2 ON"
            if(!forcePumpOn_2.GetIsHighlighted() )
            {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(true);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);

                testFloatInput1.SetIsHighlighted(false);
            }
            

            break;

            case 3: // "Pump 3 ON"
            if(!forcePumpOn_3.GetIsHighlighted() )
            {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(true);
                forcePumpOn_4.SetIsHighlighted(false);

                testFloatInput1.SetIsHighlighted(false);
            }
            

            break;

            case 4: // "Pump 4 ON"
            if(!forcePumpOn_4.GetIsHighlighted() )
            {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(true);

                testFloatInput1.SetIsHighlighted(false);
            }
            break;

            case 5: //tempfloatinput
                
                if(!testFloatInput1.GetIsHighlighted() )
                {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);

                testFloatInput1.SetIsHighlighted(true);
                }
            break;

            

        }

    }

    // If confirm button is pressed, check at which y index it is,  Set select colour and/or condition
    else if(user_input.button_confirm)
    {
        // Any clickable button should be toggled
        // Any float input element should active inner logic loop

        switch(cursor_y_pos)
        {
            case 0: // "Go Back"
           
            if(returnButton.GetIsSelected())
                returnButton.SetIsSelected(false);
            else
            {
                returnButton.SetIsSelected(true);
                returnButton.SetIsHighlighted(false);
            }
                
                
            break;

            case 1: // "Pump 1 ON"

            if(forcePumpOn_1.GetIsSelected())
            {
                forcePumpOn_1.SetIsSelected(false);
                forcePumpOn_1.SetButtonText("Pump 1 OFF");
            } 
            else
            {
                forcePumpOn_1.SetIsSelected(true);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_1.SetButtonText("Pump 1 ON");
            }

            break;

            case 2: // "Pump 2 ON"
           
            if(forcePumpOn_2.GetIsSelected())
            {
                forcePumpOn_2.SetIsSelected(false);
                forcePumpOn_2.SetButtonText("Pump 2 OFF");
            }
            else
            {
                forcePumpOn_2.SetIsSelected(true);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_2.SetButtonText("Pump 2 ON");
            }
            

            break;

            case 3: // "Pump 3 ON"
            
            if(forcePumpOn_3.GetIsSelected())
            {
                forcePumpOn_3.SetButtonText("Pump 3 OFF");
                forcePumpOn_3.SetIsSelected(false);
            }
            else
            {
                forcePumpOn_3.SetIsSelected(true);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_3.SetButtonText("Pump 3 ON");
            }

            break;

            case 4: // "Pump 4 ON"

            if(forcePumpOn_4.GetIsSelected())
            {
                forcePumpOn_4.SetButtonText("Pump 4 OFF");
                forcePumpOn_4.SetIsSelected(false);
            }
            else
            {
                forcePumpOn_4.SetIsSelected(true);
                forcePumpOn_4.SetIsHighlighted(false);
                forcePumpOn_4.SetButtonText("Pump 4 ON");
            }
            
            break;

            case 5: // temp float thing

            if(testFloatInput1.GetIsSelected())
                testFloatInput1.SetIsSelected(false);
            else
            {
                testFloatInput1.SetIsSelected(true);
                testFloatInput1.SetIsHighlighted(false);
                testFloatInput1.ResetExitCondition();

            }

            break;

            

        }
    }

    




    //// Temp exit condition
    //if (user_input.button_confirm || user_input.button_return)
    //{
    //
    //    is_done = true;
    //}

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

