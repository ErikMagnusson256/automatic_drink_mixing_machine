 #include "SettingsScreen.h"


SettingsScreen::SettingsScreen() :
                            returnButton(SCREEN_WIDTH/2-75, 65, 150, 35, DARK_GREY, GREEN, YELLOW, "Go back", 2, WHITE),
                            forcePumpOn_1(10, 100, 150, 35, DARK_GREY, GREEN, YELLOW, "Pump 1 OFF", 2, WHITE),
                            forcePumpOn_2(10, 135, 150, 35, DARK_GREY, GREEN, YELLOW, "Pump 2 OFF", 2, WHITE),
                            forcePumpOn_3(10, 170, 150, 35, DARK_GREY, GREEN, YELLOW, "Pump 3 OFF", 2, WHITE),
                            forcePumpOn_4(10, 205, 150, 35, DARK_GREY, GREEN, YELLOW, "Pump 4 OFF", 2, WHITE),
                            glassSizeFloatInput(10, 240, 300, 45, DARK_GREY, GREEN, YELLOW, 2, WHITE, "Glass Size", "cl", 1.0f),
                            loadCellCalPointFloatInput1(10, 305, 300, 45, DARK_GREY, GREEN, YELLOW, 2, WHITE, "LC Cal 50g", "", 1.0f),
                            loadCellCalPointFloatInput2(10, 350, 300, 45, DARK_GREY, GREEN, YELLOW, 2, WHITE, "LC Cal 250g", "", 1.0f),
                            displayCurrentLoadCellWeight(SCREEN_WIDTH/2-100, 430, 200, 50, DARK_GREY, GREEN, YELLOW, "xxxx", 2, WHITE)
                            
