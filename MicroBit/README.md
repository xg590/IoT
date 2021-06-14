### Use Arduino IDE to play with BBC Micro:bit
```
arduino-cli core update-index --additional-urls https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json
arduino-cli core search       --additional-urls https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json
arduino-cli core install sandeepmistry:nRF5 --additional-urls https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json
arduino-cli board listall|grep micro # Now we know the FQBN sandeepmistry:nRF5:BBCmicrobit
```
### Choose One Interface to Communicate with Micro:Bit<br>
USB / Bluetooth
