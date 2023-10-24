#pragma once
#ifndef __MAINSCREEN__
#define __MAINSCREEN__

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>




/* Include custom libraries and header files */
#include "DM_Graphics_config.h"
#include "InputVector.h"
#include "DM_General_Config.h"
#include "PumpControl.h"

class MainScreen {

public:
/* Public Functions */
MainScreen(); // Constructor
bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); 
bool Update(const InputVector &user_input, uint32_t  dt_ms);

bool IsReadyToPour();
bool ResetReadyToPour();
bool GetDrinkAmounts(float* amount1, float* amount2, float* amount3,  float* amount4);

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

// True if user has pressed pour drink button and the pump amounts are valid.
bool ready_to_pour_drink;

// Internal state variables to keep track if screen elements have been cleared or not
bool cleared_screen;
bool last_render_pour_drink_highlight;
bool last_render_pour_drink_selected;
bool re_render_pour_drink_button;
bool last_render_randomize_drink_highlight;
bool last_render_randomize_drink_selected;
bool re_render_randomize_drink_button;
bool last_render_settings_highlight;
bool last_render_settings_selected;
bool re_render_settings_button;


};

#endif