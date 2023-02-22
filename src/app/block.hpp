//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCK_HPP
#define PROYECTO_BLOCKCHAIN_BLOCK_HPP

#include "algorithm"
#include "ctime"
#include "lib/dynamic_array.hpp"
#include "sstream"

//class block
template<typename T>
class block {
public:
    block();

    block(size_t index, dynamic_array<T> transactions, std::size_t *prevHash);

    block(block &&other) noexcept;

    block(const block &other);

    block &operator=(const block &other);

    void mineBlock(unsigned short difficulty);

    [[nodiscard]] const std::size_t &getHash() const;

    [[nodiscard]] std::size_t calculateHash() const;

    [[nodiscard]] const std::size_t &getPrevHash() const;

    void setPrevHash(const std::size_t &prevH);

    [[nodiscard]] const dynamic_array<T> &getTransactions() const;

    [[nodiscard]] const size_t &getIndex() const;

    [[nodiscard]] std::string serialize() const;

    [[nodiscard]] bool isValid() const;

    friend class blockchain;

    [[nodiscard]] std::string jsonify() const;

    virtual ~block();


private:
    [[nodiscard]] std::string serializeTransactions() const;

    [[nodiscard]] std::string jsonifyTransactions() const;

    size_t index = 0;
    dynamic_array<T> transactions;
    std::time_t timestamp = 0;
    std::size_t hash = 0;
    size_t nonce = -1;
    std::size_t *prevHash = new size_t(0);
    block *next = nullptr;
};

template<typename T>
std::string block<T>::serializeTransactions() const {
    std::stringstream ss;
    for (auto &transaction: transactions) {
        ss << transaction->serialize();
    }
    return ss.str();
}

template<typename T>
std::string block<T>::jsonifyTransactions() const {
    std::stringstream ss;
    ss << "[";
    for (auto &transaction: transactions) {
        ss << transaction->jsonify();
        if (transaction != transactions[transactions.size() - 1]) {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}

template<typename T>
block<T>::block() = default;

template<typename T>
block<T>::~block() = default;

template<typename T>
void block<T>::mineBlock(unsigned short difficulty) {
    std::string target(difficulty, '0');
    do {
        nonce++;
        hash = calculateHash();
    } while (std::to_string(hash).substr(std::to_string(hash).size() - difficulty) != target);
}

template<typename T>
std::size_t block<T>::calculateHash() const {
    std::stringstream ss;
    std::hash<std::string> newHash;
    ss << index << timestamp << serializeTransactions() << nonce << *prevHash;
    return newHash(ss.str());
}

template<typename T>
const std::size_t &block<T>::getPrevHash() const {
    return *prevHash;
}

template<typename T>
void block<T>::setPrevHash(const std::size_t &prevH) {
    *block<T>::prevHash = prevH;
}

template<typename T>
const dynamic_array<T> &block<T>::getTransactions() const {
    return transactions;
}

template<typename T>
const size_t &block<T>::getIndex() const {
    return index;
}

template<typename T>
block<T>::block(size_t index, dynamic_array<T> transactions, std::size_t *prevHash) : index(index),
                                                                                      transactions(std::move(transactions)),
                                                                                      prevHash(prevHash) {
    timestamp = std::time(nullptr);
    hash = calculateHash();
}


template<typename T>
const std::size_t &block<T>::getHash() const {
    return hash;
}

template<typename T>
block<T>::block(block &&other) noexcept : index(other.index), transactions(std::move(other.transactions)),
                                          timestamp(other.timestamp), hash(other.hash), nonce(other.nonce),
                                          prevHash(other.prevHash), next(other.next) {
    other.prevHash = nullptr;
}

template<typename T>
bool block<T>::isValid() const {
    return calculateHash() == hash;
}

template<typename T>
block<T>::block(const block &other) : index(other.index), transactions(other.transactions),
                                      timestamp(other.timestamp), hash(other.hash), nonce(other.nonce),
                                      prevHash(new std::size_t(*other.prevHash)), next(other.next) {
}

template<typename T>
block<T> &block<T>::operator=(const block &other) {
    if (this == &other) return *this;
    index = other.index;
    transactions = other.transactions;
    timestamp = other.timestamp;
    hash = other.hash;
    nonce = other.nonce;
    prevHash = new std::size_t(*other.prevHash);
    return *this;
}


template<typename T>
std::string block<T>::jsonify() const {
    std::stringstream ss;
    ss << "{"
       << R"("index" : )" << index << ","
       << R"("timestamp" : )" << timestamp << ","
       << R"("transactions" : )" << jsonifyTransactions() << ","
       << R"("hash" : ")" << hash << R"(",)"
       << R"("prevhash" : ")" << *prevHash << R"(",)"
       << R"("nonce" : )" << nonce
       << "}";

    return ss.str();
}

template<typename T>
std::string block<T>::serialize() const {
    std::stringstream ss;
    ss << index << timestamp << serializeTransactions() << nonce << *prevHash;
    return ss.str();
}


#endif//PROYECTO_BLOCKCHAIN_BLOCK_HPP
