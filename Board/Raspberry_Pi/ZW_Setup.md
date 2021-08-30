### Setup Raspberry Pi ZW/3A/3B/4
1) Download the Operating System "Raspbian" (I prefer the Raspbian Stretch with desktop)<br>
https://downloads.raspberrypi.org/raspbian_latest
2) Write the img or iso of Raspbian to an empty 8GB+ Micro SD card. <br> 
* On Windows: https://rufus.ie/<br>
* Using dd in Linux: 
```
  umount /dev/sda1 # umount TF card
  dd bs=4M if=2018-11-13-raspbian-stretch.img of=/dev/sdX conv=fsync
```
3) Configure SSH and WIFI so the SBC (single-board computer) could be accessed remotely few minites after booting up.
* A new partition named "Boot" appeared after the Raspbian was written to the Micro SD card. Two files should be created in that partition.
  * 3.1 Create an empty file named "ssh"
  * 3.2 Create a file named "wpa_supplicant.conf" and the content should be like
```shell
  ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
  network={
      ssid="YOUR_SSID"
      psk="YOUR_WIFI_PASSWORD"
      key_mgmt=WPA-PSK
  }
```
  * Edit /etc/dhcpcd.conf if a static ip is wanted
* Caution: The 'NewLine Character' in wpa_supplicant.conf should follow Unix convention.

4) Dealing with NYU WiFi. Thanks to [Baris Unver](https://www.bunver.com/connecting-raspberry-pi-to-wpa2-enterprise-wireless-network/)<br>
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
