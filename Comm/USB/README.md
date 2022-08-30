### USB Protocol Stack
* Some board has USB protocol stack. This feature means that the USB function can be changed by the code.
* SAMD21 (Seeed Xiao), ATmega32u4 (Arduino Leonardo/Pro Micro)
```
#include <Keyboard.h> 
void setup() { delay(1000); Keyboard.println("Hello world!") ; } 
void loop() {}
```
