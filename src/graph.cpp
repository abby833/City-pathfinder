#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void Graph::AddNode(string& u, string& v, double w) {
    NodeList[u].push_back({v, w});
    NodeList[v].push_back({u, w});
}

void Graph::loadFromFile(const string& filename) {
    ifstream file(filename);
    string line, u, v, w_str;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, u, ',');
        getline(ss, v, ',');
        getline(ss, w_str, ',');
        if(!w_str.empty()) {
            AddNode(u, v, stod(w_str));
        }
    }
}

void Graph::printGraph() {
    for(auto const& [station, edges] : NodeList) {
        cout << "Nodul: " << station << " este conectat cu: ";
        for(auto const& s : edges)
            cout << s.destination << " (cost: " << s.weight << "); ";
        cout << endl;
    }
}

std::vector<std::string> Graph::Dijkstra(const std::string& start, const std::string& end) {
    unordered_map<string, double> distance;
    unordered_map<string, string> parent; 
    
    for(auto const& [node, edges] : NodeList) {
        distance[node] = INT_MAX;
        parent[node] = ""; 
    }
    
    auto cmp = [](const pair<string, double>& a, const pair<string, double>& b) { 
        return a.second > b.second; 
    };

    priority_queue<pair<string, double>, vector<pair<string, double>>, decltype(cmp)> p(cmp);
    
    distance[start] = 0;
    p.push({start, 0});

    while(!p.empty()) {
        pair<string, double> aux = p.top();
        p.pop();
        
        string curent = aux.first;
        double dist = aux.second;

        if(dist > distance[curent]) continue;
        if(curent == end) break; 

        for(auto const& q : NodeList[curent]) {
            if(distance[curent] + q.weight < distance[q.destination]) {
                distance[q.destination] = distance[curent] + q.weight;
                parent[q.destination] = curent;
                p.push({q.destination, distance[q.destination]});
            }
        }
    }

    if(distance[end] == INT_MAX) 
            return {};
     else 
    {
        ///Reconstruiesc drumul pentru a-l pune intr-un fisier
        vector<string> path;
        for(string at = end; at != ""; at = parent[at]) {
            path.push_back(at);
            if (at == start) break;
        }
        std::reverse(path.begin(), path.end());
       
        return path;
    }
}

void Graph::savePathToFile(const std::vector<std::string>& path, const std::string& filename) {
    std::ofstream outFile(filename);
    for (const auto& node : path) outFile << node << "\n";
    outFile.close();
}