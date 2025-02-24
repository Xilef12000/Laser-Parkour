# How to compile MicroPython firmware for RPI Pico W with frozen modules:
see: 
- https://forum.micropython.org/viewtopic.php?t=12268
- https://github.com/micropython/micropython/wiki/Getting-Started


1. follow `firmware.sh`
2. flash firmware



# module sources:
## lib-to-freeze/
- `microdot`: https://github.com/miguelgrinberg/microdot
- `collections`, `urllib`: https://github.com/micropython/micropython-lib

## project/lib/
- `rotary.py`: https://www.elektronik-kompendium.de/sites/raspberry-pi/code/rotary.py
- `lcd_api.py`, `machine_i2c_lcd.py`: https://www.elektronik-kompendium.de/sites/raspberry-pi/2612251.htm