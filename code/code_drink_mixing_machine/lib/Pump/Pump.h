#ifndef __PUMP__
#define __PUMP__

/*
Include libraries, external libraries must be specified in platform.io file
*/
#include <Arduino.h>
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>


/*
Local constants
*/

#define ICON_SIZE_X 100
#define ICON_SIZE_Y 85
#define HIGHLIGHT_WIDTH 4

class Pump {
public:

Pump(int x0, int y0, int pump_pin_nr, int pump_nr);
Pump();
bool Init(int x0, int y0, int pump_pin_nr, int pump_nr);

bool ForceReRender();

bool SetHighlight(uint16_t colour);
bool RemoveHighlight();

bool SetVolume(float amount);
float GetVolume();

bool Render(MCUFRIEND_kbv *screen);



private:

int x0_, y0_;
int pump_nr_;
int pump_pin_nr_;

float pump_volume_;
float last_pump_volume_; // Save last known pump volume, to indicate weather the amount is increasing or decreasing

bool is_highlighted_;
bool re_render_;
uint16_t colour_highlight;

};

#endif