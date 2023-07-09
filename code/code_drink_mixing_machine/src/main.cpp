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

void testing_splash_screen(int nr_poured_drinks, int cl_poured);
void draw_filled_glass(int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4);

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
    testing_splash_screen(69, 420);
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


void testing_splash_screen(int nr_poured_drinks, int cl_poured)
{
  tft.fillScreen(WHITE);

  //String titleText = "Groggbot 3!";
  //int x1 = 0, y1=0, w=0, h=0;
  //tft.getTextBounds(&titleText, 0, 0, &x1, &y1, &w, &h);


  tft.fillRoundRect(20, 5, SCREEN_WIDTH - 2 *20, 60, 5, GREY);
  tft.fillRoundRect(25, 10, SCREEN_WIDTH - 2*25, 50, 5, BLACK);
  tft.setCursor(65, 23);
  tft.setTextSize(3);
  tft.print("Groggbot 3!!");


  draw_filled_glass(37, 85, SCREEN_WIDTH - 74, 275, 25, 3, 3, 3, 7);

  tft.setCursor(20, 400);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("Poured " + String(nr_poured_drinks) + " drinks so far!");
  tft.setCursor(20, 430);
  tft.setTextSize(2);
  tft.println("That is a total of " + String(cl_poured) + " cl poured!");
 


}


void draw_filled_glass(int x0, int y0, int width, int height, float glass_volume_cl, float proc_1, float proc_2, float proc_3, float proc_4)
{
  
  int center_x = (x0 + width)/2;

  tft.drawLine(x0, y0, x0+width, y0, BLACK);
  tft.drawLine(x0, y0, x0 + width/5, y0 + height, BLACK);
  tft.drawLine(x0 + width, y0, x0 + (width/5)*4, y0 + height, BLACK);
  tft.drawLine(x0 + width/5, y0 + height,  x0 + (width/5)*4, y0 + height, BLACK);

  tft.fillTriangle()
}

void loop(void) {
    delay(1000);

    

    Serial.println("loop success");
}

