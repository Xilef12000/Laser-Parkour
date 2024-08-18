#include <Wire.h>

#define LED 6

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  Wire.flush();
  Wire.requestFrom(8, 2);
  while (Wire.available() < 2) {}
  byte b0, b1;
  b0 = Wire.read();
  b1 = Wire.read();
  /*Serial.print(b1, BIN);
  Serial.print(" ");
  Serial.print(b0, BIN);
  Serial.println(" ");*/
  uint16_t value = b0 + (b1 << 8);
  Serial.println(value);
  analogWrite(LED, map(value, 0, 1023, 0, 255));

  delay(200);
}