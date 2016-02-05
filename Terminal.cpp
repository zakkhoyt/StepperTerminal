//
//  Terminal.cpp
//  StepperMotorSpeed
//
//  Created by Zakk Hoyt on 2/4/16.
//  Copyright © 2016 Zakk Hoyt. All rights reserved.
//

#include "Terminal.h"

Terminal::Terminal() {
    
}

Terminal::~Terminal() {
    
}

void Terminal::start(long baud) {
    Serial.begin(baud);
    Serial.flush();
}

uint16_t Terminal::readSerial() {
    while (Serial.available()) {
        delay(1);
        char c = Serial.read();
        if (c == '\n') {
            parseSerialString();
            return numCommands;
        }
        g_serialString += c;
        return 0;
    }
}

int Terminal::valueForKey(String key) {
  for(int i = 0; i < 16; i++) {
    TerminalCommand cmd = commands[i];
    if(cmd.key.equals(key)) {
      return cmd.value;
    }
  }
  return -1;
}

void Terminal::appendCommand(String cmdSet, int index) {
 
  int colonIndex = cmdSet.indexOf(':');
  String key = cmdSet.substring(0, colonIndex);
  String valueString = cmdSet.substring(colonIndex+1, cmdSet.length());
  int value = valueString.toInt();

  TerminalCommand cmd = TerminalCommand();
  cmd.key = key;
  cmd.value = value;
 
  commands[index] = cmd;
  numCommands = index+1;
}

void Terminal::printCommands() {
  Serial.println("************** command list ************");
  for(int i = 0; i < numCommands; i++) {
    TerminalCommand cmd = commands[i];
    Serial.print("i: "); Serial.println(i);
    Serial.print("cmd.key: "); Serial.println(cmd.key);
    Serial.print("cmd.value: "); Serial.println(cmd.value);
  }
}


void Terminal::clearCommands() {
  for(int i = 0; i < 16; i++) {
    TerminalCommand cmd = TerminalCommand();
    cmd.key = "";
    cmd.value = -1;
    commands[i] = cmd;
  }
  numCommands = 0;
}
void Terminal::parseSerialString() {
    
    if(g_serialString.length() > 0) {
        
        clearCommands();
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
            appendCommand(cmdSet, x);
      
            // Remove cmdSet from g_serialString
            String n = g_serialString.substring(pipeIndex+1);
            g_serialString = n;
          } else {
            // Last command
            appendCommand(g_serialString, x);
            g_serialString = "";
            break;
          }
        }
    }
}
