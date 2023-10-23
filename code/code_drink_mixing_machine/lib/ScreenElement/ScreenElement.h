#pragma once

#ifndef __SCREENELEMENT__
#define __SCREENELEMENT__

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/* Include custom made libraries */
#include "IO_Vector.h"
#include "DM_CONFIG.h"

/*

Screen element a generic virtual class for an on screen element

virtual class on which implemented screen elements are based on

Every screen element should have

    update
    draw
    forcedraw

examples of on screen elements;
    button
    text display
    text input
    ....

*/

class ScreenElement {
    private:

    protected:

    public:
    
    int pos_x;
    int pos_y;

    int width;
    int height;
    int border_size;

    bool rounded_corner;


    ScreenElement();
    ScreenElement(int pos_x_input, int pos_y_input, int width_input, int height_input, int border_size_input, bool rounded_corner_input);

    virtual bool Draw(MCUFRIEND_kbv *screen, uint32_t dt_ms);

    virtual bool ForceDraw(MCUFRIEND_kbv *screen);

    virtual bool Update(const InputVector &user_input, OutputVector &machine_output_request, uint32_t  dt_ms);

};

#endif