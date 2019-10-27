## Program Arduino Nano on Raspberry Pi Zero W
1. Download  [ARDUINO 1.8.10 IDE / Linux ARM 32 bits](https://www.arduino.cc/en/Main/Software)
2. Decompress it<br>
$ tar Jxvf arduino-1.8.10-linuxarm.tar.xz
3. Create a source file blink.ino on RPi ZW:
```
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
}
```
4. In case of Permission denied of accessing /dev/ttyUSB0
```shell
$ sudo su
# usermod -aG dialout pi
# exit
$ newgrp dialout
```
4. Upload it to Arduino Nano
$ ./arduino-1.8.10/arduino --board arduino:avr:nano:cpu=atmega328 --port /dev/ttyUSB0 --upload blink.ino