{
    this->reset_screen_gui = true;
    this->is_done = false;

    cursor_y_pos = 0;

    // TODO LOAD CALIBRATION POINTS FROM EEPROM
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


        screen->drawFastHLine(10, 285, SCREEN_WIDTH-20, BLACK);
        screen->setCursor(10, 290);
        screen->setTextSize(2);
        screen->setTextColor(BLACK);
        screen->println("Non-Volatile Parameters");

        screen->drawFastHLine(10, 400, SCREEN_WIDTH-20, BLACK);
        screen->setCursor(10, 405);
        screen->setTextSize(2);
        screen->setTextColor(BLACK);
        screen->println("Loadcell measured weight!");


        // reset value
        reset_screen_gui = false;
    }

    returnButton.Render(screen, dt_ms);
    forcePumpOn_1.Render(screen, dt_ms);
    forcePumpOn_2.Render(screen, dt_ms);
    forcePumpOn_3.Render(screen, dt_ms);
    forcePumpOn_4.Render(screen, dt_ms);

    glassSizeFloatInput.Render(screen, dt_ms);
    loadCellCalPointFloatInput1.Render(screen, dt_ms);
    loadCellCalPointFloatInput2.Render(screen, dt_ms);
    displayCurrentLoadCellWeight.Render(screen, dt_ms);

    //testFloatInput1.Render(screen, dt_ms);

    return true;
} 
bool SettingsScreen::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    // Update any internal logic
    
    // Update text ond isplayCurrentLoadCellWeight 

    displayCurrentLoadCellWeight.SetButtonText(String(user_input.weight)+" grams");


     /* Update virtual cursor position if not inside logic of a float element input*/

    if (!glassSizeFloatInput.GetIsSelected() &&
        !loadCellCalPointFloatInput1.GetIsSelected() &&
        !loadCellCalPointFloatInput2.GetIsSelected() )
    {
        if(user_input.joystick_y < JOYSTICK_Y_DECREASE_TRIGGER_LIMIT )
        {
            cursor_y_pos--;

            if(cursor_y_pos < 0)
                cursor_y_pos = 0;
        }

        else if(user_input.joystick_y > JOYSTICK_Y_INCREASE_TRIGGER_LIMIT )
        {
            cursor_y_pos++;
            
            if(cursor_y_pos > 7)
                cursor_y_pos = 7;
        }
    }

    


    //String test123 = "Selected?" + String(testFloatInput1.GetIsSelected()) + " exit condition?" + String(!testFloatInput1.GetExitCondition()) + " ypos?" + String(cursor_y_pos);
    //Serial.println(test123);
    
    // Handle any logic for float input boxes
    if(glassSizeFloatInput.GetIsSelected() && !glassSizeFloatInput.GetExitCondition())
    {
        glassSizeFloatInput.Update(user_input, dt_ms);

        if(glassSizeFloatInput.GetExitCondition())
            glassSizeFloatInput.SetIsSelected(false);
    }
    else if(loadCellCalPointFloatInput1.GetIsSelected() && !loadCellCalPointFloatInput1.GetExitCondition())
    {
        loadCellCalPointFloatInput1.Update(user_input, dt_ms);

        if(loadCellCalPointFloatInput1.GetExitCondition())
        {           
            loadCellCalPointFloatInput1.SetIsSelected(false);
            // TODO UPDATE EEPROM HERE
        }
    }
    else if(loadCellCalPointFloatInput2.GetIsSelected() && !loadCellCalPointFloatInput2.GetExitCondition())
    {
        loadCellCalPointFloatInput2.Update(user_input, dt_ms);

        if(loadCellCalPointFloatInput2.GetExitCondition())
        {           
            loadCellCalPointFloatInput2.SetIsSelected(false);
            // TODO UPDATE EEPROM HERE
        }
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

                glassSizeFloatInput.SetIsHighlighted(false);
                loadCellCalPointFloatInput1.SetIsHighlighted(false);
                loadCellCalPointFloatInput2.SetIsHighlighted(false);
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

                glassSizeFloatInput.SetIsHighlighted(false);
                loadCellCalPointFloatInput1.SetIsHighlighted(false);
                loadCellCalPointFloatInput2.SetIsHighlighted(false);
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

                glassSizeFloatInput.SetIsHighlighted(false);
                loadCellCalPointFloatInput1.SetIsHighlighted(false);
                loadCellCalPointFloatInput2.SetIsHighlighted(false);
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

                glassSizeFloatInput.SetIsHighlighted(false);
                loadCellCalPointFloatInput1.SetIsHighlighted(false);
                loadCellCalPointFloatInput2.SetIsHighlighted(false);
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

                glassSizeFloatInput.SetIsHighlighted(false);
                loadCellCalPointFloatInput1.SetIsHighlighted(false);
                loadCellCalPointFloatInput2.SetIsHighlighted(false);
            }
            break;

            case 5: //glassSizeFloatInput;

                
                if(!glassSizeFloatInput.GetIsHighlighted() )
                {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);

                glassSizeFloatInput.SetIsHighlighted(true);
                loadCellCalPointFloatInput1.SetIsHighlighted(false);
                loadCellCalPointFloatInput2.SetIsHighlighted(false);
                }
            break;

            case 6: //loadCellCalPointFloatInput1;

                
                if(!loadCellCalPointFloatInput1.GetIsHighlighted() )
                {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);

                glassSizeFloatInput.SetIsHighlighted(false);
                loadCellCalPointFloatInput1.SetIsHighlighted(true);
                loadCellCalPointFloatInput2.SetIsHighlighted(false);
                }
            break;

            case 7: //loadCellCalPointFloatInput2;

                
                if(!loadCellCalPointFloatInput2.GetIsHighlighted() )
                {
                returnButton.SetIsHighlighted(false);
                forcePumpOn_1.SetIsHighlighted(false);
                forcePumpOn_2.SetIsHighlighted(false);
                forcePumpOn_3.SetIsHighlighted(false);
                forcePumpOn_4.SetIsHighlighted(false);

                glassSizeFloatInput.SetIsHighlighted(false);
                loadCellCalPointFloatInput1.SetIsHighlighted(false);
                loadCellCalPointFloatInput2.SetIsHighlighted(true);
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
           
            is_done = true; // exit settings screen!!
            cursor_y_pos = 0;
            // Reset things
            returnButton.SetIsHighlighted(false);
            forcePumpOn_1.SetIsHighlighted(false);
            forcePumpOn_2.SetIsHighlighted(false);
            forcePumpOn_3.SetIsHighlighted(false);
            forcePumpOn_4.SetIsHighlighted(false);
            glassSizeFloatInput.SetIsHighlighted(false);
            loadCellCalPointFloatInput1.SetIsHighlighted(false);
            loadCellCalPointFloatInput2.SetIsHighlighted(false);

            returnButton.SetIsSelected(false);
            forcePumpOn_1.SetIsSelected(false);
            forcePumpOn_2.SetIsSelected(false);
            forcePumpOn_3.SetIsSelected(false);
            forcePumpOn_4.SetIsSelected(false);
            glassSizeFloatInput.SetIsSelected(false);
            loadCellCalPointFloatInput1.SetIsSelected(false);
            loadCellCalPointFloatInput2.SetIsSelected(false);



            //if(returnButton.GetIsSelected())
            //    returnButton.SetIsSelected(false);
            //else
            //{
            //    returnButton.SetIsSelected(true);
            //    returnButton.SetIsHighlighted(false);
            //
            //    
            //}
                
                
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

            case 5: // glassSizeFloatInput

            if(glassSizeFloatInput.GetIsSelected())
                glassSizeFloatInput.SetIsSelected(false);
            else
            {
                glassSizeFloatInput.SetIsSelected(true);
                glassSizeFloatInput.SetIsHighlighted(false);
                glassSizeFloatInput.ResetExitCondition();

            }
            break;

            
            case 6: // loadCellCalPointFloatInput1

            if(loadCellCalPointFloatInput1.GetIsSelected())
                loadCellCalPointFloatInput1.SetIsSelected(false);
            else
            {
                loadCellCalPointFloatInput1.SetIsSelected(true);
                loadCellCalPointFloatInput1.SetIsHighlighted(false);
                loadCellCalPointFloatInput1.ResetExitCondition();

            }
            break;

            case 7: // loadCellCalPointFloatInput2

            if(loadCellCalPointFloatInput2.GetIsSelected())
                loadCellCalPointFloatInput2.SetIsSelected(false);
            else
            {
                loadCellCalPointFloatInput2.SetIsSelected(true);
                loadCellCalPointFloatInput2.SetIsHighlighted(false);
                loadCellCalPointFloatInput2.ResetExitCondition();

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

