#include <TinyGPS++.h>
#include "utilities.h"
TinyGPSPlus gps;
unsigned long lastReportTime, sat;
void setup()
{
    initBoard();
    delay(1500);// When the power is turned on, a delay is required.
    lastReportTime = millis();
}

void loop()
{ 
    while (Serial1.available()) { //  a new sentence is correctly encoded.
        int r = Serial1.read(); 
        gps.encode(r);
    } 
    if (millis() - lastReportTime < 1000) return;
    if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {
        sat = gps.satellites.value();
        char sz[48];
        sprintf(sz,
                "%.6f,%.6f@%02d-%02d-%02dT%02d:%02d:%02dZ",
                gps.location.lat(), gps.location.lng(),
                gps.date.year(), gps.date.month(), gps.date.day(),
                gps.time.hour(), gps.time.minute(), gps.time.second() // gps.time.centisecond()
                );
        Serial.print(sz);
        
    } else {
        Serial.print(F("NO_GPS"));
    }
    Serial.println(); 
    lastReportTime = millis(); 
}
