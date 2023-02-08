//
// Created by Leonardo Candio on 7/02/23.
//

#include "block.h"
#include "iostream"
#include <utility>

block::block(uint64_t index, std::string data) : index(index), data(std::move(data)) {
    timestamp = std::time(nullptr);
    nonce = -1;
    mdout = static_cast<unsigned char *>(OPENSSL_malloc(EVP_MAX_MD_SIZE));
    sha256 = EVP_MD_fetch(nullptr, "SHA256", nullptr);
}

std::string block::getHash() {
    return hash;
}

void block::mineBlock(uint64_t difficulty) {
    while (true) {
        timestamp = std::time(nullptr);
        for (uint64_t i = 0; i < UINT64_MAX; ++i) {
            nonce = i;
            hash = calculateHash();
            if (hash.substr(0, difficulty) == std::string(difficulty, '0')) {
                return;
            }
        }
        timestamp = std::time(nullptr);
    }

}

std::string block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << data << nonce << prevHash;
    EVP_Digest(ss.str().c_str(), ss.str().length(), mdout, nullptr, sha256, nullptr);

    return {reinterpret_cast<char *>(mdout)};
}

const std::string &block::getPrevHash() const {
    return prevHash;
}

void block::setPrevHash(const std::string &prevHash) {
    block::prevHash = prevHash;
}

block::~block() {
}

const std::string &block::getData() const {
    return data;
}

const uint64_t &block::getIndex() const {
    return index;
}

block *block::getPrevBlock() const {
    return prevBlock;
}

void block::setPrevBlock(block *pBlock) {
    prevBlock = pBlock;
}
