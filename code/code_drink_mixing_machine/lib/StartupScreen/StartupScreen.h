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
#include "EEPROM.h"


/* Include custom libraries and header files */
#include "DM_CONFIG.h"
#include "IO_Vector.h"
#include "ScreenBase.h"


/* Constants */
#define LOADING_SCREEN_DURATION_MS 7000
#define LOADING_SCREEN_PAUSE 1500

class StartupScreen {

public:
/* Public Functions */
StartupScreen(); // Constructor
bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); 
bool Update(const InputVector &user_input, uint32_t  dt_ms);

/* Set/Get Functions */
float GetGlasSize();
bool IsSetupFinnished();

private:
/* Private Functions */


private:
/* Variables */
float glas_size; //cl
bool finnished_loading_screen;
uint32_t loading_screen_timer;
bool re_render_selecing_screen;
bool finnished_selecting_glass_size_screen;

bool finnished_setup; // True if the whole startup/setup procedure is finnished

};

#endif