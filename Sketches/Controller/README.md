# How to compile MicroPython firmware for RPI Pico W with frozen modules:
see: 
- [forum.micropython.org](https://forum.micropython.org/viewtopic.php?t=12268)
- [ithub.com/micropython/micropython/wiki/Getting-Started](https://github.com/micropython/micropython/wiki/Getting-Started)


1. follow `firmware.sh`
2. flash firmware



# module sources:
## lib-to-freeze/
- `microdot`: [github.com/miguelgrinberg/microdot](https://github.com/miguelgrinberg/microdot)
- `collections`, `urllib`: [github.com/micropython/micropython-lib](https://github.com/micropython/micropython-lib)

## project/lib/
- `rotary.py`: [www.elektronik-kompendium.de/sites/raspberry-pi/2703131.htm](https://www.elektronik-kompendium.de/sites/raspberry-pi/2703131.htm)
- `lcd_api.py`, `machine_i2c_lcd.py`: [www.elektronik-kompendium.de/sites/raspberry-pi/2612251.htm](https://www.elektronik-kompendium.de/sites/raspberry-pi/2612251.htm)