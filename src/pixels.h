#ifndef pixels_h
#define pixels_h

#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

void setAll(Adafruit_NeoPixel &pix, uint32_t c){
  int16_t len = pix.numPixels();
  for(int i = 0; i < len; i++){
    pix.setPixelColor(i, c);
  }
  pix.show();
}

#endif
