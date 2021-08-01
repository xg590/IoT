#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 
#include "/etc/wifi_secret.h" /* 
cat << EOF > /etc/wifi_secret.h
#define HUB_STASSID "wifi_ssid"
#define HUB_STAPSK  "wifi_passwd"
EOF
*/ 
  
const char *ssid = HUB_STASSID;
const char *password = HUB_STAPSK;
int mswda_flag = 0; // microsoft_wireless_display_adapter
const int  relay_pin = D8; // relay that control power of display adapter
const int  kvm_switch_pin = D5;

ESP8266WebServer server(80);
    
void _mswda() {  // microsoft_wireless_display_adapter
  String s = "<!DOCTYPE html><html><head><title>HDMI Relay</title></head><body>";
  if (mswda_flag) {
    mswda_flag = 0; s += "Turn Microsoft Wireless Display Adapter <a href=\"mswda\"><b style=\"font-size:2em\">ON </b></a>";
  } else { 
    mswda_flag = 1; s += "Turn Microsoft Wireless Display Adapter <a href=\"mswda\"><b style=\"font-size:2em\">OFF</b></a>";
  } 
  s += "</body></html>";
  server.send(200, "text/html", s); 
  
  digitalWrite(relay_pin, mswda_flag);
  digitalWrite(LED_BUILTIN, 0); 
  delay(200); 
  digitalWrite(LED_BUILTIN, 1);
} 

void _kvm() {  
  String s = "<!DOCTYPE html><html><head><title>KVM</title></head><body>Swtich KVM in 5 seconds</body></html>";
  server.send(200, "text/html", s);
  
  delay(5000); 
  digitalWrite(LED_BUILTIN, 0);
  digitalWrite(kvm_switch_pin, 0);
  delay(200);
  digitalWrite(kvm_switch_pin, 1); 
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
  pinMode(     LED_BUILTIN   , OUTPUT);
  digitalWrite(LED_BUILTIN   ,      1);
  pinMode(     relay_pin     , OUTPUT);
  digitalWrite(relay_pin     ,      0);
  pinMode(     kvm_switch_pin, OUTPUT); 
  digitalWrite(kvm_switch_pin,      1); 
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
  server.on("/mswda", _mswda); 
  server.on("/kvm", _kvm); 
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient(); 
}
