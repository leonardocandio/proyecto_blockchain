//
// Created by Leonardo Candio on 7/02/23.
//

#include "blockchain.h"
#include "iostream"

blockchain::blockchain() : difficulty(2) {
    latest = new block(0, "Genesis Block");
    latest->mineBlock(difficulty);
}

bool blockchain::isChainValid() const {
    block *current = latest;
    while (current != nullptr) {
        if (current->getHash() != current->calculateHash()) {
            return false;
        }
        if (current->getPrevBlock() != nullptr) {
            if (current->getPrevHash() != current->getPrevBlock()->getHash()) {
                return false;
            }
        }
        current = current->getPrevBlock();
    }
    return true;
}


void blockchain::addBlock(const std::string &data) {
    std::string prevHash = getLastest()->getHash();
    auto temp = latest;
    latest = new block(temp->getIndex() + 1, data);
    latest->setPrevHash(prevHash);
    latest->mineBlock(difficulty);
    latest->setPrevBlock(temp);
}

block *const blockchain::getLastest() const {
    return latest;
}

blockchain::~blockchain() {
    while (latest != nullptr) {
        block *prev = latest->getPrevBlock();
        delete latest;
        latest = prev;
    }
}

