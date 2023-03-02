//
// Created by Leonardo Candio on 7/02/23.
//

#include "blockchain.h"
#include "iostream"
#include "sstream"
#include <utility>

bool blockchain::isChainValid() const { return false; }

blockchain::blockchain(size_t _size, unsigned short difficulty) : _size(_size), difficulty(difficulty), lastBlock(firstBlock) {
    firstBlock->mineBlock(difficulty);
    maxHeapAmount =
            heap<double, transaction *>([](double a, double b) { return a > b; });
    minHeapAmount =
            heap<double, transaction *>([](double a, double b) { return a < b; });
    maxHeapOldbalanceOrg =
            heap<double, transaction *>([](double a, double b) { return a > b; });
    minHeapOldbalanceOrg =
            heap<double, transaction *>([](double a, double b) { return a < b; });
    maxHeapNewbalanceOrig =
            heap<double, transaction *>([](double a, double b) { return a > b; });
    minHeapNewbalanceOrig =
            heap<double, transaction *>([](double a, double b) { return a < b; });
    maxHeapNewbalanceDest =
            heap<double, transaction *>([](double a, double b) { return a > b; });
    minHeapNewbalanceDest =
            heap<double, transaction *>([](double a, double b) { return a < b; });
    maxHeapOldbalanceDest =
            heap<double, transaction *>([](double a, double b) { return a > b; });
    minHeapOldbalanceDest =
            heap<double, transaction *>([](double a, double b) { return a < b; });
}

blockchain::~blockchain() {
    block<transaction *> *currentBlock = firstBlock;
    while (currentBlock != nullptr) {
        block<transaction *> *nextBlock = currentBlock->next;
        delete currentBlock;
        currentBlock = nextBlock;
    }
}

void blockchain::addFromFile(const std::string &path, bool skipFirstLine, size_t transactionPerBlock) {

    std::fstream file(path, std::ios::in);
    dynamic_array<transaction *> newTransactions;

    if (!file.is_open()) return;

    std::string line;
    if (skipFirstLine) std::getline(file, line);
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string item;
        dynamic_array<std::string> lineV;
        while (std::getline(ss, item, ',')) {
            lineV.push_back(item);
        }
        transactions.push_back(
                new transaction((unsigned short) std::stoi(lineV[0]), lineV[1], std::stod(lineV[2]), lineV[3], std::stod(lineV[4]),
                                std::stod(lineV[5]), lineV[6], std::stod(lineV[7]), std::stod(lineV[8])));
        maxHeapAmount.push(std::make_pair(transactions.back()->getAmount(), transactions.back()));
        minHeapAmount.push(std::make_pair(transactions.back()->getAmount(), transactions.back()));
        maxHeapOldbalanceOrg.push(std::make_pair(transactions.back()->getOldbalanceOrg(), transactions.back()));
        minHeapOldbalanceOrg.push(std::make_pair(transactions.back()->getOldbalanceOrg(), transactions.back()));
        maxHeapNewbalanceOrig.push(std::make_pair(transactions.back()->getNewbalanceOrig(), transactions.back()));
        minHeapNewbalanceOrig.push(std::make_pair(transactions.back()->getNewbalanceOrig(), transactions.back()));
        maxHeapOldbalanceDest.push(std::make_pair(transactions.back()->getOldbalanceDest(), transactions.back()));
        minHeapOldbalanceDest.push(std::make_pair(transactions.back()->getOldbalanceDest(), transactions.back()));
        maxHeapNewbalanceDest.push(std::make_pair(transactions.back()->getNewbalanceDest(), transactions.back()));
        minHeapNewbalanceDest.push(std::make_pair(transactions.back()->getNewbalanceDest(), transactions.back()));

        patricia.insert(lineV[6], transactions.back());
        hashMap.set(transactions.back()->getuniq(), transactions.back());

        bTreeAmount.insert(transactions.back()->getAmount(), transactions.back());
        bTreeNewbalanceDest.insert(transactions.back()->getNewbalanceDest(), transactions.back());
        bTreeNewbalanceOrig.insert(transactions.back()->getNewbalanceOrig(), transactions.back());
        bTreeOldbalanceDest.insert(transactions.back()->getOldbalanceDest(), transactions.back());
        bTreeOldbalanceOrg.insert(transactions.back()->getOldbalanceOrg(), transactions.back());
    }
    transactionsToBlocks(transactionPerBlock);
}


