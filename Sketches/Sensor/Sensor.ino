// !IMPORTANT  set clockspeed do 1MHz

#include <Wire.h>
#include <EEPROM.h>

#define APIN A3
#define PIN 3
#define LED 1
#define OPENDRAIN PB4
#define ADDR 0x10  // individual adress for each chip, starting with 0x08

// EEPROM
#define EEDEVTYPE 0x01
#define EEDEVMODE 0x02

uint16_t state = 0;
uint8_t deviceType = 3;  // 0: undefined; 1: LDR Sensor; 2: start buzzer; 3: end buzzer
uint8_t deviceMode = 0;  // 0: get type; 1: curent value

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
      while (true) {
        pinMode(LED, OUTPUT);
      }
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
        state = (uint16_t)analogRead(APIN);
        analogWrite(LED, map(state, 0, 1023, 0, 255));
        delay(100);
      }
      break;
    case 2:
    case 3:
      while (true) {
        state = (uint16_t)digitalRead(PIN);
        if (state == LOW) {
          digitalWrite(LED, LOW);
          DDRB |= (1 << OPENDRAIN);
        } else {
          digitalWrite(LED, HIGH);
          DDRB &= ~(1 << OPENDRAIN);
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
  switch (t) {
    case 0b0001:
      setDeviceMode(d);
      break;
    case 0b0010:
      setDeviceType(d);
      break;
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
          uint16_t value = state;
          uint8_t arr[2];
          arr[1] = value & 0xff;
          arr[0] = (value >> 8);
          Wire.write(arr[0]);
          Wire.write(arr[1]);
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
