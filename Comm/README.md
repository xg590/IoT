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
