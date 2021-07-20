### Pinout
<img src="Pico_Pinout.png"></img>
### Micropython Hello World
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
