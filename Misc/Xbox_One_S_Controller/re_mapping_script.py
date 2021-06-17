### Under Development
from IPython.display import clear_output 
from evdev import InputDevice, ecodes 
device = InputDevice('/dev/input/event0')  

def clear_buffer():
    while True:
        event = device.read_one()
        if not event:
            break

import signal

def handler(signum, frame): 
    raise TimeoutError
    
def button_analyzer(timeout=3): # how many times can you press the button in 2 seconds once you begin pressing 
    clear_buffer()
    count = 0 
    code = 0
    signal.signal(signal.SIGALRM, handler)
    try:
        for event in device.read_loop():  
            if event.type == ecodes.EV_KEY and event.value == 1:
                code = event.code 
                if count == 0:
                    count = 1
                    signal.alarm(timeout)
                else:
                    count += 1 
    except TimeoutError:
        pass
    signal.alarm(0)
    return count, code 

flag = True
while True:
    clear_output()
    if flag: print('Please press a button you want to bind one time~!') 
    else: print('Please press a new button you want to bind one time~!')  
    _, code_num = button_analyzer() 
    clear_output()
    if flag: print(f"We are going to bind the button you pressed to a name called '{code2name[code_num]}'\n\nThe choice you have:\nIf the name is OK, you can press the button once more to begin next binding\nIf something went wrong, you can press the button twice more to input a name manually\nIf you press the button thrice, you can input a name manually but binding would stop after then.\nIf you press more than thrice, binding would stop immediately") 
    else: print(f"Do you like the name '{code2name[code_num]} for newly pressed button?'\n\nHint: Once for OK, twice for customizing the name, thrice for customization and exit, more than thrice for exit instantly")
    flag = False
    count, _ = button_analyzer()
    if count == 1:
        pass
    elif count == 2: 
        code2name[code_num] = input("The name you like for the button we are binding\n")
    elif count == 3: 
        code2name[code_num] = input("The name you like for the button we are binding\n")
        flag = True
    else:
        clear_output()
        print('Key Binding process finished ~')
        break 
    if flag: break

def axis_recorder(timeout=3): # how many times can you press the button in 2 seconds once you begin pressing 
    clear_buffer()
    flag = True 
    data = []
    signal.signal(signal.SIGALRM, handler)
    try:
        for event in device.read_loop():  
            if event.type == ecodes.EV_ABS: 
                value = event.value
                if value > 1024 and value < 60000: continue
                if flag:
                    flag = False
                    signal.alarm(timeout) 
                data.append([event.code, value])
            elif event.type == ecodes.EV_KEY:
                signal.alarm(0)
                return None
    except TimeoutError:
        pass
    signal.alarm(0)
    return data  

def axis_analyser(record):
    joystick = len([j for _, j in record if j> 60000]) # joystick ranges from 0~65535
    trigger = len([j for _, j in record if j > 2 and j < 1024]) # trigger ranges from 0~1023
    hat = len([j for _, j in record if j in [-1,0,1]]) # hat in [-1, 0, 1]
    if joystick:
        sequence = [] 
        [ sequence.append(k) for k in [i for i, j in record if j > 60000] if k not in sequence] 
        return 'joystick', sequence[:2]
    elif trigger:
        return 'trigger', [i for i, j in record if j > 2 and j < 1024][:2]
    elif hat:
        sequence = [] 
        [ sequence.append(k) for k in [i for i, j in record if j in [-1,0,1]] if k not in sequence]
        return 'hat', sequence[:2]

while True:
    print("Now, let's bind axes ~") 
    print("If you are going to bind joystick, please tweak it to 12 O'clock position first and then rotate the joystick clockwise.") 
    print("If you are going to bind trigger, simply pull it.") 
    print("If you are going to bind hat, please press the up button and then the right") 
    print("If you press any botton, binding would stop immediately please press the up button and then the right")  
    record = axis_recorder()
    if not record:
        break
    type_, sequence = axis_analyser(record)
    clear_output()
    if type_ == 'joystick':
        print(f"You just rotated a joystick and the axes associated with it are '{code2name[sequence[0]]}' and '{code2name[sequence[1]]}'.")
    elif type_ == 'trigger':
        print(f"You just pulled a trigger named '{code2name[sequence[0]]}'")
        sequence.pop()
    elif type_ == 'hat':
        print(f"You just rotated a hat and the axes associated with it are '{code2name[sequence[0]]}' and '{code2name[sequence[1]]}'.")
    print("If the name is OK, you can press one button once to begin next binding\nIf something went wrong, you can press the button twice to input a name manually\nIf you want stop binding, you can press the button more than twice")
    count, _ = button_analyzer()
    if count == 1: 
        pass
    elif count == 2: 
        for code_num in sequence:
            code2name[code_num] = input(f"Enter a new name for the so-called button '{code2name[code_num]}'") 
    else:
        clear_output()
        print('Axis Binding process finished')
        break   
    clear_output()
