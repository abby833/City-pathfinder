#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

void Graph::AddNode(string u, string v, double w) {
    NodeList[u].push_back({v, w});
    NodeList[v].push_back({u, w});
}

void Graph::loadFromFile(string filename) {
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

void Graph::Dijkstra(string start, string end) {
    map<string, double> distance;
    map<string, string> parent; 
    
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

    if(distance[end] == INT_MAX) {
        cout << "Nu exista drum intre " << start << " si " << end << endl;
    } else {
        ///Reconstruiesc drumul pentru a-l pune intr-un fisier
        vector<string> path;
        for(string at = end; at != ""; at = parent[at]) {
            path.push_back(at);
        }
        
        // Deschid fisierul pt a salva rezultatul in python
        ofstream outFile("src/traseu.txt");
        //scriu drumul invers
        for(int i = path.size() - 1; i >= 0; i--) {
            outFile << path[i] << endl;
        }
        outFile.close();
        
        cout << "Distanta: " << distance[end] << ". Traseul a fost salvat in 'src/traseu.txt'." << endl;
    }
}