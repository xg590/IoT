#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  
#include "Adafruit_SHT4x.h"
#include "env.h" 
/* 
cat << EOF > env.h
#define STASSID "wifi_ssid"
#define STAPSK  "wifi_passwd"
#define LOG_URL "http://192.168.x.x:x/log" 
EOF
*/
const int sensorPin = A0, OLED_SDA = D2, OLED_SCL = D1; 

WiFiClient client;
HTTPClient http; 
Adafruit_SHT4x sht4 = Adafruit_SHT4x(); 

void initWIFI() { 
  WiFi.begin(STASSID, STAPSK); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  Serial.print("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());  
  delay(3000); 
  http.begin(client, LOG_URL); //HTTP
}

void initSHT4x() {  
  Serial.println("Adafruit SHT4x test");
  if (! sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    while (1) delay(1);
  }
  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);

  // You can have 3 different precisions, higher precision takes longer
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  switch (sht4.getPrecision()) {
     case SHT4X_HIGH_PRECISION: 
       Serial.println("High precision");
       break;
     case SHT4X_MED_PRECISION: 
       Serial.println("Med precision");
       break;
     case SHT4X_LOW_PRECISION: 
       Serial.println("Low precision");
       break;
  }

  // You can have 6 different heater settings
  // higher heat and longer times uses more power
  // and reads will take longer too!
  sht4.setHeater(SHT4X_NO_HEATER);
  switch (sht4.getHeater()) {
     case SHT4X_NO_HEATER: 
       Serial.println("No heater");
       break;
     case SHT4X_HIGH_HEATER_1S: 
       Serial.println("High heat for 1 second");
       break;
     case SHT4X_HIGH_HEATER_100MS: 
       Serial.println("High heat for 0.1 second");
       break;
     case SHT4X_MED_HEATER_1S: 
       Serial.println("Medium heat for 1 second");
       break;
     case SHT4X_MED_HEATER_100MS: 
       Serial.println("Medium heat for 0.1 second");
       break;
     case SHT4X_LOW_HEATER_1S: 
       Serial.println("Low heat for 1 second");
       break;
     case SHT4X_LOW_HEATER_100MS: 
       Serial.println("Low heat for 0.1 second");
       break;
  }
} 

void setup() {  
  Serial.begin(115200); 
  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens 
  Serial.print("\n\n\n");
  
  pinMode(sensorPin, INPUT);

  initWIFI();
  initSHT4x(); 
} 

float T, H; int P; 
void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    sensors_event_t humidity, temp; 
    sht4.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data   
    T = temp.temperature; 
    H = humidity.relative_humidity; 
    P = analogRead(sensorPin);  
    char json[96];  
    sprintf(json,"{\"Temperature (C)\":%f,\"Humidity (%% rH)\":%f,\"Photoresistor\":%d}", T, H, P);  
    Serial.println("[HTTP] POSTing "+String(json)); 
    http.addHeader("Content-Type", "application/json"); 
    int httpCode = http.POST(json); 
    if (httpCode == HTTP_CODE_OK) { 
        // const String& payload = http.getString();
        Serial.print("[HTTP] Payload received~\n\n");   
    } else {
        Serial.printf("[HTTP] Problematic returncode: %s\n\n", http.errorToString(httpCode).c_str());
    }  
  } 
  delay(3000);
}

// http.end();
