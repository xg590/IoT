### Keyboard and Mouse Simulation
* Remote control via the HID 
```
arduino-cli lib install Keyboard
arduino-cli lib install Mouse
```
USB Stack: Arduino or TinyUSB
```
-fqbn=Seeeduino:samd:seeed_XIAO_m0:usbstack=arduino,debug=off,sercom4=exclude  
-fqbn=Seeeduino:samd:seeed_XIAO_m0:usbstack=tinyusb,debug=off,sercom4=exclude
```
```
arduino-cli compile -b arduino:avr:uno --build-property build.extra_flags=-DPIN=2 --build-property "compiler.cpp.extra_flags=\"-DSSID=\"hello world\"\"" /home/user/Arduino/MySketch
                                                                                                                              "-DSSID= "hello world " "   
```
Key_map @ ~/Arduino/libraries/Keyboard/src/Keyboard.h
