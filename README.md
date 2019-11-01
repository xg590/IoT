# IoT
Raspberry &amp; Arduino<br>
My Inventory:  <pre>
    Raspberry Pi 3B / Zero_W
    Arduino Uno_Rev3 / Pro mini / Nano
    GPS Module: GY-NEO-6MV2
    3 Axis 6DOF Gyro Accelerometer: GY-521 MPU-6050
    Distance Sensor: HC-SR04
    Motor Driver: DRV8833 DC/Stepper Breakout Board
    LoRa: SX1278 433MHz 1W TTL LoRa Wireless Module
    Driver Board: PCA9685+TB6612 Stepper Motor Dual DC Motor Driver Controller Board for Arduino https://www.ebay.com/itm/311834775630
</pre>
### Setup Raspberry Pi 
1. Download the Operating System "Raspbian" (I prefer the Raspbian Stretch with desktop)<br>
https://downloads.raspberrypi.org/raspbian_latest 
2. Write the img or iso of Raspbian to an empty 8GB+ Micro SD card. <br>
https://www.raspberrypi.org/documentation/installation/installing-images/<br>
Using rufus in Windows: https://rufus.ie/<br>
Using dd in Linux: dd bs=4M if=2018-11-13-raspbian-stretch.img of=/dev/sdX conv=fsync
3. Configure SSH and WIFI so the SBC could be accessed remotely few minites after booting up.<br>
A new partition named "Boot" appeared after the Raspbian was written to the Micro SD card. Two files should be created in that partition. 
  - 3.1 Create an empty file named "ssh" 
  - 3.2 Create a file named "wpa_supplicant.conf" and the content should be like
```shell
  ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
  network={
      ssid="YOUR_SSID"
      psk="YOUR_WIFI_PASSWORD"
      key_mgmt=WPA-PSK
  }
```
Caution: The 'NewLine Character' in wpa_supplicant.conf should follow Unix convention.  

4. Dealing with eduroam. Thanks to [Baris Unver](https://www.bunver.com/connecting-raspberry-pi-to-wpa2-enterprise-wireless-network/)<br>
I have the access to NYU Wireless service, which is protected by the wpa-enterprise protocol. Here is how I configure my Raspberry Pi. <br>
Edit the /etc/wpa_supplicant/wpa_supplicant.conf and add a new network configuration <br>
```shell
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=US

network={
    ssid="nyu-legacy"
    scan_ssid=1
    key_mgmt=WPA-EAP
    group=CCMP TKIP
    eap=PEAP
    identity="NYUNetID"
    password="NetID_Password"
    phase1="peapver=0"
    phase2="MSCHAPV2"
}
```
Then create a new file as /etc/network/interfaces.d/nyu, whose content is:<br>
```shell
auto lo
iface lo inet loopback
iface eth0 inet manual

allow-hotplug wlan0
iface wlan0 inet manual
    pre-up wpa_supplicant -B -Dwext -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf
    post-down killall -q wpa_supplicant
```
### Program Arduino Nano on Raspberry Pi Zero W
1. Download  [ARDUINO 1.8.10 IDE / Linux ARM 32 bits](https://www.arduino.cc/en/Main/Software)
2. Decompress it<br>
$ tar Jxvf arduino-1.8.10-linuxarm.tar.xz 
3. In case of Permission denied of accessing /dev/ttyUSB0
```shell
$ sudo su
# usermod -aG dialout pi
# exit
$ newgrp dialout
```
4. Test blink 
```
$ ./arduino-1.8.10/arduino --board arduino:avr:nano:cpu=atmega328 --port /dev/ttyUSB0 --upload arduino-1.8.10/examples/01.Basics/Blink/Blink.ino 
```
