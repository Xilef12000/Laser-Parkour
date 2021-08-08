////////////////////////////////
//Laser-Parkour test sketch   //
//                            //
//by Manuel König             //
////////////////////////////////

#define diods 2 //number of used photodiods
#define diod_pin 0 //(analog)pin of the first photodio, normally (analog)pin 0
#define baudrate 9600 // Serial comunication speed/baudrate, normally 9600
void setup() {
  // put your setup code here, to run once:
  Serial.begin(baudrate);
  //Serial.println("\n////////////////////////////////\n//Laser-Parkour test sketch   //\n//                            //\n//by Manuel König             //\n////////////////////////////////\n");
  for (int i = diod_pin; i <= diod_pin + diods - 1; i++) {
    //Serial.println("using photodiod on pin " + String(i));
  }
  //Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = diod_pin; i <= diod_pin + diods - 1; i++) {
    Serial.print(String(analogRead(i)));
    Serial.print("  ");
  }
  Serial.println("uT");
}
