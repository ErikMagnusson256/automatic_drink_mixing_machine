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
void lcd_background();
void center_text_box(int center_x, int center_y, String text, int16_t text_colour, int16_t outline_colour, int16_t infill_colour, int* width, int* height);

void testing_splash_screen(int nr_poured_drinks, int cl_poured);
void draw_filled_glass(int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4);

void fill_glass_animation(int duration, int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4);

int confirm_glass_size_screen();

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
    delay(5000);
    confirm_glass_size_screen();
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

  draw_filled_glass(37, 85, SCREEN_WIDTH - 74, 275, 25, 3, 3, 3, 7);
  fill_glass_animation(100, 7, 85, SCREEN_WIDTH - 74, 275, 25, 3, 3, 3, 7);

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
  
  

  tft.drawLine(x0, y0, x0+width, y0, BLACK);
  tft.drawLine(x0, y0, x0 + width/5, y0 + height, BLACK);
  tft.drawLine(x0 + width, y0, x0 + (width/5)*4, y0 + height, BLACK);
  tft.drawLine(x0 + width/5, y0 + height,  x0 + (width/5)*4, y0 + height, BLACK);

  
}

void fill_glass_animation(int duration, int x0, int y0, int width, int height, float glass_volume_cl, float amount_1, float amount_2, float amount_3, float amount_4)
{
    int center_x = (x0 + width)/2;
    float h0 = y0 + height, w0 = width/5;
    float delta = atan(w0 / (5*h0));
    Serial.println("delta: " + String(delta));

    float center_width = (width/5)*3; 
    float tan_delta = tan(delta);
    Serial.println("tan delta:" + String(tan_delta));
    for(int i = 0; i < height; i++)
    {
        float layerwidth = 2*(tan_delta * i) + center_width;
        Serial.println("Layerwidth:" + String(layerwidth));

        tft.drawFastHLine(center_x - (layerwidth)/2, y0 + height - i, layerwidth, RED);
        delay(10);
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

    /*for (int t_delay = 50 ; t_delay < 2000 ; t_delay += 50)
    {
    //int t_delay = 100;
    tft.fillScreen(BLACK);
    tft.fillRect(100, 275, 200, 40, CYAN);
    tft.setCursor(110, 280);
    tft.setTextSize(1);
    tft.println("Test screen refresh rate " + String(t_delay));
   
    
    delay(t_delay);
    }
    */
    //Serial.println("loop success");
}

