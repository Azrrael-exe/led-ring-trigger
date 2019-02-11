#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#include "rotary.h"
#include "pixels.h"

#define PIXEL_COUNT 24
#define PIXEL_PIN 3
#define P1 4
#define P2 5
#define P3 6
#define P4 7
#define INPUT_BUTTON 11
#define TRIGGER_OUTPUT 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
Rotary dip = Rotary(P1, P2, P3, P4);

void setup() {
  dip.init();
  pinMode(INPUT_BUTTON, INPUT);
  pixels.begin();
  setAll(pixels, 0x00FF0000);
  delay(100);
  setAll(pixels, 0x0000FF00);
  delay(100);
  setAll(pixels, 0x000000FF);
  delay(100);
  setAll(pixels, 0x00000000);
}

void loop() {
  if(digitalRead(INPUT_BUTTON)){
    while(digitalRead(INPUT_BUTTON)){
      ;
    }
    // --- Step Zero: Calculate timers
    uint8_t total_time = (4 + dip.getPosition())*1000;         // Total time of the process
    float step = float(PIXEL_COUNT)/float(total_time);  // Time of each step
    
    // --- Step One: Set all Green
    setAll(pixels, 0x00006400);                         // Set all to Green

    // --- Step Two: Countdown
    for(int i=0; i<PIXEL_COUNT; i++){
      long timer = millis();
      pixels.setPixelColor(i, 0x00000000);
      pixels.show();
      delay(step);
    }

    // --- Step Tree: Trigger the Camera
    digitalWrite(TRIGGER_OUTPUT, 1);
    delay(350);
    digitalWrite(TRIGGER_OUTPUT,0);
  }
}