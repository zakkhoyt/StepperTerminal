//
//  Terminal.hpp
//  StepperMotorSpeed
//
//  Created by Zakk Hoyt on 2/4/16.
//  Copyright © 2016 Zakk Hoyt. All rights reserved.
//

#ifndef Terminal_hpp
#define Terminal_hpp

#include <stdio.h>
#include <Arduino.h>

struct TerminalCommand {
    String key;
    uint16_t value;
};

class Terminal {
public:
    Terminal();
    virtual ~Terminal();
    
    
    void start(long baud);
    uint16_t readSerial();
    // ret of -1 means not found
    int valueForKey(String key);
private:

    void parseSerialString();
    
    void clearCommands();
    void appendCommand(String command, int index);
    void printCommands();
    String g_serialString;
    
    TerminalCommand commands[16];
    uint16_t numCommands;
};

#endif /* Terminal_hpp */
