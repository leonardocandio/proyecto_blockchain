//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
#define PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H

#include "block.hpp"
#include "../app/lib/dynamic_array.hpp"
#include "fstream"
#include "transaction.h"
#include "../app/lib/heap.hpp"

class blockchain {
public:
    blockchain();

    void addBlock(const dynamic_array<transaction *> &transactions);

    [[nodiscard]] bool isChainValid() const;

    virtual ~blockchain();

    void addFromFile(const std::string &path, bool skipFirstLine = true);

    dynamic_array<block<transaction>> *getChain();

    [[nodiscard]] std::string jsonify() const;

    block<transaction> *getLastBlock();

private:
    short unsigned int difficulty;

    dynamic_array<block<transaction>> chain;

    heap<double, block<transaction>> maxHeap;
    heap<double, block<transaction>> minHeap;
};


#endif //PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
