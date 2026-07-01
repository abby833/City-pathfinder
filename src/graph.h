#pragma once
#include <vector>
#include <unordered_map>
#include <string>

struct Node {
    std::string destination;
    double weight;
};

class Graph {
private:
    std::unordered_map<std::string, std::vector<Node>> NodeList;
public:
    void AddNode(std::string& u, std::string& v, double w);
    void loadFromFile(const std::string& filename);
    std::vector<std::string> Dijkstra(const std::string& start, const std::string& end);
    void printGraph();
    void savePathToFile(const std::vector<std::string>& path, const std::string& filename);
};
