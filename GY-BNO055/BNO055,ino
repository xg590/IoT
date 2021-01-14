/*
sudo ln -s /home/pi/arduino-1.8.13/arduino /usr/local/bin/arduino 
arduino --install-library "Adafruit Unified Sensor"
arduino --install-library "Adafruit BNO055"
arduino --board arduino:avr:nano:cpu=atmega328old --port /dev/ttyUSB0 --upload Sensor.ino
import serial
with serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=3) as s:
    while 1: print(s.readline())
*/ 
#include <Wire.h> // I2C comm
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>    
Adafruit_BNO055 compass_i2c = Adafruit_BNO055(55, 0x29); // wire A4/A5 to SDA/SCL.
void setup()
{
  compass_i2c.begin();       // Compass
  delay(1000);               // Delay for compass readiness
  Serial.begin(9600); 
}
void loop()
{ 
    sensors_event_t bno;
    compass_i2c.getEvent(&bno, Adafruit_BNO055::VECTOR_EULER);
    Serial.print(" x|") ; Serial.print(bno.orientation.x);
    Serial.print(" y|") ; Serial.print(bno.orientation.y);
    Serial.print(" z|") ; Serial.print(bno.orientation.z);
    Serial.print(" T|") ; Serial.println(compass_i2c.getTemp()); 
}
