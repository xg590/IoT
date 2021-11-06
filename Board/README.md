## Arduino-Cli Cheat code
``` 
arduino-cli lib search irremote                     # Search library. case-insensitive
arduino-cli lib install "IRremote" 

arduino-cli board listall                           # Find FQBN
arduino-cli compile . --fqbn esp8266:esp8266:d1_mini && \
arduino-cli upload  . --fqbn esp8266:esp8266:d1_mini -p /dev/ttyUSB0 
```
## Test Serial
```
cat << EOF > ser.py
#!/usr/bin/python3
import serial, sys, datetime  
with serial.Serial(f'/dev/tty{sys.argv[1]}', baudrate=int(sys.argv[2]), timeout=30) as s:
    while 1: print(datetime.datetime.now().strftime('[%Y:%m:%dT%H:%M:%S] '),  s.readline())
EOF
ser.py USB0 9600
```
## Pin convention
* For ESP8266, Digital Pin 4 (D4) is GPIO2 
* In Arduino IDE, pin is specified by on-board printed name like A0, A2, D1, or D3. Meanwhile, GPIO number is recommended for MicroPython (ESP8266) or Python (Raspberry Pi).
* Following C code will light up built-in LED on ESP8266 dev board
```C     
void setup() { pinMode(D4, OUTPUT); digitalWrite(D4, 0); }  
void loop () {}
```
* Following MicroPython code also light up built-in LED on ESP8266 dev board
```Python
from machine import Pin   
Pin( 2, Pin.OUT, value=0) 
```
