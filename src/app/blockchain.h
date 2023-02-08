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

    void addBlock(const std::string &data);

    [[nodiscard]] bool isChainValid() const;

    virtual ~blockchain();

    block *const getLastest() const;

private:
    short unsigned int difficulty;

    block *latest;

};


#endif //PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
