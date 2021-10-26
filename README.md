# Laser-Parkour
Laser Parkour repository

## This is a Preview-Version, it may has bugs

This is the Laser Parkour repository, for the laser parkour project in cooperation between the Hochschule Heilbronn and the Dillmann-Gymnasium Stuttgart.

How to use the Laser-Parkour sketch:

0. **for the first use of a esp32 you have to install the necessary Board Manager by Pressing Strg + , on your keyboard and then adding https://dl.espressif.com/dl/package_esp32_index.json to the "Additional Boards Manager URLs" field.  
For this action and for the first time you flash the esp23 a Internet-connection is necessary.**
1. build the circuit displayed in the file "wiring diagram.pdf"
2. if you don't know the correct values for your used parts, find them out by using the "test_sketch":
	1. open the "test_sketch.ino" sketch
	2. Set the correct settings under "Tools" for the Arduino:

		| Settings: | Arduino Uno:  |
		|-----------|---------------|
		| Board:    | "Arduino Uno" |
		| Port:     | your Port     |

	3. upload the sketch to your Arduino  
		**!!!IMPORTANT: to upload the sketch disconnect any wires from the TX and RX pins!!!**
	4. open the Serial plotter under "Tools/Serial Plotter" or by pressing "strg + shift + l"
	5. now interrupt the light shining on the photo-diodes, and look for a trigger value which is good for all diodes.
3. open the "sketch.ino" sketch
4. read the definitions in the sketch careful, and adjust them for your needs
5. upload the adjusted sketch on your Arduino

	| Settings: | Arduino Uno:  |
	|-----------|---------------|
	| Board:    | "Arduino Uno" |
	| Port:     | your Port     |

	**!!!IMPORTANT: to upload the sketch disconnect any wires from the TX and RX pins!!!**
6. open the "sketch_esp.ino" sketch
7. if your want, change the ssid and password
8. Set the correct settings under "Tools" for the ESP32:
	
	| Settings:         | ESP32:                                             |
	|-------------------|----------------------------------------------------|
	| Board:            | "ESP32 Dev Module"                                 |
	| Upload Speed:     | "921600"                                           |
	| CPU Frequency:    | "240MHz (WIFI/BT)"                                 |
	| Flash Frequency:  | "80MHz"                                            |
	| Flash Mode:       | "QIO"                                              |
	| Flash Size:       | "4MB (32Mb)"                                       |
	| Partition Scheme: | "Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)" |
	| Core Debug Level: | "None"                                             |
	| PSRAM:            | "Disabled"                                         |
	| Port:             | your Port                                          |

9. upload the sketch to your esp32
	**!!!IMPORTANT: to upload the sketch disconnect any wires from the TX and RX pins!!!**
10. reconnect the RX and TX pins correctly
11. restart the esp32 and Arduino by disconnecting both from the power-supply/USB-Port and then reconnecting them
12. connect to the Hotspot of the esp32
13. open the webpage http://192.168.1.1 for the name-input-page or the webpage http://192.168.1.1/table for only the Top-10 table
14. use the Laser-Parkour...

# Current version: pre-4.0:
- photo-diodes are connected in series
- top-list in web-interface
- name input via web-interface
- penalty time in case of laser interruption
- start and stop button

# Changes compared to version 3.0.1:
- Interaction with the Arduino via web-interface hosted on a esp32


