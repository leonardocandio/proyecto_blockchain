//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
#define PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H

#include "block.h"
#include "../app/lib/vector.hpp"
#include "fstream"

class blockchain {
public:
    blockchain();

    void addBlock(const std::string &data);

    [[nodiscard]] bool isChainValid() const;

    virtual ~blockchain();

    void addFromFile(const std::string &path, bool skipFirstLine=true);

    vector<block> *getChain();

    [[nodiscard]] std::string jsonify() const;

private:
    short unsigned int difficulty;

    vector<block> chain;

};


#endif //PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
