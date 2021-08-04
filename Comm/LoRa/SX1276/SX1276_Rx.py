import time, urandom
from machine import SPI, Pin
'''
Overview: How to use SX1276
1. Enable the module
2. Configure SPI communication
3. Configure the LoRa mode
4. Transmit
'''
####################
#                  #
#     1.Enable     #
#                  #
####################
# RFM95W         Pico GPIO
LoRa_MISO_Pin  = 16
LoRa_CS_Pin    = 17
LoRa_SCK_Pin   = 18
LoRa_MOSI_Pin  = 19
LoRa_G0_Pin    = 20 # DIO0_Pin
LoRa_RST_Pin   = 21
LoRa_EN_Pin    = 22

# Enable LoRa Module
lora_en_pin = Pin(LoRa_EN_Pin, Pin.OUT)
lora_en_pin.on()
time.sleep(0.01)

# Reset LoRa Module
lora_rst_pin = Pin(LoRa_RST_Pin, Pin.OUT)
lora_rst_pin.off()
time.sleep(0.01)
lora_rst_pin.on()
time.sleep(0.01)

####################
#                  #
#      2.SPI       #
#                  #
####################
'''
We command LoRa module to perform Tx/Rx operations via the SPI interface.
We disable SPI communication first to ensure it only happends when we need.
Define communication functions read and write.
The SPI comm is enabled temporarily for reading and writing and disabled thereafter.
'''
# Disable SPI communication with the LoRa module
lora_cs_pin  = Pin(LoRa_CS_Pin, Pin.OUT)
lora_cs_pin.on() # Release board from SPI Bus by bringing it into high impedance status.
time.sleep(0.01)

# SPI communication
# See datasheet: Device support SPI mode 0 (polarity & phase = 0) up to a max of 10MHz.
spi = SPI(0, baudrate=10_000_000, polarity=0, phase=0,
          sck=Pin(LoRa_SCK_Pin), mosi=Pin(LoRa_MOSI_Pin), miso=Pin(LoRa_MISO_Pin)) # We are using 0/first/default SPI

def write(reg, data):
    if type(data) == int:
        data = [data]
    elif type(data) == bytes:
        data = [p for p in data]
    elif type(data) == str:
        data = [ord(s) for s in data]
    lora_cs_pin.value(0) # Bring the CS pin low to enable communication
    spi.write(bytearray([reg | 0x80] + data))
    lora_cs_pin.value(1) # release the bus.

def read(reg=None, length=1):
    lora_cs_pin.value(0)
    # https://docs.micropython.org/en/latest/library/machine.SPI.html#machine-softspi
    if length == 1:
        data = spi.read(length+1, reg)[1]
    else:
        data = spi.read(length+1, reg)[1:]
    lora_cs_pin.value(1)
    return data

####################
#                  #
#      3.Lora      #
#                  #
####################
'''
Choose LoRa mode and Test write/read functions
Set bandwidth, coding rate, header mode, spreading factor, CRC, and etc.
'''
RegOpMode         = 0x01
Mode_SLEEP        = 0b00000000
LongRangeMode     = 0b1
# Choose LoRa (instead of FSK) mode for SX1276 and put the module in sleep mode
write(RegOpMode, Mode_SLEEP | LongRangeMode << 7)
time.sleep(0.1)
# Check if mode is set
assert read(RegOpMode) == (Mode_SLEEP | LongRangeMode << 7), "LoRa initialization failed"

# Set modem config (Bw125Cr45Sf128)
# See 4.4. LoRa Mode Register Map
RegModemConfig1      = 0x1d
Bw                   = {'125KHz':0b0111, '500kHz':0b1001}
CodingRate           = {5:0b001, 6:0b010, 7:0b011, 8:0b100}
ImplicitHeaderModeOn = {'Implicit':0b1, 'Explicit':0b0}
write(RegModemConfig1, Bw['125KHz'] << 4 | CodingRate[5] << 1 | ImplicitHeaderModeOn['Explicit'])

