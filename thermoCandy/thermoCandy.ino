//thermoCandy
//for kids only

////////////////////////////////////////////////
//https://github.com/adafruit/Adafruit_NeoPixel
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define pixelPin 4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 4, NEO_GRB + NEO_KHZ800);
//////////////////////////////////

////////////////////////////////////
//https://github.com/belidzs/PreciseLM35
#include <PreciseLM35.h>
const int pinLM35 = A0;
PreciseLM35 lm35(pinLM35, DEFAULT);
////////////////////////////////////

//////////////////
// https://github.com/arduino/Arduino/issues/3934
const int filterWeight = 8;  // higher numbers = heavier filtering
const int numReadings = 10;
int average = 0;                // the average

void setup() {
  Serial.begin(9600);
  pixels.begin();

  average = analogRead(pinLM35);
}

void loop() {
  int temp = lm35.readCelsius();

  for (int i = 0; i < numReadings; i++) {
    average = average + (temp - average) / filterWeight;
  }
  Serial.println(String(average) + " " + String(temp));

  byte red, green, blue;
  constrain(temp, 24, 32);
  red = map(temp, 24, 32, 0, 255);
  green = 255 - red;
  blue = 0;

  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.show();
  
}
