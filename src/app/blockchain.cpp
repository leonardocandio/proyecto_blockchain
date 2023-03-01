//
// Created by Leonardo Candio on 7/02/23.
//

#include "blockchain.h"
#include "sstream"
#include <utility>

bool blockchain::isChainValid() const { return false; }

blockchain::blockchain(size_t _size, unsigned short difficulty) : _size(_size), difficulty(difficulty), lastBlock(firstBlock) {
    firstBlock->mineBlock(difficulty);
    maxHeap =
            heap<double, transaction *>([](double a, double b) { return a > b; });
    minHeap =
            heap<double, transaction *>([](double a, double b) { return a < b; });
}

blockchain::~blockchain() {
    block<transaction *> *currentBlock = firstBlock;
    while (currentBlock != nullptr) {
        block<transaction *> *nextBlock = currentBlock->next;
        delete currentBlock;
        currentBlock = nextBlock;
    }
}

void blockchain::addFromFile(const std::string &path, bool skipFirstLine, size_t transactionPerBlock) {

    std::fstream file(path, std::ios::in);
    dynamic_array<transaction *> newTransactions;
    if (file.is_open()) {
        std::string line;
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

            if (newTransactions.size() == transactionPerBlock) {
                addBlock(newTransactions);
                newTransactions.clear();
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
    indexNewData(newTransactions);

    lastBlock->next = new block<transaction *>(lastBlock->getIndex() + 1,
                                               newTransactions, &lastBlock->hash);
    lastBlock = lastBlock->next;
    lastBlock->mineBlock(difficulty);
    _size++;
}

block<transaction *> *blockchain::getLastBlock() { return lastBlock; }

void blockchain::indexNewData(const dynamic_array<transaction *> &newT) {
    for (const auto &t: newT) {
        transactions.push_back(t);
    }

    for (const auto &t: newT) {
        maxHeap.push(std::make_pair(t->getAmount(), t));
        minHeap.push(std::make_pair(t->getAmount(), t));
        patricia.insert(t->getNameDest(), t);
        Hash.set(t->getuniq(),t);
    }
}

size_t blockchain::getSize() const { return _size; }

dynamic_array<transaction *> blockchain::getTransactionsByKey(std::string key,
                                                              size_t limit) {
    dynamic_array<transaction *> result;
    switch (resolveSearchType(std::move(key))) {
        case MAX: {
            auto temp = maxHeap;
            for (size_t i = 0; i < limit; i++) {
                result.push_back(temp.top().second);
                temp.pop();
            }
            break;
        }
        case MIN: {
            auto temp2 = minHeap;
            for (size_t i = 0; i < limit; i++) {
                result.push_back(temp2.top().second);
                temp2.pop();
            }
            break;
        }
        default:
            throw std::invalid_argument("Invalid search type");
    }
    return result;
}

blockchain::searchType blockchain::resolveSearchType(std::string_view const &key) const {
    if (key == "max") {
        return MAX;
    } else if (key == "min") {
        return MIN;
    } else {
        throw std::invalid_argument("Invalid search type");
    }
}
