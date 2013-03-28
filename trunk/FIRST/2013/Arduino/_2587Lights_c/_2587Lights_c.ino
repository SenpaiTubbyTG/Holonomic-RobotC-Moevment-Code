#include <SPI.h>
#include <Wire.h>
#include <LPD8806.h>
/********************************************************************************/
uint32_t Wheel(uint16_t WheelPos);
void setLEDs(int type);
void setLEDs(int type, int r, int g, int b);
/********************************************************************************/

const int leds = 25;
const int dataPin = 2;
const int clockPin = 3;
LPD8806 strip = LPD8806(leds, dataPin, clockPin);

void setup() {
  strip.begin();
  Wire.begin();
  strip.show();
}
boolean firstrun = true;
void loop() {
   while(Wire.available() < 2);
   double a = Wire.read() / 127; // 100%
   double a10 = Wire.read() / 127; // 10%
   while(Wire.available() < 4);
   double t = (Wire.read() / 127) * (1 / a);
   double r = (Wire.read() / 127) * (1 / a);
   double g = (Wire.read() / 127) * (1 / a);
   double b = (Wire.read() / 127) * (1 / a);
   if (((int) (t * 127)) >= 20)
     setLEDs((int) (t * 127),(int) (r * 255),(int) (g * 255),(int) (b * 255));
   else 
     setLEDs(t);
   delay(20);
   
}

const int RANDOM = 10, RAINBOW = 11;
const int CUSTOM = 20;

void setLEDs(int type, int r, int g, int b) {
 if (type != 20)
   return;
 uint32_t color = strip.Color(r, g, b);
 for(int i=0; i<strip.numPixels(); i++) {
   strip.setPixelColor(i, color);
   strip.show();
 }
}
void setLEDs(int type) {
 if (type < 20) {
    if (type == 10) {
      for(int i=0; i<strip.numPixels(); i++) {
        uint32_t color = strip.Color(random(225), random(225), random(225));
        strip.setPixelColor(i, color);
        strip.show();
      }
    } else if (type == 11) {
      for (int j=0; j < 384 * 5; j++) {
        for (int i=0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(((i * 384 / strip.numPixels()) + j) % 384));
          strip.show();
        }
      }
    }
  }
}

uint32_t Wheel(uint16_t WheelPos) {
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128; // red down
      g = WheelPos % 128;       // green up
      b = 0;                    // blue off
      break;
    case 1:
      g = 127 - WheelPos % 128; // green down
      b = WheelPos % 128;       // blue up
      r = 0;                    // red off
      break;
    case 2:
      b = 127 - WheelPos % 128; // blue down
      r = WheelPos % 128;       // red up
      g = 0;                    // green off
      break;
  }
  return(strip.Color(r,g,b));
}
