### WiFi Internet Development Board
    * Brand: KeeYees
    * Available on Amazon: https://www.amazon.com/gp/product/B07S5Z3VYZ
    * WiFi Module: ESP-12E
    * WiFi Microchip: ESP8266
    * USB Interface: CP2102
    * Firmware: NodeMCU (written in C and programmable with Lua)

### Program WiFi dev board via CLI
1. [Setup Arduino IDE](https://github.com/xg590/IoT/tree/master/Arduino#install-arduino-ide-on-raspbian-os-via-usb) 
2. Additional Board Manager: Download [package_esp8266com_index.json](http://arduino.esp8266.com/stable/package_esp8266com_index.json) and replace arduino-1.8.10/hardware/package_index_bundled.json with it. 
   ```python
   # Here is a python script to combine two json files
   import json
   with open('package_esp8266com_index.json', 'r') as fr: ESP8266 = json.loads(fr.read())
   with open('package_index_bundled.json'   , 'r') as fr: OLD     = json.loads(fr.read())
   OLD['packages'].append(ESP8266['packages'][0])
   with open('package_index_bundled.json'  , 'w') as fw: fw.write(json.dumps(OLD))
   ```
3. Install Board [1]: 
```
$ cd arduino-1.8.10
$ ./arduino --install-boards esp8266:esp8266
```
4. Test the Blink.ino
```
$ ./arduino --port /dev/ttyUSB0 --upload examples/01.Basics/Blink/Blink.ino  --board 'esp8266:esp8266:nodemcuv2:baud=921600'
``` 

### GUI
1. Get the virtual COM port (VCP) driver from [Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
2. Enter https://arduino.esp8266.com/stable/package_esp8266com_index.json into the File>Preferences>Additional Boards Manager URLs field of the Arduino IDE. 
3. Open Boards Manager from Tools > Board menu and install <i>esp8266</i> platform 

[1] [arduino manpage](https://github.com/arduino/Arduino/blob/master/build/shared/manpage.adoc)
