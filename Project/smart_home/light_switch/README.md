```python
import time  
from machine import Pin, PWM 
PIN_MOSFET = 4
PIN_Servo = 5 
p0 = Pin(PIN_MOSFET, Pin.OUT, value=0)    
pwm0 = PWM(Pin(PIN_Servo))      

p0.on()      
pwm0.freq(50) 
for i in range(33,134,10): # Range from 33 to 133
    print(i) 
    pwm0.duty(i)          
    time.sleep(3)
pwm0.deinit()           
```
