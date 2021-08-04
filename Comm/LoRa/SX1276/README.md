### Materials
* Raspberry Pi Pico (sender)
* RFM95W
* Heltec WiFi LoRa 32 V2 (receiver)
### Pin Scheme
* Raspberry Pi Pico
```
# RFM95W       Pico GPIO
MISO_Pin     = 16
CS_Pin       = 17
SCK_Pin      = 18
MOSI_Pin     = 19
G0_Pin       = 20 # DIO0_Pin
RST_Pin      = 21
EN_Pin       = 22
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
### SX1276 Datasheet
#### 4.1.2. LoRa ® Digital Interface
* The LoRa ® modem comprises three types of digital interface,
  * static configuration registers
  * status registers
  * a 256-byte user-defined FIFO data buffer
#### Data Transmission Sequence (Figure 9)
1. Change to Standby mode
2. Fill FIFO data buffer
3. Change to Tx mode
4. Wait for TxDone IRQ
5. Fall back to Standby mode automatically
#### Single Mode Data Reception Sequence (Figure 10)
* Tx is periodical and imminent.
1. Change to Standby mode
2. Change to Rx Single mode
3. Wait for RxTimeout or RxDone IRQs
4. RxTimeout and fall back to Standby mode automatically.
* Or
4. RxDone
5. Wait for PayloadCrcError IRQ
6. Read then fall back to Standby mode automatically. (The FIFO data buffer is safe since it can only be cleared after another Rx mode or Sleep mode requests)
#### Continous Mode Data Reception Sequence (Figure 10)
1. Change to Standby mode
2. Change to Rx Continuous mode
3. Wait for RxDone IRQs
4. Wait for PayloadCrcError IRQ
5. Read then go back to step 3
#### Jargon
* {LowFreq: Bands 2&3, HF: Band 1}, {Band 1: ~915MHz, Band 2: ~433MHz, Band 3: ~150MHz}
* RFI: RF Input
* RFO: RF Output
* Three amplifiers: RFO_LF, RFO_HF, PA_BOOST
* AFC: automatic frequency correction
* PA: Power Amplifier
* PA_HP: High Power
* PA_HF and PA_LF are high efficiency amplifiers
* RFOP: RF output power
