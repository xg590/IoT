### Add MicroPython ESP32
* ROM: Read-only memory. Everything that would not lost after power off stays here.
* Firmware: Codes in the rom.
* Bootloader: First part of firmware. Only used in one step of power-up sequence, dormant thereafter.
* esptool: Tool that talks to bootloader. 
  * By talking to bootloader, we can add or remove more codes in the rom. For example, operating system is "more codes"
  * Let's remove "more codes"
  ```
  pip install esptool
  sudo usermod -aG dialout $USER
  newgrp dialout
  .local/bin/esptool.py --port /dev/ttyUSB0              erase_flash # Erase flash. Only bootload left in ROM
  ```
  * Let's add "more codes" which is MicroPython (Adding more codes is called flashing because we are storing codes in flash memory.)
  ```
  wget https://micropython.org/resources/firmware/esp32-20210623-v1.16.bin
  .local/bin/esptool.py --port /dev/ttyUSB0 --chip esp32 write_flash -z 0x1000 esp32-20210623-v1.16.bin
  ```
