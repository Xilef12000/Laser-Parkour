////////////////////////////////
//Laser-Parkour sketch        //
//                            //
//by Linus Prange             //
//and Manuel König            //
////////////////////////////////

#include "laser_parkour.h"
#include "sort_algorithm.h"

#define diodes_pin 0 //(analog)pin of the photo-diodes, normally (analog)pin 0
#define start_pin 12 //pin of start button, normally pin 13
#define stop_pin 11 //pin of stop button, normally pin 12
#define penalty 10000 //penalty time for Laser interruption in ms
#define trigger_value 180 //value to trigger

#define baudrate 9600 //Serial communication speed/baudrate, normally 9600

laser_parkour parkour;
sort_algorithm sort;
userdata list[11] = {  {4294967295, "Test0"},  {4294967295, "Test1"},  {4294967295, "Test2"},  {4294967295, "Test3"},  {4294967295, "Test4"},  {4294967295, "Test5"},  {4294967295, "Test6"},  {4294967295, "Test7"},  {4294967295, "Test8"},  {4294967295, "Test9"}, {4294967295, "Test10"}}; //Dummy runs
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
  Serial.begin(baudrate); //Start serial communication
  Serial.setTimeout(10); //timeout for receiving strings in ms
  //configure pins      |diodes     |start     |stop:
  parkour.configurePins(diodes_pin, start_pin, stop_pin);
  //configure game      |trigger value |penalty time:
  parkour.configureGame(trigger_value, penalty);
  //this function gets called on the start of a round:
  parkour.onstart(started);
  //this function gets called on the end of a round:
  parkour.onstop(stopped);
  //this function gets called on the interruption of a laser:
  parkour.onfail(failed);
  //initialize the control-system;
  parkour.begin();


}

void loop() {
  delay(2000);
  Serial.println("\nNew Game:");
  Serial.println(parkour.game());
  //delay(10000);
  //exit(0);
}
