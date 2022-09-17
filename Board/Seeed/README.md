## SAMD21
* 3.3V GPIOs
* Power from VIN/5V PINs  
* SERCOM: None
* samd21 has USB interface
### Arduino CLI
``` 
arduino-cli core  install seeeduino:samd --additional-urls https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
arduino-cli board listall
alias xiao='arduino-cli compile . --fqbn Seeeduino:samd:seeed_XIAO_m0 && arduino-cli upload . --fqbn Seeeduino:samd:seeed_XIAO_m0 -p'
```
### Pinout
<img style="height:400px;weight:500px" src="samd21.jpg"><img>
