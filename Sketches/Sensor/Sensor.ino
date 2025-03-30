// !IMPORTANT  set clockspeed do 1MHz

#include <Wire.h>
#include <EEPROM.h>

#define APIN A3
#define PIN 3
#define LED 1
#define OPENDRAIN PB4
#define ADDR 0x12  // individual adress for each chip, starting with 0x08

// EEPROM
#define EEDEVTYPE 0x01
#define EEDEVMODE 0x02

uint16_t value = 0;
uint8_t deviceType = 1;  // 0: undefined; 1: LDR Sensor; 2: start buzzer; 3: end buzzer
uint8_t deviceMode = 0;  // 0: get type; 1: curent value 2: hit/miss
uint16_t threshold = 240;
bool hit = 0;
bool hitold = 0;
bool nextI2CThreshold = 0;
uint8_t thresholdMSB = 0;

void setDeviceType(uint8_t t);
void setDeviceMode(uint8_t m);
void receiveEvent();
void requestEvent();

void setup() {
  Wire.begin(ADDR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  switch (deviceType) {
    case 1:
      pinMode(LED, OUTPUT);
      break;
    case 2:
    case 3:
      pinMode(LED, OUTPUT);
      pinMode(PIN, INPUT);
      break;
    default:
      break;
  }
  //EEPROM.get(EEDEVTYPE, deviceType);
  //EEPROM.get(EEDEVMODE, deviceMode);

  switch (deviceType) {
    case 1:
      while (true) {
        //value = (uint16_t)analogRead(APIN);
        value = ((uint16_t)analogRead(APIN) + 15 * value) / 16;
        hit = value > threshold;
        //analogWrite(LED, map(value, 0, 1023, 0, 255));
        digitalWrite(LED, hit);
        delay(10);
      }
      break;
    case 2:
    case 3:
      while (true) {
        value = (uint16_t)digitalRead(PIN);
        if (value == LOW) {
          digitalWrite(LED, LOW);
          DDRB |= (1 << OPENDRAIN);
          hit = 1;
        } else {
          digitalWrite(LED, HIGH);
          DDRB &= ~(1 << OPENDRAIN);
          hit = 0;
        }
      }
      break;
    default:
      while (true) {}
  }
}

void loop() {
}

void receiveEvent() {
  uint8_t r = Wire.read();
  uint8_t t = (r >> 4);
  uint8_t d = (r & 0b00001111);
  if (nextI2CThreshold) {
    threshold = (thresholdMSB << 8) | r;
    nextI2CThreshold = 0;
  } else {
    switch (t) {
      case 0b0001:
        setDeviceMode(d);
        break;
      case 0b0010:
        setDeviceType(d);
        break;
      case 0b0100:
        thresholdMSB = d;
        nextI2CThreshold = 1;
        break;
    }
  }
}
void requestEvent() {
  switch (deviceMode) {
    default:
    case 0:
    case 255:
      Wire.write(deviceType);
      break;
    case 1:
      switch (deviceType) {
        default:
        case 0:
        case 255:
          break;
        case 1:
        case 2:
        case 3:
          uint16_t data = value;
          uint8_t arr[2];
          arr[1] = data & 0xff;
          arr[0] = (data >> 8);
          Wire.write(arr[0]);
          Wire.write(arr[1]);
          break;
      }
      break;
    case 2:
      switch (deviceType) {
        default:
        case 0:
        case 255:
          break;
        case 1:
          Wire.write(hit & ~hitold);
          hitold = hit;
          break;
        case 2:
        case 3:
          Wire.write(hit);
          break;
      }
      break;
  }
}
void setDeviceType(uint8_t t) {
  deviceType = t;
  EEPROM.put(EEDEVTYPE, deviceType);
}
void setDeviceMode(uint8_t m) {
  deviceMode = m;
  //EEPROM.put(EEDEVMODE, deviceMode);
}
