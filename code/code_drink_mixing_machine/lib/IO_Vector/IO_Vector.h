#pragma once

#ifndef __IO_VECTOR__
#define __IO_VECTOR__

struct InputVector {
    int joystick_x; // Valid ranges [0, 1023]
    int joystick_y; // Valid ranges [0, 1023]
    bool button_confirm; // Valid ranges [true, false]
    bool button_return; 
    float weight; // The value of which is read from the weight sensor
};

struct OutputVector {

};

#endif