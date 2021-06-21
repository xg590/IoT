#include "SPI.h"
#include "SD.h"   
#include <SoftwareSerial.h> 

const int LoRa_Rx = D1, LoRa_Tx = D2;   
SoftwareSerial  lora_uart(LoRa_Rx,  LoRa_Tx); 
const int chipSelect = D8;  // used for ESP8266
void setup() {   
  Serial.begin(115200);  
  lora_uart.begin(115200);
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    while (1);
  }
}

int count = 1;
void loop() { 
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
}

 
 
