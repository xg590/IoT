[GY-BNO055](https://www.ebay.com/itm/172970055900) is available on Ebay for 10 bucks.
1. Wiring:
```
   RPi      GY-BNO055
   5V  <--> VIN
   GND <--> GND
   SDA <--> SDA
   SCL <--> SCL
```
2. Test Wiring
```shell
$ sudo su
# apt-get install i2c-tools
# i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- 29 -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
```
3. Test Sensor
```shell
$ pip3 install adafruit-circuitpython-bno055
```
```python
import adafruit_bno055
from busio import I2C
from board import SDA, SCL
i2c = I2C(SCL, SDA)
sensor = adafruit_bno055.BNO055(i2c, address=0x29)
while True: 
    print('Magnetometer (microteslas): {}'.format(sensor.magnetic))  
    time.sleep(1)
```
https://github.com/adafruit/Adafruit_CircuitPython_BNO055
https://forums.adafruit.com/viewtopic.php?f=19&t=75497

