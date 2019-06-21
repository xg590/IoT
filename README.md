# IoT
Raspberry &amp; Arduino<br>
My Inventory:  <pre>
    Raspberry Pi 3B / Zero_W
    Arduino Uno_Rev3 / Pro mini / Nano
    GPS Module: GY-NEO-6MV2
    3 Axis 6DOF Gyro Accelerometer: GY-521 MPU-6050
    Distance Sensor: HC-SR04
    Motor Driver: DRV8833 DC/Stepper Breakout Board
</pre>
How to setup Raspberry Pi
1. Download the Operating System "Raspbian" (I prefer the Raspbian Stretch with desktop)
https://downloads.raspberrypi.org/raspbian_latest
2. Write the img or iso of Raspbian to an empty 8GB+ Micro SD card.
https://www.raspberrypi.org/documentation/installation/installing-images/
Using rufus in Windows: https://rufus.ie/
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
