### Listen to FM Radio with RTL-SDR.
* WNYC-FM (93.9 MHz) is a non-profit, non-commercial, public radio station licensed to New York City. 
#### Hardware 
* Dipole antenna [[Amazon](https://www.amazon.com/gp/product/B075445JDF)]
   * 5cm to 13cm telescopic antenna x2
   * 23cm to 1m telescopic antenna x2
   * Dipole base with 60cm RG174 cable
   * 3m RG173 extension cable 
* RTL-SDR [[Amazon](https://www.amazon.com/gp/product/B0129EBDS2)]
   * A usb dongle that only receive signal from 500 kHz to 1.7 GHz. It has up to 3.2 MHz of instantaneous bandwidth (2.4 MHz stable). (HF reception below 24 MHz in direct sampling mode with reduced performance).   
* Listen FM radio
   * 93.9MHz target frequency -> 3.2m wavelength -> 1.6m dipole -> 0.8m antenna x2 -> use VNA to measure SWR spectrum from 50~150MHz -> adjust dipole antenna to ensure low SWR around 93.9MHz -> connect to RTL-SDR -> plug it to PC and follow RTL-SDR's [Quick Start Guide](https://www.rtl-sdr.com/rtl-sdr-quick-start-guide/) -> Listen to WNYC-FM through RTL-SDR and check the content with [online version](https://www.wnyc.org/) (4sec delay for online version than realtime FM radio).
#### Software (Ubuntu)
* Disable the original driver for the dongle and install the RTL-SDR driver 
```
echo 'blacklist dvb_usb_rtl28xxu' | sudo tee --append /etc/modprobe.d/blacklist-dvb_usb_rtl28xxu.conf
sudo apt install rtl-sdr
```
* Install open source software defined radio receiver
```
sudo apt install gqrx-sdr 
```
* Use Gqrx
```
1. Configure I/O devices --> Select Realtek RTL2838UHIDIR
2. Use mouse wheel to tune hardware frequency to 93.9 MHz
3. Select Mono-WFM (wideband freq modulation) mode 
```