### Data in Flash memory of ESP32
* Addr and type
  ```
  0x0000 Reserve for Secure Boot (4KB in total)
  0x1000 Second Stage Bootloader
  0x8000 Partition Table
  0x9000 First Partition
  ```
* Let's do an experiment with the example "hello_world" (Suppose ESP-IDF was installed)
  ```
  cp -r $IDF_PATH/examples/get-started/hello_world /tmp
  cd /tmp/hello_world
  idf.py set-target esp32
  idf.py build
  ```
* During the build process, partition table (3 partitions) was printed out at the very beginning. 
* You can run "idf.py partition-table" at any time to print the table.
  ``` 
  # ESP-IDF Partition Table
  # Name,    Type,  SubType,  Offset,   Size, Flags
  nvs,       data,  nvs,      0x9000,   24K,
  phy_init,  data,  phy,      0xf000,   4K,
  factory,   app,   factory,  0x10000,  1M,
  ``` 
### ESPTool
* At the end of build process, you get the following output (I removed some irrelevant info)
  ```
  Project build complete. To flash, run this command:
  esptool.py -p (PORT) erase_flash
  esptool.py -p (PORT) write_flash 0x1000  bootloader.bin      \
                                   0x8000  partition-table.bin \
                                   0x10000 hello_world.bin 
  or run 'idf.py -p (PORT) flash'
  ```
* As you can see, we will skip first 4k flash memory, flash the bootloader/part-table/application to the right places. 
* Or you can combine all binary files together
  ```
  esptool.py merge_bin -o merged.bin 0x1000  bootloader.bin      \
                                     0x8000  partition-table.bin \
                                     0x10000 hello_world.bin
  esptool.py -p (PORT) write_flash   0x0     merged.bin
  ```
### Misc 
* Enable WSL in PowerShell
  ```
  Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
  ```
* Virtual Com Port in WSL (COM34 -> /dev/ttyS34)
* Memory Type [ref](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/memory-types.html)
  * iram: Instruction RAM
  * dram: Data RAM
  * drom: data stored in flash
