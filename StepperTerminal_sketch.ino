#include "Terminal.h"

int dirpin = 2;
int steppin = 3;

Terminal term = Terminal();

void setup()
{
    pinMode(dirpin, OUTPUT);
    pinMode(steppin, OUTPUT);
    term.start(115200); 
}
void loop()
{
  uint16_t numCommands = term.readSerial();
  if(numCommands > 0) {
    // s:1000|dir:1|del:1000
    // s:5000|dir:1|del:75
    // s:5000|dir:0|del:75
    uint16_t steps = term.valueForKey("s");
    uint16_t dir = term.valueForKey("dir");
    uint16_t del = term.valueForKey("del");
    
    if(steps == -1 || dir == -1 || del == -1) {
      Serial.println("missing commands");    
    } else {
      digitalWrite(dirpin, dir);     // Set the direction.
      delay(100);
 
      for (uint16_t i = 0; i<steps; i++)       // Iterate for 4000 microsteps.
      {
          digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
          digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
          delayMicroseconds(del);      // This delay time is close to top speed for this
      }                              // particular motor. Any faster the motor stalls. 
    }
  }
}
