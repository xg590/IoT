 
#include "SSD1306Wire.h"  
const int OLED_SDA = 4, OLED_SCL = 15, OLED_RST = 16;
 
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);

void setup()
{                       
    
    pinMode(OLED_RST,OUTPUT); digitalWrite(OLED_RST, LOW); delay(50); digitalWrite(OLED_RST, HIGH);  
    display.init(); 
    display.setTextAlignment(TEXT_ALIGN_CENTER);     
    display.clear();  
      display.setTextAlignment(TEXT_ALIGN_CENTER); display.drawString( 64, 24, "Tx succeed!"); 
    display.display(); 
}
 
void loop()
{    
    delay(3000);
} 
