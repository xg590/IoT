#include "SSD1306Wire.h"
#include "boards.h"

SSD1306Wire display(0x3c, I2C_SDA, I2C_SCL);
void setup()
{
    initBoard(); delay(1500);
    display.init();
    //display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
}

void loop()
{
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString(  0,  0, "Upper_Left");
    display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(128,  0, "Upper_Right");
    display.setTextAlignment(TEXT_ALIGN_CENTER);  display.drawString( 64, 24, "Center");
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString(  0, 48, "Bottom_Left");
    display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(128, 48, "Bottom_Right");
    display.display();// write the buffer to the display
    delay(10);
}