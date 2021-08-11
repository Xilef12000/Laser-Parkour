////////////////////////////////
//Laser-Parkour sketch        //
//                            //
//by Linus Prange             //
//and Manuel König            //
////////////////////////////////

#include "laser_parkour.h"

#define diodes_pin 0 //(analog)pin of the photo-diodes, normally (analog)pin 0
#define start_pin 12 //pin of start button, normally pin 13
#define stop_pin 11 //pin of stop button, normally pin 12
#define baudrate 9600 //Serial comunication speed/baudrate, normally 9600

laser_parkour parkour;
void started(){
  Serial.println("start");
}
void stopped(){
  Serial.println("stop");
}
void failed(){
  Serial.println("fail");
}
void setup() {
  Serial.begin(baudrate); //Start serial comunication
  Serial.setTimeout(10); //timeout for reciving strings in ms
  parkour.begin(diodes_pin, start_pin, stop_pin);
  parkour.onstart(started);
  parkour.onstop(stopped);
  parkour.onfail(failed);
  parkour.game();
}

void loop() {
}
