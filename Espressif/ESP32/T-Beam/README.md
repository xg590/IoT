### T-beam
* Version: LILYGO® TTGO T-Beam V1.1
* LoRa: Semtech SX1276
* VCP Driver: CP2102
* Board name in Arduino IDE: T-beam
* Official GitHub: https://github.com/Xinyuan-LilyGO/LilyGo-LoRa-Series
* Install libraries: Move all sub-folders in LilyGo-LoRa-Series/libdeps to ~/Arduino/libraries
### Difference between LoRa and LoRaWAN
* LoRa is the Physical Layer protocol that supports Network Layer protocol LoRaWAN.
* LoRa is about RF signal and LoRaWAN addresses MAC/Encryption.
### Two libraries in LilyGo-LoRa-Series examples
* Arduino LoRa is the library for LoRa operations. 
* RadioLib supports LoRa operations but intends to include LoRaWAN functions.
### Play examples
* Must uncomment board version and change LoRa_frequency in [utilities.h](utilities.h) 
``` 
#define LILYGO_TBeam_V1_1 
#define LoRa_frequency      915.0
``` 
### Recv.py
```
$ pip install pyserial
import serial
with serial.Serial(port='/dev/ttyUSB0',baudrate=115200) as s:
  while 1:
    print(s.readline().decode())
```
