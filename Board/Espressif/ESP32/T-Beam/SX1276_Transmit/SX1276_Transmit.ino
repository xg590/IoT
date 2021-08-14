#include <RadioLib.h>
#include "boards.h"
SX1276 radio = new Module(RADIO_CS_PIN, RADIO_DI0_PIN, RADIO_RST_PIN, RADIO_BUSY_PIN);
void setup()
{
    initBoard(); delay(1500); 
                            //  float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain
    int state = radio.begin(LoRa_frequency,    125.0,         12,          8, SX127X_SYNC_WORD,           20,                       8,            0); 
}

int counter = 0;
void loop()
{   
    String msg = "[T-Beam] Hello ( " + String(++counter) +" )";
    int state = radio.transmit(msg);   
    delay(15000);
}
