#include <RadioLib.h>
#include "boards.h"
SX1276 radio = new Module(RADIO_CS_PIN, RADIO_DI0_PIN, RADIO_RST_PIN, RADIO_BUSY_PIN);
void setup()
{
    initBoard(); delay(1500); 
    int state = radio.begin(LoRa_frequency); 
}
void loop()
{ 
    int state = radio.transmit("Hello World!");  
    delay(1000);
}
