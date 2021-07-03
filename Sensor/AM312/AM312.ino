const int interruptPin = D7; 
volatile bool flag = LOW;
void setup() {  
  flag = false;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptHandler, RISING);   
  Serial.begin(115200);
} 

void loop() {
  if (flag) {
    Serial.println("motion detected");
    flag = false;
  }   
}

ICACHE_RAM_ATTR void interruptHandler() {
  flag = true;
}
