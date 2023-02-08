//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_BLOCK_H
#define PROYECTO_BLOCKCHAIN_BLOCK_H

#include "ctime"
#include "sstream"
#include "openssl/evp.h"

class block {
public:

    block(uint64_t index, std::string data);

    std::string getHash();

    void mineBlock(uint64_t difficulty);

    [[nodiscard]] std::string calculateHash() const;

    const std::string &getPrevHash() const;

    void setPrevHash(const std::string &prevHash);

private:
    uint64_t index;
    std::string data;
    std::time_t timestamp;
    std::string hash;
    uint64_t nonce;
    std::string prevHash;

    EVP_MD *sha256;
    unsigned char *mdout;

public:
    virtual ~block();

};


#endif //PROYECTO_BLOCKCHAIN_BLOCK_H
