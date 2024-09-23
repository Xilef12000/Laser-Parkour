from time import sleep_ms, ticks_ms
from machine import I2C, Pin
from machine_i2c_lcd import I2cLcd
from sys import exit
import network
import rp2
import socket

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

def init():
    # init lcd
    global lcd
    lcd = I2cLcd(I2C(lcd_i2c, sda=lcd_sda, scl=lcd_scl, freq=100000), 0x27, 2, 16)

    lcd.putstr("...")

    # init bus
    global i2c
    i2c = I2C(bus_i2c,sda=bus_sda,scl=bus_scl,freq=100000)

    # bus scan
    print('Scaning Sensor Bus...')
    devices = i2c.scan()
    if len(devices) == 0:
        print('No Sensor found!\nexiting...')
        exit(0)
    else:
        print(f'{len(devices)} Sensors found')
        global sensors
        sensors = []
        for device in devices:
            sensors.append(dict(adrress = device, type = 'sensor', status = 1, value = -1))
        print(sensors) 
            
def main():
    time_last = ticks_ms() 
    while True:
        serveWeb()
        if ticks_ms() >= time_last + 200:
            readSensors()
        
def readSensors():
    for sensor in sensors:
        try:
            data = i2c.readfrom(sensor['adrress'], 2, True)
        except OSError as error:
            sensor['status'] -= 1
            #print(f'sensor {hex(sensor["adrress"])} faulty')
            continue
        sensor['status']
        sensor['value'] = int.from_bytes(data, 'big')
        #print(f'{hex(sensor["adrress"])} : {sensor['value']}')
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

def createWeb():
    addr = socket.getaddrinfo(pico_ip, 80)[0][-1]
    global server
    server = socket.socket()
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(addr)
    server.listen(1)
    print('Server listening on', addr)

def serveWeb():
    try:
        conn, addr = server.accept()
        #print('HTTP-Request von Client', addr)
        request = conn.recv(1024)
        #print('Request:', request)
        response = '<!doctype html><html>' + str(sensors) + '<script>setTimeout("window.location.reload();", 1000)</script></html>'
        conn.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
        conn.send(response)
        conn.close()
        #print('HTTP-Response gesendet')
        #print()
    except OSError as e:
        return

if __name__=="__main__":
    createWap()
    createWeb()
    init()
    main()