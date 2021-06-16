
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremote.h>

#define STASSID "my_wifi_ssid"
#define STAPSK  "my_wifi_passwd"
#define IR_SEND_PIN 15 // Pin number is GPIO number not what printed on the board.

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/plain", "hello from esp8266!");
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}

void handleIRLED() { 
  float dly = .0;
  uint8_t sCommand, sRepeats = 0;
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i)=="cmd") {
      sCommand = atoi(server.arg(i).c_str());
    } else if (server.argName(i)=="delay") {
      dly = atof(server.arg(i).c_str());
      dly *= 1000;
    } else {
      server.send(200, "text/plain", "Error in arguments");
      digitalWrite(LED_BUILTIN, HIGH);
      return;
    }
  }
  IrSender.sendNEC(0xF483, sCommand, sRepeats);
  server.send(200, "text/plain", "Infred signal sent");
  digitalWrite(LED_BUILTIN, LOW);
  delay(dly);
  digitalWrite(LED_BUILTIN, HIGH);
}

void handleNotFound() {
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
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);
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

  server.on("/", handleRoot);
  server.on("/irled", handleIRLED); // /irled?cmd=13&delay=1
  server.on("/gotohdmi", []() { 
    uint8_t sRepeats = 0;
    digitalWrite(LED_BUILTIN, LOW); 
    IrSender.sendNEC(0xF483, 0x16, sRepeats);//Home
    delay(5000);
    IrSender.sendNEC(0xF483, 0xf, sRepeats);//Right
    delay(1000);
    IrSender.sendNEC(0xF483, 0xf, sRepeats);//Right
    delay(1000);
    IrSender.sendNEC(0xF483, 0xf, sRepeats);//Right
    delay(1000);
    IrSender.sendNEC(0xF483, 0x15, sRepeats);//OK 
    server.send(200, "text/plain", "Infred signal sent");  
    digitalWrite(LED_BUILTIN, HIGH);
  });
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
