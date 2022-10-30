* Enable WSL in PowerShell
```
Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
```
* Virtual Com Port in WSL (COM34 -> /dev/ttyS34)
* Binary data can be written to the ESP’s flash chip via the serial <i><b>write_flash</b></i> command: 
* Multiple flash addresses and file names can be given on the same command line:
```
idf.py -p (PORT) flash
```
Or:
```
esptool.py 
  -p (PORT) 
  -b 460800 
  --before default_reset 
  --after hard_reset 
  --chip esp32  
  write_flash 
  --flash_mode dio 
  --flash_size detect 
  --flash_freq 40m 
  0x1000  build/bootloader/bootloader.bin 
  0x8000  build/partition_table/partition-table.bin 
  0x10000 build/blink.bin
``` 