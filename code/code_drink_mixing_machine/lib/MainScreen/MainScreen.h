#pragma once
#ifndef __MAINSCREEN__
#define __MAINSCREEN__

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>




/* Include custom libraries and header files */
#include "IO_Vector.h"
#include "DM_CONFIG.h"
#include "PumpControl.h"

class MainScreen {

public:
/* Public Functions */
MainScreen(); // Constructor
bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); 
bool Update(const InputVector &user_input, uint32_t  dt_ms);

private:
PumpControl pump_control;

int screen_x_cursor; // Virtual cursor x
int screen_y_cursor; // Virtual cursor y

// Menu selection flags, If menu is active flag is set true
bool p1_selected;
bool p2_selected;
bool p3_selected;
bool p4_selected;
bool pour_drink_selected;
bool randomize_drink_selected;
bool settings_selected;

// Extra Menu highligt flags, pump highlight flages are stored in pumpcontrol object
bool pour_drink_highlight;
bool randomize_drink_highlight;
bool settings_highlight;

};

#endif