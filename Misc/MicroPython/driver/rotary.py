# Xiaokang Guo @ 2021-07-24 
from machine import Pin 
class ROTARY():
    def __init__(self, pin_a, pin_b, reverse=False): 
        if reverse:
            self._pin_a = Pin(pin_b, Pin.IN)  
            self._pin_b = Pin(pin_a, Pin.IN)  
        else:
            self._pin_a = Pin(pin_a, Pin.IN)  
            self._pin_b = Pin(pin_b, Pin.IN) 
        self._pin_a.irq(self._irq_handler_a, Pin.IRQ_RISING) 
        self._pin_b.irq(self._irq_handler_b, Pin.IRQ_RISING)   
        self._EED = {8:5, 5:8, 9:4, 4:9}
        self._OE  =  8
        self._ERR = {8:5, 5:5, 9:9, 4:9}
        self.counter = 0

    def _irq_handler_a(self, pin_a): # [8, 9]
        _NE = self._pin_b.value() +  pin_a.irq().flags()    
        #print('a',_NE)
        if self._EED[self._OE] == _NE:  
            if _NE == 8: 
                self.counter += 1
                #print(self.counter, 'a counter')
            self._OE = _NE
        else:
            self._OE = self._ERR[_NE]   

    def _irq_handler_b(self, pin_b): # [4, 5]
        _NE = self._pin_a.value() + (pin_b.irq().flags() >> 1)  
        #print('b',_NE)
        if self._EED[self._OE] == _NE:  
            if _NE == 4: 
                self.counter -= 1
                #print(self.counter, 'b counter')
            self._OE = _NE
        else:
            self._OE = self._ERR[_NE]

