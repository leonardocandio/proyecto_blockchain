//
// Created by Leonardo Candio on 7/02/23.
//

#include "blockchain.h"
#include "iostream"
#include "random"


bool blockchain::isChainValid() const {
    for (int i = 1; i < chain.size(); ++i) {
        auto currentBlock = chain[i];
        auto previousBlock = chain[i - 1];
        if (currentBlock.calculateHash() != currentBlock.hash) {
            return false;
        }
        if (currentBlock.getPrevHash() != previousBlock.hash) {
            return false;
        }
    }
    return true;
}



blockchain::blockchain() {
    difficulty = 2;
    chain.emplace_back(0, "Genesis Block");
    chain.back().mineBlock(difficulty);
}

blockchain::~blockchain() {
}

vector<block<transaction>> *blockchain::getChain() {
    return &chain;
}

void blockchain::addFromFile(const std::string &path, bool skipFirstLine) {

    std::fstream file(path, std::ios::in);
    vector<transaction> transactions;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 5);

    if (file.is_open()) {
        std::string line;
        if (skipFirstLine) std::getline(file, line);
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            std::stringstream ss(line);
            std::string item;
            vector<std::string> lineV;
            int size = dis(gen);
            while (std::getline(ss, item, ',')) {
                lineV.push_back(item);
            }
            transactions.emplace_back(std::stoi(lineV[0]), std::stod(lineV[1]), std::stod(lineV[2]),
                                      std::stod(lineV[3]), lineV[4], std::stod(lineV[5]), std::stod(lineV[6]));
            if (transactions.size() == size) {

                size = dis(gen);
            }
        }
        if (transactions.size() > 0) {
        }
    }
}


std::string blockchain::jsonify() const {
    std::stringstream ss;
    ss << "[";
    for (const auto &block: chain) {
        ss << block.jsonify() << ",";
    }
    ss.seekp(-1, std::ios_base::end);
    ss << "]";
    return ss.str();
}

void blockchain::addBlock(const vector<transaction* >& transactions) {
    chain.emplace_back(transactions, chain.back().hash);
    chain.back().mineBlock(difficulty);
}


