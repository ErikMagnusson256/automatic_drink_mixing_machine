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

private:
PumpControl pump_control;

};

#endif