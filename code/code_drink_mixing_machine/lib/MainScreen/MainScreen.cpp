#include "MainScreen.h"

MainScreen::MainScreen()
{
    pump_control.Init(SCREEN_WIDTH/12, SCREEN_HEIGHT/6, SCREEN_WIDTH*10/12, SCREEN_HEIGHT*4/8 );

    screen_x_cursor = 0; // Virtual cursor x
    screen_y_cursor = 0; // Virtual cursor y

    // Menu selection flags, If menu is active flag is set true
    p1_selected = false;
    p2_selected = false;
    p3_selected = false;
    p4_selected = false;
    pour_drink_selected = false;
    randomize_drink_selected = false;
    settings_selected = false;

    // Extra Menu highligt flags, pump highlight flages are stored in pumpcontrol object
    pour_drink_highlight = false;
    randomize_drink_highlight = false;
    settings_highlight = false;
}

bool MainScreen::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{
    // Clear screen and set to a known background once
    static bool cleared_screen = false;
    if(!cleared_screen)
    {
        screen->fillScreen(WHITE);
        lcd_background(screen);
            
        cleared_screen = true;
    }

    /* DEBUG - Render cursor (x,y) location */

    static int last_x_cursor = -1;
    static int last_y_cursor = -1;
    if(last_x_cursor != screen_x_cursor || last_y_cursor != screen_y_cursor)
    {
        last_x_cursor = screen_x_cursor;
        last_y_cursor = screen_y_cursor;

        screen->fillRect(20, SCREEN_HEIGHT-10, 100, 19, WHITE);
        screen->setCursor(20, SCREEN_HEIGHT-10);
        screen->setTextSize(1);
        screen->setTextColor(BLACK);
        screen->println("Cursor:(" + String(screen_x_cursor) + ","+ String(screen_y_cursor) + ")");
    }

    /* END DEBUG */
    

    pump_control.Render(screen, dt_ms);

    // Draw Menu Items
    /*
    
    Make Drink

    Randomize Grogg

    Drinkmachine 
    Configuration


    To save on compute resources for the arduino mega, only re render the buttons if a change to its state has been made
    This is done with static state variables for various elements of each button

    @TODO FUTURE WORK simplify this logic it is very messy and I'm tired
    */

   //====== pour drink button ========

    static bool last_render_pour_drink_highlight = false;
    static bool last_render_pour_drink_selected = false;
    static bool re_render_pour_drink_button = true;

    if(pour_drink_highlight == false && last_render_pour_drink_highlight == true)
    {
        last_render_pour_drink_highlight = false;
        re_render_pour_drink_button = true;
    }
    
    if(pour_drink_selected == false && last_render_pour_drink_selected == true)
    {
        last_render_pour_drink_selected = false;
        re_render_pour_drink_button = true;
    }

    if(pour_drink_highlight == true && last_render_pour_drink_highlight == false)
    {
        screen->fillRoundRect(50, 320, SCREEN_WIDTH-100, 60, 5, YELLOW);
        last_render_pour_drink_highlight = true;
        re_render_pour_drink_button = true;
    }
    else if(pour_drink_selected == true && last_render_pour_drink_highlight == false)
    {
        screen->fillRoundRect(50, 320, SCREEN_WIDTH-100, 60, 5, RED);
        last_render_pour_drink_selected = true;
        re_render_pour_drink_button = true;
    } 
    else if ( (pour_drink_highlight == false && pour_drink_selected == false) && re_render_pour_drink_button)
    {
        screen->fillRoundRect(50, 320, SCREEN_WIDTH-100, 60, 5, WHITE);
        last_render_pour_drink_selected = false;
        re_render_pour_drink_button = true;
    }

    if(re_render_pour_drink_button)
    {
        screen->fillRoundRect(55, 325, SCREEN_WIDTH-110, 50, 5, DARK_GREY);
        screen->drawRoundRect(55, 325, SCREEN_WIDTH-110, 50, 5, BLACK);
        screen->setCursor(60, 335);
        screen->setTextSize(3);
        screen->setTextColor(WHITE);
        screen->println("Pour Drink!");

        re_render_pour_drink_button = false;
    }
    

    

   
   //====== randomize drink button ========
    static bool last_render_randomize_drink_highlight = false;
    static bool last_render_randomize_drink_selected = false;
    static bool re_render_randomize_drink_button = true;

    if(randomize_drink_highlight == false && last_render_randomize_drink_highlight == true)
    {
        last_render_randomize_drink_highlight = false;
        re_render_randomize_drink_button = true;
    }
    
    if(randomize_drink_selected == false && last_render_randomize_drink_selected == true)
    {
        last_render_randomize_drink_selected = false;
        re_render_randomize_drink_button = true;
    }

    if(randomize_drink_highlight == true && last_render_randomize_drink_highlight == false)
    {
        screen->fillRoundRect(50, 385, SCREEN_WIDTH-100, 40, 5, YELLOW);
        last_render_randomize_drink_highlight = true;
        re_render_randomize_drink_button = true;
    }
    else if(randomize_drink_selected == true && last_render_randomize_drink_highlight == false)
    {
        screen->fillRoundRect(50, 385, SCREEN_WIDTH-100, 40, 5, RED);
        last_render_randomize_drink_selected = true;
        re_render_randomize_drink_button = true;
    } 
    else if ( (randomize_drink_highlight == false && randomize_drink_selected == false) && re_render_randomize_drink_button)
    {
        screen->fillRoundRect(50, 385, SCREEN_WIDTH-100, 40, 5, WHITE);
        last_render_randomize_drink_selected = false;
        re_render_randomize_drink_button = true;
    }

    if(re_render_randomize_drink_button)
    {
        screen->fillRoundRect(55, 390, SCREEN_WIDTH-110, 30, 5, DARK_GREY);
        screen->drawRoundRect(55, 390, SCREEN_WIDTH-110, 30, 5, BLACK);
        screen->setCursor(60, 395);
        screen->setTextSize(2);
        screen->setTextColor(WHITE);
        screen->println("Randomize Drink!");

        re_render_randomize_drink_button = false;
    }

  

    //====== settings button ========
    static bool last_render_settings_highlight = false;
    static bool last_render_settings_selected = false;
    static bool re_render_settings_button = true;


    if(settings_highlight == false && last_render_settings_highlight == true)
    {
        last_render_settings_highlight = false;
        re_render_settings_button = true;
    }
    
    if(settings_selected == false && last_render_settings_selected == true)
    {
        last_render_settings_selected = false;
        re_render_settings_button = true;
    }

    if(settings_highlight == true && last_render_settings_highlight == false)
    {
        screen->fillRoundRect(50, 440, SCREEN_WIDTH-100, 40, 5, YELLOW);
        last_render_settings_highlight = true;
        re_render_settings_button = true;
    }
    else if(settings_selected == true && last_render_settings_highlight == false)
    {
        screen->fillRoundRect(50, 440, SCREEN_WIDTH-100, 40, 5, RED);
        last_render_settings_selected = true;
        re_render_settings_button = true;
    } 
    else if ( (settings_highlight == false && settings_selected == false) && re_render_settings_button)
    {
        screen->fillRoundRect(50, 440, SCREEN_WIDTH-100, 40, 5, WHITE);
        last_render_settings_selected = false;
        re_render_settings_button = true;
    }

    if(re_render_settings_button)
    {
        screen->fillRoundRect(55, 445, SCREEN_WIDTH-110, 30, 5, DARK_GREY);
        screen->drawRoundRect(55, 445, SCREEN_WIDTH-110, 30, 5, BLACK);
        screen->setCursor(60, 450);
        screen->setTextSize(2);
        screen->setTextColor(WHITE);
        screen->println("Settings!");

        re_render_settings_button = false;
    }


}

