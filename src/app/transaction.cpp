//
// Created by Leonardo Candio on 11/02/23.
//

#include "transaction.h"

#include <utility>


transaction::transaction(unsigned short step, double amount, double oldbalanceOrg, double newbalanceOrig,
                         std::string nameDest, double oldbalanceDest, double newbalanceDest) :
        step(step), amount(amount), oldbalanceOrg(oldbalanceOrg), newbalanceOrig(newbalanceOrig),
        nameDest(std::move(nameDest)), oldbalanceDest(oldbalanceDest), newbalanceDest(newbalanceDest) {}
