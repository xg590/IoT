/*
sudo ln -s /home/pi/arduino-1.8.12/arduino /usr/local/bin/arduino
arduino --install-library "Adafruit Unified Sensor"
arduino --install-library "Adafruit BNO055"
arduino --install-library TinyGPS
arduino --board arduino:avr:uno --port /dev/ttyUSB0 --upload sensor.ino

import serial
with serial.Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=2) as s:
    while 1: print(s.readline())
*/

#include <TinyGPS.h> 
#include <SoftwareSerial.h>  
#include <Wire.h>

TinyGPS tinygps;
SoftwareSerial uart(0, 1); 

void setup(void) {
  Serial.begin(115200);
  uart.begin(9600); // gps 
  delay(1000);      // delay for compass
}

void loop() { 
  gy_neo6mv2();  
  delay(1000);
}

static void gy_neo6mv2() {
  while (uart.available()) {
    char c = uart.read(); 
    tinygps.encode(c); 
  } 
    
  float lat, lon; unsigned long _; 
  gps.f_get_position(&lat, &lon, &_); 
  if (lat                != TinyGPS::GPS_INVALID_F_ANGLE   ) { Serial.print(" lat|") ; Serial.print(lat                );}
  if (lon                != TinyGPS::GPS_INVALID_F_ANGLE   ) { Serial.print(" lon|") ; Serial.print(lon                );}
  if (gps.f_altitude()   != TinyGPS::GPS_INVALID_F_ALTITUDE) { Serial.print(" alt|") ; Serial.print(gps.f_altitude()   );}
  if (gps.f_course()     != TinyGPS::GPS_INVALID_F_ANGLE   ) { Serial.print(" cus|") ; Serial.print(gps.f_course()     );}
  if (gps.f_speed_kmph() != TinyGPS::GPS_INVALID_F_SPEED   ) { Serial.print(" spd|") ; Serial.print(gps.f_speed_kmph() );}
  if (gps.satellites()   != TinyGPS::GPS_INVALID_SATELLITES) { Serial.print(" sat|") ; Serial.print(gps.satellites()   );} 
  print_date(gps);
  Serial.println(); 
} 
 
static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age; // A varible defined by Library author
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age != TinyGPS::GPS_INVALID_AGE) {
    char sz[32];
    sprintf(sz, " ts|%02d-%02d-%02dT%02d:%02d:%02d",
        year, day, month, hour, minute, second); 
    Serial.print(sz);
  }  
} 
