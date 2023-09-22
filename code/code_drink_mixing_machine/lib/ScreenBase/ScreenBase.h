#pragma once

#ifndef __BASESCREEN__
#define __BASESCREEN__

/*

    EM 22/9 2023

    Virtual class representing a basic screen.

    A basic generic screen shall have;
        * Functions
            - virtual bool Update(...) : Update the logic for the specific screen and its content
                - Inputs:
                    dt : time since last update
                    user input : user input from higher level software, i.e joystick or button presses or current weight fromn loadcell
            - virtual bool Draw(...) : 
                - Inputs:
                    dt : time since last draw
                    screen : screen object
            - virtual bool ForceDraw(...) : Force a redraw of all screen elements
        
        * Variables
            - Background colour
            - screen size x
            - screen size y
            - is active

*/

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/* Include custom made libraries */
#include "IO_Vector.h"
#include "DM_CONFIG.h"


class ScreenBase {
    private:

    protected:

    uint16_t background_colour;
    int size_x;
    int size_y;
    bool is_active;

    public:
    
    ScreenBase() {this->background_colour = WHITE; this->size_x = SCREEN_WIDTH; this->size_y = SCREEN_HEIGHT; this->is_active = false;}
    ScreenBase(uint16_t background_colour) {this->background_colour = background_colour; this->size_x = SCREEN_WIDTH; this->size_y = SCREEN_HEIGHT;this->is_active = false;}

    virtual bool Draw(MCUFRIEND_kbv *screen, uint32_t dt_ms);

    virtual bool ForceDraw(MCUFRIEND_kbv *screen);

    virtual bool Update(const InputVector &user_input, OutputVector &machine_output, uint32_t  dt_ms);

};

#endif