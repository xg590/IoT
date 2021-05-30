### How radio wave transmit
* Electromagnetic radiation pattern<br/>
[![EM](http://img.youtube.com/vi/FWCN_uI5ygY/0.jpg)](https://youtu.be/FWCN_uI5ygY "EM")
### How is band devided 
* Electromagnetic spectrum 
```
        |  HF  |  VHF  |   UHF   |   SHF  |
f(MHz)  3     30      300       3k       30k
λ(m)   100    10       1        0.1      0.01
``` 
### Terminology
* RG: Radio Guide (Coaxial Cable)
  * RG-174/U: 174 is type number; U stands for Universal/All-purposes. This type is popular for GPS / WLAN / UHF signal
* AWG: American Wire Gauge
  * 26 AWG: 26 is the Gauge number; Higher number, smaller diameter of wire. 26 AWG = 0.405mm. 0.1339Ω/m for copper wire. 
* RF Connector:
  * MHF or U.FL: appears on my M.2 wireless NIC
  * MHF4: appears on GPS breakout
  * RP-SMA: reverse-polarity SubMiniature version A  
#### Vector network analyzer [[Amazon](https://www.amazon.com/gp/product/B07T6LXNTV)] 
* NanoVNA body [[Docu](http://nanovna.com/)]
* Calibration Kit: OPEN | SHORT | 50Ω LOAD  
![alt text](https://github.com/xg590/IoT/raw/master/Radio/calibration_kit.jpg "cal kit")
* SMA Female to Female Through Connector
* SMA Male to Male cable x 2 
##### Calibration
* Brief summary: 1. Connect CH0; 2. Calibrate -> Reset -> Calibrate -> (Screw Open cap) Open -> (Screw Short cap) Short -> (Screw Load cap) Load -> (Keep load cap on) Isoln -> Thru -> Done <br/>
##### Measure SWR
[![SWR](http://img.youtube.com/vi/QJYeFpiqY8c/0.jpg)](https://www.youtube.com/watch?v=QJYeFpiqY8c "SWR")
##### Measure Coax Loss
[![Loss](http://img.youtube.com/vi/mU71rGUKlBI/0.jpg)](https://www.youtube.com/watch?v=mU71rGUKlBI "Loss")
