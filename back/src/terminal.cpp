#include "../include/terminal.h"

Terminal::Terminal(){
    commands["exit"] = &Terminal::exit; // Здесь добавлять новые функции
};

void Terminal::run(){
    int res = 0;
    while(1){
        res = 0;
        std::string comand;
        std::cout << "> ";  // На данном участке принимаются команды
        std::getline(std::cin, comand);
        
        auto it = commands.find(comand);
        if(it != commands.end()){
            res = (this->*(it->second))();  // Если находим команду в словаре, то запускаем её
        } else {
            res = -2;
        }
        switch(res){ // Обработка команд
            case 0:
                break;
            case -1:
                return;
            case -2:
                std::cout << "Incorrect comand" << std::endl;
                break;
            default:
                std::cout <<"Uncategorized issue" << std::endl;
                break;
        }

    }
}


int Terminal::exit(){
    return -1;
}