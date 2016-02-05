//
//  CommandCommandTerminal.cpp
//  StepperMotorSpeed
//
//  Created by Zakk Hoyt on 2/4/16.
//  Copyright © 2016 Zakk Hoyt. All rights reserved.
//

#include "CommandTerminal.h"

CommandTerminal::CommandTerminal() {
    
}

CommandTerminal::~CommandTerminal() {
    
}

void CommandTerminal::start(long baud) {
    Serial.begin(baud);
    Serial.flush();
}

uint16_t CommandTerminal::readSerial() {
    while (Serial.available()) {
        delay(1);
        char c = Serial.read();
        if (c == '\n') {
            parseParams();
            return numParams;
        }
        g_serialString += c;
        return 0;
    }
}

int CommandTerminal::valueForKey(String key) {
  for(int i = 0; i < 16; i++) {
    CommandTerminalParam param = params[i];
    if(param.key.equals(key)) {
      return param.value;
    }
  }
  return -1;
}

void CommandTerminal::appendParam(String cmdSet, int index) {
 
  int colonIndex = cmdSet.indexOf(':');
  String key = cmdSet.substring(0, colonIndex);
  String valueString = cmdSet.substring(colonIndex+1, cmdSet.length());
  int value = valueString.toInt();

  CommandTerminalParam param = CommandTerminalParam();
  param.key = key;
  param.value = value;
 
  params[index] = param;
  numParams = index+1;
}

void CommandTerminal::printParams() {
  Serial.println("************** command list ************");
  for(int i = 0; i < numParams; i++) {
    CommandTerminalParam param = params[i];
    Serial.print("i: "); Serial.println(i);
    Serial.print("param.key: "); Serial.println(param.key);
    Serial.print("param.value: "); Serial.println(param.value);
  }
}


void CommandTerminal::clearParams() {
  for(int i = 0; i < 16; i++) {
    CommandTerminalParam param = CommandTerminalParam();
    param.key = "";
    param.value = -1;
    params[i] = param;
  }
  numParams = 0;
}
void CommandTerminal::parseParams() {
    
    if(g_serialString.length() > 0) {
        
        clearParams();
        // Command strings will look like:
        //    x:3|y:0|r:255|g:255|b:128
        //    x:4|y:0|r:255|g:128|b:128
        //    x:5|y:0|r:234|g:188|b:164
        //    x:6|y:0|r:234|g:188|b:164
              
        // First split by '|'
        const int kMaxCommands = 16;
        int pipeIndexex[kMaxCommands] = {};

        int pipeIndex = -1;
        for(int x = 0; x < 16; x++) {
          pipeIndex = g_serialString.indexOf('|');
          if (pipeIndex > -1) {
            // get text left of index
            String cmdSet = g_serialString.substring(0, pipeIndex);
            appendParam(cmdSet, x);
      
            // Remove cmdSet from g_serialString
            String n = g_serialString.substring(pipeIndex+1);
            g_serialString = n;
          } else {
            // Last command
            appendParam(g_serialString, x);
            g_serialString = "";
            break;
          }
        }
    }
}
