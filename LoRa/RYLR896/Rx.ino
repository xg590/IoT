#include <SoftwareSerial.h>
SoftwareSerial lora(4,5);
 
void setup()
{ 
  Serial.begin(115200);
  lora.begin(115200); 
}
 
void loop()
{
  String inString;
  while (lora.available())
  {
    if(lora.available()){
      inString += String(char(lora.read()));
    }
  }
  if(inString.length()>0)
  {
      Serial.println(inString);
      inString.remove(0);
  } 
}
