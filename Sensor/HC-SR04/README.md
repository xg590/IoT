Distance.py 
````
import RPi.GPIO as GPIO
import time 

GPIO.setmode(GPIO.BCM)             # GPIO Mode (BOARD / BCM) 
GPIO_TRIGGER, GPIO_ECHO = 21, 20   # set GPIO Pins 
GPIO.setup(GPIO_TRIGGER, GPIO.OUT) # set GPIO direction (IN / OUT)
GPIO.setup(GPIO_ECHO, GPIO.IN)
 
def distance(): 
    GPIO.output(GPIO_TRIGGER, GPIO.HIGH)  # set Trigger to HIGH 
    time.sleep(0.00001)
    GPIO.output(GPIO_TRIGGER, GPIO.LOW)   # set Trigger after 0.01ms to LOW
 
    StartTime, StopTime = time.time(), time.time() # save StartTime
   
    while GPIO.input(GPIO_ECHO) == 0:
        StartTime = time.time()
 
    # save time of arrival
    while GPIO.input(GPIO_ECHO) == 1:
        StopTime = time.time()
 
    
    TimeElapsed = StopTime - StartTime            # time difference between start and arrival
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distance = (TimeElapsed * 34300) / 2
 
    return distance
````