std::string blockchain::jsonify() const {
    std::stringstream ss;
    ss << "[";
    auto *currentBlock = firstBlock;
    while (currentBlock != nullptr) {
        ss << currentBlock->jsonify();
        currentBlock = currentBlock->next;
        if (currentBlock != nullptr) {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}

void blockchain::addBlock(const dynamic_array<transaction *> &newTransactions) {
    indexNewData(newTransactions);

    lastBlock->next = new block<transaction *>(lastBlock->getIndex() + 1,
                                               newTransactions, &lastBlock->hash);
    lastBlock = lastBlock->next;
    lastBlock->mineBlock(difficulty);
    _size++;
}

void blockchain::addBlock(const dynamic_array_iterator<transaction *> &begin, const dynamic_array_iterator<transaction *> &end) {
    indexNewData(begin, end);
    auto start = transactions.end() - (end - begin);
    auto finish = transactions.end();
    lastBlock->next = new block<transaction *>(lastBlock->getIndex() + 1,
                                               start, finish, &lastBlock->hash);
    lastBlock = lastBlock->next;
    lastBlock->mineBlock(difficulty);
    _size++;
}


block<transaction *> *blockchain::getLastBlock() { return lastBlock; }

void blockchain::indexNewData(const dynamic_array<transaction *> &newT) {
    for (const auto &t: newT) {
        transactions.push_back(t);
        maxHeapAmount.push(std::make_pair(t->getAmount(), t));
        minHeapAmount.push(std::make_pair(t->getAmount(), t));
        patricia.insert(t->getNameDest(), t);
        hashMap.set(t->getuniq(), t);
        maxHeapOldbalanceOrg.push(std::make_pair(t->getOldbalanceOrg(), t));
        minHeapOldbalanceOrg.push(std::make_pair(t->getOldbalanceOrg(), t));
        maxHeapNewbalanceOrig.push(std::make_pair(t->getNewbalanceOrig(), t));
        minHeapNewbalanceOrig.push(std::make_pair(t->getNewbalanceOrig(), t));
        maxHeapOldbalanceDest.push(std::make_pair(t->getOldbalanceDest(), t));
        minHeapOldbalanceDest.push(std::make_pair(t->getOldbalanceDest(), t));
        maxHeapNewbalanceDest.push(std::make_pair(t->getNewbalanceDest(), t));
        minHeapNewbalanceDest.push(std::make_pair(t->getNewbalanceDest(), t));
    }
}

size_t blockchain::getSize() const { return _size; }

dynamic_array<transaction *> blockchain::getTransactionsByParamType(const std::string &param,
                                                                    const std::string &type,
                                                                    size_t limit,
                                                                    size_t rangeLow,
                                                                    size_t rangeHigh) {
    dynamic_array<transaction *> result;
    switch (resolveSearchParam(param)) {
        case ALL: {
            result.push_back(hashMap[type]);
            break;
        }
        case AMOUNT: {
            switch (resolveSearchType(type)) {
                case MAX: {
                    auto temp = maxHeapAmount;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp.top().second);
                        temp.pop();
                    }
                    break;
                }
                case MIN: {
                    auto temp2 = minHeapAmount;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp2.top().second);
                        temp2.pop();
                    }
                    break;
                }
                case RANGE: {
                    result = bTreeAmount.rangeSearch(rangeLow, rangeHigh);
                    break;
                }
            }
            break;
        }
        case TYPE: {
            break;
        }
        case NAMEORIG: {
            break;
        }
        case OLDBALANCEORG: {
            switch (resolveSearchType(type)) {
                case MAX: {
                    auto temp = maxHeapOldbalanceOrg;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp.top().second);
                        temp.pop();
                    }
                    break;
                }
                case MIN: {
                    auto temp2 = minHeapOldbalanceOrg;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp2.top().second);
                        temp2.pop();
                    }
                    break;
                }
                case RANGE: {
                    result = bTreeOldbalanceOrg.rangeSearch(rangeLow, rangeHigh);
                    break;
                }
            }
            break;
        }
        case NEWBALANCEORIG: {
            switch (resolveSearchType(type)) {
                case MAX: {
                    auto temp = maxHeapNewbalanceOrig;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp.top().second);
                        temp.pop();
                    }
                    break;
                }
                case MIN: {
                    auto temp2 = minHeapNewbalanceOrig;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp2.top().second);
                        temp2.pop();
                    }
                    break;
                }
                case RANGE: {
                    result = bTreeNewbalanceOrig.rangeSearch(rangeLow, rangeHigh);
                    break;
                }
            }
            break;
        }
        case NAMEDEST: {
            break;
        }
        case OLDBALANCEDEST: {
            switch (resolveSearchType(type)) {
                case MAX: {
                    auto temp = maxHeapOldbalanceDest;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp.top().second);
                        temp.pop();
                    }
                    break;
                }
                case MIN: {
                    auto temp2 = minHeapOldbalanceDest;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp2.top().second);
                        temp2.pop();
                    }
                    break;
                }
                case RANGE: {
                    result = bTreeOldbalanceDest.rangeSearch(rangeLow, rangeHigh);
                    break;
                }
            }
            break;
        }
        case NEWBALANCEDEST: {
            switch (resolveSearchType(type)) {
                case MAX: {
                    auto temp = maxHeapNewbalanceDest;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp.top().second);
                        temp.pop();
                    }
                    break;
                }
                case MIN: {
                    auto temp2 = minHeapNewbalanceDest;
                    for (size_t i = 0; i < limit; i++) {
                        result.push_back(temp2.top().second);
                        temp2.pop();
                    }
                    break;
                }
                case RANGE: {
                    result = bTreeNewbalanceDest.rangeSearch(rangeLow, rangeHigh);
                    break;
                }
            }
            break;
        }
    }
    return result;
}

