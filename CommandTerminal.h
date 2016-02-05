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
    String arg;
    uint16_t value;
};

static int kCommandTerminalNotFound = -1;

class CommandTerminal {
public:
    CommandTerminal();
    CommandTerminal(char paramDelim, char setDelim); // Default is '|' and ':'
    virtual ~CommandTerminal();
   
    void start(long baud);
    uint16_t readSerial();
    // ret of kCommandTerminalNotFound means arg not found
    int valueForArg(String arg);
private:

    void parseParams();
    void clearParams();
    void appendParam(String command, int index);
    void printParams();
    String g_serialString;

    char paramDelim;
    char setDelim;
    CommandTerminalParam params[16];
    uint16_t numParams;
};

#endif /* CommandTerminal_h */
