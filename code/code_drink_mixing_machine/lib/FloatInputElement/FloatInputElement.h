#pragma once
#ifndef __CLICKABLEBUTTON__
#define __CLICKABLEBUTTON__

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/* Include custom libraries and header files */
#include "DM_Graphics_config.h"
#include "InputVector.h"
#include "DM_General_Config.h"

/*
    A class to create a clickable button which can be reused easily

      --------------------------
    -------------------------   |
    |     Button Text        |  |
    -------------------------  

    It shall have a highlight colour (i.e if virtual cursor is hovering on button)
    and a selected colour (i.e if virtual confirm button has been pressed whilst virtual cursor is hovering over button)
    
*/

#define CLICKABLE_BUTTON_HIGHLIGHT_WIDTH 5

class ClickableButton {

public:
/* Public Functions */
ClickableButton(); // Constructor
ClickableButton(int xpos_, int ypos_, int width_, int height_, uint16_t button_colour_, uint16_t highlight_colour_, uint16_t select_colour_, String button_text_, int text_size_ , uint16_t text_colour_); // Constructor
bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); 
bool Update(const InputVector &user_input, uint32_t  dt_ms);



bool ResetButton();

// Get information out of button
bool GetIsHighlighted();
bool GetIsSelected();

// Set information to internal state variables of button
bool SetIsHighlighted(bool input);
bool SetIsSelected(bool input);

private:

bool force_redraw;

int is_highlighed;
int is_selected;

int xpos;
int ypos;
int width;
int height;
uint16_t button_colour;
uint16_t highlight_colour;
uint16_t select_colour;
String button_text;
int text_size; // According to <MCUFRIEND_kbv.h> library standard
uint16_t text_colour;

};

#endif