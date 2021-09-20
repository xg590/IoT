## Home Automation
### Materials
* Photoelectric resistor
* SHT4x temperature/humidity sensor
* 2x ESP8266 (D1 mini + oled/battery shiled)
* Tactile switches
* Raspberry Pi 3B
* TP-Link HS105 WiFi-enabled power plug
* TP-Link LB110 WiFi-enabled light bulb
### Role Assignment
* Sensors report Luminance/Temperature/Humidity to a web server running on Raspberry Pi
* DIYed WiFi remote asks web server to turn things on/off or tweak parameters.
* Server monitors the temperature and fetches sunrise/sunset data to turn on/off (A/C plugged) power plug and light bulb