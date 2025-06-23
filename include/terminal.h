#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <string>
#include <map>

class Terminal{
public:
    Terminal();
    void run();
private:
    std::map<std::string, int (Terminal::*)()> commands;
    int exit();
};


#endif