# More parameters
RegModemConfig2  = 0x1e
RegModemConfig3  = 0x26
SpreadingFactor  = {7:0x7, 9:0x9, 12:0xC}
TxContinuousMode = {'normal':0b0, 'continuous':0b1}
RxPayloadCrcOn   = {'disable':0b0, 'enable':0b1}
write(RegModemConfig2, SpreadingFactor[7] << 4 | TxContinuousMode['normal'] << 3 | RxPayloadCrcOn['enable'] << 2 | 0x00) # Last 0x00 is SymbTimeout(9:8)
write(RegModemConfig3, 0x04) # 0x04 is SymbTimeout(7:0)

# Preamble length
RegPreambleMsb    = 0x20 # Size of preamble
RegPreambleLsb    = 0x21
write(RegPreambleMsb, 0x0) # Preamble can be (2<<15)kb long, much longer than payload
write(RegPreambleLsb, 0x8) # but we just use 8-byte preamble

# See 4.1.4. Frequency Settings
RegFrfMsb         = 0x06
RegFrfMid         = 0x07
RegFrfLsb         = 0x08
FXOSC = 32e6 # Freq of XOSC
FSTEP = FXOSC / (2**19)
Frf = int(915e6 / FSTEP)
write(RegFrfMsb, (Frf >> 16) & 0xff)
write(RegFrfMid, (Frf >>  8) & 0xff)
write(RegFrfLsb,  Frf        & 0xff)

# Choose PA_BOOST (instead of RFO) as the power amplifier
RegPaConfig = 0x09
PaSelect    = {'PA_BOOST': 0b1, 'RFO': 0b0} # Select PA_BOOST pin
MaxPower    = {'15dBm':0x7} # 15dBm = 10.8 + 0.6 * 7
OutputPower = {17: 0xf, 4:0x2} # 17 = 17 - ( 15 - OutputPower ) Use this formula since we choose PA_BOOST pin by setting PaSelect
                               # Since we enabled +20dBm option on PA_BOOST pin, 20dBm is online
write(RegPaConfig, PaSelect['PA_BOOST'] << 7 | MaxPower['15dBm'] << 4 | OutputPower[4])

# Enables the +20dBm option on PA_BOOST pin.
RegPaDac = 0x4d # Higher power settings of the PA (Power Amplifier) DAC (Digital Analog Converter)
PaDac    = {'default':0x04, 'enable_PA_BOOST': 0x07}      # Can be 0x04 or 0x07. 0x07 will enables the +20dBm option on PA_BOOST pin
write(RegPaDac, PaDac['enable_PA_BOOST']) # We still can choose RFO pin in RegPaConfig. Here we just enable

####################
#                  #
#    Interrupt     #
#                  #
####################
'''
# This section is optional for Tx.
# It enable an interrupt when Tx is done.
'''
RegDioMapping1    = 0x40
DioMapping = {
    'Dio0' : {
                 'RxDone'           : 0b00 << 6,
                 'TxDone'           : 0b01 << 6,
                 'CadDone'          : 0b10 << 6
             },
    'Dio1' : {
                 'RxTimeout'        : 0b00 << 4,
                 'FhssChangeChannel': 0b01 << 4,
                 'CadDetected'      : 0b10 << 4
             },
    'Dio2' : {},
    'Dio3' : {},
    'Dio4' : {},
    'Dio5' : {},
}
write(RegDioMapping1, DioMapping['Dio0']['TxDone'])  # Configure Pin Dio0 so that this pin interrupts on TxDone, see Table 18 DIO Mapping LoRa ® Mode

RegIrqFlags = 0x12
IrqFlags = {
    'RxTimeout'        : 0b1 << 7,
    'RxDone'           : 0b1 << 6,
    'PayloadCrcError'  : 0b1 << 5,
    'ValidHeader'      : 0b1 << 4,
    'TxDone'           : 0b1 << 3,
    'CadDone'          : 0b1 << 2,
    'FhssChangeChannel': 0b1 << 1,
    'CadDetected'      : 0b1 << 0
}

