#include <SoftwareSerial.h> 
#include <TinyGPS.h> 

/*
This is for Arduino, not for ESP8266.
*/


TinyGPS gps; // create gps object 

const int GPS_Rx = 2, GPS_Tx = 13;
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

    char latLng[32] = "\"LL\":\"N/A\"";
    float lat, lng; unsigned long _;
    gps.f_get_position(&lat, &lng, &_); 
    if (lat != TinyGPS::GPS_INVALID_F_ANGLE && lng != TinyGPS::GPS_INVALID_F_ANGLE) {  
      sprintf(latLng, "\"LL\":\"%d.%07ld,%d.%07ld\"", 
                      int(lat), abs(long(lat*10000000)) % 10000000, 
                      int(lng), abs(long(lng*10000000)) % 10000000);  
    } 

    char sat[16] = "\"Sat\":\"N/A\"";
    if (gps.satellites() != TinyGPS::GPS_INVALID_SATELLITES) { sprintf(sat, "\"Sat\":\"%02d\"", gps.satellites()); } 
    /*
    if (gps.f_altitude()   != TinyGPS::GPS_INVALID_F_ALTITUDE) { Serial.print(" alt|") ; Serial.print(gps.f_altitude()   );}
    if (gps.f_course()     != TinyGPS::GPS_INVALID_F_ANGLE   ) { Serial.print(" cus|") ; Serial.print(gps.f_course()     );}
    if (gps.f_speed_kmph() != TinyGPS::GPS_INVALID_F_SPEED   ) { Serial.print(" spd|") ; Serial.print(gps.f_speed_kmph() );}
     */
 
    char timestamp[32] = "\"TS\":\"N/A\"";
    int year; byte month, day, hour, minute, second, hundredths; unsigned long age; // A varible defined by Library author
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
    if (age != TinyGPS::GPS_INVALID_AGE) {
      sprintf(timestamp, "\"TS\":\"%02d-%02d-%02dT%02d:%02d:%02dZ\"", year, month, day, hour, minute, second); 
    } 

    // size_t len = strlen(chararray);
      
    int msg_len = 4;
    msg_len += strlen(timestamp);  
    msg_len += strlen(sat); 
    msg_len += strlen(latLng);
    String msg = "AT+SEND=0," + String(msg_len) +",{"+String(timestamp)+","+String(sat)+","+String(latLng)+"}\r\n";
    Serial.println(msg);  
}  
