#include "Pump.h"


Pump::Pump(int x0, int y0, int pump_pin_nr, int pump_nr)
{
   Init(x0, y0, pump_pin_nr, pump_nr);
}

Pump::Pump()
{
    Init(0, 0, -1, -1);
    colour_highlight = 0;
}

bool Pump::Init(int x0, int y0, int pump_pin_nr, int pump_nr)
{
    //pinMode(pump_pin_nr, OUTPUT);
    x0_ = x0;
    y0_ = y0;
    pump_pin_nr_ = pump_pin_nr;
    pump_nr_ = pump_nr;

    pump_volume_ = 0;
    last_pump_volume_ = 0;

    is_highlighted_ = false;
    re_render_ = true;
}

bool Pump::SetHighlight(uint16_t colour)
{
    is_highlighted_ = true;
    re_render_ = true;
    colour_highlight = colour;
}
bool Pump::RemoveHighlight()
{
    is_highlighted_ = false;
    re_render_ = true;
}

bool Pump::SetVolume(float volume)
{
    last_pump_volume_ = pump_volume_;
    pump_volume_ = volume;
    re_render_ = true;
}

float Pump::GetVolume()
{
    return pump_volume_;
}

bool Pump::Render(MCUFRIEND_kbv *screen)
{
    if(re_render_)
    {
        // Erase local background by drawing white background
        screen->fillRect(x0_ - HIGHLIGHT_WIDTH, y0_ - HIGHLIGHT_WIDTH, ICON_SIZE_X + 2*HIGHLIGHT_WIDTH, ICON_SIZE_Y + 2*HIGHLIGHT_WIDTH, 0xFFFF);

        if(is_highlighted_)
        {
            // Draw highlight box
            
            screen->fillRoundRect(x0_ - HIGHLIGHT_WIDTH, y0_ - HIGHLIGHT_WIDTH, ICON_SIZE_X + 2*HIGHLIGHT_WIDTH, ICON_SIZE_Y + 2*HIGHLIGHT_WIDTH, 7, colour_highlight );
        }

        // Draw white area
        screen->fillRoundRect(x0_, y0_, ICON_SIZE_X, ICON_SIZE_Y, 5, 0xFFFF);

        // Outline
        screen->drawRoundRect(x0_, y0_, ICON_SIZE_X, ICON_SIZE_Y, 5, 0);

        // Text
        String upper_text = "PUMP " + String(pump_nr_), lower_text = String(pump_volume_) + " cl";

        screen->setCursor(x0_+5, y0_+5);
        screen->setTextSize(2);
        screen->setTextColor(0x0);
        screen->println(upper_text);

        screen->setCursor(x0_ + 5, y0_ + 25);
        screen->println(lower_text);

        /*
        // Up an down triangle
        int center_x = (x0_ + ICON_SIZE_X)/2;

        // Up Triangle
        int triangle_side = 25;
        int x0_up = (x0_+ICON_SIZE_X)/2 - ICON_SIZE_X/6,
            y0_up = y0_ + ICON_SIZE_Y*6/7,
            x1_up = x0_up - triangle_side*sin(DEG_TO_RAD * 30),
            y1_up = y0_up - triangle_side*cos(DEG_TO_RAD * 30),
            x2_up = x0_up + triangle_side*sin(DEG_TO_RAD * 30),
            y2_up = y0_up - triangle_side*cos(DEG_TO_RAD * 30);
        
        screen->drawTriangle(x0_up, y0_up, x1_up, y1_up, x2_up, y2_up, 0x0);

        // Down triangle
        int x0_down = (x0_+ICON_SIZE_X)/2 + ICON_SIZE_X/6,
            y0_down = y0_up - ICON_SIZE_Y*6/7,
            x1_down = x0_down - triangle_side*sin(DEG_TO_RAD * 30),
            y1_down = y0_down + triangle_side*cos(DEG_TO_RAD * 30),
            x2_down = x0_down + triangle_side*sin(DEG_TO_RAD * 30),
            y2_down = y0_down + triangle_side*cos(DEG_TO_RAD * 30);

        screen->drawTriangle(x0_down, y0_down, x1_down, y1_down, x2_down, y2_down, 0x0);
        */

       // Up triangle
        int center_x_down = (x0_) + ICON_SIZE_X/4, 
            center_y_down = y0_ + ICON_SIZE_Y*5/7, 
            triangle_side_length=30;

        int x0_down = center_x_down,
            y0_down = center_y_down + triangle_side_length*cos(DEG_TO_RAD*30)/2,
            x1_down = center_x_down - triangle_side_length*sin(DEG_TO_RAD*30),
            y1_down = center_y_down - triangle_side_length*cos(DEG_TO_RAD*30)/2,
            x2_down = center_x_down + triangle_side_length*sin(DEG_TO_RAD*30),
            y2_down = center_y_down - triangle_side_length*cos(DEG_TO_RAD*30)/2;       
        
        if(last_pump_volume_ > pump_volume_)
        {
            screen->fillTriangle(x0_down, y0_down, x1_down, y1_down, x2_down, y2_down, 0xF800);
        }
        screen->drawTriangle(x0_down, y0_down, x1_down, y1_down, x2_down, y2_down, 0x0);

        // Down triangle
        int center_x_up = (x0_+ICON_SIZE_X) - ICON_SIZE_X/4, 
            center_y_up = center_y_down;

        int x0_up = center_x_up,
            y0_up = center_y_up - triangle_side_length*cos(DEG_TO_RAD*30)/2,
            x1_up = center_x_up + triangle_side_length*sin(DEG_TO_RAD*30),
            y1_up = center_y_up + triangle_side_length*cos(DEG_TO_RAD*30)/2,
            x2_up = center_x_up - triangle_side_length*sin(DEG_TO_RAD*30),
            y2_up = center_y_up + triangle_side_length*cos(DEG_TO_RAD*30)/2;       
        
        if(last_pump_volume_ < pump_volume_)
        {
            screen->fillTriangle(x0_up, y0_up, x1_up, y1_up, x2_up, y2_up, 0xF800);
        }
        screen->drawTriangle(x0_up, y0_up, x1_up, y1_up, x2_up, y2_up, 0x0);
        
        re_render_ = false;
    }
    
    return true;
}