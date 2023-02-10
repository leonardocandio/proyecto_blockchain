#include "app/blockchain.h"
#include "iostream"


int main(int argc, char *argv[]) {
    blockchain *safe = new blockchain();

    safe->addBlock("Hola");
    safe->addBlock("Hola1");
    safe->addBlock("Hola2");
    safe->addBlock("Hola3");
    safe->addFromFile("/Users/leonardocandio/Desktop/UTEC/2023-0/EDA/proyecto-blockchain/array/transactions.csv");

    std::cout << safe->isChainValid();
}

