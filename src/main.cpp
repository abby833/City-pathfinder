#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
    G.Dijkstra(startID, endID);

    return 0;
}