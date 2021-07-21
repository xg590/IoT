import ssd1306 
from machine import Pin, I2C
from time import sleep
 
OLED_SDA_PIN = 4
OLED_SCL_PIN = 15
OLED_RST_PIN = 16  
oled_rst = Pin(OLED_RST_PIN, Pin.OUT)    # create output pin on GPIO0 
oled_rst.on()  
i2c = I2C(0, scl=Pin(OLED_SCL_PIN), sda=Pin( OLED_SDA_PIN)) 
# https://docs.micropython.org/en/latest/esp8266/tutorial/ssd1306.html
oled = ssd1306.SSD1306_I2C(128, 64, i2c)   
oled.fill(0)
oled.text('Upper Line', 0, 0, col=1) 
oled.text('Middle Line', 0, 27, col=1) 
oled.text('Lower Line', 0, 54, col=1)
oled.show()
sleep(3) 

from ulora import LoRa

# This is our callback function that runs when a message is received
def on_recv(payload):  
    oled.fill(0) 
    oled.text("RSSI: {}".format(payload.rssi), 0, 0, col=1)
    oled.text(payload.message.decode(), 0, 27, col=1) 
    oled.text("SNR: {}".format(payload.snr), 0, 54, col=1)
    oled.show() 
    print("From:", payload.header_from)
    print("Received:", payload.message)
    print("RSSI: {}; SNR: {}".format(payload.rssi, payload.snr))

# Lora Parameters  
RF95_FREQ = 915.0
RF95_POW = 20
CLIENT_ADDRESS = 1
SERVER_ADDRESS = 2
 

MISO_Pin = 19
MOSI_Pin = 27
SCK_Pin  =  5
CS_Pin   = 18
RST_Pin  = 14
DIO0_Pin = 26
DIO1_Pin = 35
DIO2_Pin = 34


# initialise radio
lora = LoRa((1, SCK_Pin, MOSI_Pin, MISO_Pin), DIO0_Pin, SERVER_ADDRESS, CS_Pin, reset_pin=RST_Pin, freq=RF95_FREQ, tx_power=RF95_POW, acks=True)

# set callback
lora.on_recv = on_recv

# set to listen continuously
lora.set_mode_rx()

# loop and wait for data
while True:
    sleep(0.1) 
