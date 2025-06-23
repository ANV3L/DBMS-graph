#include "../include/terminal.h"

Terminal::Terminal() {};

void Terminal::run() {
    while(1){
        std::string comand;
        std::cout << "> ";
        std::getline(std::cin, comand);
        if (comand == "exit")return;
        //Здесь реализовать распределение по командам
    }
}