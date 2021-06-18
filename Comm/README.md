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
### Wireless protocol: LoRa
* LoRa: Long Range communication
* A practical analog singal is typically not pure in frequency. For example, our voice is a combination of sine waves. If we do a fourier transform, we will see a broad frequency specturm. If our voice undergoes the frequency modulation, the modulated signal will produce a frequency specturm as well. 
* When we send out a message, it is digitally coded by our microprocessor/microcontroller in a sequence of 0 and 1. The frequency of this sequence is fixed. This sequence then goes through LoRa module, where it undergoes frequency modulation and a modulated analog signal leaves transmitter antenna. This modulated signal varies in frequency. The signal spreads across frequency domain. The frequency of <i>frequency varying</i> is determined by Spreading factor.
  * Spreading Factor: LoRa use CSS (Chirp Spread Spectrum) tech to modulate the digital signal. (DSSS spread the bandwidth at a higher fixed frequency; CSS spread the frequecy at the same bandwidth)
  * Bandwidth: Varying range of modulated signal on frequency domain.
  * Coding Rate: Code Rate is the degree of redundancy implemented by the forward error correction (FEC)
used to detect errors and correct them
  * Preamble: The modulated signal begins with repeated wave pattern.   
