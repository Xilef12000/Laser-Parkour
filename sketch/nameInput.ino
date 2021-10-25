String nameInput(){
  //Serial.flush(); //flush the serial buffer/delet all past inputs
  //Serial.print("Name: "); //ask for a name
  while (Serial.available() == 0) {} //wait for an input
  //String nameInput_userName = Serial.readStringUntil('\n'); //read Input from Buffer
  String nameInput_userName = Serial.readString(); //read Input from Buffer
  //Serial.println(nameInput_userName); //print name
  //Serial.print("\n\n"); //print blank lines
  return nameInput_userName; //return name
}
