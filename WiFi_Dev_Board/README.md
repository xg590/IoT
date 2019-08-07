### WiFi Internet Development Board
    * Brand: KeeYees
    * Available on Amazon: https://www.amazon.com/gp/product/B07S5Z3VYZ
    * WiFi Module: ESP-12E
    * WiFi Microchip: ESP8266
    * USB Interface: CP2102
    * Firmware: NodeMCU (written in C and programmable with Lua)


### Get feet wet
1. Build firmware through 'Cloud Builder' provided by NodeMCU: https://nodemcu-build.com/
2. The link of built firmware 'nodemcu-master-9-modules-2019-08-07-19-35-21-float.bin' will be received via E-mail 
4. Flash firmware (.bin file) to Dev Board via USB (baud rate 921600) by using NodeMCU-PyFlasher () 

Tips for flash mode: The KeeYees Dev Board bought from Amazon is a NodeMCU dev kit, and the USB connection can pull GPIO0 low so we do nothing with pins.
Tips for flash address: If you build your firmware with the cloud builder or the Docker image, or any other method that produces a combined binary, then you can flash that file directly to address 0x00000.

