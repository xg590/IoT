### Feature
* ATMega32U4 belongs to AVR family and has 32K of flash memory. 
* ATMega32U4 has a USB 2.0 Full-speed/Low Speed Device Module 
### USB-related Pins
* V<sub>BUS</sub>: Use external supply 
* D<sub>+</sub> 
* D<sub>-</sub> 
* U<sub>GND</sub> 
* U<sub>VCC</sub>: Input pin of internal regulator of ATMega32U4 if 32U4 is powered by external 3.4~5.5V supply
### HID Emulation 
* Hello World
* Key_map @ Arduino\libraries\Keyboard\src\Keyboard.h
```C
#include <Keyboard.h>
#include <Mouse.h>
void setup() {                        delay(300); 
  Keyboard.print("Hello ")           ;delay(300);  
  Keyboard.write(KEY_BACKSPACE)      ;delay(300);  
  Keyboard.write('\n')               ;delay(300); 
  Keyboard.press(KEY_BACKSPACE)      ; 
  Keyboard.release(KEY_BACKSPACE)    ;delay(300); 
  Keyboard.println(" world!")        ;delay(300); 
  Mouse.press(MOUSE_RIGHT)           ; 
  Mouse.release(MOUSE_RIGHT)         ;delay(300); 
  Mouse.move(-12, -12, 0)            ;delay(300);     // -128 < x, y and/or wheel < +127 
  Mouse.click(MOUSE_LEFT)            ;delay(300); 
  Keyboard.press(  KEY_LEFT_ALT) ; Keyboard.press(  KEY_TAB) ; delay(100); Keyboard.releaseAll();  
} 
void loop() {}
```
```
#include<Keyboard.h>
#include<Mouse.h>

void setup() {
    delay(3000);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(300);
    Keyboard.print("cmd");
    delay(300);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.releaseAll();
    delay(300);
    Keyboard.write(KEY_LEFT_ARROW);
    Keyboard.write(KEY_RETURN);
    delay(300);
    Keyboard.println("netstat -a -n -p tcp -q | find \"LISTENING\"");
    delay(9000);
    Keyboard.println("exit");
}

void loop() {}
```
### Adafruit Feather 32u4 RFM69HCW Packet Radio
```
#include <Keyboard.h> 
void setup() { delay(1000); Keyboard.println("Hello world!") ; } 
void loop() {}
```
* Install new boards. [url](https://adafruit.github.io/arduino-board-index/package_adafruit_index.json)
* Choose Tools -> Boards -> Adafruit Feather 32u4
* If you ever get in a 'weird' spot with the bootloader, or you have uploaded code that crashes and doesn't auto-reboot into the bootloader, double-click the RST button to get back into the bootloader. The red LED will pulse, so you know that its in bootloader mode. Do the reset button double-press right as the Arduino IDE says its attempting to upload the sketch, when you see the Yellow Arrow lit and the Uploading... text in the status bar.</br>
<img src="https://cdn-learn.adafruit.com/assets/assets/000/028/444/large1024/microcomputers_adafruit_products_uploading.gif"></img>
