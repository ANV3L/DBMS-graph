#include "../include/terminal.h"

Terminal::Terminal(){
    commands["exit"] = &Terminal::exit; // Здесь добавлять новые функции
    commands["show"] = &Terminal::show;
    commands["addv"] = &Terminal::add_vertex;
    commands["add vertex"] = &Terminal::add_vertex;
    commands["delv"] = &Terminal::delete_vertex;
    commands["delete vertex"] = &Terminal::delete_vertex;
    commands["make orgraph"] = &Terminal::make_orgraph;
    commands["make weight"] = &Terminal::make_weight;
    commands["make unorgraph"] = &Terminal::make_unorgraph;
    commands["make unweight"] = &Terminal::make_unweight;
};

void Terminal::run(){
    int res = 0;
    while(1){
        res = 0;
        std::string comand;
        std::cout << "> ";  // На данном участке принимаются команды
        std::getline(std::cin, comand);

        if(std::cin.eof()){
            std::cout << std::endl; return;
        }        
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
            case -11:
                std::cout << "Alloc Issues" << std::endl;
                break;
            default:
                std::cout <<"Uncategorized issue" << std::endl;
                break;
        }

    }
}

int Terminal::show(){
    return this->graph.show();
}

int Terminal::exit(){
    return -1;
}

int Terminal::add_vertex(){
    std::string name;
    std::cout << "Name of vertex << ";
    std::getline(std::cin, name);

    long weight = 1;

    if(this->graph.weight){
        std::cout << "Weight of vertex << ";
        std::cin >> weight;
    }

    return this->graph.add_vertex(name, weight);
}

int Terminal::delete_vertex(){
    std::string name;
    std::cout << "Name of vertex << ";
    std::getline(std::cin, name);

    return this->graph.delete_vertex(name);
}


int Terminal::make_orgraph(){
    this->graph.orgraph = true; return 0;
}

int Terminal::make_weight(){
    this->graph.weight = true; return 0;
}

int Terminal::make_unorgraph(){
    this->graph.orgraph = false; return 0;
}

int Terminal::make_unweight(){
    this->graph.weight = false; return 0;
}
