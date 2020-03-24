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
  Serial.print(','); 
  Serial.println();
  delay(1000);
}

static void gy_neo6mv2() {
  while (uart.available()) {
    char c = uart.read(); 
    tinygps.encode(c); 
  }
  float flat, flon;
  unsigned long age = 0; 
  
  tinygps.f_get_position(&flat, &flon, &age);
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 7);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 7);
  print_float(tinygps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 1);
  print_float(tinygps.f_course(), TinyGPS::GPS_INVALID_F_ANGLE, 2);
  print_float(tinygps.f_speed_knots(), TinyGPS::GPS_INVALID_F_SPEED, 7);
  print_int(tinygps.satellites(), TinyGPS::GPS_INVALID_SATELLITES); 
  print_date(tinygps);
} 
 
static void print_int(unsigned long val, unsigned long invalid) { 
  if (val != invalid)
    Serial.print(val); 
  Serial.print(','); 
}

static void print_float(float val, float invalid, int prec) { 
  if (val != invalid) 
    Serial.print(val, prec); 
  Serial.print(','); 
} 

static void print_date(TinyGPS &gps) {
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age != TinyGPS::GPS_INVALID_AGE) { 
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d",
        month, day, year, hour, minute, second);
    Serial.print(sz);
  } 
}