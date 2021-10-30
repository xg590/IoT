import ujson
with open("insecure_lan.json") as fr: js = ujson.load(fr) 

def test_oled():
    oled.fill(0) 
    oled.rotate(False)
    oled.text('ABCDEFGH',  0,  0, 1) 
    oled.text('VO    ID',  0,  10, 1) 
    oled.text('12345678',  0,  20, 1) 
    oled.text('Disappear',  0,  30, 1) 
    oled.text('abcdefgh',  0,  40, 1)  
    oled.show()   
    
def do_connect():
    import network
    sta_if = network.WLAN(network.STA_IF)
    if sta_if.isconnected():
        print('Already connected')
        pass
    else:
        sta_if.active(True)
        print('connecting to network...')
        sta_if.connect(js['ssid'], js['psk'])
        while not sta_if.isconnected():
            pass
    print('network config:', sta_if.ifconfig())

def welcome():
    oled.fill(0) 
    oled.text('Welcome~',  0,  20, 1)  
    oled.show()    
        
import ssd1306, socket
from machine import Pin, I2C, enable_irq, disable_irq
from time import sleep
   
OLED_SDA_PIN = 4
OLED_SCL_PIN = 5 
i2c = I2C(scl=Pin(OLED_SCL_PIN), sda=Pin( OLED_SDA_PIN)) 
# https://docs.micropython.org/en/latest/esp8266/tutorial/ssd1306.html
oled = ssd1306.SSD1306_I2C(64, 48, i2c)  
test_oled()
do_connect()
welcome() 

from machine import Pin 
from time import sleep  
   
Pin( 0, Pin.IN).irq(trigger=Pin.IRQ_FALLING, handler = lambda pin: remote.set_pin( 0) )  
Pin( 2, Pin.IN).irq(trigger=Pin.IRQ_FALLING, handler = lambda pin: remote.set_pin( 2) )   
Pin(12, Pin.IN).irq(trigger=Pin.IRQ_FALLING, handler = lambda pin: remote.set_pin(12) )   
Pin(13, Pin.IN).irq(trigger=Pin.IRQ_FALLING, handler = lambda pin: remote.set_pin(13) )    
Pin(14, Pin.IN).irq(trigger=Pin.IRQ_FALLING, handler = lambda pin: remote.set_pin(14) )   
Pin(15, Pin.IN).irq(trigger=Pin.IRQ_RISING,  handler = lambda pin: remote.set_pin(15) )   

class REMOTE():
    count = 0
    pin_pressed = None
    def set_pin(self, i):
        self.pin_pressed = i

remote = REMOTE()

while 1:
    if not isinstance(remote.pin_pressed, int):
        sleep(1)
        continue

    s = socket.socket()
    s.connect((js['hub_ip'], js['hub_port']))
    req = 'GET /remote?pin=%d HTTP/1.0\r\nHost: foo\r\n\r\nbar' % (remote.pin_pressed, )
    s.send(req.encode())
    first_line = s.readline()
    protocol, return_code, message = first_line.split(b' ', 2) 
    is_json, res_js = False, {'display':'Serv Err'}
    if return_code == b'200': 
        while 1:
            line = s.readline()
            if line == b'\r\n': 
                if is_json:
                    res_js = ujson.loads(s.read(cLen)) 
                s.close()
                break
            if line == b'Content-Type: application/json\r\n': is_json = True 
            key, value = line.split(b':', 1)
            if key == b'Content-Length':
                cLen = int(value)  
    print(res_js['display'])

    remote.count += 1
    oled.fill(0)   
    oled.text('No: %d' % (remote.count,), 0, 0, 1)   
    oled.text('Pin: %d' % (remote.pin_pressed,), 0, 10, 1)
    oled.text(res_js['display'], 0, 20, 1)        
    oled.show()
    sleep(3)    
    oled.fill(0)    
    oled.text("Welcome~", 0, 20, 1)        
    oled.show() 
    remote.pin_pressed = None
    print('End of one loop')
