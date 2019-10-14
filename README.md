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
How to setup Raspberry Pi 
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

4. Dealing with eduroam. <br>
I haven't find the right configuration to connect nyu wireless service with the default network manager came with raspbian. I have to switch back to Network-Manager. Here is a tutorial for that. https://davidxie.net/install-network-manager-on-raspbian
