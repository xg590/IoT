### Wired protocols: UART / I2C / SPI
* A master device (micro-controller or micro-processor) can use them to talk with a slave module (a sensor breakout or whatever)
* For example: My sensors communicates with Arduino Pro Mini via I2C and UART. But Arduino Pro Mini reports to Raspberry Pi through UART interface. This will save a lot of pins and processing power of Raspberry Pi. This scheme is used on my IoT-Rover project.
* UART Pins
  * RX: Receive
  * TX: Transmit
```
    Slave     Master  
    RX    <->     TX    
    TX    <->     RX
```
* I2C or IIC or SMBus Pins
  * SCL: Clock line
  * SDA: Data line
```
    Slave1     Master     Slave2
    SCL    <->  SCL   <->    SCL
    SDA    <->  SDA   <->    SDA
```
* SPI Pins
  * SCK: SPI Clock
  * MISO: Master In Slave Out. Data flow out this pin from a slave module.
  * MOSI: Data pours in a slave module through this pin.
  * CS: Chip select. For some module, this pin is marked as NSS: Negative Slave Select. This pin is pulled down by the master so that a slave module is on service. 
```
    Slave1     Master     Slave2
    SCK    <->  SCK   <->    SCK
    MISO   <->  MISO  <->   MISO
    MOSI   <->  MOSI  <->   MOSI
    CS     <->  CS1 
                CS2   <->     CS    
```
### UART
* No brain protocol.
* It is hassle-free.
* Just use a library. 
### I2C
* In practice, we need look into I2C device datasheet to find its I2C bus address. 
* If we are using a sensor, we may want to know register address. 
* By using these address duo, we can read or write certain bytes of data from or to the device. 
* An example (Reading compass data) can be found [here]()
### SPI
* There is no I2C bus address but we use Chip select pin to specify the SPI device we want to access.
* 
