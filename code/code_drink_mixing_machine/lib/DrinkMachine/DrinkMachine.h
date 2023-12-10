#ifndef __DRINKMACHINE__
#define __DRINKMACHINE__

/* Include Custom Headers */
#include "InputVector.h"
#include "StartupScreen.h"
#include "MainScreen.h"
#include "DM_Graphics_Config.h"
#include "PourDrink.h"
#include "SettingsScreen.h"

/* Include Standard Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h" 
#include <MCUFRIEND_kbv.h>

class DrinkMachine {


/* Public Functions */
public:

DrinkMachine(); // Constructor

bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); // Renders state of DrinkMachien
bool Update(const InputVector &user_input, uint32_t  dt_ms);

/* Private variables and objects */
private:

StartupScreen startup_screen;
MainScreen main_screen;
PourDrink pour_drink_screen;
SettingsScreen settings_screen;


};

#endif
