### Use Xbox One S Wireless Controller as Input Device
#### Preparation
1) Disable ERTM (Enhanced Re-Transmission Mode)
```
$ sudo su
# echo 1 > /sys/module/bluetooth/parameters/disable_ertm
```
2) Put controller into Discovery Mode <br>
Press <b>Xbox button</b> and it flashs. Then Press <b>Wireless enrollment button</b> and <b>Xbox button</b> begins to flash quicker. (Please refer to https://support.xbox.com/en-US/xbox-one/accessories/xbox-one-wireless-controller )
#### GUI / iMac 2017 / Ubuntu 18.04.02
Pair controller with iMac via graphical bluetooth utility and then use <b>Jstest-gtk</b> to test the controller 
```
$ sudo apt install jstest-gtk 
```
#### CLI / Raspberry Pi Zero W / Raspbian Buster with desktop July 2019
Pair Controller with RPi Zero W via terminal bluetooth utility [1]
```
$ sudo su
# bluetoothctl
[bluetooth]# agent on
[bluetooth]# default-agent
[bluetooth]# scan on
```
Controller is supposed to be listed like:
```
[CHG] Device 00:9E:C8:63:EA:71 Name: Xbox Wireless Controller
[CHG] Device 00:9E:C8:63:EA:71 Alias: Xbox Wireless Controller
[CHG] Device 00:9E:C8:63:EA:71 UUIDs: 00000000-0000-0000-0000-000000000000
```
Pair and connect RPi Zero W with controller
```
[bluetooth]# pair 00:9E:C8:63:EA:71
[bluetooth]# connect 00:9E:C8:63:EA:71
```
use <b>Jstest</b> to test the controller 
```
$ sudo apt-get install joystick
$ jstest --normal /dev/input/js0
```
##### Reconnect RPi Zero W with Controller (Put the controller in discovery mode and disable ERTM first) [2]
```
# echo 1 > /sys/module/bluetooth/parameters/disable_ertm; coproc bluetoothctl; echo -e 'connect 00:9E:C8:63:EA:71\nexit' >&${COPROC[1]}
```

### Use Xbox One S Wireless Controller in Python
I wrote two jupyter notebooks which demonstrate how to read controller event in python. Actually, the two notebooks run in different RPi Zero W. One RPi Zero W pairs with Xbox One S controller via bluetooth and reports every movement on controller to another RPi Zero. <br>
##### Xbox_One_S_Controller_As_Input.ipynb reads movement from controller and reports to the a web server.
##### Receiver_for_Xbox_One_S_Controller.ipynb setups a web server and receives the movement.
##### Sometime the key/axis binding messes up, and the re-mapping python script is under development.

#### Reference: <br>
[1] https://core-electronics.com.au/tutorials/using-usb-and-bluetooth-controllers-with-python.html <br>
[2] https://www.linuxquestions.org/questions/programming-9/control-bluetoothctl-with-scripting-4175615328/
