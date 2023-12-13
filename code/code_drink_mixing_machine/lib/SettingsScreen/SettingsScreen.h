#pragma once
#ifndef __SETTINGS_SCREEN__
#define __SETTINGS_SCREEN__

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/* Include custom libraries and header files */
#include "DM_Graphics_config.h"
#include "InputVector.h"
#include "DM_General_Config.h"
#include "ClickableButton.h"
#include "FloatInputElement.h"

/*
    Settings Screeen general idea

    The settings screen should have a list of parameters which the user can configure

    There are both volatile and non volatile parameters which the user can configure

    Buttons on screen

            [Apply changes & Return]

            - Volatile Parameters -

            [ Glass Size | 3 cl ] 

            - Non Volatile Parameters - 

            [ Loadcell 50g calibration point | 556.97 ]

            [ Loadcell 200g calibration point | 235.786 ]

            - Manuall pump actuation -

            [ Pump 1 ]
            [ Pump 2 ]
            [ Pump 3 ]
            [ Pump 4 ]


*/

class SettingsScreen {

public:
/* Public Functions */
SettingsScreen(); // Constructor
bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); 
bool Update(const InputVector &user_input, uint32_t  dt_ms);

bool ResetScreen();

bool GetIsDone();

private:

/* Clickable buttons */
ClickableButton returnButton;
ClickableButton forcePumpOn_1;
ClickableButton forcePumpOn_2;
ClickableButton forcePumpOn_3;
ClickableButton forcePumpOn_4;

/* Variable input buttons */
FloatInputElement glassSizeFloatInput;
FloatInputElement loadCellCalPointFloatInput1;
FloatInputElement loadCellCalPointFloatInput2;

// Use a non clickable button as information display
ClickableButton displayCurrentLoadCellWeight;


bool is_done;
bool reset_screen_gui;

int cursor_y_pos;


};

#endif