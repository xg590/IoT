### Program Arduino on Raspberry Pi (Linux)
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
* Connect USB ports on Pi and Arduino Nano 
![alt text](https://github.com/xg590/IoT/blob/master/Arduino/Arduino_Nano_Pinout.jpg?raw=true "Nano")
```shell
arduino --upload examples/01.Basics/Blink/Blink.ino --port /dev/ttyUSB0 --board arduino:avr:nano:cpu=atmega328 # Arduino Nano 
arduino --upload examples/01.Basics/Blink/Blink.ino --port /dev/ttyUSB0 --board arduino:avr:nano:cpu=atmega328old # Arduino Nano with old bootloader
```
* Connect USB ports on Pi and Arduino Uno
```shell
arduino --upload examples/01.Basics/Blink/Blink.ino --port /dev/ttyUSB0 --board arduino:avr:uno                # Arduino Uno
```
* Or use a USB to TTL adapter for Arduino Pro/Pro-Mini. GND, VCC, RX, TX, and DTR (Data Terminal Ready) should be all connected.
![alt text](https://github.com/xg590/IoT/blob/master/Arduino/Arduino_Pro_Mini_Pinout.png?raw=true "Pro_Mini") 
```shell 
arduino --upload examples/01.Basics/Blink/Blink.ino --port /dev/ttyUSB0 --board arduino:avr:pro                # Arduino Pro Mini
``` 
#### Install IDE Library
```shell
arduino --install-library "Adafruit Unified Sensor"
```
### Program Arduino Pro/Pro-Mini on PC (Win10)
#### Install Drivers
1. Buy a <b>USB to Serial/TTL Adapter</b> (skip this step if you are for Arduino Nano)<br/>
What I got is based on chip FT232RL, made by FTDI.
2. Get the Virtual COM port (VCP) driver<br/>
Go to driver page of manufacturer [FTDI](https://www.ftdichip.com/Drivers/VCP.htm) and download the <b>CDM v2.12.28 WHQL Certified.zip</b>.
3. Use <b>Windows Device Manager</b> to install driver manually and get an additional COM port.
#### Use Arduino to program
* Windows version Arduino IDE is easy to use.
### Reference
[Arduino manpage](https://github.com/arduino/Arduino/blob/master/build/shared/manpage.adoc)
