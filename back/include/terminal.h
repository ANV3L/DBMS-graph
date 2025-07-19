#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <string>
#include <map>
#include "graph.h"

class Terminal{
public:
    Terminal();
    void run();
private:
    Graph graph;
    std::map<std::string, int (Terminal::*)()> commands;
    int exit();
    int add_vertex();





    int show();
};


#endif