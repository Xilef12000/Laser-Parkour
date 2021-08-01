void results(unsigned long results_start_time, unsigned long results_stop_time, unsigned long results_penalty_time) { //get times from input
  unsigned long results_total_time = results_stop_time - results_start_time + results_penalty_time; //calculate total time
  Serial.print("\n\n"); //print blank lines
  Serial.println("Your Time is " + String(results_total_time) + " milliseconds"); //print total time
  Serial.println("You interrupted " + String(results_penalty_time / penalty) + " Lasers"); //print number of interrupted lasers
  userdata[10].userdataTime = results_total_time; //save totaltime at the end  of Top 10
  userdata[10].userdataName = userName; //save name at the end of Top 10

  sort(userdata); //sort Top 10 delet last run (11th place)
  for (int i = 0; i < 10; i++) { //print Top 10 one by one
    Serial.println("Place " + String(i + 1) + ": " +  String(userdata[i].userdataTime) + " : " + String(userdata[i].userdataName)); //print Top 10
  }
  Serial.print("\n\n\n\n\n"); //print blank lines
  for (int i = 0; i < 10; i++) { //check if currrent is in Top 10 one by yone
    if (userdata[i].userdataName == userName) { //if currrent is in Top 10
      noTone(speaker_pin); //stop all other tones
      for (int n = 0; n < 4; n++) { //read melody
        tone(speaker_pin, winMelody[n].melodyTone, winMelody[n].melodyLength); //play melody
        delay(winMelody[n].melodyLength); //wait for tone to finish
      }
      noTone(speaker_pin);//stop all other tones
    }
  }
}
