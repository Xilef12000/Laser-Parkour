from time import sleep_ms, time
from machine import I2C, Pin
from machine_i2c_lcd import I2cLcd
import network
from sys import exit
from microdot import Microdot, send_file
from microdot.websocket import with_websocket
import uasyncio as asyncio
from urllib.parse import urlparse, parse_qs
from rgb_led import rgb_led
from menu import menu
from rotary import Rotary
import json


app = Microdot()

# mode and statemachine
systemMode = 0 # 0:config 1:game -10:config error -1:sensor disconnected
systemStateMachine = 0 # 0:noGame 1:awaitName 2:awaitStart 3:awaitEnd
nextName = ""

sensors = []
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
            if self.conStatus < -5:
                global systemMode
                systemMode = -1
            #print(f'sensor {self.address} faulty')\

def init():
    # init LCD
    lcd = I2cLcd(I2C(1, sda=14, scl=15, freq=100000), 0x27, 2, 16)
    # init Menu
    global menu
    menu = menu(lcd)
    menu.add_entry("", "Laser-Parcour")
    menu.show()
    # led config
    global led
    led = rgb_led(7,8,9,500)
    # open_drain
    open_drain = Pin(18, Pin.IN, Pin.PULL_UP)
    def open_drain_handler(pin):
        print(time())
    open_drain.irq(trigger=Pin.IRQ_FALLING, handler=open_drain_handler)
    # roraty encoder config
    rotary = Rotary(11, 13, 12)
    def rotary_changed(change):
        if change == Rotary.ROT_CW:
            menu.rot_cw()
        elif change == Rotary.ROT_CCW:
            menu.rot_ccw()
        elif change == Rotary.SW_PRESS:
            menu.rot_go()
        elif change == Rotary.SW_RELEASE:
            pass
    rotary.add_handler(rotary_changed)
    # init bus
    global i2c
    i2c = I2C(0,sda=Pin(16),scl=Pin(17),freq=4800) # set speed form 100000 to xxx
    scanBus()
    
def scanBus():
    global systemMode
    systemMode = 0
    global sensors
    global ldrSensors
    global startSensor
    global endSensor
    sensors = []
    ldrSensors = []
    startSensor = None
    endSensor = None
    print('Scaning Sensor Bus...')
    foundAdresses = i2c.scan()
    if len(foundAdresses) == 0:
        print('No Sensor found!')
    else:
        print(f'{len(foundAdresses)} Sensors found')       
        for address in foundAdresses:
            sensor = Sensor(address)
            print(str(sensor))
            sensors.append(sensor)
            if sensor.deviceType == 1:
                ldrSensors.append(sensor)
            elif sensor.deviceType == 2:
                if startSensor != None:
                    print("more then one startSensor found")
                    systemMode = -10
                startSensor = sensor
            elif sensor.deviceType == 3:
                if endSensor != None:
                    print("more then one endSensor found")
                    systemMode = -10
                endSensor = sensor
    if startSensor == None:
        print("no startSensor found")
        systemMode = -10
    if endSensor == None:
        print("no endSensor found")
        systemMode = -10
                
    for sensor in sensors:
        sensor.setMode(1)
        #sensor.setType(1)
        
def createWap():
    rp2.country('DE')
    wap = network.WLAN(network.AP_IF)
    wap.config(essid='Laser-Parkour', password='nN7o1xt3')
    wap.active(True)   

def checkForWap():
    return network.WLAN(network.AP_IF).active()

def netInfo():
    netConfig = network.WLAN(network.AP_IF).ifconfig()
    menu.add_entry(netConfig[0], "Network:", "IP:")
    menu.add_entry(netConfig[1], "Network:", "Mask:")
    menu.add_entry(netConfig[2], "Network:", "Gateway:")
    menu.add_entry(netConfig[3], "Network:", "DNS:")
    
@app.route('/')
async def index(request):
    return send_file('index.html')

@app.route('/action/rescan')
async def index(request):
    scanBus()
    return '0'

@app.route('/action/name')
async def index(request):
    global systemStateMachine
    #print(parse_qs(urlparse('?' + request.query_string).query))
    if systemStateMachine == 1:
        nextName = request.query_string
        systemStateMachine = 2
    return parse_qs(urlparse('?' + request.query_string).query)['name'][0]

@app.route('/action/startgame')
async def index(request):
    global systemMode
    if systemMode == 0:
        systemMode = 1
    return str(systemMode)

@app.route('/API/sensors')
@with_websocket
async def api(request, ws):
    while True:
        global sensors
        response = '['
        for sensor in sensors:
            response += str(sensor).replace("'", '"') + ','
        response = response[:-1]
        response += ']'
        led.single('g', 255)
        await ws.send(response)
        await ws.receive()
        led.single('g', 0)
        await asyncio.sleep(0.5)

@app.route('/API/game')
@with_websocket
async def api(request, ws):
    global systemMode
    global systemStateMachine
    while True:
        data = {}
        data['systemMode'] = systemMode
        data['systemStateMachine'] = systemStateMachine
        response = json.dumps(data)
        led.single('g', 255)
        await ws.send(response)
        await ws.receive()
        led.single('g', 0)
        await asyncio.sleep(0.5)

    
async def startWeb():
    await app.run(debug=True)
      
async def main() :
    asyncio.create_task(startWeb())
    while True:
        led.single('b', 255)
        for sensor in sensors:
            sensor.readValue()
        global systemMode
        if systemMode == -1:
            errcount = 0
            for sensor in sensors:
                if sensor.conStatus != 1:
                    errcount = 1
            if errcount == 0:
                systemMode = 0
        led.single('b', 0)
        await asyncio.sleep(0.1)   # Sleep for 0.1 seconds  
        
if __name__=="__main__":
    if not checkForWap():
        createWap()
    init()
    netInfo()
    try:
        asyncio.run(main())
    finally:
        asyncio.new_event_loop()
