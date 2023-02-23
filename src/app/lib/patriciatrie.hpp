//
// Created by rvilc on 22/02/2023.
//

#ifndef PROYECTO_BLOCKCHAIN_PATRICIATRIE_HPP
#define PROYECTO_BLOCKCHAIN_PATRICIATRIE_HPP

#include "dynamic_array.hpp"
#include "trie.hpp"
#include <iostream>
#include <list>
#include <map>
#include <stack>
#include <vector>
using namespace std;

const unsigned ALPHA_SIZE = 26;
template<class DataT>
class TriePatricia : public Trie<DataT> {
private:
    struct TrieNode {
        TrieNode **children;
        string prefix;
        dynamic_array<DataT> endWord; //array para almacenar punteros a transactions

        TrieNode() {
            children = new TrieNode *[ALPHA_SIZE];
            for (int i = 0; i < ALPHA_SIZE; i++) {
                children[i] = nullptr;
            }
            endWord = dynamic_array<DataT>();
        }

        ~TrieNode() {
            for (int i = 0; i < ALPHA_SIZE; i++) {
                if (children[i] != nullptr) {
                    delete children[i];
                }
            }
        }
    };

    TrieNode *root;

public:
    TriePatricia() : root(new TrieNode()) {}

    void insert(string key, DataT coming) {
        if (root == nullptr) {
            root = new TrieNode;
        }
        TrieNode *current = root;
        int i = 0;
        while (i < key.length()) {
            char c = key[i];
            TrieNode *child = current->children[c - 'a'];
            if (child == nullptr) {
                child = new TrieNode();
                child->prefix = key.substr(i);
                current->children[c - 'a'] = child;
                current = child;
                break;
            } else {
                string childPrefix = child->prefix;// childprefix = romano
                int j = 0;
                while (i < key.length() && j < childPrefix.length() && key[i] == childPrefix[j]) {
                    i++;// r o m a n o   r o s a r i o ---  r a t a
                    j++;// r o m a       r o m a       ---  r o
                }
                if (j == childPrefix.length()) {
                    current = child;// Si tiene caracteres en comun con todo el prefijo de su hijo, current se mueve al hijo
                } else {
                    TrieNode *newChild = new TrieNode();
                    newChild->prefix = childPrefix.substr(j);
                    newChild->endWord = child->endWord;
                    for (int k = 0; k < ALPHA_SIZE; k++) {
                        newChild->children[k] = child->children[k];
                        child->children[k] = nullptr;
                    }
                    child->prefix = childPrefix.substr(0, j);
                    //child->endWord = false;
                    child->children[newChild->prefix[0] - 'a'] = newChild;
                    if (i < key.length()) {
                        TrieNode *newChild2 = new TrieNode();
                        newChild2->prefix = key.substr(i);
                        child->children[newChild2->prefix[0] - 'a'] = newChild2;
                        current = newChild2;
                        break;
                    }
                    current = child;
                }
            }
        }
        //if (!count(current->endWord.begin(), current->endWord.end(), coming))
        current->endWord.push_back(coming);
    }

    bool search(string key) {
        TrieNode *current = root;
        int i = 0;
        while (i < key.length()) {
            char c = key[i];
            TrieNode *child = current->children[c - 'a'];
            if (child == nullptr) {
                return false;
            } else {
                string childPrefix = child->prefix;
                int j = 0;
                while (i < key.length() && j < childPrefix.length() && key[i] == childPrefix[j]) {
                    i++;
                    j++;
                }
                if (j == childPrefix.length()) {
                    current = child;
                } else {
                    return false;
                }
            }
        }
        return (current->endWord.size() > 0);
    }
    void remove(string key) {
        if (!search(key)) {
            return;
        }
        TrieNode *current = root;
        TrieNode *parent = nullptr;
        TrieNode *nodeToDelete = nullptr;
        char charToDelete = '\0';
        int i = 0;
        while (i < key.length()) {
            char c = key[i];
            TrieNode *child = current->children[c - 'a'];
            if (child == nullptr) {
                return;
            } else {
                string childPrefix = child->prefix;
                int j = 0;
                while (i < key.length() && j < childPrefix.length() && key[i] == childPrefix[j]) {
                    i++;
                    j++;
                }
                if (i == key.length() && j == childPrefix.length()) {
                    child->endWord.clear();
                    if (isLeaf(child)) {
                        delete child;
                        current->children[c - 'a'] = nullptr;
                    }
                    return;
                }
                if (j == childPrefix.length()) {
                    parent = current;
                    current = child;
                    charToDelete = c;
                } else {
                    TrieNode *newChild = new TrieNode();
                    newChild->prefix = childPrefix.substr(j);
                    newChild->endWord = child->endWord;
                    for (int k = 0; k < ALPHA_SIZE; k++) {
                        newChild->children[k] = child->children[k];
                        child->children[k] = nullptr;
                    }
                    child->prefix = childPrefix.substr(0, j);
                    child->endWord.clear();
                    child->children[newChild->prefix[0] - 'a'] = newChild;
                    parent = current;
                    current = child;
                    charToDelete = newChild->prefix[0];
                }
            }
        }
        nodeToDelete = current;
        current->endWord.clear();
        if (isLeaf(current)) {
            delete current;
            parent->children[charToDelete - 'a'] = nullptr;
        }
    }
    string toString(string sep = ",") {
        vector<string> words;
        getWords(root, "", words);
        string result = "";
        for (int i = 0; i < words.size(); i++) {
            result += words[i];
            if (i < words.size() - 1) {
                result += sep;
            }
        }
        return result + " ";
    }

private:
    void getWords(TrieNode *node, string prefix, vector<string> &words) {
        if (node == nullptr) {
            return;
        }
        if (node->endWord.size()) {
            words.push_back(prefix + node->prefix);
        }
        for (int i = 0; i < ALPHA_SIZE; i++) {
            getWords(node->children[i], prefix + node->prefix, words);
        }
    }
    bool isLeaf(TrieNode *node) {
        for (int i = 0; i < ALPHA_SIZE; i++) {
            if (node->children[i] != nullptr) {
                return false;
            }
        }
        return true;
    }
};
#endif