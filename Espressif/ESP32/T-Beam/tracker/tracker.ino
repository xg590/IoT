#include <RadioLib.h>
#include <TinyGPS++.h>
#include "SSD1306Wire.h"
#include "boards.h"
#include "utilities.h"

SX1276 radio = new Module(RADIO_CS_PIN, RADIO_DI0_PIN, RADIO_RST_PIN, RADIO_BUSY_PIN);
TinyGPSPlus gps;
SSD1306Wire display(0x3c, I2C_SDA, I2C_SCL);

unsigned long lastReportTime = millis();
const int reportInterval = 1000; // millisecond

void setup()
{
    initBoard(); delay(1500);
    int state = radio.begin(LoRa_frequency);
    if (state == ERR_NONE) {
        Serial.println("[ Radio ] Begin!");
    } else {
        Serial.print("[ Radio ] Failed! Code="); Serial.println(state);
        while (true);
    }
    display.init(); // 128x64 OLED
    //display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
}

void loop()
{
    while (Serial1.available()) { //  a new sentence is correctly encoded.
        int r = Serial1.read();
        gps.encode(r);
    }
    if (millis() - lastReportTime < reportInterval) return;
    lastReportTime = millis();
 
    char char_vol[16] = "V:N/A", char_amp[16] = "A:N/A";
    if (PMU.isBatteryConnect()) {
        float vol = PMU.getBattVoltage()/1000,
              amp = PMU.getBattDischargeCurrent()/1000;
        Serial.println("[Battery] OK"); 
    sprintf(char_vol, "V:%.2f", vol); // V:4.12
    sprintf(char_amp, "A:%.3f", amp); // A:0.123
    } else {
      Serial.println("[Battery] V:N/A, A:N/A"); 
    }

    char char_latLng[32] = "LL:N/A", char_timestamp[32] = "Ts:N/A", char_sat[16] = "S:00";
    if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {
        Serial.println("[  GPS  ] Vaild");
        sprintf(char_latLng, "LL:%.6f,%.6f", gps.location.lat(), gps.location.lng());
        sprintf(char_timestamp, "Ts:%02d-%02d-%02dT%02d:%02d:%02dZ", 
                gps.date.year(), gps.date.month(), gps.date.day(),
                gps.time.hour(), gps.time.minute(), gps.time.second() // gps.time.centisecond()
                );
        sprintf(char_sat, "S:%02d", gps.satellites.value()); 
    } else {
        Serial.println("[  GPS  ] Invalid"); 
    }
    
    String msg = String(char_vol)+","+String(char_amp)+","+ 
                 String(char_latLng)+","+String(char_timestamp)+","+String(char_sat);
    Serial.println(String("[  MSG  ] ")+msg);
    
    int state = radio.transmit(msg);
    char char_txRate[16] = "Tx:N/A"; 
    if (state == ERR_NONE) {
        Serial.println(F("[ Radio ] Good Tx!"));
        sprintf(char_txRate, "Tx:%.3f", radio.getDataRate()/1000);   // Tx:512.345
    } else if (state == ERR_PACKET_TOO_LONG) {
        Serial.println("[ Radio ] No longer than 256 bytes!");
    } else if (state == ERR_TX_TIMEOUT) {
        Serial.println("[ Radio ] Transmitting Timeout!");
    } else {
        Serial.print("[ Radio ] Failed! Code="); Serial.println(state);
    } 
  
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString(  0,  0, char_vol);
    display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(128,  0, char_amp);
    display.setTextAlignment(TEXT_ALIGN_CENTER);  display.drawString( 64, 24, char_timestamp);
    display.setTextAlignment(TEXT_ALIGN_LEFT  );  display.drawString(  0, 48, char_sat);
    display.setTextAlignment(TEXT_ALIGN_RIGHT );  display.drawString(128, 48, char_txRate);
    display.display();// write the buffer to the display
    delay(1000);
}
