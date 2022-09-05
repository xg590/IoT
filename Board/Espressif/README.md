### USB-to-UART Bridge Chip
* It seems like both ESP8266-based and ESP32-based board have CP2102 usb-to-uart bridge chip.
* Remove brltty because it conflicts
* Get the virtual COM port (VCP) drive from [Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) or [here](CP210x_Universal_Windows_Driver.zip)
