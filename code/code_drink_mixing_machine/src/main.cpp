/*
Erik Magnusson 2023

Codebase for automatic drink mixing machine

A 3.5 inch TFT lcd screen displays the GUI.
GUI is handled using the MCUFRIEND_kbv and Adafruit_GFX libraries. Initial code is inspired by the hello world graphic test

User input is handled using a 2 axis joystick and two navigational buttons.

Code is run on an Arduino Mega 2560

*/

#include <Arduino.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

/* Include Standard Imported Libraries */

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

/* Include Custom Libraries created for the drink machine */
#include "PumpControl.h"
#include "InputVector.h"
#include "DM_Graphics_config.h"


void setup();
void loop();






void testing_splash_screen(int nr_poured_drinks, int cl_poured);
void draw_filled_glass(int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4);

void fill_glass_animation(int duration, int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4);

int confirm_glass_size_screen();


PumpControl testPumpCtrl;

void setup() {
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



    /* Arduino Mega PIN configuration */

    pinMode(14, INPUT_PULLUP); 
    pinMode(15, INPUT_PULLUP);
    pinMode(16, INPUT_PULLUP);
    

    }

void testing_splash_screen(int nr_poured_drinks, int cl_poured)
{
  
    lcd_background(&tft);

  tft.setCursor(35, 80);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("Initializing...");

  tft.setCursor(20, 400);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("Poured " + String(nr_poured_drinks) + " drinks so far!");
  tft.setCursor(20, 430);
  tft.setTextSize(2);
  tft.println("That is a total of " + String(cl_poured) + " cl poured!");


  draw_filled_glass(37, 100, SCREEN_WIDTH - 74, 275, 25, 3, 3, 3, 3);
  fill_glass_animation(500, 37, 100, SCREEN_WIDTH - 74, 275, 13, 3, 3, 3, 3);

}


void draw_filled_glass(int x0, int y0, int width, int height, float glass_volume_cl, float proc_1, float proc_2, float proc_3, float proc_4)
{
  
  

  tft.drawLine(x0, y0, x0+width, y0, BLACK);
  tft.drawLine(x0, y0, x0 + width/5, y0 + height, BLACK);
  tft.drawLine(x0 + width, y0, x0 + (width/5)*4, y0 + height, BLACK);
  tft.drawLine(x0 + width/5, y0 + height,  x0 + (width/5)*4, y0 + height, BLACK);

  
}

void fill_glass_animation(int duration, int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4)
{
    int delta_t = height/duration;
    int center_x = (x0 + width)/2;
    float h0 = y0 + height, w0 = width/5;
    float delta = atan(w0 / (5*h0));
    Serial.println("delta: " + String(delta));
    //delta = 5;

    float center_width = (width/5)*3; 
    float tan_delta = tan(delta);
    tan_delta = 0.18; //???
    Serial.println("tan delta:" + String(tan_delta));
    for(int i = 0; i < height; i++)
    {
        float layerwidth = 2*(tan_delta * i) + center_width;
        Serial.println("Layerwidth:" + String(layerwidth));

        uint16_t glass_fill_colour = RED;
        if ((float)i / (float)height > 0 / glass_volume_cl)
            glass_fill_colour = YELLOW;
        if ((float)i / (float)height > (amount_1) / glass_volume_cl)
            glass_fill_colour = BLUE;
        if ((float)i / (float)height > (amount_1 + amount_2) / glass_volume_cl)
            glass_fill_colour = GREEN;
        if ((float)i / (float)height > (amount_1 + amount_2 + amount_3) / glass_volume_cl)
            glass_fill_colour = MAGENTA;
        if ((float)i / (float)height > (amount_1 + amount_2 + amount_3+amount_4) / glass_volume_cl)
            return;
       

        tft.drawFastHLine(SCREEN_WIDTH/2 - (layerwidth)/2, y0 + height - i, layerwidth, glass_fill_colour);
        delay(delta_t);
    }
}

int confirm_glass_size_screen()
{

    lcd_background(&tft);

    tft.setTextColor(BLACK);
    tft.setCursor(40, 100);
    tft.setTextSize(3);
    tft.println("Please confirm \n  glass size!");

    tft.drawRoundRect(120, 250, 60, 60, 7, BLACK);
    tft.setCursor(120, 250);
    tft.setTextSize(2);
    int temp = 25;
    tft.println(String(temp) + " cl");



    return 0;
}



void loop() {

    /* Read user input and save states to "InputVector" storage object */
    int j_x = 1023 - analogRead(A8);
    int j_y = 1023 - analogRead(A9);
    int joystick_press = digitalRead(14);
    int button_ok = digitalRead(15);
    int button_return = digitalRead(16);

    
    InputVector user_input;

    user_input.joystick_x = j_x;
    user_input.joystick_y = j_y;

    if (joystick_press == 0)
        user_input.button_confirm = true;
    else
        user_input.button_confirm = false;


    /* Calculate the programming loop execution time to get a delta_t between iterations */

    static uint32_t  t_old = 0;


    /* Handle Drink Machine Logic */
    // @todo

    /* Render Drink Machine State */
    // @todo

}

