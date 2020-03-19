### Use Arduino Uno connected to Raspberry Pi 3B via USB
#### Install Arduino IDE on Raspbian OS
1. Download  [ARDUINO 1.8.10 IDE / Linux ARM 32 bits](https://www.arduino.cc/en/Main/Software)
2. Decompress it<br>
```shell
$ tar Jxvf arduino-1.8.10-linuxarm.tar.xz 
```
3. Setup right permission of accessing /dev/ttyUSB0
```shell
$ sudo su
$ sudo usermod -aG dialout pi 
$ newgrp dialout
```
#### Program Arduino Nano (Test blink) 
```
$ cd arduino-1.8.10
$ ./arduino --board arduino:avr:nano:cpu=atmega328 --port /dev/ttyUSB0 --upload examples/01.Basics/Blink/Blink.ino 
```
#### Program Arduino Uno (Test blink) 
```shell
$ cd arduino-1.8.12/
$ ./arduino --board arduino:avr:uno --port /dev/ttyUSB0 --upload examples/01.Basics/Blink/Blink.ino 
```
#### Install Library
```
./arduino --install-library "Adafruit Unified Sensor"
```
