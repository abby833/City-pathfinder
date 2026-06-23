#pragma once
#include <unordered_map>
#include <string>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    std::string streetID;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false), streetID("") {}
};

class Trie {
private:
    TrieNode* root;
    void clear(TrieNode* node);

public:
    Trie();
    ~Trie(); 

    void insert(const std::string& streetName, const std::string& id);
    std::string search(const std::string& streetName);
};