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
#include "lib/circular_array.hpp"

class blockchain {
public:
    blockchain();


    void addBlock(const dynamic_array<transaction *> &newT);

    [[nodiscard]] bool isChainValid() const;

    virtual ~blockchain();

    void addFromFile(const std::string &path, bool skipFirstLine = true);

    [[nodiscard]] std::string jsonify() const;

    block<transaction *> *getLastBlock();


private:

    void indexNewData(const dynamic_array<transaction *> &newT);

    short unsigned int difficulty;

    block<transaction *> *lastBlock;
    block<transaction *> *firstBlock;

    heap<double, transaction *> maxHeap;
    heap<double, transaction *> minHeap;

    circular_array<transaction *> transactions;
};


#endif //PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
