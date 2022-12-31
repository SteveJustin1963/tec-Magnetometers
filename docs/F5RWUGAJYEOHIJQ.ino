/*
 * Magnetic Field Display by Andy Mitofsky, July 2019 
 * 
 * This progam draws axes and arrows on a TFT display.
 * It also displays an arrow showing the magnetic field.
 * 
 * Refs I used: 
 * - The adafruit graphics test library.
 * - This adafruit tutorial to set up the TFT and get needed libs:
 *   https://learn.adafruit.com/adafruit-1-44-color-tft-with-micro-sd-socket/overview
 * - The formulas for isometric projection from wikipedia:
     https://en.wikipedia.org/wiki/Isometric_projection
 */

 /* 
 *  Notes on Ranges: 
 *  
 *  The display has 128 by 128 pixels.
 *  Arduino analog inputs range from 0 to 1023
 *  For the MKR, use a 3.3V source for the sensors. 
 *  For the UNO, use a 5V source for the sensors.
 */

 /*
  * Info on wiring:
  * A1 - Connect the sensor pointing along x to A1 on the arduino.
  * A2 - Connect the sensor pointing along y to A2.
  * A3 - Connect the sensor pointing along z to A3.
  * For the sensor use 3.3V for supply (not 5V). 
  * 
  * 
  * Connect the following pins on the TFT display 
  * to the specified pins on the arduino. (NC=not connected) 
  * Pins of the display are on the left in the list.
  * Option 1, Arduino MKR1010
  * Vin -> 5V
  * 3v3 - NC
  * GND -> GND
  * SCK -> Pin 9, SCK
  * SO - NC
  * SI -> Pin 8, MOSI 
  * TCS -> Pin 5
  * RST -> Pin 4
  * D/C -> Pin 3
  * CCS - NC
  * Lite - NC
  * 
  * 
  * Option 2, Arduino Uno  
  * Vin -> 5V
  * 3v3 - NC
  * GND -> GND
  * SCK -> Pin 13, SCK
  * SO - NC
  * SI -> Pin 11, MOSI 
  * TCS -> Pin 10
  * RST -> Pin 9
  * D/C -> Pin 8
  * CCS - NC
  * Lite - NC
  * 
  */

  
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Color definitions
    #define BLACK    0x0000
    #define BLUE     0x001F
    #define RED      0xF800
    #define GREEN    0x07E0
    #define CYAN     0x07FF
    #define MAGENTA  0xF81F
    #define YELLOW   0xFFE0 
    #define WHITE    0xFFFF

//Set up the Display

    //Define some pins we'll use
      
    //For MKR1010 use these options
         #define TFT_CS 5
         #define TFT_RST 4
         #define TFT_DC 3
         #define TFT_MOSI 8
         #define TFT_SCLK 9

    //For Uno, uncomment the next lines
     //  #define TFT_CS 10
     //  #define TFT_RST 9
     //  #define TFT_DC 8    
     //  #define TFT_MOSI 11
     //  #define TFT_SCLK 13

   Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);



//Shift the picture up by voffset so that it fits on the screen better.
#define voffset  10
//Zoom is the zoom factor. Use 1 for no zoom. Use 2, 3, or higher for zoom.
#define zoom 1
 
//Use Vcc=3.3V for the sensors with the MKR1010. 
   #define vcc 3.3
//Use Vcc=5.0V for the sensors with the UNO.
   //#define vcc 5.0
 
void setup() {

  tft.initR(INITR_144GREENTAB); 
  tft.fillScreen(ST77XX_BLACK);
  delay(1000);
  
  
  
}

void loop() {
  
  tft.fillScreen(BLACK);
  drawAxes3d();
  drawArrow3d(analogRead(A1), analogRead(A2), analogRead(A3) );
  delay(1000); //Lower this for faster refresh.
  
}


