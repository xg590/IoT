### Python
Use <i>pyserial</i> to read the [NMEA](https://en.wikipedia.org/wiki/NMEA_0183) data and <i>pynmea2</i> to process the data

### Arduino
Programming the arduino for reading the NMEA data and processing it
* The GPS breakout must be powered off before programming (Disconnect the VCC pin)
```
./arduino --board arduino:avr:uno --port /dev/ttyUSB0 --upload examples/01.Basics/Blink/Blink.ino
```
