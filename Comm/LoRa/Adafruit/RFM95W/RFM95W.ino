#include <RadioLib.h>

#define RADIO_CS_PIN                15 // D8
#define RADIO_IRQ_PIN                0 // D3
#define RADIO_RST_PIN                5 // D1
#define RADIO_En_PIN                 4 // D2
#define LoRa_frequency           915.0

                        //      cs    ,       irq    ,       rst
SX1276 radio = new Module(RADIO_CS_PIN, RADIO_IRQ_PIN, RADIO_RST_PIN);
void setup()
{ 
    Serial.begin(115200);
    pinMode(RADIO_En_PIN, OUTPUT);
    digitalWrite(4, HIGH); 
    Serial.println("dwadwa"); 
                          //    float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain
    int state = radio.begin(LoRa_frequency,    125.0,          9,          7, SX127X_SYNC_WORD,           17,                       8,            0); 
    
    if (state == ERR_NONE) {
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code ")); 
        while (true);
    }
}
void loop()
{ 
    int state = radio.transmit("Hello World From RFM95W!");  
    delay(1000);
}
