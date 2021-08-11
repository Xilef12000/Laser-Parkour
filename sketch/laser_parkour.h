class laser_parkour {
<<<<<<< Updated upstream
  public:
    int diodes_pin = 0;
    int start_pin = 12;
    int stop_pin = 11;
    void begin(diodes_pin, start_pin, stop_pin) {

    }
    unsigned int game() {

=======
  private:
    int diodes_pin = 1;
    int start_pin = 12;
    int stop_pin = 11;
  public:
    void begin(int diodes_pin_local, int  start_pin_local, int  stop_pin_local) {

    }
    void game() {
      Serial.println(diodes_pin);
>>>>>>> Stashed changes
    }
};
