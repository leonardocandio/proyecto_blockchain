//
// Created by Leonardo Candio on 7/02/23.
//

#include "block.h"
#include "iostream"
#include <utility>

block::block(uint64_t index, std::string data) : index(index), data(std::move(data)) {
    timestamp = std::time(nullptr);
    nonce = -1;
    prevHash = new std::size_t();
}

void block::mineBlock(uint64_t difficulty) {
    std::string target(difficulty, '0');
    do {
        nonce++;
        hash = calculateHash();
    } while (std::to_string(hash).substr(std::to_string(hash).size() - difficulty) != target);
    std::cout << "Block mined: " << hash << std::endl;
}

std::size_t block::calculateHash() const {
    std::stringstream ss;
    std::hash<std::string> newHash;
    ss << index << timestamp << data << nonce << prevHash;
    return newHash(ss.str());
}

const std::size_t &block::getPrevHash() const {
    return *prevHash;
}

void block::setPrevHash(const std::size_t &prevHash) {
    *block::prevHash = prevHash;
}

block::~block() {
}

const std::string &block::getData() const {
    return data;
}

const uint64_t &block::getIndex() const {
    return index;
}

block::block(uint64_t index, std::string data, std::size_t *prevHash) {
    block::index = index;
    block::data = std::move(data);
    block::prevHash = prevHash;
    timestamp = std::time(nullptr);
    nonce = -1;

}

block::block() {
}

const std::size_t &block::getHash() const {
    return hash;
}


