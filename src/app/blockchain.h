//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
#define PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H

#include "block.h"
#include "lib/flist.hpp"

class blockchain {
public:
    blockchain();

    void addBlock(const std::string& data);

    bool isChainValid() const;

private:
    uint64_t difficulty;

    flist<block> chain;

    block getLastBlock() const;
};


#endif //PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
