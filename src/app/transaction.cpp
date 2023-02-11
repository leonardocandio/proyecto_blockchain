//
// Created by Leonardo Candio on 11/02/23.
//

#include "transaction.h"


transaction::transaction(std::string account, std::string date, std::string transactionDetails,
                         std::string checkingNumber, std::string valueDate, std::string withdrawalAmount,
                         std::string depositAmount, std::string balance) {
    transaction::account = std::move(account);
    transaction::date = std::move(date);
    transaction::transactionDetails = std::move(transactionDetails);
    transaction::checkingNumber = std::move(checkingNumber);
    transaction::valueDate = std::move(valueDate);
    transaction::withdrawalAmount = std::move(withdrawalAmount);
    transaction::depositAmount = std::move(depositAmount);
    transaction::balance = std::move(balance);


}

std::string transaction::serialize() const {
    return account + "," + date + "," + transactionDetails + "," + checkingNumber + "," + valueDate + "," +
           withdrawalAmount + "," + depositAmount + "," + balance;
}
