#include <RadioLib.h> 
#include "SSD1306Wire.h" 

const int LoRa_CS = 18, LoRa_DIO0 = 26, LoRa_RST = 14;
const float LoRa_frequency = 915.0;   
const int OLED_SDA = 4, OLED_SCL = 15, OLED_RST = 16;

SX1276 radio = new Module(LoRa_CS, LoRa_DIO0, LoRa_RST);  // LoRa_DIO0 is for interrupt 
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);

void setup()
{                         //    float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain
    int state = radio.begin(LoRa_frequency,    125.0,          9,          7, SX127X_SYNC_WORD,           10,                       8,            0); 
    
    pinMode(OLED_RST,OUTPUT); digitalWrite(OLED_RST, LOW); delay(50); digitalWrite(OLED_RST, HIGH);  
    display.init(); 
    display.setTextAlignment(TEXT_ALIGN_CENTER);   
    if (state == ERR_NONE) display.drawString( 64, 24, "Lora online!"); 
    display.display();// write the buffer to the display 
}

int counter = 0;
void loop()
{   
    String msg = String(++counter)+") Hello World From [Heltec WiFi LoRa 32 V2]!";
    int state = radio.transmit(msg);  
    display.clear();
    if (state == ERR_NONE) { 
      display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString(  0,  0, "Cnt: "+String(counter));
      display.setTextAlignment(TEXT_ALIGN_CENTER);  display.drawString( 64, 24, "Tx succeed!");
    }
    display.display();// write the buffer to the display  
    delay(3000);
} 