def _handler(pin):
    assert read(RegIrqFlags) == IrqFlags['TxDone'], 'IRQ Error for TxDone'
    print('TxDone~')
    write(RegIrqFlags, 0xab) # write anything could clear all types of interrupt flags

lora_irq_pin = Pin(LoRa_G0_Pin, Pin.IN)
lora_irq_pin.irq(handler=_handler, trigger=Pin.IRQ_RISING)

''' # interrupt flag mask: use to deactive a particular interrupt
RegIrqFlagsMask = 0x11;
IrqFlagsMask = {
    'RxTimeoutMask'        : 0b1 << 7,
    'RxDoneMask'           : 0b1 << 6,
    'PayloadCrcErrorMask'  : 0b1 << 5,
    'ValidHeaderMask'      : 0b1 << 4,
    'TxDoneMask'           : 0b1 << 3,
    'CadDoneMask'          : 0b1 << 2,
    'FhssChangeChannelMask': 0b1 << 1,
    'CadDetectedMask'      : 0b1 << 0
}
write(RegIrqFlagsMask, IrqFlagsMask['TxDoneMask'])  #  This will deactivate interrupt on TxDone.
'''

####################
#                  #
#       4.Tx       #
#                  #
####################


### LoRa Mode Register Table (Table 41)
FifoRxCurrentAddr = 0x10
RegRxNbBytes      = 0x13 # Number of received bytes
RegPktSnrValue    = 0x19
RegPktRssiValue   = 0x1a
RegSyncWord       = 0x39
RegVersion        = 0x42

### Register Value
Mode_RXCONTINUOUS = 0b00000101
Mode_CAD          = 0b00000111
'''
SX1276 has a 256 byte memory area as the FIFO buffer for Tx/Rx operations.
How do we know which area is for Tx and which is for Rx.
We must set the base addresses RegFifoTxBaseAddr and RegFifoRxBaseAddr independently.
Since SX1276 work in a half-duplex manner, we better set both base addresses
at the bottom (0x00) of the FIFO buffer so that we can buffer 256 byte data
during transmition or reception.
'''
RegFifoTxBaseAddr = 0x0e
RegFifoRxBaseAddr = 0x0f
Fifo_Bottom       = 0x00 # We choose this value to max buffer we can write (then send out)
write(RegFifoTxBaseAddr, Fifo_Bottom)
write(RegFifoRxBaseAddr, Fifo_Bottom)

while 1:
    # Prepare the payload
    data = str(urandom.randint(100,999))+") Hello1~"
    print(data)
    CLIENT_ADDRESS = 1
    SERVER_ADDRESS = 2
    header = [SERVER_ADDRESS, CLIENT_ADDRESS, 1, 0]
    data = [ord(s) for s in data]
    payload = header + data

    # Reg and value
    RegFifoAddrPtr    = 0x0d
    Mode_STDBY        = 0b00000001
    RegFifo           = 0x00
    RegPayloadLength  = 0x22
    Mode_TX           = 0b00000011

    # Send Data
    write(RegOpMode, Mode_STDBY)       # Request Standby mode so SX1276 performs transmition initialization.
    write(RegFifoAddrPtr, Fifo_Bottom) # Before fill the buffer, move this point manually to where we set for RegFifoTxBaseAddr.
                                       # Static configuration registers can only be accessed in Sleep mode, Standby mode or FSTX mode.
    write(RegFifo, payload)            # Write Data FIFO
    assert read(RegFifoAddrPtr) == len(payload), 'Prove me wrong' # After writing, RegFifoAddrPtr moves to Fifo_Bottom + len(payload)
    write(RegPayloadLength, len(payload))
    write(RegOpMode, Mode_TX)          # Request Standby mode so SX1276 send out payload
    time.sleep(10)
