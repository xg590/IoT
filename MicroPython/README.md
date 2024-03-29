## Why use MicroPython
* Python is more user-friendly than C/C++
* Board can be remotely controlled via WebREPL in a real-time manner: [Here](ESP8266_WebREPL.ipynb) is a Python client.
## Concept to learn before flashing MicroPython to boards 
  * ROM: Read-only memory. Everything that would not lost after power off the device stays here.
  * Firmware: Codes in the rom.
  * Bootloader: 
    * First part of firmware. 
    * First execute during power-up sequence (remain dormant thereafter)
    * Responsible for guide rest of firmware. 
  * esptool: Tool that talks to Espressif boards' bootloader.
    * By talking to bootloader, we can add or remove more codes in the rom. For example, operating system is "more codes"
    * Change Linux user's group id so we gain the right to talking with bootloader.
    ``` 
      sudo usermod -aG dialout $USER
      newgrp dialout
    ```
  * Flash: Adding more codes is called flashing because we are storing codes in flash memory. 
## Flashing 
<details>
  <summary> To Raspberry Pi Pico [W] (Hello world)</summary>
  
  1. Connect Pico to PC via USB cable.
  2. A new removable media appears as RPI-RP2
  3. There is a pre-compiled micropython fireware, a downloadable [UF2 file](https://www.raspberrypi.com/documentation/microcontrollers/micropython.html).
  4. Download the UF2 file into RPI-RP2.
  5. Pico will restart automatically then boot into micropython.
  6. A new serial port is now avaiable at /dev/ttyACM0
  7. Use screen to play with micropython (ported Python3.4)
  ```
  # screen /dev/ttyACM0 115200
  >>> import sys
  >>> print(sys.version)
  3.4.0
  ```
  8. Pico's MicroPython [Docs](https://docs.micropython.org/en/latest/rp2/quickref.html)
</details>
 
<details>
  <summary> To ESP32 </summary>
  
 * Remove "more codes" (For some special board like <i>Heltec Wireless Stick Lite</i>, One [has to](https://github.com/espressif/esptool/wiki/ESP32-Boot-Mode-Selection) bring down GPIO0 to flash the board)
  ```
  pip install esptool
  esptool.py --port /dev/ttyUSB0 erase_flash                         # Erase flash. Only bootload left in ROM
  ```
  * Add "more codes" which is MicroPython
  ```
  # https://micropython.org/download/esp32/
  wget https://micropython.org/resources/firmware/esp32-20210902-v1.17.bin
  esptool.py --port /dev/ttyUSB0 --chip esp32 write_flash -z 0x1000 esp32-20210902-v1.17.bin
  ```
  * Hello World
  ```
  $ screen /dev/ttyUSB0 115200
  >>> import sys
  >>> print(sys.version)
  3.4.0
  ```
</details>

<details>
  <summary> To ESP8266 </summary>
  
  * Flash MicroPython
  ```shell
  esptool.py --port /dev/ttyUSB0               erase_flash
  esptool.py --port /dev/ttyUSB0 --baud 460800 write_flash --flash_size=detect 0 esp8266-20210902-v1.17.bin
  ```
</details> 

## Use MicroPython

<details> 
  <summary> All-in-One script: Flash ESP8266 and Enable WebREPL </summary>  
   
  ```shell 
  wget https://micropython.org/resources/firmware/esp8266-20220618-v1.19.1.bin
  bash flash_esp.sh --model esp8266 --port /dev/ttyUSB0 --bin esp8266-20220618-v1.19.1.bin --hostname myESP8266 --webrepl-passwd 123456 --ssid xxx --wifi-passwd xxx
  ```
</details>

<details> 
  <summary> Access ESP board Remotely (WebSocket) </summary>  
 
  * Setup [WebREPL](https://learn.adafruit.com/micropython-basics-esp8266-webrepl/access-webrepl)
    1. Flash MicroPython (>1.8.6)
    2. Use Serial Communication
    ```
    screen /dev/ttyUSB0 115200
    import webrepl_setup
    # >>> E (Press Shift + E Keys)
    # >>> 123456 (As WebREPL password)
    ``` 
    3. Visit https://micropython.org/webrepl/ so one can connect to ESP board after step 4.
    4. Connect MicroPython's WiFi access point so the board can be accessed remotely. 
  * Access WebREPL when ESP board is in Station Mode 
    * Run following code via Serial Com to join the board to a WiFi network and it will be accessiable via WebSocket automatically even after reboot. 
    ```
    import network 
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.config(dhcp_hostname="IwantThisHostname") 
    wlan.connect('ssid', 'password')
    wlan.ifconfig()
    # ('192.168.x.128', '255.255.255.0', '192.168.x.x', '8.8.8.8')
    ```
  * [Here](ESP8266_WebREPL.ipynb) is a Python client
  * All in One
    ```shell
    esptool.py --port /dev/ttyUSB0               erase_flash
    esptool.py --port /dev/ttyUSB0 --baud 460800 write_flash --flash_size=detect 0 esp8266-20210902-v1.17.bin 
    
    screen -d -m -S esp8266 /dev/ttyUSB0 115200  
    screen -S esp8266 -X stuff "^M"
    screen -S esp8266 -X stuff "import webrepl_setup ^M"
    screen -S esp8266 -X stuff "E^M"
    screen -S esp8266 -X stuff "123456^M"
    screen -S esp8266 -X stuff "123456^M"
    screen -S esp8266 -X stuff "y^M" 
    screen -S esp8266 -X stuff "^M"
    screen -S esp8266 -X stuff "import network ^M"
    screen -S esp8266 -X stuff "wlan = network.WLAN(network.STA_IF) ^M"
    screen -S esp8266 -X stuff "wlan.active(True) ^M"
    screen -S esp8266 -X stuff "wlan.config(dhcp_hostname='IRreceiver') ^M"
    screen -S esp8266 -X stuff "wlan.connect('SSID', 'PASSWORD') ^M"
    screen -S esp8266 -X stuff "wlan.ifconfig() ^M" 
    screen -S esp8266 -X quit  
    ```
 
</details>

<details> 
  <summary> Develop on a remote device --- esptool </summary>  

  * Caution: We are going to run esp_rfc2217_server.py and it listens tcp/4000 on 0.0.0.0
  * [Ref](https://docs.espressif.com/projects/esptool/en/latest/esp32/esptool/remote-serial-ports.html#raw-sockets)
  * An ESP32 is attached to a remote raspberry "piMachine" 
  * The remote PiMachine has pySerial installed on it.
  * Run on the client
  ``` 
  wget https://raw.githubusercontent.com/espressif/esptool/master/esp_rfc2217_server.py
  scp piMachine esp_rfc2217_server.py
  # Start a remote screen session on pi 
  ssh piMachine "screen -S esp_rfc2217_server -d -m -s /bin/bash"
  # Run esp_rfc2217_server in remote screen session so that piMachine:4000 is listening.
  ssh piMachine "screen -S esp_rfc2217_server -X stuff \"python3 esp_rfc2217_server.py -p 4000 /dev/ttyUSB0 ^M\"" 
  esptool.py --port rfc2217://piMachine:4000?ign_set_control --chip esp32 erase_flash
  ```
  
</details>

<details> 
  <summary> Use VScode as IDE </summary>  
  
  1. Install [VScode](https://code.visualstudio.com/)
  2. Search <i>Pico-Go</i> in extensions marketplace
  3. Create a folder so we can configure Pico-Go
  4. In Vscode's <i>Command Palette</i>, run "Pico-Go > Global settings".
     * Change global settings' pico-go.json 
     ```
     { 
       "auto_connect": false
     }
     ```
  5. In Vscode's <i>Command Palette</i>, run "Pico-Go > configurate project"
     * Add new key and value in project's pico-go.json 
     ```
     {
       "sync_folder": "",
       "open_on_start": true,  
       "manual_com_device": "/dev/ttyACM0"
     }
     ```
  6. Restart VScode
</details>  
 
<details> 
  <summary> Run a script after boot</summary> 
  
  * Just name a script main.py instead of test.py and use [rshell](https://github.com/dhylands/rshell) to upload
  * When the board reboot, the script will run. 
</details>  

<details> 
  <summary> Paste code into REPL in screen (Better to use VScode) </summary>  
  
  * [2.3.5. Paste mode](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html#paste-mode)
  * [2.3.6. Other control commands](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html#other-control-commands)
</details> 

<details> 
  <summary> Use jupyter-notebook instead of screen (Better to use VScode) </summary>  
  
  * Add MicroPython [Kernel](https://github.com/goatchurchprime/jupyter_micropython_kernel)
  ```
  pip install jupyter_micropython_kernel
  python -m jupyter_micropython_kernel.install
  ``` 
</details> 

<details> 
  <summary> Use rshell for file upload (Better to use VScode) </summary> 
  
  1. Prepare a lib on Desktop
  ```shell
  cat << EOF > test.py
  def hello_world():
    print("Hello World!")
  EOF
  ```
  2. Use [rshell](https://github.com/dhylands/rshell) to transfer file
  ```shell
  rshell -p /dev/ttyACM0 cp test.py /pyboard
  ```
  3. Import lib
  ```
  >>> import test
  >>> test.hello_world()
  Hello World!
  ```
</details> 

## Troubleshooting
* ENOMEM: Not enough memory
## Cheat sheet
* create output pin on GPIO14 
``` 
from time import sleep 
from machine import Pin  
p = Pin(14, Pin.OUT, value=0)  
p.value(1)   
```
