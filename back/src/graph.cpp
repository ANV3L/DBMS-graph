#include "../include/graph.h"

Graph::Graph(bool is_orgraph, bool is_weight){
    this->orgraph = is_orgraph;
    this->weight = is_weight;
    this->vertex_quantity = 0;
}

Graph::~Graph() {
    for(auto i = this->vertices.begin(); i != this->vertices.end(); ){
        auto temp = i; i++;
        this->delete_vertex(temp->first);
    }
}


int Graph::add_vertex(std::string str, long vertex_weight){
    Vertex* cat = new Vertex();
    cat->weight = vertex_weight;
    cat->info = str;
    this->vertices.emplace(str, cat);
    this->vertex_quantity++;
    return 0;
}

int Graph::add_edge(std::string first_str, std::string second_str, long weight = 1){
    Vertex* first = this->vertices[first_str];
    Vertex* second = this->vertices[second_str];
    if (!first or !second){
        return Not_Founded; // нет таких вершин
    }

    Edge* temp = new Edge();
    temp->first = first;
    temp->second = second;
    temp->weight = weight;
    first->edges.emplace(second_str, temp);
    first->edge_quantity++;
    if(!this->orgraph and first_str != second_str){
        second->edges.emplace(first_str, temp);
        second->edge_quantity++;
    }
    return 0;
}


int Graph::delete_edge(std::string first_str, std::string second_str){
    auto first = this->vertices.find(first_str);
    if (first == this->vertices.end())return Not_Founded;
    auto edge = first->second->edges.find(second_str); 
    if(edge == first->second->edges.end())return Not_Founded; // not founded
    Edge* temp = edge->second;
    this->vertices[first_str]->edges.erase(second_str);
    if(!this->orgraph){
        auto second = this->vertices.find(second_str);
        if(second == this->vertices.end())return ERROR; // Ошибка, которой не должно возникать при корректной работе кода
        this->vertices[second_str]->edges.erase(first_str);
    }
    delete temp;
    return 0;
}

int Graph::delete_vertex(std::string name){
    auto vertex = this->vertices.find(name);
    if(vertex == this->vertices.end()){
        return Not_Founded;
    }
    auto& edges = vertex->second->edges;
    for(auto i = edges.begin(); i != edges.end(); i){
        auto temp = i; i++;
        this->delete_edge(name, temp->first);
    }
    Vertex* vrtx = vertex->second;
    this->vertices.erase(name);
    delete vrtx;
    return 0;
}

int Graph::show(){
    if(!this->vertex_quantity)return Empty_graph;
    std::string name = "back/data/graph.dot";

    std::ofstream file(name);
    if(!file)return Alloc_Issue;
    
    file << (this->orgraph ? "digraph" : "graph") << " G {\n";
    file << "  node [shape=circle, style=filled, fillcolor=lightblue];\n";

    for(auto i : this->vertices){
        file << " \"" << i.first << "\"";
        file << "[label=\"" << i.first;
        if(this->weight)file << "\\n" << i.second->weight;
        file << "\"];\n";
    }

    std::set<std::pair<std::string, std::string>> memory;

    for(auto vertex : this->vertices){
        for(auto edge : vertex.second->edges){
            if(!this->orgraph)
                if(memory.count({vertex.first, edge.first}))continue;

            file << " \"" << vertex.first << "\" " 
            << (this->orgraph ? "->" : "--") << " "
            << "\"" << edge.first << "\"";

            if(this->weight){
                file << " [label=\"" << edge.second->weight << "\"]";
            }

            file << ";\n";

            memory.insert({edge.first, vertex.first});
        }
    }


    file << "}\n";
    file.close();


    int res = system("dot -Tpng back/data/graph.dot -o back/data/graph.png");
    if(res != 0){
        return Dot_File_Issue;
    }

    #ifdef _WIN32
        system("start back/data/graph.png");
    #elif __APPLE__
        system("open back/data/graph.png");
    #else
        system("xdg-open back/data/graph.png");
    #endif

    std::remove("back/data/graph.dot");
    std::remove("back/data/graph.png");

    return 0;
}


int Graph::save(std::string file_name){
    std::ofstream file("back/data/" + file_name);


    if(!file.is_open())return Cant_Open_File;

    file << this->orgraph << " " << this->weight << "\n";

    for(auto i : this->vertices) {
        file << i.first << "╬" << i.second->weight << "\n";
    }

    file << "╬\n";

    std::set<std::pair<std::string, std::string>> memory;

    for(auto vertex : this->vertices){
        for(auto edge : vertex.second->edges){
            if(!this->orgraph)
                if(memory.count({vertex.first, edge.first}))continue;
            memory.insert({edge.first, vertex.first});
            file << vertex.first << "╬" << edge.first << "╬" << edge.second->weight << "\n";
        }

    }

    file.close();
    return 0;
}

int Graph::free(){
    this->orgraph = false;
    this->weight = false;

    for(auto vertex : vertices){
        for(auto edge : vertex.second->edges)delete edge.second;
        vertex.second->edges.clear();
        delete vertex.second;
    }
    vertices.clear();
    vertex_quantity = 0;
    return 0;
}

int Graph::load(std::string file_name){
    std::ifstream file("back/data/" + file_name);
    if(!file.is_open())return Cant_Open_File;

    free();

    int temp1, temp2;
    file >> temp1 >> temp2;
    this->orgraph = (bool)temp1;
    this->weight = (bool)temp2;

    std::string line;
    std::getline(file, line);

    bool logic = false;

    size_t index;
    while(std::getline(file, line)){
        if(line == "╬"){
            logic = true; continue;
        }


        if(logic){
            index = line.find('╬');
            size_t second_index = line.find('╬', index + 1);
            std::string from = line.substr(0, index);
            std::string to = line.substr(index + 1, second_index - index - 1);
            long weight = std::stol(line.substr(second_index + 1));
            this->add_edge(from, to, weight);
        } else {
            index = line.find('╬');
            if(index == std::string::npos)return Format_Error;
            std::string vertex_name = line.substr(0, index);
            long vertex_weight = std::stol(line.substr(index + 1));
            this->add_vertex(vertex_name, vertex_weight);
        }
    }
    return 0;
}