### Pin convention 
* For MCU D1 mini, D4 (digital pin 4) is GPIO2.
* In Arduino IDE, pin is specified by on-board printed name like A0 (analog pin 0) and D4. Following C code will light up built-in LED on D1 mini.
```C     
void setup() { pinMode(D4, OUTPUT); digitalWrite(D4, 0); }  
void loop () {}
``` 
* Meanwhile, MicroPython (ESP8266) or Python (Raspberry Pi) recommends GPIO number. Following MicroPython code also lights up built-in LED on D1 mini.
```Python
from machine import Pin   
Pin( 2, Pin.OUT, value=0) 
```
### Trouble shooting
* error while loading shared libraries: libfl.so.2
```
sudo apt install libfl-dev
```
* May need python and pyserial library
```
sudo apt update && sudo apt install python3-pip
ln -s /usr/bin/python3 /usr/bin/python
pip3 install pyserial
```
