#pragma once
#ifndef __FLOATINPUTELEMENT__
#define __FLOATINPUTELEMENT__

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/* Include custom libraries and header files */
#include "DM_Graphics_config.h"
#include "InputVector.h"
#include "DM_General_Config.h"

/*
    A class to create a interacttable screen element - used to set a float variable

      ---------------------------------
    --------------------------------   |
    |  ^     <NAME>  < 1.56>     V  |  |
    --------------------------------  

    It shall have a highlight colour (i.e if virtual cursor is hovering on button)
    and a selected colour (i.e if virtual confirm button has been pressed whilst virtual cursor is hovering over button)
    
    User may increase the float value
*/

#define CLICKABLE_BUTTON_HIGHLIGHT_WIDTH 5

class FloatInputElement {

public:
/* Public Functions */
FloatInputElement(); // Constructor
FloatInputElement(int xpos_, int ypos_, int width_, int height_, uint16_t button_colour_, uint16_t highlight_colour_, uint16_t select_colour_, int text_size_ , uint16_t text_colour_, String float_name_, String float_unit_, float incdec_amount_); // Constructor
bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); 
bool Update(const InputVector &user_input, uint32_t  dt_ms);


// Get information out of button
bool GetIsHighlighted();
bool GetIsSelected();

// Set information to internal state variables of button
bool SetIsHighlighted(bool input);
bool SetIsSelected(bool input);

bool SetFloatVal(float inputval);
float GetFloatVal();

bool GetExitCondition();
bool ResetExitCondition();

private:

bool force_redraw;

int is_highlighed;
int is_selected;

//    <float_name>     <float_val>     <float_unit>
// I.e  "pour_amount"       3.67 cl         "cl"

String float_name;
float float_val;
float last_float_val;
float incdec_amount;    // How much the float value should increase or decrease each system tick
String float_unit; 

int xpos;
int ypos;
int width;
int height;
uint16_t button_colour;
uint16_t highlight_colour;
uint16_t select_colour;
int text_size; // According to <MCUFRIEND_kbv.h> library standard
uint16_t text_colour;

bool exit_logic_condition;

};

#endif