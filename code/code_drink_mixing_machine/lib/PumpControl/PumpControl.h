#ifndef __PUMPCONTROL__
#define __PUMPCONTROL__

/*
Include libraries, external libraries must be specified in platform.io file
*/

#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include "Pump.h"

/*
Constants
*/

#define PC_SIZE_X 250.0f
#define PC_SIZE_Y 



class PumpControl {
public:

PumpControl();
bool Init(int x0, int y0, int width, int height);

bool SetPumpVolume(int pump_nr, float volume, float glass_max_volume);
bool SetPumpHighlight(int pump_nr);

bool PourDrink();

bool Render(MCUFRIEND_kbv *screen);

/*
Private variables
*/

// Box location and size
int x0_, y0_, width_, height_;

// Individual Pump Controls
Pump pump_1, pump_2, pump_3, pump_4;

};

#endif