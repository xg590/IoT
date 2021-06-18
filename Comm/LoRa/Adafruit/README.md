### RFM95W 
* SX1276 LoRa based module with 3.3V SPI interface
* Up tp 100 mW Power Output Capability
### Pinout
* Have to checkout the scheme to know wich pin mapping between the module and SX1276<br/>
<img src="RFM95W_schem.png"></img>
*  VIN: 3.3~6VDC in. ensure 150mA current to Tx
*   EN: Pull down the enable pin to DISABLE the module
*   G0: DIO0. IRQ, interrupt request. 3.3V.
* G1~5:DIO1~5
### Wiring
```
RFM95W     WeMos_D1_mini 
    G0 <-> D2
   SCK <-> D5
  MISO <-> D6
  MOSI <-> D7
    CS <-> D8
   RST <-> D1         
```
### Coding
* Using RadioLib
* [Tx example](RFM95W)
