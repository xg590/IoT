#include "SSD1306Wire.h"
const int OLED_SDA = D2, OLED_SCL = D1;
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL, GEOMETRY_64_48);// 64x48 screen

void initScreen() {  
    display.init();
    //display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);  
    display.clear(); 
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString( 0,  0, "UL");
    display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(64,  0, "UR");
    display.setTextAlignment(TEXT_ALIGN_CENTER);  display.drawString(32, 16, "Center");
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString( 0, 32, "BL");
    display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(64, 32, "BR");
    delay(3000);
    display.display();// write the buffer to the display 
}

void setup() {
  // put your setup code here, to run once:
  initScreen();
}

void loop() {
  // put your main code here, to run repeatedly:

}
