### Usb-to-uart bridge chip
* It seems like both ESP8266-based and ESP32-based board have CP2102 usb-to-uart bridge chip.
* Get the virtual COM port (VCP) drive from [Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) or [here](CP210x_Universal_Windows_Driver.zip)
### Install ESP32 or ESP8266
```  
arduino-cli core install esp8266:esp8266 --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json 
arduino-cli core install esp32:esp32     --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli board listall 
arduino-cli compile --fqbn esp8266:esp8266:d1_mini /tmp/blink 
```
