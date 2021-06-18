#include <RadioLib.h>

#define CS_PIN                15 // D8@WeMos_D1_mini 
#define G0_PIN                 4 // D2@WeMos_D1_mini This pin is for interrupt. All except GPIO16 is interruptible on WeMos_D1_mini 
#define RST_PIN                5 // D1@WeMos_D1_mini  
#define LoRa_frequency     915.0 

                        //cs    ,irq   ,  rst 
SX1276 radio = new Module(CS_PIN, G0_PIN, RST_PIN);   
void setup()
{   
    Serial.begin(115200);     
                          //    float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain
    int state = radio.begin(LoRa_frequency,    125.0,          9,          7, SX127X_SYNC_WORD,           10,                       8,            0); 
    if (state == ERR_NONE) Serial.println(F("Init success!")); 
}

int count = 0;
void loop()
{   
    String msg = String(++count)+") Hello World From RFM95W!";
    int state = radio.transmit(msg); 
    if (state == ERR_NONE) Serial.println(F("Tx success!"));  
    delay(3000);
} 
