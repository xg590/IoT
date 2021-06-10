#include <SoftwareSerial.h>
SoftwareSerial lora(4,5);
  
void setup()
{ 
  Serial.begin(115200);
  lora.begin(115200); 
}
 
void loop()
{ 
  String str = "Hello World!";
  String cmd = "AT+SEND=0,"+String(str.length()) +","+ str +"\r"; 
  lora.println(cmd);
  while(lora.available()){
    Serial.write(lora.read());
  } 
  Serial.println(cmd);
  delay(1000);
}
