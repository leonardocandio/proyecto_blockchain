//
// Created by Leonardo Candio on 7/02/23.
//

#include "blockchain.h"
#include "iostream"
#include "lib/lazycsv.hpp"
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

void blockchain::addFromFile(const std::string &path, size_t transactionPerBlock) {
    lazycsv::parser parser{path};
    dynamic_array<transaction *> newTransactions;
    for (const auto row: parser) {
        const auto [step, type, amount, nameOrig, oldbalanceOrg, newbalanceOrig,
                    nameDest, oldbalanceDest, newbalanceDest] = row.cells(0, 1, 2, 3, 4, 5, 6, 7, 8);
        auto *t = new transaction(std::stoi(step.unescaped()), type.unescaped(), std::stod(amount.unescaped()), nameOrig.unescaped(), std::stod(oldbalanceOrg.unescaped()),
                                  std::stod(newbalanceOrig.unescaped()),
                                  nameDest.unescaped(), std::stod(oldbalanceDest.unescaped()), std::stod(newbalanceDest.unescaped()));
        newTransactions.push_back(t);
        if (newTransactions.size() == transactionPerBlock) {
            addBlock(newTransactions);
            newTransactions.clear();
        }
    }
    if (newTransactions.size()) addBlock(newTransactions);
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
