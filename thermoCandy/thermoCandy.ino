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

/////////////////////////////////
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


void setup() {
  Serial.begin(9600);
  pixels.begin();

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  int temp = lm35.readCelsius();
  
  total = total - readings[readIndex];
  readings[readIndex] = temp;
  total += readings[readIndex];
  readIndex += 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;
  Serial.println(String(average) + " " + String(temp));


  byte red, green, blue;
  constrain(average, 24, 38);
  red = map(average, 24, 32, 0, 255);
  green = 255 - red;
  blue = 0;

  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.show();

}
