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
