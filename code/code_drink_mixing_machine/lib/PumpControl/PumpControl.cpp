#include "PumpControl.h"

PumpControl::PumpControl()
{

}

bool PumpControl::Init(int x0, int y0, int width, int height)
{
    this->x0_ = x0;
    this->y0_ = y0;
    this->width_ = width;
    this->height_ = height;

    pump_1.Init(x0 + 15, y0 + 35, -1, 1);
    

    pump_2.Init(x0 + 145, y0 + 35, -1, 2);
    

    pump_3.Init(x0 + 15, y0 + 135, -1, 3);
    

    pump_4.Init(x0 + 145, y0 + 135, -1, 4);
    


}

float PumpControl::GetPumpVolume(int pump_nr)
{
    if(pump_nr < 0 || pump_nr > 4)
        return -1.0;

    switch(pump_nr)
    {
        case 1:
        {
            return pump_1.GetVolume();
            break;
        }
        case 2:
        {
            return pump_2.GetVolume();
            break;
        }
        case 3:
        {
            return pump_3.GetVolume();
            break;
        }
        case 4:
        {
            return pump_4.GetVolume();
            break;
        }
    }

    return -1;
}

bool PumpControl::SetPumpVolume(int pump_nr,float volume, float glass_max_volume)
{
    // Valid pumps are 1,2,3 and 4
    if( pump_nr  < 1 || pump_nr > 4)
    {
        return false;
    }

    //check volume is positive 
    if(volume < 0)
    {
        return false;
    }

    // Check that new total volume is less than glass volume and update specific pump amount
    switch (pump_nr)
    {
    case 1:

        if(volume + pump_2.GetVolume() + pump_3.GetVolume() + pump_4.GetVolume() > glass_max_volume)
        {
            return false;
        }

        pump_1.SetVolume(volume);

        break;

    case 2:
        
        if( pump_1.GetVolume() + volume  + pump_3.GetVolume() + pump_4.GetVolume() > glass_max_volume)
        {
            return false;
        }

        pump_2.SetVolume(volume);
        break;

    case 3:
        if( pump_1.GetVolume() + pump_2.GetVolume() + volume + pump_4.GetVolume() > glass_max_volume)
        {
            return false;
        }

        pump_3.SetVolume(volume);
        break;

    case 4:
        if( pump_1.GetVolume() + pump_2.GetVolume() + pump_3.GetVolume() + volume > glass_max_volume)
        {
            return false;
        }

        pump_4.SetVolume(volume);
        
        break;
    }

    return true;
}

bool PumpControl::SetPumpHighlight(int pump_nr, uint16_t colour)
{   
    // Valid pumps are 1,2,3 and 4, 0 is a flag to deselect all pumps
    if( pump_nr  < 0 || pump_nr > 4)
    {
        return false;
    }
    
    

    // Keep track of last active pump - no need to re render if nothing has been changed regardign highlight
    static int last_pump_nr = -1;
    uint32_t last_colour = 0;

    if( last_pump_nr == pump_nr )
        return true;


    // De select all pumps and then exit without selecting new pump
    if (pump_nr == 0)
    {
        // Turn off  highlight for previously selected pump
        switch (last_pump_nr)
        {
        case 1:
            pump_1.RemoveHighlight();
            break;
        case 2:
            pump_2.RemoveHighlight();
            break;
        case 3:
            pump_3.RemoveHighlight();
            break;
        case 4:
            pump_4.RemoveHighlight();
            break;
        }
        last_pump_nr = pump_nr;
    
        return true;
    }

    // Turn off  highlight for previously selected pump
    switch (last_pump_nr)
    {
    case 1:
        pump_1.RemoveHighlight();
        break;
    case 2:
        pump_2.RemoveHighlight();
        break;
    case 3:
        pump_3.RemoveHighlight();
        break;
    case 4:
        pump_4.RemoveHighlight();
        break;
    }
    
    
    // Turn on highlight for newly selected pump
    switch (pump_nr)
    {
    case 1:
        pump_1.SetHighlight(colour);
        break;
    case 2:
        pump_2.SetHighlight(colour);
        break;
    case 3:
        pump_3.SetHighlight(colour);
        break;
    case 4:
        pump_4.SetHighlight(colour);
        break;
    }

    last_pump_nr = pump_nr;
    last_colour = colour;
    return true;
}

bool PumpControl::PourDrink()
{
    
}

bool PumpControl::Render(MCUFRIEND_kbv *screen,  uint32_t dt_ms)
{   

    

    // Draw outline rounded rectangle
    //screen->fillRoundRect(this->x0_, this->y0_, this->width_, this->height_, 10, DARK_GREEN);
    screen->drawRoundRect(this->x0_, this->y0_, this->width_, this->height_, 10, BLACK);

    // Draw title text
    int16_t x0_txt, y0_txt;
    uint16_t w_txt, h_txt;
    String txt = "Pump Volume Control";
    screen->setTextSize(2);
    screen->getTextBounds(txt.c_str(), 0, 0, &x0_txt, &y0_txt, &w_txt, &h_txt);
    screen->setCursor( screen->width()/2 - w_txt/2, y0_ + 10);
    screen->setTextColor(0x0000); //black
    screen->println(txt);

    pump_1.Render(screen);
    pump_2.Render(screen);
    pump_3.Render(screen);
    pump_4.Render(screen);



    return true;
}