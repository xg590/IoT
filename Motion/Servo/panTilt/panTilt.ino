#include <Servo.h> 
#include <stdio.h>
#include <string.h>

Servo servo_yaw;   
Servo servo_pitch;   
int pin_yaw   = A0;
int pin_pitch = A2;  
char s[10]    = ""; 

void setup() {
  servo_yaw.attach(pin_yaw);  
  servo_pitch.attach(pin_pitch); 
  Serial.begin(9600);
  while (!Serial) { ; } 
} 

void append(char* s, int i) {
  int len = strlen(s);
  s[len] = (char)i;
  s[len+1] = '\0';
}

void loop() { 
  while (Serial.available() > 0) {
    int i = Serial.read();
    append(s, i) ;  
    if (i == 10) {   
        char * pch; 
        pch = strtok (s,","); 
        int pos_yaw = String(pch).toInt(); Serial.print(pos_yaw);
        pch = strtok (NULL, ",");
        int pos_pitch = String(pch).toInt();
        Serial.print(" "); Serial.println(pos_pitch); 
        servo_yaw.write(pos_yaw);  
        servo_pitch.write(pos_pitch); 
        s[0] = '\0';  
    } 
  }
}
