//
// Created by Leonardo Candio on 11/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_TRANSACTION_H
#define PROYECTO_BLOCKCHAIN_TRANSACTION_H

#include "string"

class transaction {
public:
    transaction() = default;

    transaction(unsigned short step, std::string type, double amount, std::string nameOrig, double oldbalanceOrg,
                double newbalanceOrig,
                std::string nameDest, double oldbalanceDest, double newbalanceDest);

    [[nodiscard]] std::string jsonify() const;

    [[nodiscard]] std::string serialize() const;

    [[nodiscard]] double getAmount() const;
    [[nodiscard]] std::string getNameDest() const;

private:
    unsigned short step{};
    std::string type;
    double amount{};
    std::string nameOrig;
    double oldbalanceOrg{};
    double newbalanceOrig{};
    std::string nameDest;
    double oldbalanceDest{};
    double newbalanceDest{};


};


#endif //PROYECTO_BLOCKCHAIN_TRANSACTION_H
