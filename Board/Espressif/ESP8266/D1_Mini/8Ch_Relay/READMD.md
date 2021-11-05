### 8-Channel Relay
<img src="8ChRelay.png"></img>
### Specs 
* VCC: 5V power vol 
* IO: 3V3 operating voltage
### Pin mapping
``` 
from machine import Pin   
k1 = Pin( 2, Pin.OUT, value=1) # off state of 1st relay is 1, controlled by GPIO2
k2 = Pin( 0, Pin.OUT, value=1)   
k3 = Pin(15, Pin.OUT, value=1)  
k4 = Pin(13, Pin.OUT, value=0) # off state of 4th relay is 0, controlled by GPIO13
k5 = Pin(12, Pin.OUT, value=1)  
k6 = Pin(14, Pin.OUT, value=1)  
k7 = Pin( 4, Pin.OUT, value=1)  
k8 = Pin( 5, Pin.OUT, value=1)  
k1.off()                       # turn on k1
```
