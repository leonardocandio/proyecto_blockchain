//
// Created by Leonardo Candio on 11/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_TRANSACTION_H
#define PROYECTO_BLOCKCHAIN_TRANSACTION_H

#include "string"
class transaction {
public:
    transaction() = default;

    transaction(std::string account, std::string date, std::string transactionDetails, std::string checkingNumber,
                std::string valueDate, std::string withdrawalAmount, std::string depositAmount,
                std::string balance);

    std::string serialize() const;


private:
    std::string account;
    std::string date;
    std::string transactionDetails;
    std::string checkingNumber;
    std::string valueDate;
    std::string withdrawalAmount;
    std::string depositAmount;
    std::string balance;
};


#endif //PROYECTO_BLOCKCHAIN_TRANSACTION_H
