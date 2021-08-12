class laser_parkour {
  private:
    int diodes_pin = 5;
    int start_pin = 9;
    int stop_pin = 8;
    int trigger_value = 255;
    int penalty_time = 5000;
    void (*onstart_function)();
    void (*onstop_function)();
    void (*onfail_function)();
  public:
    void game() {
      while (digitalRead(start_pin) == 1) {}
      int start_time = millis();
      (*onstart_function)();
      while (digitalRead(stop_pin) == 1) {
        if (analogRead(diodes_pin) >= trigger_value) {
          (*onfail_function)();
          while (analogRead(diodes_pin) >= trigger_value) {}
        }
      }
      (*onstop_function)();
      //return (millis() - start_time);
    }
    void configurePins(int diodes_pin_local, int start_pin_local, int stop_pin_local) {
      diodes_pin = diodes_pin_local;
      start_pin = start_pin_local;
      stop_pin = stop_pin_local;
    }
    void configureGame(int trigger_value_local, int penalty_time_local) {
      trigger_value = trigger_value_local;
      penalty_time = penalty_time_local;
    }
    void onstart(void (*function_local)()) {
      onstart_function = function_local;
    }
    void onstop(void (*function_local)()) {
      onstop_function = function_local;
    }
    void onfail(void (*function_local)()) {
      onfail_function = function_local;
    }
};
