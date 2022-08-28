### Dev Env  
* ESP32 (Heltec WiFi LoRa 32 V2): AArch32
* VM    : x86_64 and Ubuntu 20.04.3
### Hello World with ESP-IDF (IoT Dev Framework) [ref](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html)
1. Toolchain
```
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
```
2. ESP-IDF
``` 
git clone -b v4.4.2 --recursive https://github.com/espressif/esp-idf.git esp_dev/esp_idf_442
```
3. Board-specific setup
``` 
./esp_dev/esp_idf_442/install.sh esp32
```
4. Env var
```
. ./esp_dev/esp_idf_442/export.sh
```
5. Build "Hello World" (<b>It is FreeRTOS-based C</b>)
``` 
cp -r $IDF_PATH/examples/get-started/hello_world /tmp
cd /tmp/hello_world
idf.py set-target esp32 
idf.py build
```
6. Connect the ESP32 to PC via USB and gain permission to access it
```
sudo usermod -aG dialout $USER && newgrp dialout
```
7. Flash and print "Hello World"
```
idf.py -p /dev/ttyUSB0 flash
screen /dev/ttyUSB0 115200
```
### Blink Heltec WiFi LoRa 32 V2
```
. /data/esp_dev/esp_idf_442/export.sh
cp -r $IDF_PATH/examples/get-started/blink /tmp
cd /tmp/blink
# idf.py set-target esp32 # because run before
sed -i '34s/default 5/default 25/' main/Kconfig.projbuild # LED_GPIO is 25 instead of 5
idf.py build
idf.py -p /dev/ttyUSB0 flash
```
