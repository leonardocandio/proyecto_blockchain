//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
#define PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H

#include "../app/lib/dynamic_array.hpp"
#include "../app/lib/heap.hpp"
#include "../app/lib/patriciatrie.hpp"
#include "block.hpp"
#include "fstream"
#include "lib/circular_array.hpp"
#include "transaction.h"

class blockchain {
public:
    explicit blockchain(size_t _size = 0, unsigned short difficulty = 3);

    void addBlock(const dynamic_array<transaction *> &newT);

    void addBlock(const dynamic_array_iterator<transaction *> &begin, const dynamic_array_iterator<transaction *> &end);

    [[nodiscard]] bool isChainValid() const;

    virtual ~blockchain();

    void addFromFile(const std::string &path, bool skipFirstLine = true, size_t transactionPerBlock = 10);

    [[nodiscard]] std::string jsonify() const;

    block<transaction *> *getLastBlock();


    dynamic_array<transaction *> getTransactionsByKey(const std::string &key, size_t limit);

    [[nodiscard]] size_t getSize() const;


private:
    void indexNewData(const dynamic_array<transaction *> &newT);
    void indexNewData(const dynamic_array_iterator<transaction *> &begin, const dynamic_array_iterator<transaction *> &end);
    void transactionsToBlocks(size_t transactionPerBlock);

    size_t _size;
    short unsigned int difficulty;

    block<transaction *> *firstBlock = new block<transaction *>();
    block<transaction *> *lastBlock;

    heap<double, transaction *> maxHeap;
    heap<double, transaction *> minHeap;
    TriePatricia<transaction> patriciatrie;

    dynamic_array<transaction *> transactions;

    enum searchType {
        MAX,
        MIN
    };

    searchType resolveSearchType(std::string_view const &key) const;
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


#endif//PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
