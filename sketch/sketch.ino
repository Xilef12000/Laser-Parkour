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
#define penalty 10000 //penalty time for Laser interruption in ms
#define trigger_value 180 //value to trigger

#define baudrate 9600 //Serial comunication speed/baudrate, normally 9600

laser_parkour parkour;
void started() {
  Serial.println("start");
}
void stopped() {
  Serial.println("stop");
}
void failed() {
  Serial.println("fail");
}
void setup() {
  Serial.begin(baudrate); //Start serial comunication
  Serial.setTimeout(10); //timeout for reciving strings in ms
  //configure pins      |diodes     |start     |stop:
  parkour.configurePins(diodes_pin, start_pin, stop_pin);
  //configure game      |trigger value |penalty time:
  parkour.configureGame(trigger_value, penalty);
  //this function gets called on the start of a round:
  parkour.onstart(started);
  //this function gets called on the end of a round:
  parkour.onstop(stopped);
  //this function gets called on the interruptionof a laser:
  parkour.onfail(failed);



}

void loop() {
  delay(2000);
  Serial.println("\nNew Game:");
  parkour.game();
  //delay(10000);
  //exit(0);
}
