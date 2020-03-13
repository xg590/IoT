[GY-BNO055](https://www.ebay.com/itm/172970055900) is available on Ebay for 10 bucks.<br>
### Some Soldering Work to enable I2C communication<br>  
An important quote from [VitallyRaccoon's post](https://forum.arduino.cc/index.php?topic=574580.0): "To configure the module for i2c communication both jumpers should be closed."<br>
![Soldering Problem](https://raw.githubusercontent.com/xg590/IoT/master/GY-BNO055/GY-BNO055_Soldering_Problem.jpg)
### Read Out GY-BNO055 from Raspberry Pi Directly
1. Wiring:
```
GY-BNO055      RPi      
   VIN   <-->  5V   
   GND   <-->  GND  
   SCL   <-->  SCL 
   SDA   <-->  SDA  
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
$ pip3 install adafruit-circuitpython-bno055 # https://github.com/adafruit/Adafruit_CircuitPython_BNO055
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
### Read Out GY-BNO055 From Raspberry Pi or PC Indirectly (GY-BNO055 <--> Arduino <--> PC / RPi)
0. Program Arduino<br>
Please refer to [this tutorial](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/arduino-code). Basically, we need to install two Libraries from Adafruit: 1. Adafruit Unified Sensor; 2. Adafruit BNO055. Then, see the newly added example. <br>
1. Wiring 
```
GY-BNO055      Nano      Win10
   VIN   <-->  5V   <-->  USB
   GND   <-->  GND  
   SCL   <-->  A5  
   SDA   <-->  A4            
```
2. Which Port to Read (Win10)<br>
![alt text](https://raw.githubusercontent.com/xg590/IoT/master/src/COM_6.png "COM6")<br>
Here we know which port to read out the result.<br>
3. Jupyter Notebook Running on PC
```python
import serial
with serial.Serial(port='COM6', baudrate=115200, timeout=3) as s:
    while 1:
        data = s.readline() # You can get GPS data if the on-board LED blinks.
        print(data)
```
