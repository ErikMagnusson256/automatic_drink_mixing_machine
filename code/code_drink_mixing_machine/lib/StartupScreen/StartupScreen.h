#ifndef __STARTUPSCREEN__
#define __STARTUPSCREEN__

/*
Object to collect logic and illustrations related to the startup procedure
of the drink mixing machine

Upon startup the display shall show a loading screen and a glass size confirmation screen

*/

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/* Include custom libraries and header files */
#include "DM_Graphics_config.h"
#include "InputVector.h"

class StartupScreen {

/* Public Functions */
StartupScreen(); // Constructor
bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); 
bool Update(const InputVector &user_input, uint32_t  dt_ms);


};

#endif