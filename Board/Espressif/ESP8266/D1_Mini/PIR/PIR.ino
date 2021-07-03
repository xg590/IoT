#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> 
#include "/etc/wifi_secret.h" /* 
cat << EOF > /etc/wifi_secret.h
#define STASSID "wifi_ssid"
#define STAPSK  "wifi_passwd"
#define LOG_URL "http://192.168.x.x:x/log" 
EOF
*/ 
 
const int interruptPin = D7; 
volatile bool flag = LOW;

void setup() {  
  flag = false;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptHandler, RISING);   
  Serial.begin(115200);


  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());    
} 

void loop() {
  if (flag) {
    Serial.println("motion detected");
    flag = false;

    if ((WiFi.status() == WL_CONNECTED)) { 
      Serial.println("[HTTP] Visiting Lightbulb~");   
      
      WiFiClient client;
      HTTPClient http; 
      if (http.begin(client, Kitchen_LB_URL)) { 
        int httpCode = http.GET(); 
        if (httpCode == HTTP_CODE_OK) { 
          // const String& payload = http.getString();
          Serial.print("[HTTP] Lightbulb visited~\n\n");   
        } else {
          Serial.printf("[HTTP] Problematic returncode: [%d] %s\n\n", httpCode, http.errorToString(httpCode).c_str());
        }
      }  
      http.end(); 
    }  
  }   
}

ICACHE_RAM_ATTR void interruptHandler() {
  flag = true;
}
