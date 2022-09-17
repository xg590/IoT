## Material
* Heltec Wireless Stick Lite ESP32
* Seeed Xiao SAMD21
## Connection
```
        Lite <-> Xiao
SDA :   4           4     
SCL :   15          5     
```
## Code
* Flash i2c.ino to Xiao and run i2c.notebook on Lite through MicroPython 
* Lite ask the length of a string first and then read the string 