### Linux(Ubuntu 18.04.02) Communicates with Micro:bit  
Follow this [link](https://ukbaz.github.io/howto/ubit_workshop.html) <br>
Here is the brief summary:
1. Use [Makecode](https://makecode.microbit.org/#editor) to flash the Micro:bit
2. Put Micro:bit into pairing mode: Buttons A&B were held, reset button pressed once, LED array filled, bluetooth icon appears and useless passcode pattern presented (that pattern is for mobile phone app) 
3. Establish the Connection
````
$ bluetoothctl
[NEW] Controller 6D:01:E9:70:C4:DE a [default]
[NEW] Device 46:EC:67:6E:3E:27 BBC micro:bit [pegiv]
[NEW] Device 61:27:68:D4:2F:49 Redmi
[NEW] Device 61:12:E0:BE:D3:19 61:12:E0:BE:D3:19
....
````
The above info is prompted automatically, here we need to record the bluetooth address of Controller (a iMac) and Micro:bit, which are 6D:01:E9:70:C4:DE and 46:EC:67:6E:3E:27
````
pair 46:EC:67:6E:3E:27
connect 46:EC:67:6E:3E:27
````
Then we can program and play with Micro:bit wirelessly in Python.
Please refer to the microbit.ipynb 
