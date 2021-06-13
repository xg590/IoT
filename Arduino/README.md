### Common boards
* Arduino Uno
* Arduino Nano
* Arduino Pro Mini 
### Get Started
* [Windows Caveat] Install the Virtual COM port (VCP) driver for the <b>USB to serial/TTL adapter</b> 
   * Uno: Adapter chip is CH340, so use this [driver](driver/CH341SER.EXE)
   * Pro Mimi: My off-board chip is FT232RL, made by FTDI, use this ([driver](driver/CDM%20v2.12.28%20WHQL%20Certified.zip). Or go to manufacturer [FTDI](https://www.ftdichip.com/Drivers/VCP.htm) and check out the latest verion.). Use <b>Windows Device Manager</b> to install driver manually and get an additional COM port.
* Install Arduino IDE
* Choose the right board in IDE
* Try a blink test 
### Pro Mini
* Pro Mini is the smallest Arduino board
* It is too small that it does not have the <b>USB to serial/TTL adapter</b> on board while others have. Buy one!  
* To connect usb-to-serial adapter and Arduino Pro Mini, GND, VCC, RX, TX, and DTR (Data Terminal Ready) should be all connected.
### USB to serial/TTL adapter
* Our PC cannot talk to the micro-controller on arduino board directly and we need an adapter as a translator
* The translator need proper driver to function
* Install  driver for the Serial/TTL convert chip  
### Choose board in IDE
* There is a set of parameters for each arduino board, choosing the right one is the key.
### 3.3v board and 5v board
* Among Uno, Nano and Pro Mini, only Pro Mini has the 3.3v version, which means the GPIO pins operate at between 0~3.3v (voltage)
* Some sensors (loads) need 5V voltage to power but communicates with the board on a 3.3v logic level
* You would risk to fry the sensor if there is a mismatch 
* BTW, raspberry pi's GPIO pins are 5v.
* Use a logic level converter to step down the voltage for fragile sensor.
### Arduino-CLI is a new tool. 
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
```
arduino-cli board listall
``` 