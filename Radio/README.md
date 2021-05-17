### Electromagnetic radiation pattern
[![EM](http://img.youtube.com/vi/FWCN_uI5ygY/0.jpg)](https://youtu.be/FWCN_uI5ygY "EM")
### Electromagnetic spectrum 
```
        |  HF  |  VHF  |   UHF   |   SHF  |
f(MHz)  3     30      300       3k       30k
λ(m)   100    10       1        0.1      0.01
```
### Nearby FM Radio station 
WNYC-FM (93.9 MHz) is a non-profit, non-commercial, public radio station licensed to New York City. 
### Terminology
* RG: Radio Guide (Coaxial Cable)
  * RG-174/U: 174 is type number; U stands for Universal/All-purposes. This type is popular for GPS / WLAN / UHF signal
* AWG: American Wire Gauge
  * 26 AWG: 26 is the Gauge number; Higher number, smaller diameter of wire. 26 AWG = 0.405mm. 0.1339Ω/m for copper wire. 
* RF Connector:
  * MHF or U.FL: appears on my M.2 wireless NIC
  * MHF4: appears on GPS breakout
  * RP-SMA: reverse-polarity SubMiniature version A 
### Hardware
#### Dipole antenna [[Amazon](https://www.amazon.com/gp/product/B075445JDF)]
* 5cm to 13cm telescopic antenna x2
* 23cm to 1m telescopic antenna x2
* Dipole base with 60cm RG174 cable
* 3m RG173 extension cable
#### Vector network analyzer [[Amazon](https://www.amazon.com/gp/product/B07T6LXNTV)] 
* NanoVNA body [[Docu](http://nanovna.com/)]
* Calibration Kit: OPEN | SHORT | 50Ω LOAD  
![alt text](https://github.com/xg590/IoT/raw/master/Radio/calibration_kit.jpg "cal kit")
* SMA Female to Female Through Connector
* SMA Male to Male cable x 2
#### RTL-SDR [[Amazon](https://www.amazon.com/gp/product/B0129EBDS2)]
* A usb dongle and it only receive signal
### NanoVNA Calibration
* Brief summary: 1. Connect CH0; 2. Calibrate -> Reset -> Calibrate -> (Screw Open cap) Open -> (Screw Short cap) Short -> (Screw Load cap) Load -> (Keep load cap on) Isoln -> Thru -> Done <br/>
[![Cal](http://img.youtube.com/vi/QJYeFpiqY8c/0.jpg)](https://www.youtube.com/watch?v=QJYeFpiqY8c "Cal")
### Listen FM radio
* 93.9MHz target frequency -> 3.2m wavelength -> 1.6m dipole -> 0.8m antenna x2 -> use VNA to measure SWR spectrum from 50~150MHz -> adjust dipole antenna to ensure low SWR around 93.9MHz -> connect to RTL-SDR -> plug it to PC and follow RTL-SDR's [Quick Start Guide](https://www.rtl-sdr.com/rtl-sdr-quick-start-guide/) -> Listen to WNYC-FM through RTL-SDR and check the content with [online version](https://www.wnyc.org/)(4sec delay for online version than realtime FM radio).
