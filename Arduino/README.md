# How to play with Arduino board or compatible board.
1. Get usb-to-uart driver installed
<br/>The driver enables our PC/Mac/Raspberry_Pi to communicate with the arduino board.
2. Install Arduino IDE<br/>
This is where we are going to program the board.
3. Configure board manager in IDE<br/>
In case we are playing compatible board, we use board manager to install programming toolchain for them. 
4. Choose the right board in IDE
5. Do a blink test
## Table of Contents
1. [Program Arduino on Raspberry Pi (Linux)](#Linux)  
1. [Program Arduino on PC (Win10)](#Win10)  
### Program Arduino on Raspberry Pi (Linux)<a name="Linux"></a>
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
#### Test blink 
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
### Program Arduino on PC (Win10)<a name="Win10"></a>
* Serial/TTL conversion <br/>
Pro Mini: Buy a <b>USB to Serial/TTL Adapter</b> because there is no on-board Serial/TTL convert chip.<br/>
Uno/Nano/micro-usb Nano: There is a on-board convert chip.
* Install the Virtual COM port (VCP) driver for the Serial/TTL convert chip  
  * Uno: Chip is CH340, so use this [driver](https://github.com/xg590/IoT/raw/master/Arduino/CH341SER.EXE)
  * Pro Mimi: Off-board chip is FT232RL, made by FTDI, use this ([driver](https://github.com/xg590/IoT/raw/master/Arduino/CDM%20v2.12.28%20WHQL%20Certified.zip). Or go to manufacturer [FTDI](https://www.ftdichip.com/Drivers/VCP.htm) and check out the latest verion.). 
* Use <b>Windows Device Manager</b> to install driver manually and get an additional COM port.
* Use Arduino IDE to program 
### Reference
[Arduino manpage](https://github.com/arduino/Arduino/blob/master/build/shared/manpage.adoc)
