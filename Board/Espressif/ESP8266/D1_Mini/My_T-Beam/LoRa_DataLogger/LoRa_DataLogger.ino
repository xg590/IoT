#include "SPI.h"
#include "SD.h"   
#include <SoftwareSerial.h> 
#include "SSD1306Wire.h"
 
const int chipSelect = D8;  // used for ESP8266

const int reportInterval = 1000; // millisecond
const int GPS_Rx = D7, GPS_Tx = D8, OLED_SDA = D2, OLED_SCL = D1;
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);

void RYLR896(String cmd) {
    ;
}
void setup() {    
    Serial.begin(115200); // connect serial   
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);  
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString(  0,  0, "Upper_Left");
    display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(128,  0, "Upper_Right");
    display.setTextAlignment(TEXT_ALIGN_CENTER);  display.drawString( 64, 24, "Center");
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString(  0, 48, "Bottom_Left");
    display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(128, 48, "Bottom_Right");
    display.display();// write the buffer to the display
    delay(2000);  

    
    display.clear();
    Serial.println("AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90");
    unsigned long lastReportTime = millis(); 
    while (1) { 
        if (millis() - lastReportTime > 5000) break;
        String msg = "Nothing";
        if (Serial.available()) {
          msg = Serial.readString(); 
        } else {
          continue;
        }
        display.setTextAlignment(TEXT_ALIGN_CENTER);  display.drawString( 64, 24, msg); 
        break;
    } 
    display.display();// write the buffer to the display 
    delay(1000);
     
}

void loop() { 
  
  
  
  }
/*
void setup1() {   
  Serial.begin(115200);   
  delay(1000);
  RYLR896_init();Serial.println("over2");
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    while (1);
  }
}

int count = 1;
void loop1() { 
  Serial.println("[New] gps_logger_"+String(count)+".log"); 
  File f = SD.open("gps_logger_"+String(count)+".log", FILE_WRITE);  
  count++; 
  while (1) {
    String msg = "";
    if (lora_uart.available()) {  
      msg = lora_uart.readString(); 
    }
    if (msg == "") {
      continue;
    } else if (msg.indexOf("NewLog") > -1 ) {
      Serial.println("[End] New Log");   
      break;
    } else {
      Serial.print(msg);   
      f.print(msg); 
      f.flush();
    }
  }; 
  f.close(); 
}*/

 
 
