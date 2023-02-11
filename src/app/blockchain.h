//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
#define PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H

#include "block.hpp"
#include "../app/lib/vector.hpp"
#include "fstream"
#include "transaction.h"

class blockchain {
public:
    blockchain();

    void addBlock(const vector<transaction* >& transactions);

    [[nodiscard]] bool isChainValid() const;

    virtual ~blockchain();

    void addFromFile(const std::string &path, bool skipFirstLine = true);

    vector<block<transaction>> *getChain();

    [[nodiscard]] std::string jsonify() const;

private:
    short unsigned int difficulty;

    vector<block<transaction>> chain;

};


#endif //PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
