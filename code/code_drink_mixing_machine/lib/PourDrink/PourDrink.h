#pragma once
#ifndef __POURDRINK__
#define __POURDRINK__

/* Include standard library Headers */
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>

/* Include custom libraries and header files */
#include "DM_Graphics_config.h"
#include "InputVector.h"
#include "DM_General_Config.h"

/*
    
    Pour drink screen general idea

    1. New pump volume amounts are set
    2. Clear screen and draw standard background
    3. Ask user to confirm to that empty glass is placed [OK] [RETURN]
    4. Start pouring
    5. Whilst pouring have an [PRESS TO STOP POURING] button on screen. A glass should be filling contously on screen
    6. When done pouring. Ask user to confirm that glass is removed
    */

class PourDrink {

public:
/* Public Functions */
PourDrink(); // Constructor
bool Render(MCUFRIEND_kbv *screen, uint32_t dt_ms); 
bool Update(const InputVector &user_input, uint32_t  dt_ms);

// Interface to set how many cl of liquid to pour from each pump
bool InsertPumpAmounts(float amount1_, float amount2_, float amount3_, float amount4_);

bool ResetPourDrinkScreen();

bool IsDone();

private:

int screen_x_cursor; // Virtual cursor x
int screen_y_cursor; // Virtual cursor y

bool screen_reset;
bool is_screen_done;

float amount1;
float amount2;
float amount3;
float amount4;

float empty_glass_weight;

};

#endif