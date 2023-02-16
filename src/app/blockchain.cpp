//
// Created by Leonardo Candio on 7/02/23.
//

#include "blockchain.h"
#include "iostream"
#include "random"


bool blockchain::isChainValid() const {
    return false;
}


blockchain::blockchain() {
    difficulty = 2;
    firstBlock = new block<transaction *>();
    firstBlock->mineBlock(difficulty);
    lastBlock = firstBlock;
    maxHeap = heap<double, transaction *>([](double a, double b) { return a > b; });
    minHeap = heap<double, transaction *>([](double a, double b) { return a < b; });
}

blockchain::~blockchain() {
}

void blockchain::addFromFile(const std::string &path, bool skipFirstLine) {

    std::fstream file(path, std::ios::in);
    dynamic_array<transaction *> newTransactions;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(5, 7);

    if (file.is_open()) {
        std::string line;
        int size = dis(gen);
        if (skipFirstLine) std::getline(file, line);
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            std::stringstream ss(line);
            std::string item;
            dynamic_array<std::string> lineV;
            while (std::getline(ss, item, ',')) {
                lineV.push_back(item);
            }
            newTransactions.push_back(
                    new transaction(std::stoi(lineV[0]), lineV[1], std::stod(lineV[2]), lineV[3], std::stod(lineV[4]),
                                    std::stod(lineV[5]), lineV[6], std::stod(lineV[7]), std::stod(lineV[8])));

            if (newTransactions.size() == size) {
                addBlock(newTransactions);
                newTransactions.clear();
                size = dis(gen);
            }
        }
        if (newTransactions.size() > 0) {
            addBlock(newTransactions);
        }
    }
}


std::string blockchain::jsonify() const {
    std::stringstream ss;
    ss << "[";
    auto *currentBlock = firstBlock;
    while (currentBlock != nullptr) {
        ss << currentBlock->jsonify();
        currentBlock = currentBlock->next;
        if (currentBlock != nullptr) {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}

void blockchain::addBlock(const dynamic_array<transaction *> &newTransactions) {
    for (const auto &t: newTransactions) {
        transactions.push_back(t);
    }

    lastBlock->next = new block<transaction *>(lastBlock->getIndex() + 1, newTransactions, &lastBlock->hash);
    lastBlock = lastBlock->next;
    lastBlock->mineBlock(difficulty);
}

block<transaction *> *blockchain::getLastBlock() {
    return lastBlock;
}

void blockchain::indexNewData(const dynamic_array<transaction *> &newT) {
    for (const auto &t: newT) {
        transactions.push_back(t);
    }

    for (const auto &t: newT) {
        maxHeap.push(std::make_pair(t->getAmount(), t));
        minHeap.push(std::make_pair(t->getAmount(), t));
    }
}








