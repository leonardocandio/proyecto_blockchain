//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
#define PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H

#include "block.hpp"
#include "../app/lib/dynamic_array.hpp"
#include "fstream"
#include "transaction.h"
#include "../app/lib/heap.hpp"
#include "lib/circular_array.hpp"

class blockchain {
public:
    blockchain();

    void addBlock(const dynamic_array<transaction *> &newT);

    [[nodiscard]] bool isChainValid() const;

    virtual ~blockchain();

    void addFromFile(const std::string &path, bool skipFirstLine = true, size_t transactionsPerBlock = 10);

    [[nodiscard]] std::string jsonify() const;

    block<transaction *> *getLastBlock();


    dynamic_array<transaction *> getTransactionsByKey(std::string key);

    [[nodiscard]] size_t getSize() const;


private:

    void indexNewData(const dynamic_array<transaction *> &newT);

    short unsigned int difficulty;

    block<transaction *> *lastBlock;
    block<transaction *> *firstBlock;
    size_t _size;

    heap<double, transaction *> maxHeap;
    heap<double, transaction *> minHeap;

    circular_array<transaction *> transactions;

    enum searchType {
        MAX, MIN
    };

    searchType resolveSearchType(std::string key);

};


template<typename T>
std::string jsonifyArray(const dynamic_array<T> &array) {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < array.size(); ++i) {
        ss << array[i]->jsonify();
        if (i != array.size() - 1) {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}


#endif //PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
