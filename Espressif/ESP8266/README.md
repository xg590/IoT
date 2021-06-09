### Arduino-cli
``` 
arduino-cli core install esp8266:esp8266 --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json   
mkdir /tmp/blink
cat << EOF > /tmp/blink/blink.ino
void setup() { pinMode(LED_BUILTIN, OUTPUT); }
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); delay(1000);  
  digitalWrite(LED_BUILTIN,  LOW); delay(1000);  
}
EOF
```
#### d1_mini
```
arduino-cli compile --fqbn esp8266:esp8266:d1_mini /tmp/blink
arduino-cli upload /tmp/blink -p /dev/ttyUSB0 --fqbn esp8266:esp8266:d1_mini 
```
