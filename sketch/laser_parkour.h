class laser_parkour {
  private:
    unsigned int diodes_pin = 5;
    unsigned int start_pin = 9;
    unsigned int stop_pin = 8;
    int trigger_value = 255;
    unsigned long penalty_time = 5000;
    void (*onstart_function)();
    void (*onstop_function)();
    void (*onfail_function)();
  public:
    void begin() {
      pinMode(start_pin, INPUT_PULLUP);
      pinMode(stop_pin, INPUT_PULLUP);
    }
    unsigned long game() {
      unsigned int fails = 0;
      while (digitalRead(start_pin) == 1) {}
      unsigned long start_time = millis();
      (*onstart_function)();
      while (digitalRead(stop_pin) == 1) {
        if (analogRead(diodes_pin) >= trigger_value) {
          (*onfail_function)();
          fails ++;
          while (analogRead(diodes_pin) >= trigger_value) {}
        }
      }
      (*onstop_function)();
      unsigned long stop_time = millis();
      return (stop_time - start_time + penalty_time * fails);
    }
    void configurePins(unsigned int diodes_pin_local, unsigned int start_pin_local, unsigned int stop_pin_local) {
      diodes_pin = diodes_pin_local;
      start_pin = start_pin_local;
      stop_pin = stop_pin_local;
    }
    void configureGame(unsigned int trigger_value_local, unsigned int penalty_time_local) {
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
