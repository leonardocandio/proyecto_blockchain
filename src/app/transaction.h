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

    std::string jsonify() const;

    std::string serialize() const;

private:
    unsigned short step;
    std::string type;
    double amount;
    std::string nameOrig;
    double oldbalanceOrg;
    double newbalanceOrig;
    std::string nameDest;
    double oldbalanceDest;
    double newbalanceDest;


};


#endif //PROYECTO_BLOCKCHAIN_TRANSACTION_H