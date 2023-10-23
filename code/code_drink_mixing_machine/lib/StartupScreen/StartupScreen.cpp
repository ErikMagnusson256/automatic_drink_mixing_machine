#include "StartupScreen.h"


StartupScreen::StartupScreen() 
{
    glas_size = 25; //cl
    finnished_loading_screen = false;
    loading_screen_timer = 0;
    re_render_selecing_screen = true;
    finnished_selecting_glass_size_screen = false;
    finnished_setup = false;

    randomSeed(analogRead(RANDOMIZER_PIN));
}

bool StartupScreen::Render(MCUFRIEND_kbv *screen, uint32_t dt_ms)
{
    if(finnished_loading_screen == false)
    {
        // Clear screen and set to a known background once
        static bool cleared_screen = false;
        if(!cleared_screen)
        {
            screen->fillScreen(WHITE);
            lcd_background(screen);
            
            // Add some informative text
            screen->setCursor(35, 80);
            screen->setTextSize(2);
            screen->setTextColor(BLACK);
            screen->println("Initializing...");
                
            int nr_poured_drinks = -1;
            float cl_poured = -1;

            EEPROM.get(EEPROM_ADR_NR_DRINKS, nr_poured_drinks);
            EEPROM.get(EEPROM_ADR_NR_CL, cl_poured);

            screen->setCursor(20, 400);
            screen->setTextSize(2);
            screen->setTextColor(BLACK);
            screen->println("Poured " + String(nr_poured_drinks) + " drinks so far!");
            screen->setCursor(20, 425);
            screen->setTextSize(2);
            screen->println("That is a total of " + String(cl_poured) + " cl poured!");
            
            cleared_screen = true;
        }

        


        // Variables to draw a glass filling up
        int x0 = 37;
        int y0 = 100;
        int width = SCREEN_WIDTH - 74;
        int height = 275;
        float temp_volume = 10;
        float p1 = 2.5;
        float p2 = 2.5;
        float p3 = 2.5;
        float p4 = 2.5;

        // Draw empty glass 
        screen->drawLine(x0, y0, x0+width, y0, BLACK);
        screen->drawLine(x0, y0, x0 + width/5, y0 + height, BLACK);
        screen->drawLine(x0 + width, y0, x0 + (width/5)*4, y0 + height, BLACK);
        screen->drawLine(x0 + width/5, y0 + height,  x0 + (width/5)*4, y0 + height, BLACK);

        // Render "loading screen" aka fillinga glass, once upon first render

        //int delta_t = height/duration;
        int center_x = (x0 + width)/2;
        float h0 = y0 + height, w0 = width/5;
        float delta = atan(w0 / (5*h0));
     
        float center_width = (width/5)*3; 
        float tan_delta = tan(delta);
        tan_delta = 0.18; //???

        static int current_height = 0; // y position of last layered filled

        //at this time, the glass should be filled x%
        int new_fill_height = loading_screen_timer/( (float)LOADING_SCREEN_DURATION_MS ) * height;
        
        // Avoid overfilling glass
        if (new_fill_height > height)
        {
            return true;
        }

        // start at current_height, draw lines until new_fill_height

        for(int i = current_height; i < new_fill_height; i++)
        {   
            float layerwidth = 2*(tan_delta * i) + center_width;
            uint16_t glass_fill_colour = RED;
            if ((float)i / (float)height > 0 / temp_volume)
                glass_fill_colour = YELLOW;
            if ((float)i / (float)height > (p1) / temp_volume)
                glass_fill_colour = BLUE;
            if ((float)i / (float)height > (p1 + p2) / temp_volume)
                glass_fill_colour = GREEN;
            if ((float)i / (float)height > (p1 + p2 + p3) / temp_volume)
                glass_fill_colour = MAGENTA;

            screen->drawFastHLine(SCREEN_WIDTH/2 - (layerwidth)/2, y0 + height - i, layerwidth, glass_fill_colour);

            // Draw random bubbles in glass
            /*if(random(0,10) > 8)
            {
                int x = center_x + random(-width/3,width/3);
                int y = y0 + height - i + random(0, 25);
                int radius = random(5,20);
                uint16_t col = random(0, 65536);
                screen->fillCircle(x,y,radius, col);
            }*/
            

        }

        current_height = new_fill_height;
        return true;

    } else if(finnished_selecting_glass_size_screen == false)
    {



        // Clear screen and set to a known background once
        static bool cleared_screen = false;
        if(!cleared_screen)
        {
            screen->fillScreen(WHITE);
            lcd_background(screen);
            
            cleared_screen = true;
        }

        if(re_render_selecing_screen)
        {
            re_render_selecing_screen = false;

            // Draw white area over previous area
            screen->fillRoundRect(40,220,250,250,7,WHITE);

            screen->setTextColor(BLACK);
            screen->setCursor(40, 100);
            screen->setTextSize(3);
            screen->println("Please confirm \n  glass size!");

            // Display currently set glass size
            //screen->drawRoundRect(90, 250, 160, 45, 7, BLACK);
            screen->setCursor(50, 250);
            screen->setTextSize(5);
            screen->setTextColor(BLACK);
            screen->println(String(glas_size) + " cl");

            // Display up and down arrow to indicate user that amount is changable
        }
        


        return true;
    } else 
    {

        screen->fillScreen(WHITE);
        screen->setCursor(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        screen->setTextColor(BLACK);
        screen->setTextSize(2);
        screen->println("user should not end up here?? startupscreen");

        return false;
    }

    return true;
} 

bool StartupScreen::Update(const InputVector &user_input, uint32_t  dt_ms)
{
    if(finnished_loading_screen == false)
    {   
        // Logic for loading screen duration, how long the gui should display a filling glass

        // Skip loading screen when user presses button
        if(user_input.button_confirm)
        {
            finnished_loading_screen = true;
        }

        loading_screen_timer += dt_ms;

        if(loading_screen_timer > (uint32_t) LOADING_SCREEN_DURATION_MS + LOADING_SCREEN_PAUSE )
        {
            finnished_loading_screen = true;

            return true;
        }
    } 
    else if (finnished_selecting_glass_size_screen == false)
    {
        //todo logic for selecting glass size

        float max_rate = 5; // max volume change per 1000 ms
        static float temp_glas_volume = 25;

        if(user_input.joystick_y > 600)
        {
            temp_glas_volume -= max_rate*dt_ms/1000.0;
           
            re_render_selecing_screen = true;
        }
        else if (user_input.joystick_y < 400)
        {
            temp_glas_volume += max_rate*dt_ms/1000.0;

            re_render_selecing_screen = true;
        } 
        
        if(user_input.button_confirm)
        {
            finnished_loading_screen = true;
            finnished_selecting_glass_size_screen = true;
            finnished_setup = true;
            
        }

        if(temp_glas_volume < 0)
            temp_glas_volume = 0;

        
        glas_size = roundf(temp_glas_volume);

        if(glas_size < 0)
                glas_size = 0;

    } 
    else 
    {
        finnished_setup = true;
    }

    return true;
}

float StartupScreen::GetGlasSize()
{
    return glas_size;
}

bool StartupScreen::IsSetupFinnished()
{
    return finnished_setup;
}