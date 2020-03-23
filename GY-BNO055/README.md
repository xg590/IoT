[GY-BNO055](https://www.ebay.com/itm/172970055900) is available on Ebay for 10 bucks.<br>
### Some Soldering Work to enable I2C communication<br>  
An important quote from [VitallyRaccoon's post](https://forum.arduino.cc/index.php?topic=574580.0): "To configure the module for i2c communication both jumpers should be closed."<br>
![Soldering Problem](https://raw.githubusercontent.com/xg590/IoT/master/GY-BNO055/GY-BNO055_Soldering_Problem.jpg)
### Read Out GY-BNO055 from Raspberry Pi Directly (GY-BNO055 <--I2C--> Raspberry Pi)
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
### Read Out GY-BNO055 From Raspberry Pi Indirectly (GY-BNO055 <--I2C--> Arduino <--USB--> Raspberry Pi)
#### Program Arduino using PC / Mac (GUI is simpler)
Basically, we need to install two Libraries from Adafruit: 1. Adafruit Unified Sensor; 2. Adafruit BNO055. Then, see the newly added example in Arduino IDE.<br>
Please refer to [this tutorial](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/arduino-code) except for the wiring because the GY-BNO055 is not used in it.
```
GY-BNO055      Nano      Win10
   VIN   <-->  5V   <-->  USB
   GND   <-->  GND  
   SCL   <-->  A5  
   SDA   <-->  A4            
```  
#### Program Arduino using Raspberry Pi (CLI)
Wiring 
```
GY-BNO055      Uno        RPi
   VIN   <-->  5V   <-->  USB
   GND   <-->  GND  
   SCL   <-->  SCL  
   SDA   <-->  SDA           
```
Please refer to [this tutorial](https://github.com/xg590/IoT/blob/master/Arduino/README.md) for installing Arduino IDE on Raspbian
```shell
cd arduino-1.8.12/
./arduino --install-library "Adafruit Unified Sensor"
./arduino --install-library "Adafruit BNO055"
./arduino --board arduino:avr:uno --port /dev/ttyUSB0 --upload bno055.ino
# Warning: Unexpected conflict between .ino files in the same directory may occur, so keep .ino file in an isolated directory if you only need one. 
```
##### Content of <i>bno055.ino</i>
```cpp
#include <SoftwareSerial.h>  
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 i2c = Adafruit_BNO055(55, 0x29); 

void setup(void) {
  Serial.begin(115200); 
  i2c.begin(); // compass
  delay(1000);
}

void loop() {  
  gy_bno055(); 
  delay(1000);
} 

static void gy_bno055() {
  sensors_event_t bno;
  i2c.getEvent(&bno, Adafruit_BNO055::VECTOR_EULER); 
  Serial.print(i2c.getTemp());
  Serial.print(',');
  Serial.print(bno.orientation.x);
  Serial.print(',');
  Serial.print(bno.orientation.y);
  Serial.print(',');
  Serial.print(bno.orientation.z);  
  Serial.println();  
} 
```
#### Read out from Raspberry Pi
After programming, arduino is reset and start to throw out sensor reading via serial port <i>/dev/ttyUSB0</i> 
```python
import serial
with serial.Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=2) as s:
    while 1:
        data = s.readline()  
        print(data)
```