blockchain::searchType blockchain::resolveSearchType(std::string_view const &type) const {
    if (type == "max") {
        return MAX;
    } else if (type == "min") {
        return MIN;
    } else if (type == "range") {
        return RANGE;
    } else {
        throw std::invalid_argument("Invalid search type");
    }
}
blockchain::searchParam blockchain::resolveSearchParam(const std::string_view &param) const {
    if (param == "amount") {
        return AMOUNT;
    } else if (param == "oldbalanceOrg") {
        return OLDBALANCEORG;
    } else if (param == "newbalanceOrig") {
        return NEWBALANCEORIG;
    } else if (param == "oldbalanceDest") {
        return OLDBALANCEDEST;
    } else if (param == "newbalanceDest") {
        return NEWBALANCEDEST;
    } else if (param == "all") {
        return ALL;
    } else {
        throw std::invalid_argument("Invalid search param");
    }
}
void blockchain::transactionsToBlocks(size_t transactionsPerBlock) {
    auto start = transactions.begin();
    auto finish = start + (int) transactionsPerBlock;
    while (start != transactions.end()) {
        lastBlock->next = new block<transaction *>(lastBlock->getIndex() + 1,
                                                   start, finish, &lastBlock->hash);
        lastBlock = lastBlock->next;
        lastBlock->mineBlock(difficulty);
        _size++;
        start = finish;
        finish = start + (int) transactionsPerBlock;
        if (finish > transactions.end()) {
            finish = transactions.end();
        }
    }
}
void blockchain::indexNewData(const dynamic_array_iterator<transaction *> &begin, const dynamic_array_iterator<transaction *> &end) {
    for (auto it = begin; it != end; it++) {
        transactions.push_back(*it);
        maxHeapAmount.push(std::make_pair((*it)->getAmount(), *it));
        minHeapAmount.push(std::make_pair((*it)->getAmount(), *it));
        maxHeapOldbalanceOrg.push(std::make_pair((*it)->getOldbalanceOrg(), *it));
        minHeapOldbalanceOrg.push(std::make_pair((*it)->getOldbalanceOrg(), *it));
        maxHeapNewbalanceOrig.push(std::make_pair((*it)->getNewbalanceOrig(), *it));
        minHeapNewbalanceOrig.push(std::make_pair((*it)->getNewbalanceOrig(), *it));
        maxHeapOldbalanceDest.push(std::make_pair((*it)->getOldbalanceDest(), *it));
        minHeapOldbalanceDest.push(std::make_pair((*it)->getOldbalanceDest(), *it));
        maxHeapNewbalanceDest.push(std::make_pair((*it)->getNewbalanceDest(), *it));
        minHeapNewbalanceDest.push(std::make_pair((*it)->getNewbalanceDest(), *it));


        patricia.insert((*it)->getNameDest(), *it);
        hashMap.set((*it)->getuniq(), (*it));
    }
}

void blockchain::recalculo() {
    auto temp = firstBlock;
    for (int i = 0; i < 3; ++i) {
        temp = temp->next;
    }
    std::cout << temp->jsonify() << std::endl;
    for (auto t = temp->transactionsBegin; t != temp->transactionsEnd; ++t) {
        (*t)->amount += 99;
        (*t)->oldbalanceOrg += 99;
        (*t)->newbalanceOrig += 99;
        (*t)->oldbalanceDest += 99;
        (*t)->newbalanceDest += 99;
    }
    temp->timestamp = time(nullptr);
    while (temp != nullptr) {
        temp->mineBlock(difficulty, true);
        temp = temp->next;
    }
    temp = firstBlock;
    for (int i = 0; i < 3; ++i) {
        temp = temp->next;
    }
    std::cout << temp->jsonify() << std::endl;
}
