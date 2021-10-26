////////////////////////////////
//Laser-Parkour sketch        //
//                            //
//by Linus Prange             //
//and Manuel König            //
////////////////////////////////

#define penalty 10000 //penalty time for Laser interruption in ms
#define diodes_pin 0 //(analog)pin of the photo-diodes, normally (analog)pin 0
#define start_pin 12 //pin of start button, normally pin 13
#define stop_pin 11 //pin of stop button, normally pin 12
#define baudrate 9600 //Serial comunication speed/baudrate, normally 9600
#define trigger_value 180 //value to trigger
#define speaker_pin 9 //pin of the speaker
#define start_beep 400 //tone when start button gets pressed
#define stop_beep 400 //tone when stop button gets pressed
#define laser_beep 500 //tone when laser gets interrupted
#define beep_length 300 //tone length


struct melodyFormat {  //Melody Format
  unsigned int melodyTone;
  unsigned int melodyLength;
};
melodyFormat winMelody[4] = {{262, 200}, {330, 200}, {392, 200}, {523, 500}}; //this melody will be played when a player reaches the Top 10 (that mean the first 10 runs, it will be played every time)
struct userdataFormat { //Top 10 Format
  unsigned long userdataTime;
  String userdataName;
};
userdataFormat userdata[11] = {  {4294967295, "Test0"},  {4294967295, "Test1"},  {4294967295, "Test2"},  {4294967295, "Test3"},  {4294967295, "Test4"},  {4294967295, "Test5"},  {4294967295, "Test6"},  {4294967295, "Test7"},  {4294967295, "Test8"},  {4294967295, "Test9"}, {4294967295, "Test10"}}; //Dummy runs
String userName;
unsigned long start_time; //start time of a run
unsigned long stop_time; //stop time of a run
unsigned long penalty_time; //total penalty time for interrupting Lasers
void setup() {
  Serial.begin(baudrate); //Start serial comunication
  //Serial.setTimeout(10); //timeout for reciving strings in ms
  startInfo(); //print programm and connection infos to the serial monitor
}

void loop() {
  penalty_time = 0; //reseting the total penalty time
  userName = nameInput(); //asking for a user Input
  laserMonitoring(); //monitor the lasers and buttons
  results(start_time, stop_time, penalty_time); //calculate results
}
