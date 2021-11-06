### Transmitter
* Use WiFi development board and Inferred LED to control a projector. 
* Setup a http server with the board
* Server receive command then send it to projector.
### Hardware 
* Inferred LED
* 150Ω resistor
* ESP8266 WiFi SOC
### Wiring
```
D11 <-150 Oh-> OUT (Longer electrode)
GND <--------> GND (Shorter)
```
<img src="transmitter.jpg"></img> 
### Decoded IR signal from the original projector remote 
* In receiver part of this project, we have following result:
``` 
20:25:00.723 -> Protocol=7 Address=0xF483 Command=0x17 Raw=0xE817F483 
```
* It means the original projector remote use NEC protocol send command 0x17 to address 0xF483. 
* It tells projector to power off. 
* We can clone this ir signal and use an ir led to control projector
### Command explanation 
After we decoded one ir signal, we know the command is 0x17. It is a hex. How do we send 0x17 over http to the board? We convert the hex (0x17) to decimal (23) before http request, then cast the string "23" back to integer 23 after http.
```
Button      Hex      Dec
Power       0x17     23
Home        0x16     22
Up          0xb      11
Left        0xe      14
OK          0x15     21
Right       0xf      15
Settings    0x30     48
Down        0xc      12
Back        0x28     40
Vol-        0x83     131
Mute        0x14     20
Vol+        0x82     130
```
### Send cloned IR signal to projector
```C
#define IR_SEND_PIN 11
#include <IRremote.h>
void setup() {
    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);
}
uint16_t sAddress = 0xF483; // uint16_t sAddress = atoi("62595");
uint8_t sRepeats = 0;
void loop() {
    uint8_t sCommand = 0x28; 
    IrSender.sendNEC(sAddress, sCommand, sRepeats);
    // IrSender.sendNECRaw(0xD728F483, sRepeats); 
    delay(3600*1000);
}
```
### Http Server + Transmitter
* [transmitter.ino](transmitter.ino) is the code 
* As the code runs on WiFi Soc, a http server runs on WLAN.
* Use GET method to tell WiFi Soc what command we want it to send.
```
import requests 
requests.get('http://192.168.0.108/irled?cmd=22&delay=5') # Home 
```
