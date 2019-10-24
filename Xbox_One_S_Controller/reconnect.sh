#!/bin/bash
sudo bash -c "echo 1 > /sys/module/bluetooth/parameters/disable_ertm"
sudo bash -c "echo -e 'connect XX:XX:XX:XX:XX:XX\nexit' | bluetoothctl"
