### Wired protocols: UART / I2C / SPI
* A master device (micro-controller or micro-processor) can use them to talk with a slave module (a sensor breakout or whatever)
* For example: My sensors communicates with WeMos D1 mini via I2C and UART. But Arduino Pro Mini reports to Raspberry Pi through UART interface. This will save a lot of pins and processing power of Raspberry Pi. This scheme is used on my IoT-Rover project.
* UART Pins
  * RX: Receive
  * TX: Transmit
```
    Slave     Master
    RX    <->     TX
    TX    <->     RX
```
### UART
* No brain protocol.
* Choose the right baud rate (Look datasheet or google it)
* It is hassle-free.
* Just use the library.
### I2C
* In practice, we need look into I2C device datasheet to find its I2C bus address.
* If we are using a sensor, we may want to know register address.
* By using these address duo, we can read or write certain bytes of data from or to the device.
* An example (Reading compass data) can be found [here]()
### SPI
#### Wiring
* Pins
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
#### Protocol
* There is no I2C bus address but we use Chip select pin to specify the SPI device we want to access.
* Pull down CS pin
* MOSI emits 1 byte. First bit indicates operation type {1: write, 0:read} and 7 bits for register address.
* MISO reply if a read operation was performed right before.
* MOSI emits more data bytes if it is a write operation while MISO idle all the time. (No Ack like i2c)
* Pull up CS pin
