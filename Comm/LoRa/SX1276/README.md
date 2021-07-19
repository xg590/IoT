### Datasheet notes
##### Data Transmission Sequence (Figure 9)
1. Change to Standby mode
2. Fill FIFO data buffer
3. Change to Tx mode
4. Wait for TxDone IRQ
5. Fall back to Standby mode automatically 
##### Data Reception Sequence (Figure 10)
* Single Mode: Tx is periodical and imminent.
1. Change to Standby mode 
2. Change to Rx Single mode
3. Wait for RxTimeout or RxDone IRQs
4. RxTimeout and fall back to Standby mode automatically. 
4'. RxDone 
5'. Wait for PayloadCrcError IRQ
6'. Read then fall back to Standby mode automatically. (The FIFO data buffer is safe since it can only be cleared after another Rx mode or Sleep mode requests)
* Continous Mode
1. Change to Standby mode
2. Change to Rx Continuous mode
3. Wait for RxDone IRQs
4. Wait for PayloadCrcError IRQ
5. Read then go back to step 3 
#### 4.1.2. LoRa ® Digital Interface
* The LoRa ® modem comprises three types of digital interface, 
  * static configuration registers 
  * status registers 
  * a 256-byte user-defined FIFO data buffer
* Registers Tables 
```
Name                 Addr    Default    Note
RegOpMode
RegFifoRxBaseAddr            0x00 
RegFifoTxBaseAddr            0x80 
RegRxNbBytes                            How many bytes received
RegFifoAddrPtr       0x07    0x00       Where the data ends in buffer
``` 

#include <RadioLib.h>  

const int LoRa_CS = 18, LoRa_DIO0 = 26, LoRa_RST = 14;
const float LoRa_frequency = 915.0;    

SX1276 radio = new Module(LoRa_CS, LoRa_DIO0, LoRa_RST);  // LoRa_DIO0 is for interrupt  
 
                          //    float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain
    int state = radio.begin(LoRa_frequency,    125.0,          9,          7, SX127X_SYNC_WORD,           10,                       8,            0); 
     
    int state = radio.transmit(msg);   

