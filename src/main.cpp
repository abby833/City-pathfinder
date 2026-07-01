#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector> 
#include "Trie.h"
#include "Graph.h" 

void loadStreetsIntoTrie(Trie& trie) {
    std::ifstream file("src/nume_strazi.txt");
    if (!file.is_open()) {
        std::cerr << "Eroare critică: Nu am putut deschide fișierul 'src/nume_strazi.txt'!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, u, v;

        if (std::getline(ss, name, ',') && 
            std::getline(ss, u, ',') && 
            std::getline(ss, v, ',')) {
            
            trie.insert(name, u);
        }
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Utilizare: " << argv[0] << " <NumeStart> <NumeDestinatie>" << std::endl;
        return 1;
    }

    std::string startName = argv[1];
    std::string endName = argv[2];

    Trie streetsTrie;
    loadStreetsIntoTrie(streetsTrie);

    std::string startID = streetsTrie.search(startName);
    std::string endID = streetsTrie.search(endName);

    if (startID == "NOT_FOUND") {
        std::cerr << "Eroare: Strada '" << startName << "' nu a fost gasita!" << std::endl;
        return 1;
    }
    if (endID == "NOT_FOUND") {
        std::cerr << "Eroare: Strada '" << endName << "' nu a fost gasita!" << std::endl;
        return 1;
    }

    Graph G;
    std::cout << "Incarc graful..." << std::endl;
    G.loadFromFile("src/statii.txt");
    
    std::cout << "Calculez ruta de la " << startID << " la " << endID << "..." << std::endl;
    
    std::vector<std::string> path = G.Dijkstra(startID, endID);

    if (path.empty()) {
        std::cout << "Nu exista drum intre " << startName << " si " << endName << std::endl;
        return 1;
    }

    std::ofstream outFile("src/traseu.txt");
    if (!outFile.is_open()) {
        std::cerr << "Eroare: Nu am putut crea fisierul 'src/traseu.txt'!" << std::endl;
        return 1;
    }

    for (const auto& node : path) {
        outFile << node << std::endl;
    }
    outFile.close();
    
    std::cout << "Traseul a fost salvat cu succes in 'src/traseu.txt' pentru aplicatia Python." << std::endl;

    return 0;
}