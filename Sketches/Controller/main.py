from time import sleep_ms, ticks_ms
from machine import I2C, Pin
from machine_i2c_lcd import I2cLcd
from sys import exit
import network
import rp2
import socket
import os
import uasyncio as asyncio 

# WAP config
wap_country = 'DE'
wap_essid = 'Laser-Parkour'
wap_passwd = 'nN7o1xt3'
# bus config
bus_i2c = 0
bus_sda = Pin(16)
bus_scl = Pin(17)
# lcd config
lcd_i2c = 1
lcd_sda = Pin(14)
lcd_scl = Pin(15)

class Sensor:
    address = 0
    deviceType = 0
    deviceMode = 0
    conStatus = 1
    value = -1
    def __init__ (self, address):
        self.address = address
        self.setMode(0)
        sleep_ms(200)
        self.deviceType = int.from_bytes(i2c.readfrom(self.address, 1, True), 'big')
    def __str__(self):
        return dict(address = hex(self.address), deviceType = self.deviceType, deviceMode = self.deviceMode, conStatus = self.conStatus, value = self.value)
    def setMode(self, mode):
        i2c.writeto(self.address, bytearray([0b00010000 + mode]), True)
        self.deviceMode = mode
    def setType(self, type):
        i2c.writeto(self.address, bytearray([0b00100000 + type]), True)
        self.deviceType = type
    def readValue(self):
        try:
            data = i2c.readfrom(self.address, 2, True)
            self.conStatus = 1
            self.value = int.from_bytes(data, 'big')
            #print(f'{hex(self.address)} : {self.value}')
        except OSError as error:
            self.conStatus -= 1
            #print(f'sensor {self.address} faulty')\

        
def init():
    # init lcd
    #global lcd
    #lcd = I2cLcd(I2C(lcd_i2c, sda=lcd_sda, scl=lcd_scl, freq=100000), 0x27, 2, 16)

    #lcd.putstr("...")

    # init bus
    global i2c
    i2c = I2C(bus_i2c,sda=bus_sda,scl=bus_scl,freq=4800) # set speed form 100000 to xxx

    # bus scan
    print('Scaning Sensor Bus...')
    foundAdresses = i2c.scan()
    if len(foundAdresses) == 0:
        print('No Sensor found!\nexiting...')
        exit(0)
    else:
        print(f'{len(foundAdresses)} Sensors found')
        global sensors
        sensors = []
        for address in foundAdresses:
            sensor = Sensor(address)
            print(str(sensor))
            sensors.append(sensor)
        
    for sensor in sensors:
        sensor.setMode(1)
        sensor.setType(1)
            
async def main():
    asyncio.create_task(asyncio.start_server(serveClient, "192.168.4.1", 80))
    init()
    time_last = ticks_ms() 
    while True:
        if ticks_ms() >= time_last + 200:
            time_last = ticks_ms() 
            for sensor in sensors:
                sensor.readValue()
        await asyncio.sleep(0.1)   # Sleep for 0.1 seconds 
        
def createWap():
    rp2.country(wap_country)
    wap = network.WLAN(network.AP_IF)
    wap.config(essid=wap_essid, password=wap_passwd)
    wap.active(True)
    netConfig = wap.ifconfig()
    global pico_ip
    pico_ip = netConfig[0]
    print('IPv4-Adrress:', netConfig[0], '/', netConfig[1])
    print('Standard-Gateway:', netConfig[2])
    print('DNS-Server:', netConfig[3])

def serveClient(reader, writer):
    #print("Client connected")  # Print message when client is connected
    request_line = await reader.readline()  # Read the HTTP request line
    #print("Request:", request_line)         # Print the received request
    # Skip HTTP request headers
    while await reader.readline() != b"\r\n":
        pass

    request = str(request_line)        # Convert request to string
    request = request.split()
    response = ''
    if request[1] == '/':
        file = open('index.html', 'r')
        response = file.read()
        file.close()
        writer.write('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
        writer.write(response)
    elif request[1] == '/API':
        response = '['
        for sensor in sensors:
            response += str(sensor).replace("'", '"') + ','
        response = response[:-1]
        response += ']'
        writer.write('HTTP/1.0 200 OK\r\nContent-type: text/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n')
        writer.write(response)
    else:
        response = '404'
        writer.write('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
        writer.write(response)

    await writer.drain()     # Drain the writer buffer
    await writer.wait_closed()  # Wait until writer is closed
    #print("Client disconnected")  # Print message when client is disconnected

if __name__=="__main__":
    createWap()
    try:
        asyncio.run(main())  # Run the main asynchronous function
    finally:
        asyncio.new_event_loop() #Create a new event loop