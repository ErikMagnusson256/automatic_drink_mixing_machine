#pragma once

#ifndef __IO_VECTOR__
#define __IO_VECTOR__

#include "Arduino.h"
#include "vector.h"

struct InputVector {
    int joystick_x; // Valid ranges [0, 1023]
    int joystick_y; // Valid ranges [0, 1023]
    bool button_confirm; // Valid ranges [true, false]
    bool button_return; 
    float weight; // The value of which is read from the weight sensor
};

typedef enum {DIGITAL_OUT, ANALOG_OUT, PWM_OUT} PIN_TYPE;

typedef struct PIN {                
    int pin_value;
    // PIN_TYPE pin_type;
    String debug_string_msg; // Used for debugging, set manually by developer, set a comment where pin_value is set
    int nr_writes_to; // // Used for debugging, set manually by developer, increase by 1 every time something writes to pin
};

struct OutputVector {
    PIN pump1_out_pin;
    PIN pump2_out_pin;
    PIN pump3_out_pin;
    PIN pump4_out_pin;
};

#endif