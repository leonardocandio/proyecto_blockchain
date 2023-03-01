//
// Created by Leonardo Candio on 11/02/23.
//

#include "transaction.h"
#include <sstream>
#include <utility>


transaction::transaction(unsigned short step, std::string type, double amount, std::string nameOrig,
                         double oldbalanceOrg,
                         double newbalanceOrig,
                         std::string nameDest, double oldbalanceDest, double newbalanceDest) :
        step(step), type(std::move(type)), amount(amount), nameOrig(std::move(nameOrig)), oldbalanceOrg(oldbalanceOrg),
        newbalanceOrig(newbalanceOrig),
        nameDest(std::move(nameDest)), oldbalanceDest(oldbalanceDest), newbalanceDest(newbalanceDest) {}

std::string transaction::jsonify() const {
    std::stringstream ss;
    ss << R"({"step":)" << step
       << R"(,"type":")" << type
       << R"(","amount":)" << amount
       << R"(,"nameOrig":")" << nameOrig
       << R"(","oldbalanceOrg":)" << oldbalanceOrg
       << R"(,"newbalanceOrig":)" << newbalanceOrig
       << R"(,"nameDest":")" << nameDest
       << R"(","oldbalanceDest":)" << oldbalanceDest
       << R"(,"newbalanceDest":)" << newbalanceDest << "}";
    return ss.str();
}

std::string transaction::serialize() const {
    std::stringstream ss;
    ss << step << ",";
    ss << type << ",";
    ss << amount << ",";
    ss << oldbalanceOrg << ",";
    ss << newbalanceOrig << ",";
    ss << nameDest << ",";
    ss << oldbalanceDest << ",";
    ss << newbalanceDest;
    return ss.str();
}

double transaction::getAmount() const {
    return amount;
}

std::string transaction::getNameDest() const{
    return nameDest;
}
std::string transaction::getTipePay() const{
    return type;
}