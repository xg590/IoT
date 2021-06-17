### Item
* WeiMeet RFP30N06LE 30A 60V N-Channel Enhancement-mode Power Mosfet TO-220 ESD Rated for Arduino ([Amazon](https://www.amazon.com/gp/product/B07CTF1JVD))
### Diagram 
<img width="400" height="200" src="https://raw.githubusercontent.com/xg590/IoT/master/MOSFET/diagram.svg"></img>
* S: Source terminal
* D: Drain terminal
* G: Gate terminal
* V<sub>DS</sub>: Voltage between D and S terminals
* V<sub>GS</sub>: Voltage between G and S terminals
* V<sub>TH</sub>: Threshold Voltage
* R<sub>GS</sub>: There should be a resistor to pull the level of gate down.[see note 1]
### Behavior in circuit
* V<sub>DS</sub> > 0 (open circuit) when V<sub>GS</sub> <  V<sub>TH</sub>
* V<sub>DS</sub> = 0 (close circuit) when V<sub>GS</sub> >  V<sub>TH</sub>
### Datasheet
https://github.com/xg590/IoT/blob/master/MOSFET/RFP30N06LE.pdf
### Tutorial from <i>Bald Engineer</i>:
[![Audi R8](http://img.youtube.com/vi/GrvvkYTW_0k/0.jpg)](https://www.youtube.com/watch?v=GrvvkYTW_0k "Audi R8")
#### Footnote
1. It creates a known level on the gate in the absence of an input signal. The gate is a high impedance node, and when left floating, can assume any voltage due to parasitic coupling, noise and other factors. The resistor prevents the bad stuff from affecting your circuit. [Credit to [Papabravo](https://forum.allaboutcircuits.com/threads/what-is-the-purpose-of-the-resistor-between-the-gate-and-source-of-an-n-fet.93315/)]
