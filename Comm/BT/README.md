* In Linux, the canonical implementation of the Bluetooth protocol stack is <b>BlueZ</b>
[WiKi](https://wiki.archlinux.org/title/bluetooth)
* Check Bluetooth driver and package
```
$ lsmod |grep btusb
btusb                  69632  0
$ apt list --installed | grep bluez 
bluez/jammy,now 5.64-0ubuntu1 amd64 [installed,automatic] 
```
* Bluetooth adapter
```
$ bluetoothctl list
Controller 11:AA:BB:33:55:99 name [default]
``` 