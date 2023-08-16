#ifndef __DRINKMACHINE__
#define __DRINKMACHINE__

/* Include Custom Headers */
#include "InputVector.h"

/* Include Standard Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h" 
#include <MCUFRIEND_kbv.h>

class DrinkMachine {


/* Public Functions */
public:

DrinkMachine(MCUFRIEND_kbv *screen); // Constructor

bool Render(MCUFRIEND_kbv *screen, int dt_ms); // Renders state of DrinkMachien
bool Update(const InputVector &user_input, int dt_ms);

};

#endif
