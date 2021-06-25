### Module
* UART:
  * E32-433T30D from EByte
  * RYLR896 from REYAX
* SPI:
  * RFM95W from adafruit
* Comment:
  * One may like UART interface LoRa modules because the transmission is transparent. But their manufacturer may not want you to control the module to the maximum extent. For example, we do not know the spreading factor of E32-915T30D (Not mentioned on manual. No command to set it). E32-915T30D is SX1276-based but I cannot coordinate it with other manufacturer's SX1276-based LoRa product. Also cannot coordinate RYLR896 with other LoRa.
  * SPI interface LoRa is hard to code but more flexible. I managed to program RFM95W breakout and use it to talk to LoRa module on T-Beam.
  * Once learned how to use SPI-interface LoRa Module, I realize other LoRa development board merely bundle it on board and also use SPI interface. This is true for [Heltec WiFi LoRa 32 (V2)](../../Board/Espressif/ESP32/WIFI_LoRa_32) or [TTGO T-Beam](../../Board/Espressif/ESP32/T-Beam)
