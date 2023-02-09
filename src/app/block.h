//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCK_H
#define PROYECTO_BLOCKCHAIN_BLOCK_H

#include "ctime"
#include "sstream"
#include "algorithm"

class block {
public:
    block();

    block(uint64_t index, std::string data);

    block(uint64_t index, std::string data, std::size_t *prevHash);


    void mineBlock(uint64_t difficulty);

    [[nodiscard]] const std::size_t &getHash() const;

    [[nodiscard]] std::size_t calculateHash() const;

    [[nodiscard]] const std::size_t &getPrevHash() const;

    void setPrevHash(const std::size_t &prevHash);

    [[nodiscard]] const std::string &getData() const;

    [[nodiscard]] const uint64_t &getIndex() const;

    bool isValid() const;

    friend class blockchain;

    virtual ~block();


private:
    uint64_t index;
    std::string data;
    std::time_t timestamp;
    std::size_t hash;
    uint64_t nonce;
    std::size_t *prevHash;


};


#endif //PROYECTO_BLOCKCHAIN_BLOCK_H
