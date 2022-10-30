
### <a name="Arduino-CLI">Arduino-CLI:</a> Program Arduino board in CLI
* Blink
```
wget arduino-cli_0.18.3_Linux_64bit.tar.gz && tar zxvf        # https://github.com/arduino/arduino-cli/releases
sudo mv arduino-cli /usr/local/bin/ 
arduino-cli core install arduino:avr                          # Install compile platform of Arduino board family  
arduino-cli core update-index               --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json 
arduino-cli core install esp8266:esp8266    --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json 
arduino-cli core update-index               --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli core install esp32:esp32        --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli core update-index               --additional-urls https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json 
arduino-cli core install seeeduino:samd     --additional-urls https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json 
arduino-cli core update-index               --additional-urls https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json 
arduino-cli core install sandeepmistry:nRF5 --additional-urls https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json
arduino-cli board listall                                     # You will see FQBN. What kind of board we can program now? 
mkdir /tmp/blink
cd    /tmp/blink
cat << EOF > blink.ino 
int count = 0;
void setup() { pinMode(LED_BUILTIN, OUTPUT); Serial.begin(9600);} 
void loop() { 
  count++; Serial.println(count);
  digitalWrite(LED_BUILTIN, HIGH); delay(1000);  
  digitalWrite(LED_BUILTIN,  LOW); delay(1000);  
}
EOF
arduino-cli compile . --fqbn arduino:avr:nano # Compile the blink test 
sudo usermod -aG dialout $USER # Give /dev/ttyUSB0 access permission to arduino-cli 
newgrp dialout
arduino-cli upload  . --fqbn arduino:avr:nano -p /dev/ttyUSB0 
```
* Install library
```
arduino-cli lib search SHT4x
arduino-cli lib install "Adafruit SHT4x Library"
```
* More
```
cat << EOF >> ~/.bashrc
export PATH=\$PATH:~/bin
alias    xiao='arduino-cli compile . --fqbn   Seeeduino:samd:seeed_XIAO_m0 && arduino-cli upload . --fqbn   Seeeduino:samd:seeed_XIAO_m0 -p'
alias d1_mini='arduino-cli compile . --fqbn        esp8266:esp8266:d1_mini && arduino-cli upload . --fqbn        esp8266:esp8266:d1_mini -p'
alias     bbc='arduino-cli compile . --fqbn sandeepmistry:nRF5:BBCmicrobit && arduino-cli upload . --fqbn sandeepmistry:nRF5:BBCmicrobit -p' 
EOF
```