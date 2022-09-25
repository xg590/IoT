### Program Arduino board on Raspberry Pi? Arduino-CLI is here for help. <a name="Arduino-CLI"></a>
1. [Download the tool](https://github.com/arduino/arduino-cli/releases)
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
int count = 0;
void setup() { pinMode(LED_BUILTIN, OUTPUT); Serial.begin(9600);} 
void loop() { 
  count++; Serial.println(count);
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
6. Install library
```
arduino-cli lib search SHT4x
arduino-cli lib install "Adafruit SHT4x Library"
```
### Trouble shooting
* May need python and pyserial library
```
sudo apt update
sudo apt install python3-pip
ln -s /usr/bin/python3 /usr/bin/python
pip3 install pyserial
```
### More about Arduino-CLI <a name="ESP-CLI"></a>
```  
arduino-cli core install esp8266:esp8266 --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json 
arduino-cli core install esp32:esp32     --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli core install seeeduino:samd  --additional-urls https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
arduino-cli board listall 
arduino-cli compile --fqbn esp8266:esp8266:d1_mini /tmp/blink 
cat << EOF >> ~/.bashrc
export PATH=\$PATH:~/bin
alias    xiao='arduino-cli compile . --fqbn Seeeduino:samd:seeed_XIAO_m0 && arduino-cli upload . --fqbn Seeeduino:samd:seeed_XIAO_m0 -p'
alias d1_mini='arduino-cli compile . --fqbn      esp8266:esp8266:d1_mini && arduino-cli upload . --fqbn      esp8266:esp8266:d1_mini -p'
EOF
```
