import time  
from machine import Pin  
PIN_BUILTIN_LED = 25
p2 = Pin(PIN_BUILTIN_LED, Pin.OUT, value=1)   
p2.on()  # Turn on the on-board LED            
time.sleep(0.5) 
p2.off()   # Turn off the on-board LED    

import ssd1306 
from machine import I2C 
 
OLED_SDA_PIN = 4
OLED_SCL_PIN = 15
OLED_RST_PIN = 16  
oled_rst = Pin(OLED_RST_PIN, Pin.OUT)    # create output pin on GPIO0 
oled_rst.on()                            # Turn on OLED

i2c = I2C(0, scl=Pin(OLED_SCL_PIN), sda=Pin( OLED_SDA_PIN))  
oled = ssd1306.SSD1306_I2C(128, 64, i2c)  

oled.fill(0)
oled.text('Upper Line', 0, 0, col=1) 
oled.text('Middle Line', 0, 27, col=1) 
oled.text('Lower Line', 0, 54, col=1)
oled.show()   
