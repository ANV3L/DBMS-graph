#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>

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
    int add_vertex(std::string, long weight);
    int add_edge(std::string first, std::string second, long weight);
    int delete_edge(std::string first, std::string second);
    int delete_edge(std::string first_str, std::string second_str);
    int delete_vertex(std::string name);
};



#endif