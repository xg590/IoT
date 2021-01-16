## Use Xbox One S Wireless Controller as Input Device on Linux
### Preparation
1) Disable ERTM (Enhanced Re-Transmission Mode)
```
sudo bash -c "echo 1 > /sys/module/bluetooth/parameters/disable_ertm"
```
2) Put controller into Discovery Mode <br>
Press <b>Xbox button</b> and it flashs. Then Press <b>Wireless enrollment button</b> and <b>Xbox button</b> begins to flash quicker. (Please refer to https://support.xbox.com/en-US/xbox-one/accessories/xbox-one-wireless-controller ) 
### GUI / iMac 2017 / Ubuntu 18.04.02
Pair controller with iMac via graphical bluetooth utility and then use <b>Jstest-gtk</b> to test the controller 
```
$ sudo apt install -y jstest-gtk 
```
### Pair Controller with Raspberry Pi via terminal bluetooth utility [1]
```
$ sudo su
# bluetoothctl 
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
[bluetooth]# exit 
```
use <b>Jstest</b> to test the controller 
```
$ sudo apt-get install -y joystick
$ jstest --normal /dev/input/js0
```
#### Test if bluetooth service is running. It is running automaticllay on my RPi
````
$ systemctl is-active bluetooth # test 
# systemctl start bluetooth     # start
````
### Use Xbox One S Wireless Controller in Python
* Install library
```shell
pip3 install evdev
```
* Python3
```python
from evdev import InputDevice, ecodes
device = InputDevice('/dev/input/event0')

code2name = {}
for type_, code_ in device.capabilities(verbose=True, absinfo=False).items():
    if type_[0] in ['EV_KEY', 'EV_ABS']:
        for name, code in code_:
            if isinstance(name,list):
                if   'BTN_A' in name: code2name[code] = 'BTN_A'
                elif 'BTN_B' in name: code2name[code] = 'BTN_B'
                elif 'BTN_X' in name: code2name[code] = 'BTN_X'
                elif 'BTN_Y' in name: code2name[code] = 'BTN_Y'
                continue
            code2name[code] = name

#     'ABS_X', # default value for left  stick X
#     'ABS_Y', # default value for left  stick Y
#     'ABS_Z', # default value for right stick X
#    'ABS_RZ', # default value for right stick Y
#   'ABS_GAS', # default value for right trigger
# 'ABS_BRAKE', # default value for left  trigger

for event in device.read_loop():
    if event.type in [ecodes.EV_ABS, ecodes.EV_KEY]:
        print(code2name[event.code], '\t', event.value)
```
#### Reference: <br>
[1] https://core-electronics.com.au/tutorials/using-usb-and-bluetooth-controllers-with-python.html <br> 
## Use Xbox One S Wireless Controller as Input Device on Windows 10
1) Install [Python](https://www.python.org/) 3.9.1
2) Download [get-pip.py](https://bootstrap.pypa.io/get-pip.py) and install it with cmd.
```cmd
py get-pip.py
```
3) Install pyglet
```cmd
pip install pygame 
```
4) Run this [script](https://raw.githubusercontent.com/xg590/IoT/master/Xbox_One_S_Controller/win.py) in cmd
```
py win.py
```
