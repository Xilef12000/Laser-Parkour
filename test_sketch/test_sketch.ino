////////////////////////////////
//Laser-Parkour test sketch   //
//                            //
//by Manuel König             //
////////////////////////////////

#define diodes_pin 0 //(analog)pin of the photodiodes, normally (analog)pin 0
#define baudrate 9600 // Serial comunication speed/baudrate, normally 9600
void setup() {
  Serial.begin(baudrate); //Start serial comunication
}

void loop() {
  Serial.println(analogRead(diodes_pin)); //print value measured on the analog pin
}
