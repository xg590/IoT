### This code is a annotated version of martynwheeler/u-lora
import time, urandom
from machine import SPI, Pin

# RFM95W         Pico GPIO
LoRa_MISO_Pin  = 16
LoRa_CS_Pin    = 17
LoRa_SCK_Pin   = 18
LoRa_MOSI_Pin  = 19
LoRa_G0_Pin    = 20 # DIO0_Pin
LoRa_RST_Pin   = 21
LoRa_EN_Pin    = 22

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
Fifo_Bottom       = 0x00 # We choose this value to max buffer we can write (then send out)
RxDone            = 0b01000000
TxDone            = 0b00001000
CadDone           = 0b00000100
CadDetected       = 0b00000001
LongRangeMode     = 0b1
Mode_SLEEP        = 0b00000000
Mode_STDBY        = 0b00000001
Mode_TX           = 0b00000011
Mode_RXCONTINUOUS = 0b00000101
Mode_CAD          = 0b00000111

# Reset LoRa Module
lora_rst_pin = Pin(LoRa_RST_Pin, Pin.OUT)
lora_rst_pin.off();
time.sleep(0.01)
lora_rst_pin.on()
time.sleep(0.01)

# Put module in idling
lora_cs_pin  = Pin(LoRa_CS_Pin, Pin.OUT)
lora_cs_pin.value(1) # Release board from SPI Bus by bringing it into high impedance status.
time.sleep(0.01)

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

# Set mode
write(RegOpMode, Mode_SLEEP | LongRangeMode << 7) # sleep and LoRa mode
time.sleep(0.1)

# check if mode is set
assert read(RegOpMode) == (Mode_SLEEP | LongRangeMode << 7), "LoRa initialization failed"

# Use all FIFO buffer. See Datasheet: Principle of Operation
write(RegFifoTxBaseAddr, Fifo_Bottom)
write(RegFifoRxBaseAddr, Fifo_Bottom)

# Set modem config (Bw125Cr45Sf128)
# See 4.4. LoRa Mode Register Map
Bw_125KHz                     = 0b0111
CodingRate                    = {5:0b001, 6:0b010, 7:0b011, 8:0b100}
ImplicitHeaderModeOn_Implicit = 0b1
ImplicitHeaderModeOn_Explicit = 0b0
write(RegModemConfig1, Bw_125KHz << 4 | CodingRate[5] << 1 | ImplicitHeaderModeOn_Explicit)

# More parameters
SpreadingFactor = {7:0x7, 9:0x9, 12:0xC}
TxContinuousMode_normal = 0b0
RxPayloadCrcOn_enable   = 0b1
write(RegModemConfig2, SpreadingFactor[7] << 4 | TxContinuousMode_normal << 3 | RxPayloadCrcOn_enable << 2 | 0x00) # Last 0x00 is SymbTimeout(9:8)
write(RegModemConfig3, 0x04) # 0x04 is SymbTimeout(7:0)

# Preamble length (8)
write(RegPreambleMsb, 0x0) # Preamble can be (2<<15)kb long, much longer than payload
write(RegPreambleLsb, 0x8) # but we just use 8-byte preamble

# See 4.1.4. Frequency Settings
FXOSC = 32e6 # Freq of XOSC
FSTEP = FXOSC / (2**19)
Frf = int(915e6 / FSTEP)
write(RegFrfMsb, (Frf >> 16) & 0xff)
write(RegFrfMid, (Frf >>  8) & 0xff)
write(RegFrfLsb,  Frf        & 0xff)

# Enables the +20dBm option on PA_BOOST pin.
PaDac = [0x04, 0x07]      # Can be 0x04 or 0x07. 0x07 will enables the +20dBm option on PA_BOOST pin
write(RegPaDac, PaDac[1]) # We still can choose RFO pin in RegPaConfig. Here we just enable

# Select PA_BOOST as output
PaSelect_PA_BOOST = 0b1 # Select PA_BOOST pin
PaSelect_RFO      = 0b0 # Select RFO pin
MaxPower_15dBm    = 0x7 # 15dBm = 10.8 + 0.6 * 7
OutputPower_17    = 0xF # 17    = 17 - ( 15 - OutputPower ) Use this formula since we choose PA_BOOST pin by setting PaSelect
                        # Since we enabled +20dBm option on PA_BOOST pin, 20dBm is online
OutputPower_4     = 0x2 # Given OutputPower_4 = 2, there is Pout == 4 = 17 - (15 - 2)
write(RegPaConfig, PaSelect_PA_BOOST << 7 | MaxPower_15dBm << 4 | OutputPower_4)

# Send Data
data = str(urandom.randint(100,999))+") Hello~"
print(data)

CLIENT_ADDRESS = 1
SERVER_ADDRESS = 2
header = [SERVER_ADDRESS, CLIENT_ADDRESS, 1, 0]
data = [ord(s) for s in data]
payload = header + data
write(RegFifoAddrPtr, Fifo_Bottom) # Before fill the buffer, move this point to where we told RegFifoTxBaseAddr
write(RegOpMode, Mode_STDBY)
write(RegFifo, payload)            # After writing, RegFifoAddrPtr moves to Fifo_Bottom + len(payload)
assert read(RegFifoAddrPtr) == len(payload), 'Prove me wrong'
write(RegPayloadLength, len(payload))
write(RegOpMode, Mode_TX)
