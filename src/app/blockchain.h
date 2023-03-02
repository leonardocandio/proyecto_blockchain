//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H
#define PROYECTO_BLOCKCHAIN_BLOCKCHAIN_H

#include "../app/lib/btree.h"
#include "../app/lib/dynamic_array.hpp"
#include "../app/lib/hash.hpp"
#include "../app/lib/heap.hpp"
#include "../app/lib/patriciatrie.hpp"
#include "block.hpp"
#include "fstream"
#include "lib/circular_array.hpp"
#include "transaction.h"


class blockchain {
public:
    blockchain(size_t _size = 0, unsigned short difficulty = 2);

    void addBlock(const dynamic_array<transaction *> &newT);

    [[nodiscard]] bool isChainValid() const;

    virtual ~blockchain();

    void addFromFile(const std::string &path, bool skipFirstLine = true, size_t transactionPerBlock = 10);

    [[nodiscard]] std::string jsonify() const;

    block<transaction *> *getLastBlock();

    void recalculo();

    dynamic_array<transaction *> getTransactionsByParamType(const std::string &param, const std::string &type, size_t limit, size_t rangeLow, size_t rangeHigh);

    [[nodiscard]] size_t getSize() const;
    void addBlock(const dynamic_array_iterator<transaction *> &begin, const dynamic_array_iterator<transaction *> &end);
    void transactionsToBlocks(size_t transactionsPerBlock);
    void indexNewData(const dynamic_array_iterator<transaction *> &begin, const dynamic_array_iterator<transaction *> &end);


private:
    void indexNewData(const dynamic_array<transaction *> &newT);

    size_t _size;
    short unsigned int difficulty;

    block<transaction *> *firstBlock = new block<transaction *>();
    block<transaction *> *lastBlock;

    heap<double, transaction *> maxHeapAmount;
    heap<double, transaction *> minHeapAmount;
    heap<double, transaction *> maxHeapOldbalanceOrg;
    heap<double, transaction *> minHeapOldbalanceOrg;
    heap<double, transaction *> maxHeapNewbalanceOrig;
    heap<double, transaction *> minHeapNewbalanceOrig;
    heap<double, transaction *> maxHeapOldbalanceDest;
    heap<double, transaction *> minHeapOldbalanceDest;
    heap<double, transaction *> maxHeapNewbalanceDest;
    heap<double, transaction *> minHeapNewbalanceDest;

    BTree<double, transaction *> bTreeAmount = BTree<double, transaction *>(5);
    BTree<double, transaction *> bTreeOldbalanceOrg = BTree<double, transaction *>(5);
    BTree<double, transaction *> bTreeNewbalanceOrig = BTree<double, transaction *>(5);
    BTree<double, transaction *> bTreeOldbalanceDest = BTree<double, transaction *>(5);
    BTree<double, transaction *> bTreeNewbalanceDest = BTree<double, transaction *>(5);



    TriePatricia<transaction *> patricia;
    ChainHash<string, transaction *> hashMap;


    dynamic_array<transaction *> transactions;

    enum searchType {
        MAX,
        MIN,
        RANGE,
    };
    enum searchParam {
        TYPE,
        AMOUNT,
        NAMEORIG,
        OLDBALANCEORG,
        NEWBALANCEORIG,
        NAMEDEST,
        OLDBALANCEDEST,
        NEWBALANCEDEST,
        ALL
    };

    [[nodiscard]] searchType resolveSearchType(std::string_view const &type) const;
    [[nodiscard]] searchParam resolveSearchParam(std::string_view const &param) const;
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
