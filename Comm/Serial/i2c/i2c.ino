#include <Wire.h>  

String WiFi_Credentials = "myCred"; 

char reqType = NULL; // string or its length
void receiveEvent(int howMany)
{
  Serial.print("[Recv]: ");      
  Serial.println(reqType);  
  while(Wire.available()) // loop through all but the last
  {
    reqType = Wire.read(); 
  } 
  Serial.println(reqType);         // print the integer
} 
 
void requestEvent() {
  Serial.print("[Send]: ");        
  Serial.println(reqType);         
  switch (reqType) {
    case 's': 
      for (int i = 0; i < WiFi_Credentials.length(); i++) 
        Wire.write(WiFi_Credentials[i]);  
      break;
    case 'l':
      Wire.write(WiFi_Credentials.length());
      break;
    default:
      Wire.write("NA");
      break;
  } 
}

void setup()
{
  delay(3000);
  Serial.begin(115200);  
  Serial.println(WiFi_Credentials);
  Serial.println(WiFi_Credentials.length());
  
  Wire.begin(0x34);             // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}

void loop()
{ 
}
 
