////////////////////////////////
//Laser-Parkour sketch        //
//                            //
//by Linus Prange             //
//and Manuel König            //
////////////////////////////////

<<<<<<< Updated upstream
#include "laserMonitoring.h"
#include "nameInput.h"
#include "results.h"
#include "sort.h"
#include "startInfo.h"

#define penalty 10000 //penalty time for Laser interruption in ms
=======
#include "laser_parkour.h"

>>>>>>> Stashed changes
#define diodes_pin 0 //(analog)pin of the photo-diodes, normally (analog)pin 0
#define start_pin 12 //pin of start button, normally pin 13
#define stop_pin 11 //pin of stop button, normally pin 12
#define baudrate 9600 //Serial comunication speed/baudrate, normally 9600
<<<<<<< Updated upstream
#define trigger_value 180 //value to trigger
#define speaker_pin 9 //pin of the speaker
#define start_beep 400 //tone when start button gets pressed
#define stop_beep 400 //tone when stop button gets pressed
#define laser_beep 500 //tone when laser gets interrupted
#define beep_length 300 //tone length

laser_parkour parkour1;
=======
>>>>>>> Stashed changes

laser_parkour parkour;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(baudrate); //Start serial comunication
  Serial.setTimeout(10); //timeout for reciving strings in ms
  parkour.begin();
  parkour.game();
}

void loop() {
<<<<<<< Updated upstream
  // put your main code here, to run repeatedly:
  penalty_time = 0; //reseting the total penalty time
  userName = nameInput(); //asking for a user Input
  laserMonitoring(); //monitor the lasers and buttons
  results(start_time, stop_time, penalty_time); //calculate results
=======


>>>>>>> Stashed changes
}
