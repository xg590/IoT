#include <RadioLib.h>
#include "boards.h"
SX1276 radio = new Module(RADIO_CS_PIN, RADIO_DI0_PIN, RADIO_RST_PIN, RADIO_BUSY_PIN);
void setup()
{
    initBoard(); delay(1500); 
                            //  float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain
    int state = radio.begin(LoRa_frequency,    125.0,          9,          7, SX127X_SYNC_WORD,           17,                       8,            0); 
}
void loop()
{ 
    int state = radio.transmit("Hello World!");  
    delay(1000);
}
