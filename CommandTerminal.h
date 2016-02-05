//
//  CommandTerminal.hpp
//
//  Created by Zakk Hoyt on 2/4/16.
//  Copyright © 2016 Zakk Hoyt. All rights reserved.
//
//  An easy way to send terminal commands to your arduino.
//  To send command=value (where command is a String and value is a uint16_t) just format it as such:
//  command:value\n
//
//  To send multiple commands format it as such:
//  command1:value1|command2:value2\n
//  
//  You can send a max of 16 commands.
//
//  It's up to you to interpret the commands. See accompanying sketch file for examples. 
//
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
