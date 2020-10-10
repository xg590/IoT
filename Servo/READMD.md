### PCA9685 16-Channel 12-bit PWM/Servo Driver
Libraries
```
pip install adafruit-circuitpython-pca9685 adafruit-circuitpython-servokit
```
Python Code
```python
import time
from adafruit_servokit import ServoKit 
class Servo: 
    # adafruit_servokit.ServoKit(*, channels, i2c=None, address=64, reference_clock_speed=25000000, frequency=50) 
    kit = ServoKit(channels=16)  
    servo_map = {'clamp_rot':1, 'clamp':4, 'arm_ele_far':3, 'arm_ele_near':6, 'arm_rot':8} 
    
    kit.servo[servo_map['arm_ele_near']].set_pulse_width_range(800,2195) # (800, 2695) 
    kit.servo[servo_map['arm_ele_near']].actuation_range = 1000
    kit.servo[servo_map['arm_ele_far']].set_pulse_width_range(800, 2500)
    kit.servo[servo_map['arm_ele_far']].actuation_range = 1000
    kit.servo[servo_map['arm_rot']].set_pulse_width_range(930, 2300) 
    kit.servo[servo_map['arm_rot']].actuation_range = 1000
    kit.servo[servo_map['clamp']].set_pulse_width_range(550, 1170) 
    kit.servo[servo_map['clamp']].actuation_range = 1000
    arm_ele_near = 1000 
    arm_ele_far  = 500 
    arm_rot      = 0 
    clamp        = 1000 
    
    def __setattr__(self, name, new_value):
        old_value = self.__getattribute__(name)
        self.__dict__[name] = new_value
        step = 1 if new_value>old_value else -1  
        for i in range(old_value, new_value,step): 
            self.kit.servo[self.servo_map[name]].angle = i
            time.sleep(0.001) 
s = Servo() 

s.arm_ele_near = 0
s.arm_ele_far = 800
s.clamp = 0
s.arm_rot = 600 
s.arm_ele_near = 1000 
s.arm_rot = 0  
s.arm_ele_far = 500 
s.clamp = 1000  
s.arm_ele_near = 0
s.arm_ele_far = 800
s.clamp = 1000
s.arm_rot = 600 
s.clamp = 0
```