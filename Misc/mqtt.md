### Broker
* Mosquitto from Eclipse, written in C
```
sudo apt install -y mosquitto mosquitto-clients
mosquitto -v
sudo tee -a /etc/mosquitto/mosquitto.conf << EOF >/dev/null

listener 1883
allow_anonymous true
EOF
sudo systemctl restart mosquitto.service
```
### Client
* Install
```
sudo apt install -y mosquitto-clients
```
* Subscribe
```
mosquitto_sub -d -t testTopic 
```
* Push
```
mosquitto_pub -h 192.168.xxx.xxx -t testTopic -m "Hello world!"
```
### Python
```
pip install paho-mqtt

import paho.mqtt.client as mqtt
 
client = mqtt.Client() 
client.connect("192.168.xxx.xxx", 1883, 60) 
client.publish("testTopic", payload="Hello World From Python", qos=0, retain=False)
```
### MicroPython
[MQTT Lib](https://raw.githubusercontent.com/micropython/micropython-lib/master/micropython/umqtt.simple/umqtt/simple.py)
```
import time
from umqtt.simple import MQTTClient
 
def sub_cb(topic, msg):
    print((topic, msg)) 
     
c = MQTTClient("client_id", "server_ip")
c.set_callback(sub_cb)
c.connect()
c.subscribe(b"foo_topic")
try:
    while 1: 
        c.wait_msg()
finally:
    c.disconnect()
```