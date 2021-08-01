# Laser-Parcour
Laser Parcour repository

This is the Laser Parcour repository, for the laser parcour project in cooperation between the Hochschule Heilbronn and the Dillmann-Gymnasium Stuttgart.

How to use the Arduino sketch:

1. to use "sketch"and "test_sketch", build the circuit named "wiring diagram"
2. upload "test_sketch" on your arduino
3. open the Serial plotter under "Tools/Serial Plotter" or by pressing "strg + shift + l"
4. now interrupt the light shining on the photodiods, and look for a trigger value wich is good for both diods.
5. open "sketch"
6. read the definitions in the sketch careful, and adjust them for your needs
7. upload the adjusted sketch on your arduino
8. open the Serial monitor under "Tools/Serial Monitor" or by pressing "strg + shift + m"
9. now test the photodiods

# Current version: 4.0:
- photodiodes are connected in series
- toplist in web interface
- name input via web interface
- penalty time in case of laser interruption
- start and stop button

# Changes compared to version 3.0:
- Interaction with the arduino via webinterface hosted on a esp32