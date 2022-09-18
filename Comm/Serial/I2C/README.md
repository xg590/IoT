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
* Flash I2C.ino to Xiao
* Run notebook I2C_MicroPython on Lite or I2C_Python on Raspberry Pi
* Lite or Raspberry Pi ask the length of a string first and then read the string 