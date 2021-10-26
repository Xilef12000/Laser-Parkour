void startInfo() {
  //Serial.println("\n////////////////////////////////\n//Laser-Parkour sketch        //\n//                            //\n//by Linus Prange             //\n//and Manuel König            //\n////////////////////////////////\n"); //print programm authors
  //Serial.println("using photo-diode on pin " + String(diodes_pin)); //print used photo-diode pins
  //Serial.println(""); //print blank lines
  pinMode(start_pin, INPUT_PULLUP); //define start pin as button-pin
  //Serial.println(String(start_pin) + " is now the start-pin"); //print start pin
  pinMode(stop_pin, INPUT_PULLUP);//define stop pin as button-pin
  //Serial.println(String(stop_pin) + " is now the stop-pin"); //print stop pin
  //Serial.println(""); //print blank lines
  //Serial.print("\n\n\n\n\n"); //print blank lines
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}
