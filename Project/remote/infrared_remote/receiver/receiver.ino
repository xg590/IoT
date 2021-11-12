/*
cat << EOF > /etc/wifi_secret.h
#define STASSID "wifi_ssid"
#define STAPSK  "wifi_passwd"
#define URL "http://192.168.10.10:13000/ir"
EOF
*/  
#include "/etc/wifi_secret.h" 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  
#include <IRremote.h>
WiFiClient client;
HTTPClient http; 

const int IR_RECEIVE_PIN = D4; 

void setup() {
  Serial.begin(9600);
  Serial.print("[WiFi] Connecting."); 
  WiFi.begin(STASSID, STAPSK); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("[WiFi] Connected! IP address: ");
  Serial.println(WiFi.localIP()); 
    
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK); //ENABLE_LED_FEEDBACK : Blink onboard led when receive data
  Serial.println("[IR] Receiver Ready");
}

void send_over_http(char *json_str) {    
  if (WiFi.status() == WL_CONNECTED) { 
    Serial.println("[WiFi] Preparing HTTP Request"); 
  
    if (http.begin(client, URL)) { 
      http.addHeader("Content-Type", "application/json"); 
      int httpCode = http.POST(json_str);  
      if (httpCode == HTTP_CODE_OK) { 
        // const String& payload = http.getString();
        Serial.println("[HTTP] Request Succeed");   
      } else {
        Serial.printf("[HTTP] Request Error: [%d] %s\n\n", httpCode, http.errorToString(httpCode).c_str()); 
      }
    } 
    http.end(); 
  }        
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("[IR] ");   
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println("{\"err\":1}");
    } else {       
      char json[32];
      sprintf(json, "{\"err\":0,\"cmd\":%d}", IrReceiver.decodedIRData.command);   
      Serial.println(json); 
      send_over_http(json);
    } 
    IrReceiver.resume(); // Enable receiving of the next value
  }
}
