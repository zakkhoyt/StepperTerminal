//
//  CommandTerminal.hpp
//
//  Created by Zakk Hoyt on 2/4/16.
//  Copyright © 2016 Zakk Hoyt. All rights reserved.
//

#ifndef CommandTerminal_h
#define CommandTerminal_h

#include <stdio.h>
#include <Arduino.h>

struct CommandTerminalParam {
    String key;
    uint16_t value;
};

class CommandTerminal {
public:
    CommandTerminal();
    virtual ~CommandTerminal();
   
    void start(long baud);
    uint16_t readSerial();
    // ret of -1 means not found
    int valueForKey(String key);
private:

    void parseParams();
    void clearParams();
    void appendParam(String command, int index);
    void printParams();
    String g_serialString;
    
    CommandTerminalParam params[16];
    uint16_t numParams;
};

#endif /* CommandTerminal_h */
