#include "CommandTerminal.h"

int dirpin = 2;
int steppin = 3;

CommandTerminal term = CommandTerminal();

void setup()
{
    pinMode(dirpin, OUTPUT);
    pinMode(steppin, OUTPUT);
    term.start(115200); 
}
void loop()
{
  if(term.readSerial() > 0) {
 
    // s:1000|dir:1|del:1000
    // s:5000|dir:1|del:75
    // s:5000|dir:0|del:75
    uint16_t steps = term.valueForKey("s");
    uint16_t dir = term.valueForKey("dir");
    uint16_t del = term.valueForKey("del");
    
    if(steps == -1 || dir == -1 || del == -1) {
      Serial.println("missing commands");    
    } else {
      digitalWrite(dirpin, dir);     
      delay(100);
      for (uint16_t i = 0; i<steps; i++)       
      {
        digitalWrite(steppin, LOW);  
        digitalWrite(steppin, HIGH); 
        delayMicroseconds(del);      
      }
    }
  }
}
