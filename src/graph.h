#pragma once
#include <vector>
#include <map>
#include <string>

struct Node {
    std::string destination;
    double weight;
};

class Graph {
private:
    std::map<std::string, std::vector<Node>> NodeList;
public:
    void AddNode(std::string u, std::string v, double w);
    void loadFromFile(std::string filename);
    void Dijkstra(std::string start, std::string end);
    void printGraph();
};
