//
// Created by rvilc on 22/02/2023.
//

#ifndef PATRICIATRIE_TRIE_H
#define PATRICIATRIE_TRIE_H
#include <string>

using namespace std;

class Trie
{
public:
    virtual void insert(string key) = 0;
    virtual bool search(string key) = 0;
    virtual void remove(string key) = 0;

    //imprime ordenado
    virtual string toString(string sep=",") = 0;
};

#endif //PATRICIATRIE_TRIE_H
