class laser_parkour {
  private:
    int diodes_pin = 5;
    int start_pin = 9;
    int stop_pin = 8;
    void (*onstart_function);
  public:
    void begin(int diodes_pin_local, int start_pin_local, int stop_pin_local) {
      diodes_pin = diodes_pin_local;
      start_pin = start_pin_local;
      stop_pin = stop_pin_local;
    }
    void game() {

    }
    void start() {
      (*onstart_function)()
    }
    void onstart(void (*function)()) {
      (*onstart_function) = (*function);
    }
};
