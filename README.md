# Laser-Parcour
Laser Parcour repository

This is the Laser Parcour repository, for the laser parcour project in cooperation between the Hochschule Heilbronn and the Dillmann-Gymnasium Stuttgart.

The content of the old "Read Me.txt"/instructions:

This readme is out of date, but the operation described below should still be the same.

1. to use "sketch_1.0"and "test_sketch", build the circuit from "Schaltplan_1.0"
2. upload "test_sketch" on your arduino
3. open the Serial plotter under "Tools/Serial Plotter" or by pressing "strg + shift + l"
4. now interrupt the light shining on the photodiods, and look for a trigger value wich is good for both diods.
5. open "sketch_1.0"
6. read the definitions in the sketch careful, and adjust them for your needs
7. upload the adjusted sketch on your arduino
8. open the Serial monitor under "Tools/Serial Monitor" or by pressing "strg + shift + m"
9. now test the photodiods

# Current version: 2.1.1:

-parallel photodiode wiring
-toplist in serial monitor
-name input via serial monitor
-penalty time in case of laser interruption