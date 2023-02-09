//
// Created by Leonardo Candio on 7/02/23.
//

#include "blockchain.h"
#include "iostream"


bool blockchain::isChainValid() const {
    for (int i = 1; i < chain.size(); ++i) {
        block currentBlock = chain[i];
        block previousBlock = chain[i - 1];
        if (currentBlock.getPrevHash() != previousBlock.calculateHash()) {
            return false;
        }
    }
    return true;
}


void blockchain::addBlock(const std::string &data) {
    chain.emplace_back(chain.size(), data, &(chain.back().hash));
    chain.back().mineBlock(difficulty);
}


blockchain::blockchain() {
    difficulty = 2;
    chain.emplace_back(0, "Genesis Block");
    chain.back().mineBlock(difficulty);
}

blockchain::~blockchain() {
}

vector<block> *blockchain::getChain() {
    return &chain;
}

void blockchain::addFromFile(const std::string &path, bool skipFirstLine) {

    std::fstream file(path, std::ios::in);
    std::stringstream ss;
    int count = 0;
    if (file.is_open()) {
        std::string line;
        if (skipFirstLine) std::getline(file, line);
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            ss << line << std::endl;
            count++;
            if (count > 9) {
                count = 0;
                addBlock(ss.str());
                ss.clear();
                ss.str("");
            }
        }
    }
}


