# Laser-Parkour
Laser Parkour repository

This is the Laser Parkour repository, for the laser parkour project in cooperation between the Hochschule Heilbronn and the Dillmann-Gymnasium Stuttgart.

How to use the Arduino sketch:

1. to use "sketch"and "test_sketch", build the circuit named "wiring diagram"
2. upload "test_sketch" on your Arduino
3. open the Serial plotter under "Tools/Serial Plotter" or by pressing "strg + shift + l"
4. now interrupt the light shining on the photo-diodes, and look for a trigger value which is good for both diodes.
5. open "sketch"
6. read the definitions in the sketch careful, and adjust them for your needs
7. upload the adjusted sketch on your Arduino
8. open the Serial monitor under "Tools/Serial Monitor" or by pressing "strg + shift + m"
9. now test the photo-diodes

# Current version: 3.0:
- photo-diodes are connected in series
- top-list in serial monitor
- name input via serial monitor
- penalty time in case of laser interruption
- start and stop button

# Changes compared to version 2.1.2:
- photo-diodes are now connected in series not parallel as it was in the older versions