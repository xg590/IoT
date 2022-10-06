#include<Keyboard.h>
#include<Mouse.h> 
#include<Wire.h> 

void receiveEvent(int howMany)
{  
  int buf[5] = {0};
  int i = 0; 
  while(Wire.available()) // loop through all but the last
  {    
    buf[i] = Wire.read(); 
    i++; 
  }
  
  char str[64];
  sprintf(str, "[Raw] %d,%d,%d,%d,%d", buf[0],buf[1],buf[2],buf[3],buf[4]);
  Serial.println(str);   
  // buf = ['k', 'p', 'q', '', ''] means key "q" on keyboard will be pressed
  if (buf[0]=='k') {
    switch(buf[1]) {
      case 'p': 
        Keyboard.press(  buf[2]) ;
        break;
      case 'w': 
        Keyboard.write(  buf[2]) ; 
        break;
      case 'r': 
        Keyboard.release(buf[2]) ; 
        break;
      default:
        return ;
    } 
  } else if (buf[0]=='m') {
    switch(buf[1]) {
      case 'c': 
        Mouse.click(  buf[2]) ;
        break;
      case 'm': 
        Mouse.move(   buf[2]-128, buf[3]-128, buf[4]-128) ;
        break;
      case 'p': 
        Mouse.press(  buf[2]) ;
        break;
      case 'r': 
        Mouse.release(buf[2]) ; 
        break;
      default:
        return ;
    } 
  } else {
    return ;  
  } 
}  

void setup()
{ 
  Serial.begin(115200);    
  Wire.begin(0x34);             // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event 
}

void loop() {}