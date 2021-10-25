void laserMonitoring() {
  while (digitalRead(start_pin) == 1) {} //wait for start button to get pressed
  start_time = millis(); //safe start time
  noTone(speaker_pin); //stop all tones
  tone(speaker_pin, start_beep, beep_length); //play start tone
  Serial.println("laserMonitoring: start-button got pressed at " + String(start_time) + "ms"); //print start time
  while (digitalRead(stop_pin) == 1) { //repeat while stop button is not pressed
    if (analogRead(diodes_pin) >= trigger_value) { //if actual light level higher then triggerlevel
      Serial.println("laserMonitoring: " + String(diodes_pin) + " rose above " + String(trigger_value)); //print which laser got interrupted
      penalty_time = penalty_time + penalty; //add penalty time
      noTone(speaker_pin); //stop all tones
      tone(speaker_pin, laser_beep, beep_length); //play laser interruption tone
      while (analogRead(diodes_pin) >= trigger_value) {} //wait for laser to be not interrupted
    }
  } //if stop button got pressed
  stop_time = millis(); //save stop time
  noTone(speaker_pin); //stop all tones
  tone(speaker_pin, stop_beep, beep_length); //play stop tone
  Serial.println("laserMonitoring: stop-button got pressed at " + String(stop_time) + "ms");//print stop time
  delay(beep_length); //wait for tone to be finished (to not interrupt the melody
}
