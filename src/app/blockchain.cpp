//
// Created by Leonardo Candio on 7/02/23.
//

#include "blockchain.h"

blockchain::blockchain() {
    difficulty = 2;
    chain.emplace_front(chain.size(), "Genesis Block");

}

bool blockchain::isChainValid() const {
    return true;
}

block blockchain::getLastBlock() const {
    return chain.front();
}

void blockchain::addBlock(const std::string& data) {
    std::string prevHash = getLastBlock().getHash();
    chain.emplace_front(chain.size(), data);
    chain.front().setPrevHash(prevHash);
    chain.front().mineBlock(difficulty);



}

