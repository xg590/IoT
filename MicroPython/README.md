## Concept
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
## Add MicroPython 
<details>
  <summary> Add to Raspberry Pi Pico (Hello world)</summary>
  
  1. Connect Pico to PC via USB cable.
  2. A new removable media appears as RPI-RP2
  3. There is a pre-compiled micropython fireware, a downloadable [UF2 file](https://www.raspberrypi.org/documentation/rp2040/getting-started/#getting-started-with-micropython).
  4. Download the UF2 file into RPI-RP2.
  5. Pico will restart automatically then boot into micropython.
  6. A new serial port is now avaiable at /dev/ttyACM0
  7. Use screen to play with micropython (ported Python3.4)
  ```
  $ screen /dev/ttyACM0 115200
  >>> import sys
  >>> print(sys.version)
  3.4.0
  ```
  8. Pico's MicroPython [Docs](https://docs.micropython.org/en/latest/rp2/quickref.html)
</details>
 
<details>
  <summary> Add to ESP32 </summary>
  
  * Remove "more codes"
  ```
  pip install esptool
  .local/bin/esptool.py --port /dev/ttyUSB0              erase_flash # Erase flash. Only bootload left in ROM
  ```
  * Add "more codes" which is MicroPython
  ```
  # https://micropython.org/download/esp32/
  wget https://micropython.org/resources/firmware/esp32-20210623-v1.16.bin
  .local/bin/esptool.py --port /dev/ttyUSB0 --chip esp32 write_flash -z 0x1000 esp32-20210623-v1.16.bin
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
  <summary> Add to ESP8266 </summary>
  
  * Flash MicroPython
  ```shell
  esptool.py --port /dev/ttyUSB0 --baud 460800 write_flash --flash_size=detect 0 esp8266-20210618-v1.16.bin
  ```
</details> 

## Use MicroPython
<details> 
  <summary> Use IDE </summary>  
  
  1. Install [VScode](https://code.visualstudio.com/)
  2. Search <i>Pico-Go</i> in extensions marketplace
  3. Create a folder so we can configure Pico-Go
  4. In Vscode's <i>Command Palette</i>, run "Pico-Go > Global settings".
    * change auto_connect's value from true to false in global settings' pico-go.json 
  5. In Vscode's <i>Command Palette</i>, run "Pico-Go > configurate project"
  6. Add new key and value in project's pico-go.json 
  ```
  {
    "sync_folder": "",
    "open_on_start": true,  
	  "manual_com_device": "/dev/ttyACM0"
  }
  ```
</details> 

<details> 
  <summary> Paste code into REPL in screen </summary>  
  
  * [2.3.5. Paste mode](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html#paste-mode)
  * [2.3.6. Other control commands](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html#other-control-commands)
</details> 

<details> 
  <summary> Use jupyter-notebook instead of screen </summary>  
  
  * Add MicroPython [Kernel](https://github.com/goatchurchprime/jupyter_micropython_kernel)
  ```
  pip install jupyter_micropython_kernel
  python -m jupyter_micropython_kernel.install
  ``` 
</details> 

<details> 
  <summary> Use rshell for file upload </summary> 
  
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
 
<details> 
  <summary> Boot into running a script </summary> 
  
  * Just name a script main.py instead of test.py and use [rshell](https://github.com/dhylands/rshell) to upload
  * When the board reboot, the script will run. 
</details>  

## Troubleshooting
* ENOMEM: Not enough memory
