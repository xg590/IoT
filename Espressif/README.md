### Usb-to-uart bridge chip
* It seems like both ESP8266-based and ESP32-based board have CP2102 usb-to-uart bridge chip.
* Get the virtual COM port (VCP) drive from [Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) or [here](CP210x_Universal_Windows_Driver.zip)
### Arduino-CLI
```  
arduino-cli core install esp8266:esp8266 --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json 
arduino-cli board listall
mkdir /tmp/blink
cat << EOF > /tmp/blink/blink.ino
void setup() { pinMode(LED_BUILTIN, OUTPUT); }
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); delay(1000); 
  digitalWrite(LED_BUILTIN,  LOW); delay(1000); 
}
EOF
arduino-cli compile --fqbn esp8266:esp8266:d1_mini /tmp/blink
arduino-cli upload /tmp/blink -p /dev/ttyUSB0 --fqbn esp8266:esp8266:d1_mini
```
