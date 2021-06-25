#include <SoftwareSerial.h> 
#include <TinyGPS++.h>
#include "SSD1306Wire.h"
TinyGPSPlus gps; // create gps object 

const int GPS_Rx = D7, GPS_Tx = D8, LoRa_Rx = D6, LoRa_Tx = D5, OLED_SDA = D2, OLED_SCL = D1;
const int reportInterval = 3000; // millisecond

SoftwareSerial  gps_uart(  GPS_Rx,  GPS_Tx); 
SoftwareSerial lora_uart( LoRa_Rx, LoRa_Tx); 
SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);

void initScreen() {
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
    delay(1000);    
    display.clear(); 
}

void screen(String text) { 
    display.clear();  
    display.setTextAlignment(TEXT_ALIGN_CENTER);  display.drawString( 64, 24, text); 
    display.display();// write the buffer to the display 
}

void lora(String cmd) { 
    unsigned long lastReportTime = millis();
    if (cmd.startsWith("Listen")) { 
      Serial.println("[LoRa Listening]"); 
    } else {
      Serial.println("[LoRa AT] "+cmd); 
      lora_uart.write(cmd.c_str());
    }
    
    String reply = "[LoRa "+cmd+"] Timeout"; 
    lastReportTime = millis();  
    while (true) { 
      while (lora_uart.available()) { 
        reply = lora_uart.readString(); 
      }
      if (millis() - lastReportTime > reportInterval) { 
        break;
      } 
    }  
    Serial.print(reply); 
    screen(reply); 
} 

void testScreenAndLora() {  
    lora("AT\r\n");    
    delay(1000);
}

void setup(){ 
     Serial.begin(115200); // connect serial 
   gps_uart.begin(9600); // connect gps  
  lora_uart.begin(115200); // connect lora 
     Serial.setTimeout(3000);
   gps_uart.setTimeout(3000);
  lora_uart.setTimeout(3000);  
    delay(3000);  
    Serial.println("\n\n\n");
    initScreen();
    //testScreenAndLora();
    lora("AT+CPIN=FABC0002EEDCAA90FABC0002EEDCAA90\r\n");  
    delay(1000);  
}  
  
int counter = 1;  
void loop(){
    unsigned long lastReportTime = millis();  
    while (true) { 
      while (gps_uart.available()) { //  a new sentence is correctly encoded.
        int r = gps_uart.read();
        gps.encode(r); 
      }
      if (millis() - lastReportTime > reportInterval) { 
        break;
      } 
    }   
    if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {  
      char gps_char[128];
      sprintf(gps_char,
              "{'#':%d,'Sat':%d,'Lat':%.6f,'Lng':%.6f,'TS':'%02d-%02d-%02dT%02d:%02d:%02dZ'}",
              counter, gps.satellites.value(), gps.location.lat(), gps.location.lng(),
              gps.date.year(), gps.date.month(), gps.date.day(),
              gps.time.hour(), gps.time.minute(), gps.time.second()//, gps.time.centisecond() 
              ); 
      String gps_str = String(gps_char);
      String lora_cmd = "AT+SEND=0,"+String(gps_str.length())+","+gps_str+"\r\n"; 
      lora(lora_cmd); // send a msg
      //lora("Listen"); // listen a respond from other lora
      counter++;
    } else {
      screen("NO GPS Sat");
      Serial.println("NO GPS Satellite");
    } 
}   
