import time 
from machine import Pin, PWM 
import ROTARY
STBY_Pin = 2 # 
AIN1_Pin, AIN2_Pin,  = 3, 4
PWMA_Pin = 5
BIN1_Pin, BIN2_Pin = 26, 27
PWMB_Pin = 	28  
dc = 0 # get current duty cycle, range 0-65535
standby_pin = Pin(STBY_Pin, Pin.OUT, Pin.PULL_UP)
standby_pin.off()
time.sleep(1)
standby_pin.on()

ain1_pin = Pin(AIN1_Pin, Pin.OUT)
ain1_pin.on()
ain2_pin = Pin(AIN2_Pin, Pin.OUT)
ain2_pin.off() # rev

pwm0 = PWM(Pin(PWMA_Pin))   
pwm0.freq()                 
pwm0.freq(1000)              
pwm0.duty_u16(dc) 
#pwm0.deinit() 
 
bin1_pin = Pin(BIN1_Pin, Pin.OUT)
bin1_pin.off()
bin2_pin = Pin(BIN2_Pin, Pin.OUT)
bin2_pin.on()

pwm1 = PWM(Pin(PWMB_Pin))   
pwm1.freq()                 
pwm1.freq(1000)              
pwm1.duty_u16(dc)        
#pwm0.deinit()              
rotary_A = ROTARY(12,13)
rotary_B = ROTARY(8,9)
#rotary_b = ROTARY(6,7)
#rotary_b = ROTARY(10,11)
while 1:
    print(rotary_A.counter, rotary_B.counter)
    time.sleep(0.5)