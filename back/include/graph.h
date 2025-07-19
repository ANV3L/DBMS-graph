#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <fstream>
#include <set>
#include <utility>

//Errors

enum{
    Not_Founded = -1,
    Alloc_Issue = -11,
    Dot_File_Issue = -12,

    ERROR = -777, // Этой ошибки быть не должно
};

class Vertex; 

class Edge{
private:
    Vertex* first;
    Vertex* second;
    long weight;

    friend class Graph;
};

class Vertex{
private:
    unsigned long edge_quantity;
    std::string info;
    std::map<std::string, Edge*> edges;
    long weight; // вес самой вершины
    

    friend class Graph;
};

class Graph{
private:
    bool orgraph; // 1, если граф ориентированный
    bool weight; // 1, если граф взвешенный
    
    std::unordered_map<std::string, Vertex*> vertices;
    unsigned long vertex_quantity;

public:
    Graph(bool is_orgraph = false, bool is_weight = false);
    ~Graph();
    int add_vertex(std::string, long weight);
    int add_edge(std::string first, std::string second, long weight);
    int delete_edge(std::string first_str, std::string second_str);
    int delete_vertex(std::string name);







    int show();


    friend class Terminal;
};



#endif