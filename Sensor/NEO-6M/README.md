### Pins
VCC: 3.3V , consume 45mA 
RX, Tx: 3.3V
### X86 / ARM 
* Connect GPS breakout to Raspberry Pi
* Use Python packages to read and process data 
  * <i>pyserial</i>: read GPS 
  * <i>pynmea2</i>: process the [NMEA](http://aprs.gids.nl/nmea/#rmc) data  

### Arduino
* Connect GPS breakout to Arduino
* Programming the arduino for reading the NMEA data and processing it.
  * Disconnect the VCC pin of GPS breakout before programming 
