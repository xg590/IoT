import pygame # https://stackoverflow.com/a/46558178 
# Another example @ # https://www.pygame.org/docs/ref/joystick.html
clock = pygame.time.Clock()
pygame.init()  
joystick = pygame.joystick.Joystick(0)
print(f"Joystick name: {joystick.get_name()}") 
btnMap = {0:'A', 1:'B', 2:'X', 3:'Y', 
          4:'LB', 5:'RB', # Left/Right shoulder button 
          6:'V', # View 
          7:'M', # Menu
          8:'LS', 9:'RS' # Left/Right stick in
         }
xMap = {0:'X', 1:'Y', 2:'RX', 3:'RY', 4:'LT', 5:'RT'}
while True:
    '''
    Logic: loop while listen joystick events. 
           At the beginning of each new loop, 
           get event happended during the last loop.
    ''' 
    events = pygame.event.get()
    for event in events:
        if event.type == pygame.JOYAXISMOTION:
            print(xMap[event.axis], event.value)
        #elif event.type == pygame.JOYBALLMOTION:
        #    print(event.dict, event.joy, event.ball, event.rel)
        elif event.type == pygame.JOYBUTTONDOWN:
            print(btnMap[event.button], 'pressed')
        elif event.type == pygame.JOYBUTTONUP:
            print(btnMap[event.button], 'released')
        elif event.type == pygame.JOYHATMOTION:
            X, Y = event.value
            print(event.hat, X, Y) 
        elif event.type == pygame.JOYDEVICEREMOVED: # pygame.JOYDEVICEADDED:
            print("Joystick removed.")  
            break
    else:
        clock.tick(10) # ensure 10 loops per second
        continue
    print('Stop getting any new event~')
    break