#include <Wire.h>
//#include <MPR121.h>
#include "Adafruit_MPR121.h"
Adafruit_MPR121 cap = Adafruit_MPR121();
//#include <ArduinoJson.h>
int state[3] = {0, 0, 0};
int Pin[3] = {7, 8, 9};
//int eeAddress = 0;
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    cap.begin(0x5A);
//    cap.setInterruptPin(15);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  Mpr_process();
}

void Mpr_process() {
  currtouched = cap.touched();
  for (uint8_t i = 0; i < 12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      if (state[i] == 0) {
        state[i] = 1;
        digitalWrite(Pin[i], state[i]);
      } else {
        state[i] = 0;
        digitalWrite(Pin[i], state[i]);
      }
    }
  }
  lasttouched = currtouched;
}
