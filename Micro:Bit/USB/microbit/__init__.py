import sys, serial  
from . import repl, api

try:
    from . import config
    PORT = config.PORT
except ImportError:
    PORT = '/dev/ttyACM0' # default port
    
class SerialPortUnavailable(Exception):
    def __init__(self, PORT):
        self.PORT=PORT
    def __str__(self):
        return f"Port '{self.PORT}' is unavailable, specify another one please~" 

try:
    s = serial.Serial(port     = PORT, 
                      baudrate = 115200, 
                      parity   = serial.PARITY_NONE, 
                      stopbits = serial.STOPBITS_ONE, 
                      timeout  = 0)
except Exception:
    raise SerialPortUnavailable(PORT)
    
repl = repl.REPL(s)
repl.to_raw()
sys.modules[__name__] = api.MicroBit(repl)
