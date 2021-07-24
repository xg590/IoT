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
