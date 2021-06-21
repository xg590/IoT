#include <SoftwareSerial.h> 
#include <TinyGPS++.h>
TinyGPSPlus gps; // create gps object 

const int GPS_Rx = D7, GPS_Tx = D8;
const int reportInterval = 1000; // millisecond

SoftwareSerial  gps_uart( GPS_Rx,  GPS_Tx); 

void setup(){ 
     Serial.begin(115200); // connect serial  
   gps_uart.begin(  9600); // connect gps sensor 
} 
 
unsigned long lastReportTime = millis();
void loop(){  
    while (gps_uart.available()) { //  a new sentence is correctly encoded.
        int r = gps_uart.read();
        gps.encode(r);
        //Serial.println(r); 
    }
    if (millis() - lastReportTime < reportInterval) return;
    lastReportTime = millis(); 
 
    char msg[128] = ",{\"Sat\":\"N/A\", \"LL\":\"N/A\", \"TS\":\"N/A\"},";
    if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) { 
        sprintf(msg,
                ",{\"Sat\":\"%02d\", \"LL\":\"%.6f,%.6f\", \"TS\":\"%02d-%02d-%02dT%02d:%02d:%02dZ\"},",
                gps.satellites.value(), gps.location.lat(), gps.location.lng(),
                gps.date.year(), gps.date.month(), gps.date.day(),
                gps.time.hour(), gps.time.minute(), gps.time.second() // gps.time.centisecond()
                );  
    } 
    size_t msg_len =strlen(msg);
    String lora_cmd = "AT+SEND=0," + String(msg_len) +String(msg)+"\r\n";
    Serial.println(lora_cmd);   
}  
