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
##### Reconnect RPi Zero W with Controller [2]
```
# coproc bluetoothctl
# echo -e 'connect 00:9E:C8:63:EA:71\nexit' >&${COPROC[1]}
```


#### Reference: <br>
[1] https://www.cnet.com/how-to/how-to-setup-bluetooth-on-a-raspberry-pi-3/ <br>
[2] https://www.linuxquestions.org/questions/programming-9/control-bluetoothctl-with-scripting-4175615328/
