### Hall Effect Based
#### Hardware 
* Encoder ([Amazon](https://www.amazon.com/dp/B07RTN8F58/))
  * Type: AB bidirectional incremental magnetic Hall encoder
  * Line speed: 12 pulse per revolution)
  * Supply voltage: DC3.3/5V
  * Basic function: comes with pull-up shaping resistor, direct connection of single chip microcomputer
  * Interface type: PH2.0 with connecting cable
  * Output signal type: square wave AB phase
  * Response frequency: 100KH 
  * Magnetic ring trigger series: 24 poles (12 pairs poles)
</br><img src="pinout.jpg" height="400px" width="400px"></img> 
#### Waveform
</br><img src="waveform.png" height="150px" width="400px"></img>
#### Coding for [MicroPython](../../Misc/MicroPython/driver/rotary.py) on Raspberry Pi Pico
* We have 4 independent events [Rising A, Falling A, Rising B, Falling B] and 4 pin states [High A, Low A, High B, Low B]
  * MicroPython identifies rising event as 8 and falling event as 4
  * Obviously, high pin state is 1 and low is 0 
  * Since we have two pins, we can shift the pin B's event identifiers to 32 and 16 
  * When two sets of identifiers combine, we have [5, 16, 8, 33, 9, 17, 4, 32] 
    * Rising A and High B can be combined together
    * But Rising A and Low A cannot be together 
    * Given
      * Rising  A, Low or High B =  8 or  9  
      * Falling A, Low or High B =  4 or  5
      * Rising  B, Low or High B = 32 or 33 if we shift rising event's value by 8 << 2
      * Falling B  Low or High B = 16 or 17                                     4 << 2
* Look at the waveform, we will only encounter combined event [5, 16, 8, 33] when rotates clockwisely or encounter [9, 17, 4, 32] when counter-clockwisely
* Another observation is one combined event only succeeds another specific one 
  * 16 would only happen after 5, otherwise, it is either error or rotation direction reversing that happens
  * We now have a EED (Event Expectation Dict) and ERR [ERRor dict]
  ```
    EED = {5:16, 16:8, 8:33, 33:5, 9:17, 17:4, 4:32, 32:9}
    ERR = {5: 5, 16:5, 8: 5, 33:5, 9: 9, 17:9, 4: 9, 32:9} 
    if NewEvent == EED[OldEvent]:  # New event is as expected 
        if   NewEvent ==  8: print('CW')
        elif NewEvent == 17: print('CCW') 
        OldEvent = NewEvent
    else:                         # New event is unexpected, reset beginning event
        OldEvent = ERR[NewEvent]  # We update old event because NewEvent could be 8 while OldEvent is 5
  ``` 
