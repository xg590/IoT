## Infrared
### Receiver VS1838B ([Amazon](https://www.amazon.com/gp/product/B06XYNDRGF/))
##### Specifications:
* Operating Voltage: 2.7 – 5.5vDC
* Infrared Frequency: 38kHz 1838 NEC Code
* Reception Angle: ~45 Degrees
* Reception Distance up to 18m
* Lead Pitch: 2.54mm
##### Pic
![alt text](https://github.com/xg590/IoT/raw/master/Infrared/VS1838B.png "VS1838B")
##### Wiring ([Good Ref](https://arduino.stackexchange.com/questions/3926/using-vs1838b-with-arduino))
```
OUT <--> D11 (digital pin not A11/Analog Pin)
GND <--> GND
VCC <--> VCC 
```
##### Code
* Library: IRremote by shirriff, z3t0, ArminJo Ver. 3.3.0
* Find protocol enum decode_type_t in [IRProtocol.h](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/src/IRProtocol.h)  
```C
#include <IRremote.h>
#define IR_RECEIVE_PIN 11
void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    //ENABLE_LED_FEEDBACK : Blink onboard led when receive data
}

void loop() {
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.print("[Unknown Protocol]");
        } else {
            Serial.print("[Known Protocol] Minimal Result: ");
            IrReceiver.printIRResultMinimal(&Serial);
        }
        Serial.println();
        IrReceiver.resume(); // Enable receiving of the next value
    }
}
```
##### Sample Result  
```
20:25:00.723 -> P=7 Address=0xF483 Command=0x17 Raw=0xE817F483
```
### Sender 
Infrared LED  
##### Wiring
```
D11 <-150 Oh-> OUT (Longer electrode)
GND <--------> GND (Shorter)
```
##### Code
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
// Results for the first loop to: Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)
