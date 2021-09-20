import ujson
with open("insecure_lan.json") as fr: js = ujson.load(fr)   

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
    return sta_if.ifconfig()[0] 

relay_ip = do_connect()

import socket

s = socket.socket()
s.connect((js['hub_ip'], js['hub_port']))
payload_2 = '{"relay_ip":"%s", "relay_port":%d}' % (relay_ip, 80)
payload_2 = payload_2.encode()
payload_1 = 'POST /params HTTP/1.1\r\n'
payload_1 += 'Content-type: application/json\r\n'
payload_1 += 'Content-length: %d\r\n\r\n' % (len(payload_2),)
payload_1 = payload_1.encode()
s.send(payload_1)
s.send(payload_2) 
s.close() 

s = socket.socket()
addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
s.bind(addr)
s.listen(1)

print('listening on', addr)

from machine import Pin 
from time import sleep 

p15 = Pin(15, Pin.OUT)    # create output pin on GPIO0
while True:
    cl, addr = s.accept()
    print('client connected from', addr)
    cl_file = cl.makefile('rwb', 0)
    first_line = cl_file.readline()
    method, path, version = first_line.split()
    if method != b'POST': # Wrong method 
        cl.close()
        break
    while True: # headers
        line = cl_file.readline()
        if line == b'\r\n':  # header is over 
            payload = ujson.loads(cl.read(cLen)) 
            p15.value(payload['switch'])      # set pin to "on" (high) level
            cl.send('HTTP/1.0 200 OK\r\nContent-type: application/json\r\n\r\n')
            cl.send('{"result":"ok"}')
            cl.close() 
            break
        key, value = line.split(b':')
        if key == b'Content-Length':
            cLen = int(value)
        elif key == b'':
            if value.strip() != b'application/json':
                cl.close()
                break 