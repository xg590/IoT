#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
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
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  char s[10];
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");
  display.clear(); 
  display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString( 0,   0, "V :");    
  sprintf(s, "%5.3f", loadvoltage);
  display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(64,   0,  s); 
  display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString( 0,  16, "mA:");    
  sprintf(s, "%5.1f", current_mA);
  display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(64,  16, s); 
  display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString( 0,  32, "mW:");    
  sprintf(s, "%5.1f", power_mW);
  display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(64,  32, s); 
  display.display();// write the buffer to the display 

    delay(500);
}
