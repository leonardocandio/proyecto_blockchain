//
// Created by rvilc on 22/02/2023.
//

#ifndef PROYECTO_BLOCKCHAIN_TRIE_HPP
#define PROYECTO_BLOCKCHAIN_TRIE_HPP
#include <string>

template<class DataT>
class Trie {
public:
    virtual void insert(std::string key, DataT coming) = 0;
    virtual bool search(std::string key) = 0;
    virtual void remove(std::string key) = 0;
    virtual ~Trie() = default;
};

#endif
