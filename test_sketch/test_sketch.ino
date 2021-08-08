////////////////////////////////
//Laser-Parkour test sketch   //
//                            //
//by Manuel König             //
////////////////////////////////

#define diodes_pin 0 //(analog)pin of the photodiodes, normally (analog)pin 0
#define baudrate 9600 // Serial comunication speed/baudrate, normally 9600
void setup() {
  // put your setup code here, to run once:
  Serial.begin(baudrate);
  //Serial.println("\n////////////////////////////////\n//Laser-Parkour test sketch   //\n//                            //\n//by Manuel König             //\n////////////////////////////////\n");
  //Serial.println("using photo-diodes on pin " + String(diodes_pin));
  //Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(diodes_pin));
  //Serial.println("uT");
}
