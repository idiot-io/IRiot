//thermoCandy
//for kids only

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 4, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin();
}

void loop() {
    pixels.setPixelColor(0, pixels.Color(44,0,100));
    pixels.show();
}
