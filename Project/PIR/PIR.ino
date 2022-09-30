#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> 
#include "wifi_secret.h"
/*
cat << EOF > wifi_secret.h
#define STASSID "wifi_ssid"
#define STAPSK  "wifi_passwd"
#define URL "http://192.168.x.x:x/log" 
EOF
*/

WiFiClient client; 
HTTPClient http;
volatile bool interruptFlag = false;
const     int interruptPin  = D7; 
const     int analogPin     = A0;

void setup() {  
    interruptFlag = false;
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
    if ((WiFi.status() == WL_CONNECTED)) { 
        Serial.println("[HTTP] Connect"); 
        if (http.begin(client, URL)) { 
            http.addHeader("Content-Type", "application/json"); 
            char js[64]; 
            sprintf(js, "{\"A\":%d, \"B\":%d}", analogRead(analogPin), interruptFlag ? 1 : 0); 
            interruptFlag = false;
            int httpCode = http.POST(js);
            if (httpCode == HTTP_CODE_OK) {  
                Serial.print ("[HTTP] HTTP_CODE_OK\n\n");   
            } else {
                Serial.printf("[HTTP] Problematic returncode: [%d] %s\n\n", httpCode, http.errorToString(httpCode).c_str());
            }
        }  
        http.end(); 
    }
    delay(1000);
} 

ICACHE_RAM_ATTR void interruptHandler() {
  interruptFlag = true;
} 