bool MainScreen::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    // If no menu item on screen is selected, the userinput should be used to move a virtual cursor, which can be used to select an menu item
    if(true)
    {   
        //@todo condition

        if(user_input.joystick_y < 400)
        {
            screen_y_cursor--;

            if(screen_y_cursor < 0)
                screen_y_cursor = 0;
        }

        if(user_input.joystick_y > 600)
        {
            screen_y_cursor++;
            
            if(screen_y_cursor > 4)
                screen_y_cursor = 4;
        }

        if(user_input.joystick_x < 400)
        {
            screen_x_cursor--;

            if(screen_x_cursor < 0)
                screen_x_cursor = 0;
        }

        if(user_input.joystick_x > 600)
        {
            screen_x_cursor++;

            if(screen_x_cursor > 1)
                screen_x_cursor = 1;
        }

        /* Check where virtual cursor is at - highlight the menu item it is located at */
        /*
        1. Remove all highlights
        2. Set new highlight where screen cursor is at
        */

       if(screen_x_cursor == 0 && screen_y_cursor == 0)
       {
        pump_control.SetPumpHighlight(1, YELLOW);
        pour_drink_highlight = false;
        randomize_drink_highlight = false;
        settings_highlight = false;
       }
       else if(screen_x_cursor == 1 && screen_y_cursor == 0)
       {
        pump_control.SetPumpHighlight(2, YELLOW);
        pour_drink_highlight = false;
        randomize_drink_highlight = false;
        settings_highlight = false;
       }
       else if(screen_x_cursor == 0 && screen_y_cursor == 1)
       {
        pump_control.SetPumpHighlight(3, YELLOW);
        pour_drink_highlight = false;
        randomize_drink_highlight = false;
        settings_highlight = false;
       }
       else if(screen_x_cursor == 1 && screen_y_cursor == 1)
       {
        pump_control.SetPumpHighlight(4, YELLOW);
        pour_drink_highlight = false;
        randomize_drink_highlight = false;
        settings_highlight = false;
       }
       else if(screen_y_cursor == 2)
       {
        // @todo
        // Highlight pour drink button
        pump_control.SetPumpHighlight(0, YELLOW);
        pour_drink_highlight = true;
        randomize_drink_highlight = false;
        settings_highlight = false;

       }
       else if(screen_y_cursor == 3)
       {
        // @todo
        // Highlight randomize drink button
        pump_control.SetPumpHighlight(0, YELLOW);
        pour_drink_highlight = false;
        randomize_drink_highlight = true;
        settings_highlight = false;
       }
       else if(screen_y_cursor == 4)
       {
        // @todo
        // Highlight settings button
        pump_control.SetPumpHighlight(0, YELLOW);
        pour_drink_highlight = false;
        randomize_drink_highlight = false;
        settings_highlight = true;
       }

        if(user_input.button_confirm)
        {
            // Check what Menu Item is currently selected with virtual cursor, then select it

            /*
                P1               P2
                P3               P4
                    Pour Drink
                    Randomize Drink
                    Settings

                        |
                        V

                (0,0)               (1,0)
                (0,1)               (1,1)
                        (-,2)
                        (-,3)
                        (-,4)
            */

           if(screen_x_cursor == 0 && screen_y_cursor == 0)
           {
            p1_selected = true;
            pump_control.SetPumpHighlight(1, RED);
           }
           
           /*
           Menu items are de-selected from their respective logic handling part bellow
           */
        }

    }
    else
    {
        // A menu item is selected, depening on what is selecting perform a different action
        
        //todo
    }

    return true;
}