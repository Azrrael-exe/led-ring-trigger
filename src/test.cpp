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

int rotary_pos = 0;

void setup() {
  Serial.begin(115200);
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
  rotary_pos = dip.getPosition();
}

void testLeds(Adafruit_NeoPixel &pixels){
  setAll(pixels, 0x00006400);
  for(int i=0; i<PIXEL_COUNT; i++){
    pixels.setPixelColor(i, 0x006400);
    pixels.show();
    delay(100);
  }
  setAll(pixels, 0x00000000);
}

void loop() {
  if(Serial.available()){
    String inp = Serial.readStringUntil('\n');
    if(inp == "leds"){
      Serial.println("test: Leds");
      testLeds(pixels);
    }
    else if(inp == "trigger"){
      Serial.println("test: Trigger");
      digitalWrite(TRIGGER_OUTPUT, 1);
      delay(350);
      digitalWrite(TRIGGER_OUTPUT,0);
    }
    else {
      Serial.println("invalid cmd");
    }
  }
  if(rotary_pos != dip.getPosition()){
    rotary_pos = dip.getPosition();
    char buffer[100];
    sprintf(buffer, "Rotary: %d", rotary_pos);
    Serial.println(buffer);
  }
  if(digitalRead(INPUT_BUTTON)){
    while(digitalRead(INPUT_BUTTON)){
      ;
    }
    Serial.println("Trigger Activated!");
  }
}