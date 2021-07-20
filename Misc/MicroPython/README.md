### Add MicroPython to Raspberry Pi Pico (Hello world)
1. Connect Pico to PC via USB cable.
2. A new removable media appears as RPI-RP2
3. There is a pre-compiled micropython fireware, a downloadable [UF2 file](https://www.raspberrypi.org/documentation/rp2040/getting-started/#getting-started-with-micropython).
4. Download the UF2 file into RPI-RP2.
5. Pico will restart automatically then boot into micropython.
6. A new serial port is now avaiable at /dev/ttyACM0
7. Use screen to play with micropython (ported Python3.4)
```
$ screen /dev/ttyACM0 115200
>>> import sys 
>>> print(sys.version)
3.4.0
```
### Use [rshell](https://github.com/dhylands/rshell) to add library to MicroPython
#### 1. Prepare a lib
```shell
cat << EOF > test.py
def hello_world():
  print("Hello World!")
EOF
```
#### 2. Copy lib to board
```shell
.local/bin/rshell
cp test.py /pyboard/
exit
```
#### 3. Import lib
```
import test
test.hello_world()
```
#### Boot into running a script
* Just name a script main.py instead of test.py and do the same copy
* When the pico reboot, the script will run. 
### Learning how to paste code into REPL is crucial
* [2.3.5. Paste mode](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html#paste-mode)
* [2.3.6. Other control commands](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html#other-control-commands)
### Add MicroPython to ESP32
* ROM: Read-only memory. Everything that would not lost after power off stays here.
* Firmware: Codes in the rom.
* Bootloader: First part of firmware. Only used in one step of power-up sequence, dormant thereafter.
* esptool: Tool that talks to bootloader. 
  * By talking to bootloader, we can add or remove more codes in the rom. For example, operating system is "more codes"
  * Let's remove "more codes"
  ```
  pip install esptool
  sudo usermod -aG dialout $USER
  newgrp dialout
  .local/bin/esptool.py --port /dev/ttyUSB0              erase_flash # Erase flash. Only bootload left in ROM
  ```
  * Let's add "more codes" which is MicroPython (Adding more codes is called flashing because we are storing codes in flash memory.)
  ```
  # https://micropython.org/download/esp32/
  wget https://micropython.org/resources/firmware/esp32-20210623-v1.16.bin 
  .local/bin/esptool.py --port /dev/ttyUSB0 --chip esp32 write_flash -z 0x1000 esp32-20210623-v1.16.bin
  ```
* Hello World
```
$ screen /dev/ttyUSB0 115200
>>> import sys 
>>> print(sys.version)
3.4.0
```
