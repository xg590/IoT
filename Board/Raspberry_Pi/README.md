## Raspberry Pi ZW(Zero Wireless)/3A/3B/4A
* All the same across boards</br>
* GPIO pins operated at 3.3V
### Setup
* [Home WiFi or Enterprise Network like NYU-EDU](ZW_Setup.md)
### Pinout
<img src="Raspberry_Pi_Pinout.png"></img>
## Raspberry Pi Pico
### Pin
```
GPIO   : 3.3V
3V3    : 300mA max current draw.
VBUS   : 5V Micro-USB input
VSYS   : 1.8~5.5V input for on-board transformer(SMPS)
GPIO25 : On-board LED
3V3_EN : Pulled-up to VSYS via a 100K resistor.
         Disable VSYS input by pull this pin down.
         In other words, transformer (Pico) will not work if this pin connected to GND.
SPI RX : MISO
SPI TX : MOSI
```
### Electronics
* Dual-core cortex M0+ at up to 133MHz (On-board [PLL](https://www.embedded.com/demystifying-phase-locked-loops/) can be asked to vary the clock frequency)
* 2MByte Flash
* 264kByte SRAM
### Pinout
* SPIx_TX = MOSI
* SPIx_RX = MISO
<img src="Pico_Pinout.png"></img>