void drawAxes3d()
{
  
    uint16_t startxx,startyy,stopxx,stopyy;
    startxx= isometricxx(128, 0, 0);
    startyy=isometricyy(128,0,0, voffset);
    stopxx=64;
    stopyy=64+voffset;
    tft.drawLine(startxx,startyy, stopxx,stopyy, RED);
    startxx= isometricxx(0,128, 0);
    startyy=isometricyy(0,128,0,voffset);
    stopxx=64;
    stopyy=64+voffset;
    tft.drawLine(startxx,startyy, stopxx,stopyy, RED);
    startxx= isometricxx(0,0,128);
    startyy=isometricyy(0,0,128, voffset);
    stopxx=64;
    stopyy=64+voffset;
    tft.drawLine(startxx,startyy, stopxx,stopyy, RED);
    tft.drawChar(108, 54, 'x', RED, BLACK, 1);
    tft.drawChar(67, 10, 'y', RED, BLACK,1);
    tft.drawChar(20, 54, 'z', RED, BLACK,1);


}


void drawArrow3d(int inxx, int inyy, int inzz)
{
  //Inputs inxx, inyy and inzz range 0 to 1023 
  //which correspond to voltages 0 to 3.3V or 0 to 5V.
  //The vector should be centered.
  int onexx,oneyy,onezz;
  int ppxx,ppyy,ppzz;
  int qqxx,qqyy,qqzz;

  //Find the endpoints of the arrow.
  
  //zoom is a zoom factor defined at the top of the program.
  //onexx, oneyy, and onezz range -128 to 128.
  onexx=zoom*(inxx-512)/4;
  oneyy=zoom*(inyy-512)/4;
  onezz=zoom*(inzz-512)/4;

  //ppxx and ppyy are the start of the arrow, and qqxx and qqyy are the end.
  ppxx=isometricxx(onexx,oneyy,onezz);
  ppyy=isometricyy(onexx,oneyy,onezz,voffset);
  qqxx=isometricxx(-1*onexx,-1*oneyy,-1*onezz);
  qqyy=isometricyy(-1*onexx,-1*oneyy,-1*onezz,voffset);

  //Draw the arrow with a circle for the tip.
  tft.drawLine(ppxx,ppyy,qqxx,qqyy, GREEN);
  tft.drawCircle(ppxx,ppyy, 3, BLUE);

  
  //Now print the voltage on the bottom of the screen
  String volts;
  double vxx,vyy,vzz;
  //Convert from the ADC value to a voltage;
  vxx=inxx*vcc/1024.0;
  vyy=inyy*vcc/1024.0;
  vzz=inzz*vcc/1024.0;
  // tft.fillRect(5, 100, 50, 128, BLACK);
  tft.setTextColor(MAGENTA);
  tft.setTextSize(1);
  tft.setTextWrap(true);
  tft.setCursor(5,100);
  volts="x=";
  volts=volts+vxx;
  volts=volts+"V";
  tft.println(volts);
  tft.setCursor(5,110);
  volts="y=";
  volts=volts+vyy;
  volts=volts+"V";
  tft.println(volts);
  tft.setCursor(5,120);
  volts="z=";
  volts=volts+vzz;
  volts=volts+"V";
  tft.println(volts);

}



int isometricxx(double inxx, double inyy, double inzz)
{
   //This is the isometric projection transformation from
   //https://en.wikipedia.org/wiki/Isometric_projection
   //This takes in raw values and returns the projection in the xy plane
   //If input ranges -128 to 128, output will range 0 to 128
   double outxx;
   int outpixelxx;
   outxx=(inxx-inzz)/sqrt(2);
   outpixelxx=round((outxx/2)+64);
   return outpixelxx;
}
    


int isometricyy(double inxx, double inyy, double inzz, int offset)
{ 
   //This is the isometric projection transformation from
   //https://en.wikipedia.org/wiki/Isometric_projection
   //This takes in raw values and returns the projection in the xy plane 
   //If input ranges -128 to 128, output will range voffset to voffset+128
   double outyy;
   int outpixelyy;
   outyy=-(inxx+2*inyy+inzz)/sqrt(6);
   outpixelyy=round((outyy/2)+64+voffset);
   return outpixelyy;
}
