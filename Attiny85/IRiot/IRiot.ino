//more info at https://github.com/shenkarSElab/IRiot

/*
 * "With timer1 running off the PLL @ 64mhz, tone() should be able to output a 32mhz signal on pin 4!"
 */
 
#include "tiny_IRremote.h"

#define ledPin    0     // pin5 / PB0
//#define touchPin  
IRsend irsend;          // pin3 / PB4 / Digital 4 / TIMER1 output compare unit

//change 00000 to a NEC code!
#define YOUR_NEC_CODE 9000

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
      send_ir();
    } else {
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);

  }
}

void send_ir() {
  irsend.sendNEC(YOUR_NEC_CODE, 32); // sending the nec code
}
