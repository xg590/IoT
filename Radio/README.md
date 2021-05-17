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
#### Antenna
* 5cm to 13cm telescopic antenna x2
* 23cm to 1m telescopic antenna x2
* Dipole base with 60cm RG174 cable
* 3m RG173 extension cable
#### Vector Network analyzer 
[AURSINC NanoVNA Vector Network Analyzer](https://www.amazon.com/gp/product/B07T6LXNTV)
* NanoVNA body [[Docu](http://nanovna.com/)]
* Calibration Kit: OPEN | SHORT | 50Ω LOAD  
![alt text](https://github.com/xg590/IoT/raw/master/Radio/calibration_kit.jpg "cal kit")
* SMA Female to Female Through Connector
* SMA Male to Male cable x 2 
### NanoVNA
* Calibration<br/>
[![Cal](http://img.youtube.com/vi/QJYeFpiqY8c/0.jpg)](https://www.youtube.com/watch?v=QJYeFpiqY8c "Cal")
  * Brief summary: 1. Connect CH0; 2. Calibrate -> Reset -> Calibrate -> (Screw Open cap) Open -> (Screw Short cap) Short -> (Screw Load cap) Load -> (Keep load cap on) Isoln -> Thru -> Done
* Measure the frequency characteristics of reflected power and passing power of a high frequency network. 
