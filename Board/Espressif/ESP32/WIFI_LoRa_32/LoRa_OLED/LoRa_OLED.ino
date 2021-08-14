#include <RadioLib.h> 
#include "SSD1306Wire.h" 

const int LoRa_CS = 18, LoRa_DIO0 = 26, LoRa_RST = 14;
const float LoRa_frequency = 915.0;   
const int OLED_SDA = 4, OLED_SCL = 15, OLED_RST = 16;

SX1276 radio = new Module(LoRa_CS, LoRa_DIO0, LoRa_RST);  // LoRa_DIO0 is for interrupt 
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);
 

volatile bool receivedFlag = false;// flag to indicate that a packet was received 
volatile bool enableInterrupt = true;// disable interrupt when it's not needed
 
void setFlag(void)// IMPORTANT: this function MUST be 'void' type and MUST NOT have any arguments!
{   // this function is called when a complete packet is received by the module
    // check if the interrupt is enabled
    if (!enableInterrupt) {
        return;
    }  
    receivedFlag = true; // we got a packet, set the flag
}

void setup()
{
    Serial.begin(115200);
    pinMode(OLED_RST,OUTPUT); digitalWrite(OLED_RST, LOW); delay(50); digitalWrite(OLED_RST, HIGH);  
                            //  float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain
    int state = radio.begin(LoRa_frequency,    125.0,         12,          8, SX127X_SYNC_WORD,           10,                       8,            0); 
    if (state == ERR_NONE) {
        Serial.println(F("[radio.begin] success!"));
    } else {
        Serial.print(F("[radio.begin] failed, code ")); Serial.println(state);
        while (true);
    } 

    // Set interrupt service routine function to call when DIO0 activates.
    radio.setDio0Action(setFlag); 

    // start listening for LoRa packets
    Serial.print(F("[SX1276] Starting to listen ... "));
    state = radio.startReceive(); 
    if (state == ERR_NONE) {
        Serial.println(F("success!"));
    } else {
        Serial.print(F("failed, code ")); Serial.println(state);
        while (true);
    }  
    display.init();
    //display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER); display.drawString( 64, 24, "Hello~");
    display.display();// write the buffer to the display 
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  
}


void loop()
{
    // check if the flag is set
    if (receivedFlag) {// disable the interrupt service routine while processing the data 
        enableInterrupt = false; 
        receivedFlag = false;// reset flag  
        
        String str;
        int state = radio.readData(str); 
        if (state == ERR_NONE) {
            // packet was successfully received
            Serial.println(F("[SX1276] Received packet!"));  
            Serial.print(F("[SX1276] Data:\t\t")); Serial.println(str); 
            Serial.print(F("[SX1276] RSSI:\t\t")); Serial.print(radio.getRSSI()); Serial.println(F(" dBm"));
            Serial.print(F("[SX1276] SNR:\t\t")); Serial.print(radio.getSNR()); Serial.println(F(" dB")); 
            Serial.print(F("[SX1276] Frequency error:\t\t")); Serial.print(radio.getFrequencyError()); Serial.println(F(" Hz"));  
            display.clear();
            display.drawString(  0,  0, "[RSSI]  "+String(radio.getRSSI())+" dBm"); 
            display.drawString(  0, 24, str);
            display.drawString(  0, 48, "[SNR ]  "+String(radio.getSNR())+" dB");  
            display.display();// write the buffer to the display 
        } else if (state == ERR_CRC_MISMATCH) { 
            Serial.println(F("[SX1276] CRC error!")); 
        } else { 
            Serial.print(F("[SX1276] Failed, code ")); Serial.println(state);
        } 

        radio.startReceive(); // put module back to listen mode

        // we're ready to receive more packets,
        // enable interrupt service routine
        enableInterrupt = true;
    }
}
