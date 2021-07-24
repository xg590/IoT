# Xiaokang Guo @ 2021-07-24 
from machine import Pin 
class ROTARY():
    def __init__(self, pin_a, pin_b, reverse=False): 
        ''' 
            ### Rotary encoder driver for Raspberry Pi Pico
            * We have 4 independent events [Rising A, Falling A, Rising B, Falling B] and 4 pin states [High A, Low A, High B, Low B]
              * MicroPython identifies rising event as 8 and falling event as 4
              * Obviously, high pin state is 1 and low is 0 
              * Since we have two pins, we can shift the pin B's event identifiers to 32 and 16 
              * When two sets of identifiers combine, we have [5, 16, 8, 33, 9, 17, 4, 32] 
                * Normally  : Rising A and High B can be combined together
                * Limitation: Rising A and Low A cannot be together 
                * Given rising A, we can identify two combined events with b state as  8 and  9  
                *      falling A                                                       4 and  5
                *       rising B, we shift rising event's value to 16, then we have   32 and 33 as values for combined events
                *      falling B                                                      16 and 17 
            * Look at the waveform, we will only encounter combined event [5, 16, 8, 33] when rotates clockwisely or encounter [9, 17, 4, 32] when counter-clockwisely
            * Another observation is one combined event only succeeds another specific one 
              * 16 would only happen after 5, otherwise, it is either error or rotation direction reversing that happens
              * We now have a EED (Event Expectation Dict) and ERR [ERRor dict]
                EED = {5:16, 16:8, 8:33, 33:5, 9:17, 17:4, 4:32, 32:9}
                ERR = {5: 5, 16:5, 8: 5, 33:5, 9: 9, 17:9, 4: 9, 32:9} 
                if NewEvent == EED[OldEvent]:  # New event is as expected 
                    if   NewEvent == 33: print('CW')
                    elif NewEvent == 32: print('CCW') 
                    OldEvent = NewEvent
                else:                         # New event is unexpected, reset beginning event
                    OldEvent = ERR[NewEvent]  # We update old event because NewEvent could be 8 while OldEvent is 5
        '''
        if reverse:
            self._pin_a = Pin(pin_b, Pin.IN)  
            self._pin_b = Pin(pin_a, Pin.IN)  
        else:
            self._pin_a = Pin(pin_a, Pin.IN)  
            self._pin_b = Pin(pin_b, Pin.IN) 
        self._pin_a.irq(self._irq_handler_a, Pin.IRQ_RISING | Pin.IRQ_FALLING) 
        self._pin_b.irq(self._irq_handler_b, Pin.IRQ_RISING | Pin.IRQ_FALLING)   
        self._EED = {5:16, 16:8, 8:33, 33:5, 9:17, 17:4, 4:32, 32:9}
        self._OE  = 5
        self._ERR = {5: 5, 16:5, 8: 5, 33:5, 9: 9, 17:9, 4: 9, 32:9} 
        self.counter = 0

    def _irq_handler_a(self, pin_a):  
        _NE = self._pin_b.value() +  pin_a.irq().flags() 
        #print(_NE, self._OE)
        if self._EED[self._OE] == _NE: 
            if _NE ==  8: self.counter += 1
            self._OE = _NE
        else:
            self._OE = self._ERR[_NE]   

    def _irq_handler_b(self, pin_b):  
        _NE = self._pin_a.value() + (pin_b.irq().flags() <<  2) 
        if self._EED[self._OE] == _NE:  
            if _NE == 17: self.counter -= 1
            self._OE = _NE
        else:
            self._OE = self._ERR[_NE]
