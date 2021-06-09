## Play with Arduino board or compatible board on Windows.
1. Get usb-to-uart driver installed<br/>
The driver enables our PC to communicate with the board.
2. Install Arduino IDE<br/>
This is where we are going to program the board.
3. Configure board manager in IDE<br/>
In case we are playing compatible board, we use board manager to install programming toolchain for them. 
4. Choose the right board in IDE
5. Do a blink test
## Use Arduino-CLI to program compatible board (Ubuntu 20.04)
```
wget arduino-cli_0.18.3_Linux_64bit.tar.gz
tar zxvf arduino-cli_0.18.3_Linux_64bit.tar.gz
sudo mv arduino-cli /usr/local/bin/arduino-cli 
arduino-cli core install esp8266:esp8266 --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json   
mkdir /tmp/blink
cat << EOF > /tmp/blink/blink.ino
void setup() { pinMode(LED_BUILTIN, OUTPUT); }
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); delay(1000);  
  digitalWrite(LED_BUILTIN,  LOW); delay(1000);  
}
EOF
arduino-cli compile --fqbn esp8266:esp8266:d1_mini /tmp/blink
sudo usermod -aG dialout $USER # Give /dev/ttyUSB0 access permission to arduino-cli 
newgrp dialout
arduino-cli upload /tmp/blink -p /dev/ttyUSB0 --fqbn esp8266:esp8266:d1_mini 
```
## Table of Contents 
1. [Program Arduino on PC (Win10)](#Win10)   
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
