#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 
#include "/etc/wifi_secret.h" /* 
cat << EOF > /etc/wifi_secret.h
#define STASSID "widi_ssid"
#define STAPSK  "wifi_passwd"
EOF
*/ 

const char *ssid = STASSID;
const char *password = STAPSK;
const int  switch_pin = 0;
int switch_flag = 0;

ESP8266WebServer server(80);
    
void _switch() {  
  String s = "<!DOCTYPE html><html><head><title>Light Switch</title></head><body>This switch is ";
  if (switch_flag) {
    switch_flag = 0;
    s += "OFF, click <a href=\"switch\">here</a> to turn it ON";
  } else {
    switch_flag = 1;
    s += "ON, click <a href=\"switch\">here</a> to turn it OFF";
  } 
  s += "</body></html>";
  server.send(200, "text/html", s);
  
  digitalWrite(switch_pin, switch_flag);
  digitalWrite(LED_BUILTIN, 0);
  delay(500);
  digitalWrite(LED_BUILTIN, 1);
} 

void handleNotFound() {  
  delay(500);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, 0);
  delay(500);
  digitalWrite(LED_BUILTIN, 1);
} 

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(switch_pin, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  digitalWrite(switch_pin, 0);
  Serial.begin(115200);
  Serial.println("STASSID");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.on("/switch", _switch); 
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient(); 
}
