### Micropython Hello world
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
