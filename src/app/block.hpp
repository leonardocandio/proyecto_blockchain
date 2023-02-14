//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCK_HPP
#define PROYECTO_BLOCKCHAIN_BLOCK_HPP

#include "ctime"
#include "sstream"
#include "algorithm"
#include "lib/vector.hpp"

template<typename T>
class block {
public:
    block();

    block(size_t index, vector<T *> transactions, std::size_t *prevHash);

    block(block &&other) noexcept;

    block(const block &other);

    block &operator=(const block &other);

    void mineBlock(uint8_t difficulty);

    [[nodiscard]] const std::size_t &getHash() const;

    [[nodiscard]] std::size_t calculateHash() const;

    [[nodiscard]] const std::size_t &getPrevHash() const;

    void setPrevHash(const std::size_t &prevHash);

    [[nodiscard]] const vector<T *> &getTransactions() const;

    [[nodiscard]] const size_t &getIndex() const;

    std::string serialize() const;


    [[nodiscard]] bool isValid() const;

    friend class blockchain;

    [[nodiscard]] std::string jsonify() const;

    virtual ~block();


private:
    size_t index;
    vector<T *> transactions;
    std::time_t timestamp;
    std::size_t hash;
    size_t nonce;
    std::size_t *prevHash;


};

template<typename T>
block<T>::block() {
    index = 0;
    timestamp = 0;
    hash = -1;
    nonce = -1;
    prevHash = new std::size_t(0);
}

template<typename T>
block<T>::~block() {
}

template<typename T>
void block<T>::mineBlock(uint8_t difficulty) {
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
    ss << index << timestamp << vector<T>::serialize(transactions) << nonce << *prevHash;
    return newHash(ss.str());
}

template<typename T>
const std::size_t &block<T>::getPrevHash() const {
    return *prevHash;
}

template<typename T>
void block<T>::setPrevHash(const std::size_t &prevHash) {
    *block<T>::prevHash = prevHash;
}

template<typename T>
const vector<T *> &block<T>::getTransactions() const {
    return transactions;
}

template<typename T>
const size_t &block<T>::getIndex() const {
    return index;
}

template<typename T>
block<T>::block(size_t index, vector<T *> transactions, std::size_t *prevHash) {
    block::index = index;
    block::prevHash = prevHash;
    block::transactions = transactions;
    timestamp = std::time(nullptr);
    hash = calculateHash();
    nonce = 0;

}


template<typename T>
const std::size_t &block<T>::getHash() const {
    return hash;
}

template<typename T>
block<T>::block(block &&other) noexcept {
    index = other.index;
    transactions = other.transactions;
    timestamp = other.timestamp;
    hash = other.hash;
    nonce = other.nonce;
    prevHash = other.prevHash;
    other.prevHash = nullptr;

}

template<typename T>
bool block<T>::isValid() const {
    return calculateHash() == hash;
}

template<typename T>
block<T>::block(const block &other) {
    index = other.index;
    transactions = other.transactions;
    timestamp = other.timestamp;
    hash = other.hash;
    nonce = other.nonce;
    prevHash = new std::size_t(*other.prevHash);
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
    ss << "{" << R"("index" : )" << index << ","
       << R"("timestamp" : )" << timestamp << ","
       << R"("transactions" : )" << vector<T>::jsonify(transactions) << ","
       << R"("hash" : ")" << hash << R"(",)"
       << R"("prevhash" : ")" << *prevHash << R"(",)"
       << R"("nonce" : )" << nonce
       << "}";

    return ss.str();
}

template<typename T>
std::string block<T>::serialize() const {
    std::stringstream ss;
    ss << index << timestamp << vector<T>::serialize(transactions) << nonce << *prevHash;
    return ss.str();

}

#endif //PROYECTO_BLOCKCHAIN_BLOCK_HPP
