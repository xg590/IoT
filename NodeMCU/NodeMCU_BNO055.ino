#include <ESP8266WiFi.h> 
#include <Wire.h> // I2C comm
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
Adafruit_BNO055 compass_i2c = Adafruit_BNO055(55, 0x29); // wire A4/A5 to SDA/SCL.
const char* ssid     = "???";
const char* password = "???";
const char* host     = "192.168.???.???";
const uint16_t port  = 12345;
void setup() {
  compass_i2c.begin();       // Compass
  delay(1000);               // Delay for compass readiness
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to "); Serial.println(ssid);
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() { 
  Serial.print("Connecting to "); Serial.print(host); Serial.print(':');  Serial.println(port);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("Connection failed after 5s waiting");
    delay(5000);
    return;
  }
  // This will send a string to the server
  Serial.println("Connection is established.");
  Serial.println("Sending data to server");
  sensors_event_t bno;
  double x = 0.0, y = 0.0, z = 0.0;
  int8_t T = 0;
  while (client.connected()) {
    compass_i2c.getEvent(&bno, Adafruit_BNO055::VECTOR_EULER); // It is fast. Refresh every 1/30s.
    x = bno.orientation.x;
    y = bno.orientation.y;
    z = bno.orientation.z;
    T = compass_i2c.getTemp();
    int len = snprintf(NULL, 0, "x|%.2f y|%.2f z|%.2f T|%d", x, y, z, T);
    char s[len];
    sprintf(s, "x|%.2f y|%.2f z|%.2f T|%d", x, y, z, T);
    Serial.println(s);
    client.println(s);
  }
  // Close the connection
  Serial.println("Connection has ended.");
  client.stop();
  Serial.println("Restart connection in 5s");
  delay(5000); 
}
