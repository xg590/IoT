const int  switch_pin = 0;

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1); // OFF
  pinMode(switch_pin, OUTPUT);
  digitalWrite(switch_pin, 0); // OFF

}

void loop(void) {
  digitalWrite(LED_BUILTIN, 0); // ON
  digitalWrite(switch_pin,  1); // ON
  delay(3000);
  digitalWrite(switch_pin,  1);
  digitalWrite(LED_BUILTIN, 1);
