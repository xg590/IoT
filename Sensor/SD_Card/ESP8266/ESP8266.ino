#include "SPI.h"
#include "SD.h"  

const int chipSelect = D8;  // used for ESP8266
void setup() {
  Serial.begin(115200); 
  SD.begin(chipSelect);
}

void loop() { 
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Hello World!");
    dataFile.close();
  } 
  delay(3000);
}
