### Prelude
$ sudo apt-get install pigpio python3-pigpio
### Usage
```
$ #sudo pkill pigpiod
$ sudo pigpiod -p 8889 ### Start PiGPIO Server / Deamon          http://abyz.me.uk/rpi/pigpio/pigpiod.html
$ python3 
>>> import pigpio
>>> pi = pigpio.pi(port=8889) ### Start PiGPIO Client 
>>> servo = lambda pin, val: pi.set_servo_pulsewidth(pin, val)  
>>> rotation_pin, elevation_pin = 17, 27  # {sky: 1300 ~ 1800 & front: 500 ~ 2500} 
>>> servo(rotation_pin, 600)
```
