#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 

#include "/etc/wifi_secret.h" 
#include <Servo.h>

const int servo_pin = 2; 
int pos = 0;       // variable to store the servo position
bool hook = false; // key is on/off hook 

ESP8266WebServer server(80);
Servo myHook;  // create servo object to control a servo
const char *ssid = STASSID;
const char *password = STAPSK;
void moveToAngle(int angle, int pace) {
  if (angle > pos) {
    for (pos = 0; pos <= angle; pos += pace) myHook.write(pos);
  } else {
    for (pos = 180; pos >= angle; pos -= pace) myHook.write(pos);
  }
}

void moveHook() { 
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i)=="hook") {
      if (server.arg(i)=="off") { 
	    moveToAngle(100, 1);
	    moveToAngle(140, 10);
	    moveToAngle(180, 10);
	    moveToAngle(140, 10);
	    moveToAngle(180, 10);
	    moveToAngle(140, 10);
	    moveToAngle(180, 10); 
        hook = false;
      } else {
        moveToAngle(0, 1);
        hook = true;     
      } 
      server.send(200, "text/plain", hook ? "key is on hook" : "key is dropping");
    } else if (server.argName(i)=="angle") {
      int angle = atoi(server.arg(i).c_str()); 
      moveToAngle(angle, 1); 
      server.send(200, "text/plain", "Hook is now on " + server.arg(i) + " degree");
    }
  }
   
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
  myHook.attach(servo_pin);  // attaches the servo on pin 9 to the servo object 
  digitalWrite(LED_BUILTIN, 1); 
  Serial.begin(115200);
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
  server.on("/mvhk", moveHook);  
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient(); 
} 
