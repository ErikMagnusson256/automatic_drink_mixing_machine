/*
Erik Magnusson 2023

Codebase for automatic drink mixing machine

Version = Alpha_0.1

A 3.5 inch TFT lcd screen displays the GUI.
GUI is handled using the MCUFRIEND_kbv and Adafruit_GFX libraries. Initial code is inspired by the hello world graphic test

User input is handled using a 2 axis joystick and two navigational buttons.

Code is run on an Arduino Mega 2560

*/

/* Include Standard Imported Libraries */
#include <Arduino.h>
#include <SPI.h>          
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>


/* Include Custom Libraries and headers created for the drink machine */
#include "PumpControl.h"
#include "InputVector.h"
#include "DM_Graphics_Config.h"
#include "DM_General_Config.h"

#include "DrinkMachine.h"

DrinkMachine drinkmachine;
MCUFRIEND_kbv tft;
InputVector user_input;

void setup();
void loop();

//PumpControl testPumpCtrl;

void setup() {

    randomSeed(analogRead(A15));

    Serial.begin(9600);
    uint32_t when = millis();
    //    while (!Serial) ;   //hangs a Leonardo until you connect a Serial
    if (!Serial) delay(5000);           //allow some time for Leonardo
    Serial.println("Serial took " + String((millis() - when)) + "ms to start");
    //    tft.reset();                 //hardware reset
    uint16_t ID = tft.readID(); //
    Serial.print("ID = 0x");
    Serial.println(ID, HEX);
    tft.begin(ID);

    
    /*
    //delay(1000);
    lcd_background(&tft);
    testPumpCtrl.Init(SCREEN_WIDTH/12, SCREEN_HEIGHT/6, SCREEN_WIDTH*10/12, SCREEN_HEIGHT*4/8 );
    testPumpCtrl.SetPumpHighlight(3);
    testPumpCtrl.Render(&tft);
    delay(1000);
    testPumpCtrl.SetPumpHighlight(2);
    testPumpCtrl.SetPumpVolume(3, 10.23, 15);
    testPumpCtrl.Render(&tft);
    delay(500);
    testPumpCtrl.SetPumpHighlight(1);
    testPumpCtrl.SetPumpVolume(1, 69, 100);
    testPumpCtrl.Render(&tft);

    delay(500);
    lcd_background(&tft);

    */

    /* Arduino Mega PIN configuration */

    pinMode(JOYSTICK_BUTTON_PIN, INPUT_PULLUP); 
    pinMode(BUTTON_OK_PIN, INPUT_PULLUP);
    pinMode(BUTTON_RETURN_PIN, INPUT_PULLUP);

    /*
    Incase EEPROM needs to be reset

    int reset_nr_drinks = 0;
    float reset_amount_poured = 0;
    EEPROM.put(EEPROM_ADR_NR_DRINKS, reset_nr_drinks);
    EEPROM.put(EEPROM_ADR_NR_CL, reset_amount_poured);

    */
    
    }

void loop() {

    /* Read user input and save states to "InputVector" storage object */
    int j_x = 1023 - analogRead(JOYSTICK_X_PIN);
    int j_y = 1023 - analogRead(JOYSTICK_Y_PIN);
    int joystick_press = digitalRead(JOYSTICK_BUTTON_PIN);
    int button_ok = digitalRead(BUTTON_OK_PIN);
    int button_return = digitalRead(BUTTON_RETURN_PIN);

    //Serial.println("j_x,j_y:" + String(j_x) + "," + String(j_y));

    user_input.joystick_x = j_x;
    user_input.joystick_y = j_y;

    if (joystick_press == 0)
        user_input.button_confirm = true;
    else
        user_input.button_confirm = false;


    /* Calculate the programming loop execution time to get a delta_t between iterations */
    static uint32_t t_old = 0;
    uint32_t t_now = millis();
    uint32_t dt = t_now - t_old;
    t_old = t_now;

    /* Render Drink Machine State */
    drinkmachine.Render(&tft, dt);

    /* Handle Drink Machine Logic */
    drinkmachine.Update(user_input, dt);

    delay(50);

}