'''
{Band 1: ~915MHz, Band 2: ~433MHz, Band 3: ~150MHz}
{LF: Bands 2&3, HF: Band 1} 
RFI: RF Input 
RFO: RF Output
Three amplifiers: RFO_LF, RFO_HF, PA_BOOST
AFC: automatic frequency correction 
PA: Power Amplifier 
PA_HP: High Power
PA_HF and PA_LF are high efficiency amplifiers
RFOP: RF output power 
RegPaDac = 0x10 << 3 | 0x07 # Enables the +20dBm option on PA_BOOST pin
''' 
```python
def _spi_write(register, payload):
    if type(payload) == int:
        payload = [payload]
    elif type(payload) == bytes:
        payload = [p for p in payload]
    elif type(payload) == str:
        payload = [ord(s) for s in payload]
    cs_pin.value(0)
    spi.write(bytearray([register | 0x80] + payload))
    cs_pin.value(1)

def _spi_read(register, length=1):
    cs_pin.value(0) # Bring the CS pin low to enable communication
    if length == 1:
        data = spi.read(length + 1, register)[1]
    else:
        data = spi.read(length + 1, register)[1:]
    cs_pin.value(1) # release the bus.
    return data  

import time, math 
from machine import SPI, Pin 
# Pins
MISO_Pin = 19
MOSI_Pin = 27
SCK_Pin = 5
CS_Pin = 18
RST_Pin = 14
DIO0_Pin = 26
DIO1_Pin = 35
DIO2_Pin = 34   
# Reset the board 
rst_pin = Pin(RST_Pin, Pin.OUT)
rst_pin.value(0);  
time.sleep(0.01)
rst_pin.value(1);  
time.sleep(0.01) 
cs_pin = Pin(CS_Pin,   Pin.OUT)
cs_pin.value(1) # Release board from SPI Bus by bringing it into high impedance status.  
# Setup Interrupt
#Pin(DIO0_Pin, Pin.IN).irq(trigger=Pin.IRQ_RISING, handler=_handle_interrupt)
# baud rate to 5MHz 
spi = SPI(1, baudrate=5000000, sck=Pin(SCK_Pin), mosi=Pin(MOSI_Pin), miso=Pin(MISO_Pin))
 
### LoRa Mode Register Table (Table 41) 
RegFifo           = 0x00
RegOpMode         = 0x01
RegFrfMsb         = 0x06
RegFrfMid         = 0x07
RegFrfLsb         = 0x08
RegPaConfig       = 0x09
RegFifoAddrPtr    = 0x0d
RegFifoTxBaseAddr = 0x0e
RegFifoRxBaseAddr = 0x0f
FifoRxCurrentAddr = 0x10
RegIrqFlags       = 0x12
RegRxNbBytes      = 0x13 # Number of received bytes
RegPktSnrValue    = 0x19
RegModemConfig1   = 0x1d
RegModemConfig2   = 0x1e
RegModemConfig3   = 0x26 
RegPktRssiValue   = 0x1a
RegPreambleMsb    = 0x20 # Size of preamble
RegPreambleLsb    = 0x21
RegPayloadLength  = 0x22
RegDioMapping1    = 0x40 # Mapping of pins DIO0 to DIO3
RegPaDac          = 0x4d # Higher power settings of the PA (Power Amplifier) DAC (Digital Analog Converter)

### Register Value
RxDone            = 0b01000000 
TxDone            = 0b00001000
CadDone           = 0b00000100
CadDetected       = 0b00000001  
LongRangeMode     = 0b01000000 
Mode_SLEEP        = 0b00000000
Mode_STDBY        = 0b00000001
Mode_TX           = 0b00000011
Mode_RXCONTINUOUS = 0b00000101
Mode_CAD          = 0b00000111
 
# set mode
_mode = None
_spi_write(RegOpMode, Mode_SLEEP | LongRangeMode) 
time.sleep(0.1) 
assert _spi_read(RegOpMode) == (Mode_SLEEP | LongRangeMode), "LoRa initialization failed"

# Use all FIFO buffer. See Datasheet: Principle of Operation
_spi_write(RegFifoTxBaseAddr, 0x00) # bottom of the memory
_spi_write(RegFifoRxBaseAddr, 0x00) 
 
_spi_write(RegOpMode, Mode_STDBY)   
 
# LoRa Configuration
# Frequency 915MHz
# Bandwidth: 125KHz
# Coding rate: 7
# Spreading Factor: 9
# Preamble Length: 8
# Sync word: SX127X_SYNC_WORD
# Power: 20dBm
# Gain: 0

# See 4.1.4. Frequency Settings
FXOSC = 32e6 # Freq of XOSC
FSTEP = FXOSC / (2**19)
Frf = int(915e6 / FSTEP)
_spi_write(RegFrfMsb, (Frf >> 16) & 0xff)
_spi_write(RegFrfMid, (Frf >>  8) & 0xff)
_spi_write(RegFrfLsb,  Frf        & 0xff) 
# See 4.4. LoRa Mode Register Map  
_spi_write(RegModemConfig1, 0b0111_011_1)  # Bw:125kHz, CodingRate:4/7, ImplicitHeaderModeOn: Off
_spi_write(RegModemConfig2, 0b1001_0_1_00) # SpreadingFactor: 9, TxContinuousMode: Normal, RxPayloadCrcOn: On, SymbTimeout(9:8):0
_spi_write(RegModemConfig3, 0x64) 
# Preamble length (8)
_spi_write(RegPreambleMsb, 0x0) # Preamble can be (2<<15)kb long, much longer than payload 
_spi_write(RegPreambleLsb, 0x8) # but we just use 8-byte preamble 
# Enables the +20dBm option on PA_BOOST pin
PaDac = [0x04, 0x07]   # Can be 0x04 or 0x07. 0x07 will enables the +20dBm option on PA_BOOST pin
_spi_write(RegPaDac, PaDac[1]) 
# Select PA_BOOST as output 
PaSelect          = 0b1_000_0000 # Select PA_BOOST pin
MaxPower          = 0b0_111_0000 # 15dBm = 10.8 + 0.6 * 7 
OutputPower       = 0b0_000_1111 # 17    = 17 - ( 15 - OutputPower ) since we choose PA_BOOST pin by setting PaSelect 
_spi_write(RegPaConfig, PaSelect | MaxPower | OutputPower)

# Send data
_spi_write(RegOpMode, Mode_STDBY)   
data = "Hello from [Heltec WiFi LoRa 32 V2]"
data = [ord(s) for s in data]  
_spi_write(RegFifoAddrPtr, 0) # Move Ptr to FIFO's bottom
_spi_write(RegFifo, data)     # Write payload
_spi_write(RegPayloadLength, len(data))
_spi_write(RegOpMode, Mode_TX)
#self._spi_write(REG_40_DIO_MAPPING1, 0x40)  # Interrupt on TxDone  



_spi_read(RegIrqFlags)
```
