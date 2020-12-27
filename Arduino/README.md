### Program Arduino on Raspberry Pi
#### Install Arduino IDE on Raspberry Pi
1. Download [ARDUINO IDE / Linux ARM 32 bits](https://www.arduino.cc/en/Main/Software)
2. Decompress it
```shell
tar Jxvf arduino-1.8.10-linuxarm.tar.xz
```
3. Create a shortcut
```shell
sudo ln -s /home/pi/arduino-1.8.10/arduino /usr/local/bin/arduino
```
3. Setup right permission of accessing /dev/ttyUSB0
```shell 
sudo usermod -aG dialout pi 
newgrp dialout
```
#### Program Arduino (Test blink) 
* Connect USB ports on Pi and Arduino Nano/Uno
```shell
arduino --upload examples/01.Basics/Blink/Blink.ino --port /dev/ttyUSB0 --board arduino:avr:nano:cpu=atmega328 # Arduino Nano 
arduino --upload examples/01.Basics/Blink/Blink.ino --port /dev/ttyUSB0 --board arduino:avr:uno                # Arduino Uno
```
* Or use a USB to TTL adapter for Arduino Pro/Pro-Mini. GND, VCC, RX, TX, and DTR (Data Terminal Ready) should be all connected. 
```shell 
arduino --upload examples/01.Basics/Blink/Blink.ino --port /dev/ttyUSB0 --board arduino:avr:pro                # Arduino Pro Mini
``` 
#### Install IDE Library
```shell
arduino --install-library "Adafruit Unified Sensor"
```
#### Reference
[Arduino manpage](https://github.com/arduino/Arduino/blob/master/build/shared/manpage.adoc)
