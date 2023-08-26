/*

Object to store User Input (joystick state, button states) and pass into objects which handles logic

*/
#pragma once
#ifndef __INPUTVECTOR__
#define __INPUTVECTOR__

struct InputVector {
    int joystick_x; // Valid ranges [0, 1023]
    int joystick_y; // Valid ranges [0, 1023]
    bool button_confirm; // Valid ranges [true, false]
    bool button_return; 
    float weight; // The value of which is read from the weight sensor
};

#endif