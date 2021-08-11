### Materials
* Raspberry Pi Pico + Adafruit RFM95W 
* Heltec WiFi LoRa 32 V2 
### Pin Scheme
* Raspberry Pi Pico
```
# RFM95W   Pico GPIO
MISO_Pin = 16
CS_Pin   = 17
SCK_Pin  = 18
MOSI_Pin = 19
G0_Pin   = 20 # DIO0_Pin
RST_Pin  = 21
EN_Pin   = 22
```
* Heltec WiFi LoRa 32 V2
```
MISO_Pin = 19
MOSI_Pin = 27
SCK_Pin  =  5
CS_Pin   = 18
RST_Pin  = 14
DIO0_Pin = 26
DIO1_Pin = 35
DIO2_Pin = 34
``` 
### How to use SX1276
* Enable the module if use Adafruit RFM95W 
* Configure SPI communication to control the LoRa modem
* Choose LoRa Modem other than FSK/OOK Modem
* Set bandwidth, coding rate, header mode, spreading factor, preamble length, frequency, amplifier
* Set an interrupt routine service to read incoming message and to monitor modem's working status 
* Write FIFO data buffer when transmit and read when receive. 
### [Datasheet](DS_SX1276-7-8-9_W_APP_V7.pdf)  
#### Jargon in it
* RF: Radio Frequency
* RFI: RF Input
* RFO: RF Output
* { HF: {Band 1: ~915MHz}, LF: {Band 2: ~433MHz, Band 3: ~150MHz} } 
* PA: Power Amplifier
* Three amplifiers: RFO_LF, RFO_HF, PA_BOOST
* PA_HP: High Power
* PA_HF and PA_LF are high efficiency amplifiers
* AFC: automatic frequency correction
* RFOP: RF output power
#### 4.1.2. LoRa ® Digital Interface
* The LoRa ® modem comprises three types of digital interface,
  * static configuration registers
  * status registers
  * a 256-byte user-defined FIFO data buffer
#### Data Transmission Sequence (Figure 9)
* Change to Standby mode so the modem initiate everything
* Start Tx loop 
  * Prepare payload to Tx
  * Fill FIFO data buffer with payload
  * Change to Tx mode
  * Wait for TxDone IRQ
    * In IRQ, do something and clear IRQ Flags 
  * Fall back to Standby mode automatically
#### Continous Mode Data Reception Sequence (Figure 10)
* Change to Standby mode so the modem initiate everything
* Change to Rx Continuous mode
* Wait for IRQ (RxDone and ValidHeader/PayloadCrcError)
  * Read FIFO data buffer to get payload
* Next IRQ 
