#include "trie.h"

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    clear(root);
}

void Trie::clear(TrieNode* node) {
    for (auto& pair : node->children) {
        clear(pair.second);
    }
    delete node;
}

void Trie::insert(const std::string& streetName, const std::string& id) {
    TrieNode* current = root;
    for (char ch : streetName) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }
    current->isEndOfWord = true;
    current->streetID = id;
}

std::string Trie::search(const std::string& streetName) {
    TrieNode* current = root;
    for (char ch : streetName) {
        if (current->children.find(ch) == current->children.end()) {
            return "NOT_FOUND";
        }
        current = current->children[ch];
    }
    return (current->isEndOfWord) ? current->streetID : "NOT_FOUND";
}