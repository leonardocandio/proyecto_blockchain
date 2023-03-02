//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCK_HPP
#define PROYECTO_BLOCKCHAIN_BLOCK_HPP

#include "algorithm"
#include "crow/TinySHA1.hpp"
#include "ctime"
#include "lib/dynamic_array.hpp"
#include "sstream"
//class block
template<typename T>
class block {
public:
    block();

    block(size_t index, dynamic_array<T> transactions, std::string *prevHash);

    block(size_t index, typename dynamic_array<T>::iterator begin, typename dynamic_array<T>::iterator end, std::string *prevHash);

    block(block &&other) noexcept;

    block(const block &other);

    block &operator=(const block &other);

    void mineBlock(unsigned short difficulty, bool bypass = false);

    [[nodiscard]] const std::string &getHash() const;

    [[nodiscard]] std::string calculateHash() const;

    [[nodiscard]] const std::string &getPrevHash() const;

    void setPrevHash(const std::string &prevH);

    [[nodiscard]] const dynamic_array<T> &getTransactions() const;

    [[nodiscard]] const size_t &getIndex() const;

    [[nodiscard]] std::string serialize() const;

    [[nodiscard]] bool isValid() const;

    friend class blockchain;

    [[nodiscard]] std::string jsonify() const;

    virtual ~block();


    dynamic_array<T> transactions;

    typename dynamic_array<T>::iterator transactionsBegin;
    typename dynamic_array<T>::iterator transactionsEnd;

private:
    [[nodiscard]] std::string serializeTransactions() const;

    [[nodiscard]] std::string jsonifyTransactions() const;

    size_t index = 0;
    std::time_t timestamp = 0;
    std::string hash;
    size_t nonce = -1;
    std::string *prevHash = nullptr;
    block *next = nullptr;
};
template<typename T>
block<T>::block(size_t index, typename dynamic_array<T>::iterator begin, typename dynamic_array<T>::iterator end, std::string *prevHash)
    : index(index), transactionsBegin(begin), transactionsEnd(end), timestamp(std::time(nullptr)), prevHash(prevHash) {

    hash = calculateHash();
}

template<typename T>
std::string block<T>::serializeTransactions() const {
    std::stringstream ss;
    for (dynamic_array_iterator<T> it = transactionsBegin; it != transactionsEnd; ++it) {
        ss << (*it)->serialize() << ";";
    }
    return ss.str();
}

template<typename T>
std::string block<T>::jsonifyTransactions() const {
    std::stringstream ss;
    ss << "[";
    for (dynamic_array_iterator<T> it = transactionsBegin; it != transactionsEnd; ++it) {
        ss << (*it)->jsonify();
        if (it + 1 != transactionsEnd) {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}

template<typename T>
block<T>::block() : prevHash(new std::string(40, '0')){};

template<typename T>
block<T>::~block() = default;

template<typename T>
void block<T>::mineBlock(unsigned short difficulty, bool bypass) {
    std::string target(difficulty, '0');
    while (hash.substr(0, difficulty) != target || bypass) {
        nonce++;
        hash = calculateHash();
        if (hash.substr(0, difficulty) == target) {
            break;
        }
    }
}

template<typename T>
std::string block<T>::calculateHash() const {
    std::string ss = jsonify();
    sha1::SHA1 sha1;
    sha1.processBytes(ss.c_str(), ss.size());
    uint32_t digest[5];
    sha1.getDigest(digest);
    char tmp[45];
    snprintf(tmp, 41, "%08x%08x%08x%08x%08x", digest[0], digest[1], digest[2], digest[3], digest[4]);
    return {tmp, 40};
}

template<typename T>
const std::string &block<T>::getPrevHash() const {
    return *prevHash;
}

template<typename T>
void block<T>::setPrevHash(const std::string &prevH) {
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
block<T>::block(size_t index, dynamic_array<T> transactions, std::string *prevHash) : index(index),
                                                                                      transactions(std::move(transactions)),
                                                                                      prevHash(prevHash) {
    timestamp = std::time(nullptr);
    hash = calculateHash();
}


template<typename T>
const std::string &block<T>::getHash() const {
    return hash;
}

template<typename T>
block<T>::block(block &&other) noexcept : index(other.index), transactions(std::move(other.transactions)),
                                          timestamp(other.timestamp), hash(other.hash), nonce(other.nonce),
                                          prevHash(other.prevHash), next(other.next), transactionsBegin(other.transactionsBegin),
                                          transactionsEnd(other.transactionsEnd) {
    other.prevHash = nullptr;
}

template<typename T>
bool block<T>::isValid() const {
    return calculateHash() == hash;
}

template<typename T>
block<T>::block(const block &other) : index(other.index), transactions(other.transactions),
                                      timestamp(other.timestamp), hash(other.hash), nonce(other.nonce),
                                      prevHash(other.prevHash), next(other.next), transactionsBegin(other.transactionsBegin),
                                      transactionsEnd(other.transactionsEnd) {
}

template<typename T>
block<T> &block<T>::operator=(const block &other) {
    if (this == &other) return *this;
    index = other.index;
    transactions = other.transactions;
    transactionsEnd = other.transactionsEnd;
    transactionsBegin = other.transactionsBegin;
    timestamp = other.timestamp;
    hash = other.hash;
    nonce = other.nonce;
    prevHash = other.prevHash;
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
