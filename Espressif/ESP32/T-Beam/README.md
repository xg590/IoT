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
* GPS / OLED / SX1276_Tx are three minimalistic examples that demonstrate how to use different component on T-Beam board.
* [Tracker](tracker) is the final project that report GPS info via LoRa protocol while display some info on screen.
### Recv.py
* Use LilyGo-LoRa-Series-master/examples/RadioLibExamples/SX1276/SX1276_Receive_Interrupt to program the receiver. 
```
$ pip install pyserial
import serial, datetime
with serial.Serial(port='/dev/ttyUSB0',baudrate=115200) as s, open('tracker.log','w') as fw:
  while 1:
    print(datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%SZ"),' | ',s.readline().decode(), file=fw)
    fw.flush()
```
###
```
arduino-cli compile --fqbn esp32:esp32:t-beam $HOME/IoT-master/Espressif/ESP32/T-Beam/SX1276_Receive && arduino-cli upload  --fqbn esp32:esp32:t-beam -p /dev/ttyUSB2 $HOME/IoT-master/Espressif/ESP32/T-Beam/SX1276_Receive  

arduino-cli compile --fqbn esp32:esp32:t-beam $HOME/IoT-master/Espressif/ESP32/T-Beam/SX1276_Transmit && arduino-cli upload  --fqbn esp32:esp32:t-beam -p /dev/ttyUSB1 $HOME/IoT-master/Espressif/ESP32/T-Beam/SX1276_Transmit
```
