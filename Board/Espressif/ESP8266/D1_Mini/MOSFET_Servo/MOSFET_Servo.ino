#include <Servo.h>   
Servo myServo;  // create servo object to control a servo

const int servo_pin = D2; 
const int mosfet_pin = D1; 
int pos = 0;       // variable to store the servo position 
void moveToAngle(int angle, int pace) {
  if (angle > pos) {
    for (pos = 0; pos <= angle; pos += pace) myServo.write(pos);
  } else {
    for (pos = 180; pos >= angle; pos -= pace) myServo.write(pos);
  }
}

void setup() { 
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, 1); 
  pinMode(mosfet_pin, OUTPUT); 
  digitalWrite(mosfet_pin, 1); 
  myServo.attach(servo_pin);   
}
 
void loop() {
  digitalWrite(LED_BUILTIN, 0); 
  moveToAngle(100, 1);
  moveToAngle(140, 10);
  moveToAngle(180, 10); 
  digitalWrite(LED_BUILTIN, 1); 
  delay(10000);                       // wait for a second 
} 
