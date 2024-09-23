#include <Wire.h>

#define PIN A3
#define LED 1
#define ADDR 0x08 // individual adress for each chip, starting with 0x08

uint16_t state = 0 ;

void setup() {
  Wire.begin(ADDR);
  Wire.onRequest(requestEvent);
  pinMode(LED, OUTPUT);
}

void loop() {
  state = (uint16_t) analogRead(PIN);
  analogWrite(LED, map(state, 0, 1023, 0, 255));
  delay(100);
}

void requestEvent() {
  uint16_t value = state;
  uint8_t arr[2];
  arr[1]=value & 0xff;
  arr[0]=(value >> 8);
  Wire.write(arr[0]);
  Wire.write(arr[1]);
}
