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

    block(uint64_t index, vector<T *> transactions, std::size_t *prevHash);

    block(block &&other) noexcept;

    block(const block &other);

    block(vector<T *> transactions, unsigned long i);

    block &operator=(const block &other);

    void mineBlock(uint64_t difficulty);

    [[nodiscard]] const std::size_t &getHash() const;

    [[nodiscard]] std::size_t calculateHash() const;

    [[nodiscard]] const std::size_t &getPrevHash() const;

    void setPrevHash(const std::size_t &prevHash);

    [[nodiscard]] const vector<T *> &getTransactions() const;

    [[nodiscard]] const uint64_t &getIndex() const;

    std::string serialize() const;


    [[nodiscard]] bool isValid() const;

    friend class blockchain;

    [[nodiscard]] std::string jsonify() const;

    virtual ~block();


private:
    uint64_t index;
    vector<T *> transactions;
    std::time_t timestamp;
    std::size_t hash;
    uint64_t nonce;
    std::size_t *prevHash;


};

template<typename T>
block<T>::block(vector<T *> transactions, unsigned long i) {

}


template<typename T>
void block<T>::mineBlock(uint64_t difficulty) {
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
    ss << index << timestamp << serialize(transactions) << nonce << *prevHash;
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
const uint64_t &block<T>::getIndex() const {
    return index;
}

template<typename T>
block<T>::block(uint64_t index, vector<T *> transactions, std::size_t *prevHash) {
    block::index = index;
    block::prevHash = prevHash;
    timestamp = std::time(nullptr);
    nonce = -1;

}

template<typename T>
block<T>::block() {
}

template<typename T>
const std::size_t &block<T>::getHash() const {
    return hash;
}

template<typename T>
block<T>::block(block &&other) noexcept {
    index = other.index;
    data = std::move(other.data);
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
    data = other.data;
    timestamp = other.timestamp;
    hash = other.hash;
    nonce = other.nonce;
    prevHash = new std::size_t(*other.prevHash);
}

template<typename T>
block<T> &block<T>::operator=(const block &other) {
    if (this == &other) return *this;
    index = other.index;
    data = other.data;
    timestamp = other.timestamp;
    hash = other.hash;
    nonce = other.nonce;
    prevHash = new std::size_t(*other.prevHash);
    return *this;
}


template<typename T>
std::string block<T>::jsonify() const {
    std::stringstream ss;
    ss << "{" << "\"index\" : " << index << ","
       << R"("timestamp" : ")" << timestamp << "\","
       << R"("transactions" : ")" << vector<T>::jsonify(transactions) << "\","
       << R"("hash" : ")" << hash << "\","
       << R"("prevhash" : ")" << *prevHash << "\","
       << "\"nonce\" : " << nonce
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
