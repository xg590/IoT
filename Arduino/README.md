### Common boards
* Arduino Uno
* Arduino Nano
* Arduino Pro Mini 
### Get Started
* [Windows Caveat] Install the Virtual COM port (VCP) driver for the <b>USB to serial/TTL adapter</b> 
   * Uno: Adapter chip is CH340, so use this [driver](driver/CH341SER.EXE)
   * Pro Mimi: My off-board chip is FT232RL, made by FTDI, use this [driver](driver/CDM%20v2.12.28%20WHQL%20Certified.zip). (Or go to manufacturer [FTDI](https://www.ftdichip.com/Drivers/VCP.htm) and check out the latest verion.) Use <b>Windows Device Manager</b> to install driver manually and get an additional COM port.
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
### Choose board in IDE
* There is a set of parameters for each arduino board, choosing the right one is the key.
### Pinout
* We need a pinout map to find special GPIO pins on each board
* For example, I2C pins are A4/A5 on Arduino Nano
* Uno<br/><img src="pinout/Uno.svg"></img>
* Nano
  * Vin: Accepts 6~12V unregulated external power source
  * 5V : Emits 5V regulated power<br/><img src="pinout/Nano.png"></img>
* Pro Mini
  * RAW: Accepts 6~12V unregulated external power source
  * VCC: Accepts 5V regulated power source<br/><img src="pinout/Pro_Mini.png"></img>
### Analog pin and digital pin in Arduino IDE
* In Arduino IDE, use A1 to indicate an analog pin, and use 1 to indicate a digital pin
```
digitalWrite(A1, HIGH); // sets the analog pin 1 on 
digitalWrite( 1, LOW);  // sets the digital pin 1 off
``` 
### 3.3v board and 5v board
* Arduino board's GPIOs are generally 5v.
* Among Uno, Nano and Pro Mini, only Pro Mini has the 3.3v version, which means the GPIO pins operate at between 0~3.3v (voltage). 
* Some sensors (loads) need 5V voltage to power but communicates with arduino board on a 3.3v logic level
* You would risk to fry the sensor if there is a mismatch 
* Use a logic level converter to step down the voltage for fragile sensor.
* BTW, [raspberry pi's GPIO pins are 3.3v](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). So if you want your Pi talk to arduino via uart interface, use a logic level converter as well.
### Program the board on Raspberry Pi? Arduino-CLI is here for help. <a name="Arduino-CLI"></a>
1. Download the tool
```
wget arduino-cli_0.18.3_Linux_64bit.tar.gz && tar zxvf 
sudo mv arduino-cli /usr/local/bin/
```
2. Install compile platform of Arduino board family
```
arduino-cli core install arduino:avr
```
3. What kind of board we can program now?
```
arduino-cli board listall # You will see FQBN
```
4. Compile the blink test
```
mkdir /tmp/blink
cat << EOF > /tmp/blink/blink.ino
void setup() { pinMode(LED_BUILTIN, OUTPUT); }
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); delay(1000);  
  digitalWrite(LED_BUILTIN,  LOW); delay(1000);  
}
EOF
arduino-cli compile /tmp/blink --fqbn arduino:avr:nano 
```
5. Permit arduino-cli to upload
```
sudo usermod -aG dialout $USER # Give /dev/ttyUSB0 access permission to arduino-cli 
newgrp dialout
arduino-cli upload /tmp/blink -p /dev/ttyUSB0 --fqbn arduino:avr:nano 
``` 

