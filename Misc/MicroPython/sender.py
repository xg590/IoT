import time, math
from machine import SPI, Pin
# Pins
MISO_Pin     = 16
CS_Pin       = 17
SCK_Pin      = 18
MOSI_Pin     = 19
G0_Pin       = 20 # DIO0_Pin
RST_Pin      = 21
EN_Pin       = 22

rst_pin = Pin(RST_Pin, Pin.OUT)
cs_pin  = Pin(CS_Pin, Pin.OUT)
#Pin(DIO0_Pin, Pin.IN).irq(trigger=Pin.IRQ_RISING, handler=_handle_interrupt) 
if 1:
    rst_pin.value(0); # Reset the board
    time.sleep(0.01)
    rst_pin.value(1)
    time.sleep(0.01)
    cs_pin.value(1) # Release board from SPI Bus by bringing it into high impedance status.
    time.sleep(0.01)

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
RegSyncWord       = 0x39
RegDioMapping1    = 0x40 # Mapping of pins DIO0 to DIO3
RegVersion        = 0x42
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

# Device support SPI mode 0 (polarity & phase = 0) up to a max of 10MHz.
spi = SPI(0, baudrate=10_000_000, polarity=0, phase=0,
          sck=Pin(SCK_Pin), mosi=Pin(MOSI_Pin), miso=Pin(MISO_Pin)) # We are using 0/first/default SPI

def write(reg, data): 
    if type(data) == int:
        data = [data]
    elif type(data) == bytes:
        data = [p for p in data]
    elif type(data) == str:
        data = [ord(s) for s in data]
    cs_pin.value(0) # Bring the CS pin low to enable communication
    spi.write(bytearray([reg | 0x80] + data))
    cs_pin.value(1) # release the bus.

def read(reg=None, length=1): 
    cs_pin.value(0)
    # https://docs.micropython.org/en/latest/library/machine.SPI.html#machine-softspi
    if length == 1:
        data = spi.read(length+1, reg)[1]
    else:
        data = spi.read(length+1, reg)[1:]
    cs_pin.value(1)
    return data 
 
print(read(reg=RegVersion))

# set mode
write(RegOpMode, Mode_SLEEP | LongRangeMode)
time.sleep(0.1)
assert read(RegOpMode,2) == (Mode_SLEEP | LongRangeMode), "LoRa initialization failed"
 
# Use all FIFO buffer. See Datasheet: Principle of Operation
write(RegFifoTxBaseAddr, 0x00) # bottom of the memory
write(RegFifoRxBaseAddr, 0x00)

write(RegOpMode, Mode_STDBY)

# LoRa Configuration
# Frequency 915MHz
# Bandwidth: 125KHz
# Coding rate: 8
# Spreading Factor: 12
# Preamble Length: 8
# Sync word: SX127X_SYNC_WORD
# Power: 20dBm
# Gain: 0

# See 4.1.4. Frequency Settings
FXOSC = 32e6 # Freq of XOSC
FSTEP = FXOSC / (2**19)
Frf = int(915e6 / FSTEP)
write(RegFrfMsb, (Frf >> 16) & 0xff)
write(RegFrfMid, (Frf >>  8) & 0xff)
write(RegFrfLsb,  Frf        & 0xff)

# See 4.4. LoRa Mode Register Map
Bw_125KHz                     = 0b0111
CodingRate_7                  = 0b011
CodingRate_8                  = 0b100
ImplicitHeaderModeOn_Implicit = 0b1
write(RegModemConfig1, Bw_125KHz << 4 | CodingRate_8 << 1 | ImplicitHeaderModeOn_Implicit)  # Bw:125kHz, CodingRate:4/7, ImplicitHeaderModeOn: Off
# More parameters
SpreadingFactor_9  = 0x9
SpreadingFactor_12 = 0xC
TxContinuousMode_normal = 0b0
RxPayloadCrcOn_enable   = 0b1  
write(RegModemConfig2, SpreadingFactor_12 << 4 | TxContinuousMode_normal << 3 | RxPayloadCrcOn_enable << 2 | 0x00) # SpreadingFactor: 9, TxContinuousMode: Normal, RxPayloadCrcOn: On, SymbTimeout(9:8): 0x00 
write(RegModemConfig3, 0x64)
# Preamble length (8)
write(RegPreambleMsb, 0x0) # Preamble can be (2<<15)kb long, much longer than payload
write(RegPreambleLsb, 0x8) # but we just use 8-byte preamble
# Enables the +20dBm option on PA_BOOST pin
PaDac = [0x04, 0x07]   # Can be 0x04 or 0x07. 0x07 will enables the +20dBm option on PA_BOOST pin
write(RegPaDac, PaDac[1])
# Select PA_BOOST as output 
PaSelect_PA_BOOST = 0b1 # Select PA_BOOST pin
PaSelect_RFO      = 0b0 # Select RFO pin
MaxPower_15dBm    = 0x7 # 15dBm = 10.8 + 0.6 * 7
OutputPower_17    = 0xF # 17    = 17 - ( 15 - OutputPower ) since we choose PA_BOOST pin by setting PaSelect
write(RegPaConfig, PaSelect_PA_BOOST << 7 | MaxPower_15dBm << 4 | OutputPower_17)
# Syncword
#SX127X_SYNC_WORD = 0x12 
#write(RegSyncWord, SX127X_SYNC_WORD)
'''
# Send data
write(RegOpMode, Mode_STDBY)
data = "Hello from [Heltec WiFi LoRa 32 V2]"
data = [ord(s) for s in data]
write(RegFifoAddrPtr, 0) # Move Ptr to FIFO's bottom
write(RegFifo, data)     # Write payload
write(RegPayloadLength, len(data))
write(RegOpMode, Mode_TX)
#self.write(REG_40_DIO_MAPPING1, 0x40)  # Interrupt on TxDone
'''
 