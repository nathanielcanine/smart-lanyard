
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x141F
#define	RED     0xF800
#define	GREEN   0x07E0
#define ORANGE    0xFC00
#define PURPLE 0xA01F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 30
int PENRADIUS = 1;
int oldcolor, currentcolor;
int old2, current2;
int backgroundcolor;

void setup(void) {
  Serial.begin(9600);
  
  tft.reset();
  
  uint16_t identifier=0x9341;

  tft.begin(identifier);
  tft.setRotation(2);

  tft.fillScreen(WHITE);
  backgroundcolor = WHITE;
  tft.fillRect(0, 0, BOXSIZE*8, BOXSIZE*2, WHITE);
  draw();
  pinMode(13, OUTPUT);
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void loop()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
   
    
    
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    //p.x = tft.width()-map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
     p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
     //p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
   
    if (p.y < BOXSIZE) {
       oldcolor = currentcolor;

       if (p.x < BOXSIZE) { 
         currentcolor = RED; 
         tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (p.x < BOXSIZE*2) {
         currentcolor = ORANGE;
         tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (p.x < BOXSIZE*3) {
         currentcolor = YELLOW;
         tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (p.x < BOXSIZE*4) {
         currentcolor = GREEN;
         tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (p.x < BOXSIZE*5) {
         currentcolor = BLUE;
         tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (p.x < BOXSIZE*6) {
         currentcolor = PURPLE;
         tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (p.x < BOXSIZE*7) {
         currentcolor = BLACK;
         tft.drawRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);
       } else if (p.x < BOXSIZE*8) {
           tft.fillScreen(WHITE);
           backgroundcolor = WHITE;
           tft.fillRect(0, 0, BOXSIZE*8, BOXSIZE*2, WHITE);
           draw();  
       }
    }
    else if(p.y < BOXSIZE*2)
    {
      old2 = current2;
      if (p.x < BOXSIZE) { 
         current2 = 1; 
         tft.drawRect(0, BOXSIZE, BOXSIZE, BOXSIZE, RED);
         PENRADIUS = 1;
       } else if (p.x < BOXSIZE*2) {
         current2 = 2;
         tft.drawRect(BOXSIZE, BOXSIZE, BOXSIZE, BOXSIZE, RED);
         PENRADIUS = 2;
       } else if (p.x < BOXSIZE*3) {
         current2 = 3;
         tft.drawRect(BOXSIZE*2, BOXSIZE, BOXSIZE, BOXSIZE, RED);
         PENRADIUS = 3;
       } else if (p.x < BOXSIZE*4) {
         current2 = 4;
         tft.drawRect(BOXSIZE*3, BOXSIZE, BOXSIZE, BOXSIZE, RED);
         PENRADIUS = 4;
       } else if (p.x < BOXSIZE*5) {
         current2 = 5;
         tft.drawRect(BOXSIZE*4, BOXSIZE, BOXSIZE, BOXSIZE, RED);
         PENRADIUS = 5;
       } else if (p.x < BOXSIZE*6) {
         current2 = 6;
         tft.drawRect(BOXSIZE*5, BOXSIZE, BOXSIZE, BOXSIZE, RED);
         PENRADIUS = 6;
       } else if (p.x < BOXSIZE*7) {
          tft.fillScreen(currentcolor);
          backgroundcolor = currentcolor;
          draw();
       } else if (p.x < BOXSIZE*8) {
          current2 == 8;
          currentcolor = backgroundcolor;
          tft.drawRect(BOXSIZE*7, BOXSIZE, BOXSIZE, BOXSIZE, RED);
       }
       if (old2 != current2) {
          if (old2 == 1) tft.drawRect(0, BOXSIZE, BOXSIZE, BOXSIZE, BLACK);
          if (old2 == 2) tft.drawRect(BOXSIZE, BOXSIZE, BOXSIZE, BOXSIZE, BLACK);
          if (old2 == 3) tft.drawRect(BOXSIZE*2, BOXSIZE, BOXSIZE, BOXSIZE, BLACK);
          if (old2 == 4) tft.drawRect(BOXSIZE*3, BOXSIZE, BOXSIZE, BOXSIZE, BLACK);
          if (old2 == 5) tft.drawRect(BOXSIZE*4, BOXSIZE, BOXSIZE, BOXSIZE, BLACK);
          if (old2 == 6) tft.drawRect(BOXSIZE*5, BOXSIZE, BOXSIZE, BOXSIZE, BLACK);
          if (old2 == 8) tft.drawRect(BOXSIZE*7, BOXSIZE, BOXSIZE, BOXSIZE, BLACK);
       }
    }
    if (oldcolor != currentcolor) {
          if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
          if (oldcolor == ORANGE) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ORANGE);
          if (oldcolor == YELLOW) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, YELLOW);
          if (oldcolor == GREEN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, GREEN);
          if (oldcolor == BLUE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
          if (oldcolor == PURPLE) tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, PURPLE);
          if (oldcolor == BLACK) tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, BLACK);
          if (oldcolor == WHITE) tft.drawRect(BOXSIZE*7, BOXSIZE, BOXSIZE, BOXSIZE, BLACK);
       }
    if (((p.y-PENRADIUS) > BOXSIZE*2) && ((p.y+PENRADIUS) < tft.height())) {
      tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
  }
}
void draw()
{
  tft.fillRect(0, 0, BOXSIZE*8, BOXSIZE*2, WHITE);
         //Colors
          tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
          tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ORANGE);
          tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, YELLOW);
          tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, GREEN);
          tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
          tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, PURPLE);
          tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, BLACK);
          // Clear
          tft.drawLine(BOXSIZE*7, 0, BOXSIZE*8, BOXSIZE, RED);
          tft.drawLine(BOXSIZE*7, BOXSIZE, BOXSIZE*8, 0, RED);
          tft.drawFastVLine(BOXSIZE*7, 0, BOXSIZE, RED);
          tft.drawFastHLine(BOXSIZE*7, 0, BOXSIZE, RED);
          tft.drawFastVLine(BOXSIZE*8, 0, BOXSIZE, RED);
          tft.drawFastHLine(BOXSIZE*7, BOXSIZE, BOXSIZE, RED);
          
          // Pen Radius
          tft.fillCircle(BOXSIZE/2, BOXSIZE*3/2, 1, BLACK);
          tft.fillCircle(BOXSIZE*3/2, BOXSIZE*3/2, 2, BLACK);
          tft.fillCircle(BOXSIZE*5/2, BOXSIZE*3/2, 3, BLACK);
          tft.fillCircle(BOXSIZE*7/2, BOXSIZE*3/2, 4, BLACK);
          tft.fillCircle(BOXSIZE*9/2, BOXSIZE*3/2, 5, BLACK);
          tft.fillCircle(BOXSIZE*11/2, BOXSIZE*3/2, 6, BLACK);
          
          // Background Set
          tft.fillRect(BOXSIZE*6+BOXSIZE/4, BOXSIZE+BOXSIZE/4, BOXSIZE/2, BOXSIZE/2, BLACK);
          
          // Erase Button
          tft.setCursor(BOXSIZE*7+6, BOXSIZE+3);
          tft.setTextColor(RED);
          tft.setTextSize(3);
          tft.println("E");
          
          //Grid
          tft.drawFastHLine(0, BOXSIZE, TS_MAXX, BLACK);
          tft.drawFastHLine(0, BOXSIZE*2, TS_MAXX, BLACK);
          tft.drawFastVLine(0, 0, BOXSIZE*2, BLACK);
          tft.drawFastVLine(BOXSIZE, 0, BOXSIZE*2, BLACK);
          tft.drawFastVLine(BOXSIZE*2, 0, BOXSIZE*2, BLACK);
          tft.drawFastVLine(BOXSIZE*3, 0, BOXSIZE*2, BLACK);
          tft.drawFastVLine(BOXSIZE*4, 0, BOXSIZE*2, BLACK);
          tft.drawFastVLine(BOXSIZE*5, 0, BOXSIZE*2, BLACK);
          tft.drawFastVLine(BOXSIZE*6, 0, BOXSIZE*2, BLACK);
          tft.drawFastVLine(BOXSIZE*7, BOXSIZE, BOXSIZE, BLACK);

          //Selection
          tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
          currentcolor = RED;
          tft.drawRect(0, BOXSIZE, BOXSIZE, BOXSIZE, RED);
          PENRADIUS = 1;
          current2 = 1;
}

