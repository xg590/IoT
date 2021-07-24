# rshell -p /dev/ttyACM0 cp rotary.py /pyboard
import time
from machine import ADC, Pin, PWM, Timer
from rotary import ROTARY
 
INT0_Pin = 11
INT1_Pin = 15 
rotary = ROTARY(INT0_Pin, INT1_Pin, reverse=True) 


Pot_Pin  = 27 # Potentiometer 
PWM0_Pin = 3
PWM1_Pin = 6 
pot_pin = ADC(Pin(Pot_Pin))   # create ADC object on ADC pin  
pwm0 = PWM(Pin(PWM0_Pin))      # create PWM object from a pin
pwm1 = PWM(Pin(PWM1_Pin))      # create PWM object from a pin

pwm0.freq()             # get current frequency
pwm0.freq(1000)         # set frequency
pwm1.freq()             # get current frequency
pwm1.freq(1000)         # set frequency  

class MOTOR():
    def __init__(self):   
        self.max_counter = 120
        self.delta_speed = 0
        Timer().init(freq=10, mode=Timer.PERIODIC, callback=self._get_speed)

    def _get_speed(self, timer): 
        target_speed = pot_pin.read_u16()   
        self.max_counter = max(self.max_counter, rotary.counter)
        real_speed   = rotary.counter / self.max_counter * 65535   # compute time difference
        delta_speed  = target_speed - real_speed 
        if delta_speed > 0:
            pwm0.duty_u16(0)      # set duty cycle, range 0-65535
            pwm1.duty_u16(int(delta_speed))          # set duty cycle, range 0-65535 
            self.delta_speed = delta_speed
        rotary.counter = 0
        #print('Speed controller:', val) 
        #print('v:', motor.speed)    

motor = MOTOR()
while 1:
    print(motor.delta_speed)
    time.sleep(3)