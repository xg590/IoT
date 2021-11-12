## Home Automation
### Materials
* ESP8266 + Sensors
  * D1 mini
  * Photoelectric resistor
  * SHT4x temperature/humidity sensor 
* Remote (New)
  * TV remote 
  * D1 mini
  * VS1838B (InfraRed receiver)
* ESP8266 Remote (Old)
  * D1 mini
  * D1 mini's oled shield, battery shiled
  * Tactile switches
* ESP8266 Relay
  * D1 mini
  * Relay
* ESP8266 Servo
  * D1 mini
  * SG90
* Raspberry Pi 3A
* TP-Link HS105 WiFi-enabled power plug
* TP-Link LB110 WiFi-enabled light bulb
### Role Assignment
* D1 with sensors reports Luminance/Temperature/Humidity to a web server running on Raspberry Pi 3A
<img src="sensor/sensor.jpg"></img>
* D1 with infrared sensor convert IR signal to HTTP request over WiFi.
<img src="remote/remote.jpg"></img>
* Server monitors the temperature and fetches sunrise/sunset data to turn on/off (A/C plugged) power plug and light bulb
* Bring WiFi to a relay that controlling a USB port 
<img src="relay/relay.jpg"></img>
* Control a light switch  
<img src="light_switch/Control_a_Light_Switch.png"></img>
