### Prelude
* Board is available on [ebay](https://www.ebay.com/itm/311834775630)<br>
* Python Code is compatible with [Adafruit Stepper + DC Motor FeatherWing](https://learn.adafruit.com/adafruit-stepper-dc-motor-featherwing/circuitpython)<br>
* Enable I2C interface
### Usage:
```
$ pip3 install adafruit-circuitpython-motorkit 
$ python3 
>> from adafruit_motorkit import MotorKit
>> import time
>> kit = MotorKit() 
>> kit.motor3.throttle = 1.0
>> kit.motor4.throttle = 1.0
>> time.sleep(0.5)
>> kit.motor3.throttle = 0
>> kit.motor4.throttle = 0
```
