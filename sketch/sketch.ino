#include "LaserParkour.h"
LaserParkour parkour;
void setup(){
    Serial.begin(9600);
}
void loop(){
    parkour.test();
    delay(1000);
    exit(0);
}