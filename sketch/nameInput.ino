String nameInput(){
  //Serial.flush(); //flush the serial buffer/delet all past inputs
  //Serial.print("Name: "); //ask for a name
  while (Serial.available() == 0) {} //wait for an input
  //String nameInput_userName = Serial.readStringUntil('\n'); //read Input from Buffer
  /*delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);*/
  String nameInput_userName = Serial.readString(); //read Input from Buffer
  nameInput_userName.replace("\n","");
  //Serial.println(nameInput_userName); //print name
  //Serial.print("\n\n"); //print blank lines
  return nameInput_userName; //return name
}
