////////////////////////////////
//Laser-Parkour sketch        //
//                            //
//by Linus Prange             //
//and Manuel König            //
////////////////////////////////
#include "LaserParkour.h"

#define diodesPin 0 //(analog)pin of the photo-diodes, normally (analog)pin 0
#define startPin 12 //pin of start button, normally pin 13
#define stopPin 11 //pin of stop button, normally pin 12
#define speakerPin 9 //pin of the speaker
#define penalty 10000 //penalty time for Laser interruption in ms
#define baudrate 9600 //Serial comunication speed/baudrate, normally 9600
#define triggerValue 180 //value to trigger
#define topListLength 10 // Legth of the Top List

LaserParkour parkour;
void setup(){
    Serial.begin(baudrate); //Start serial comunication
    Serial.setTimeout(10); //timeout for reciving strings in ms
    parkour.setup(diodesPin, startPin, stopPin, topListLength); //initialize pins
    parkour.setupInfo(); //aditional info
}
void loop(){
    parkour.game("hallo");
    //parkour.test();
    parkour.shutdown();
}