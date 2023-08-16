#include <Arduino.h>
// All the mcufriend.com UNO shields have the same pinout.
// i.e. control pins A0-A4.  Data D2-D9.  microSD D10-D13.
// Touchscreens are normally A1, A2, D7, D6 but the order varies
//
// This demo should work with most Adafruit TFT libraries
// If you are not using a shield,  use a full Adafruit constructor()
// e.g. Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
//#include <Adafruit_TFTLCD.h>
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#include "PumpControl.h"
#include "InputVector.h"

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x7BEF

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif



void setup(void);
void loop(void);


void hello_world_lcd();
void lcd_background();
void center_text_box(int center_x, int center_y, String text, int16_t text_colour, int16_t outline_colour, int16_t infill_colour, int* width, int* height);

void testing_splash_screen(int nr_poured_drinks, int cl_poured);
void draw_filled_glass(int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4);

void fill_glass_animation(int duration, int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4);

int confirm_glass_size_screen();

bool DrawRandomizerScreen();

uint16_t g_identifier;

extern const uint8_t hanzi[];
void showhanzi(unsigned int x, unsigned int y, unsigned char index)
{
    uint8_t i, j, c, first = 1;
    uint8_t *temp = (uint8_t*)hanzi;
    uint16_t color;
    tft.setAddrWindow(x, y, x + 31, y + 31); //设置区域
    temp += index * 128;
    for (j = 0; j < 128; j++)
    {
        c = pgm_read_byte(temp);
        for (i = 0; i < 8; i++)
        {
            if ((c & (1 << i)) != 0)
            {
                color = RED;
            }
            else
            {
                color = BLACK;
            }
            tft.pushColors(&color, 1, first);
            first = 0;
        }
        temp++;
    }
}

PumpControl testPumpCtrl;

void setup(void) {
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

    

    //hello_world_lcd();
    //testing_splash_screen(69, 420);
    //delay(5000);
    //confirm_glass_size_screen();

    //delay(1000);
    lcd_background();
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
    lcd_background();

    // Draw wheel


    // Initialise button

    pinMode(14, INPUT_PULLUP); 
    pinMode(15, INPUT_PULLUP);
    pinMode(16, INPUT_PULLUP);
    

    }




void printmsg(int row, const char *msg)
{
    tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(0, row);
    tft.println(msg);
}

void hello_world_lcd()
{
  tft.fillScreen(BLACK);
    tft.setTextColor(RED);

    tft.setCursor(0,0);
    tft.setTextSize(0);
    tft.println("Hello world");

    tft.setCursor(0,50);
    tft.setTextSize(1);
    tft.println("Hello world 2");

    tft.setCursor(0,100);
    tft.setTextSize(2);
    tft.println("Hello world 3");

    tft.setCursor(0,150);
    tft.setTextSize(4);
    tft.print("Hello world 3");

    

    tft.setCursor(50, 400);
    tft.drawFastHLine(0, 150, SCREEN_WIDTH, YELLOW);
    tft.drawRect(150, 350, 50, 50, CYAN);
    tft.fillRect(155, 355, 40, 40, MAGENTA);
}

void lcd_background()
{
    tft.fillScreen(WHITE);

  //String titleText = "Groggbot 3!";
  //int x1 = 0, y1=0, w=0, h=0;
  //tft.getTextBounds(&titleText, 0, 0, &x1, &y1, &w, &h);


  tft.fillRoundRect(20, 5, SCREEN_WIDTH - 2 *20, 60, 5, GREY);
  tft.fillRoundRect(25, 10, SCREEN_WIDTH - 2*25, 50, 5, BLACK);
  tft.setCursor(65, 23);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Groggbot 3!!");
  
 //int w,h;
 //tft.setTextSize(3);
 //center_text_box(SCREEN_WIDTH/2, 40, "Groggbot 3!", WHITE, GREY, BLACK, &w, &h);
 
}

void testing_splash_screen(int nr_poured_drinks, int cl_poured)
{
  
    lcd_background();

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

    lcd_background();

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

bool DrawRandomizerScreen()
{

    int circle_center_x = SCREEN_WIDTH/2,
        circle_center_y = SCREEN_HEIGHT/2,
        circle_radius = 50;

    for(float i = 0 ; i < 2*PI; i += PI/180)
    {
        tft.drawLine(circle_center_x, circle_center_y, circle_radius*cos(i), circle_center_y*sin(i), RED);
    }

}

void center_text_box(int center_x, int center_y, String text, int16_t text_colour, int16_t outline_colour, int16_t infill_colour, int* width, int* height)
{
    int cursor_x = 0, cursor_y = 0;

    int16_t x0, y0;
    uint16_t w, h;
    //String tempString = "xxxx cl";
    tft.getTextBounds(text.c_str(), cursor_x, cursor_y, &x0, &y0, &w, &h);
    
    float outline_scale = 1.25;
    int radius = 5;
    tft.fillRoundRect((center_x - w/2), (center_y - h/2), w*outline_scale, h*outline_scale, radius, outline_colour); //background box
    tft.fillRoundRect((center_x - w/2), (center_y - h/2), w, h, radius, infill_colour); //foreground box
    tft.setCursor(center_x - w/2, center_y - h/2);
    tft.setTextColor(text_colour);
    tft.println(text);

    //Serial.println("x0:" + String(x0) + " y0:" + String(y0) + " w:" + String(w) + " h:" + String(h));
}

void loop(void) {

    int j_x = 1023 - analogRead(A8);
    int j_y = 1023 - analogRead(A9);
    int joystick_press = digitalRead(14);
    int button_ok = digitalRead(15);
    int button_return = digitalRead(16);

    InputVector testInput;

    testInput.joystick_x = j_x;
    testInput.joystick_y = j_y;

    if (joystick_press == 0)
        testInput.button_confirm = true;
    else
        testInput.button_confirm = false;


    Serial.println("Jx=" + String(j_x) + ",jy=" + String(j_y)+",joystick_press=" + String(joystick_press) + ",button_ok=" + String(button_ok) + ",button_return=" + String(button_return));
    delay(100);

    int x = ((float)j_x / 1023.0)*SCREEN_WIDTH;
    int y = ((float)j_y / 1023.0)*SCREEN_HEIGHT;

    //tft.drawPixel(x, y, RED);
    tft.drawCircle(x,y,5,RED);

    Serial.println("x,y=" + String(x) + "," + String(y));
}

