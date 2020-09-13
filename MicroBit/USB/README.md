### Linux (Ubuntu 18.04.02 / Raspbian Buster) Communicates with Micro:bit via USB
Brief Summary of Usage:
1. Put bitio.hex (modified for Micro:Bit v1.5) to MICROBIT drive
2. Change the permission of reading serial port of Micro:Bit ()
```
# usermod -aG dialout your_username
```
3. Install PySerial
4. Run the USB_as_Interface.ipynb

<br> API Reference: https://github.com/whaleygeek/bitio <br>
This is merely a <b>fork</b> and <b>modification</b> of https://github.com/whaleygeek/bitio for code simplicity.<br>
If you are interested in compass data, use [IoT/Micro:Bit/USB_Lite](https://github.com/xg590/IoT/blob/master/Micro:Bit/USB_Lite/USB_as_Interface_Lite.ipynb).
