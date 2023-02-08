//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_NODE_HPP
#define PROYECTO_BLOCKCHAIN_NODE_HPP

#include "utility"

template<class T>
struct node {
    T data;
    node *next;

    node() : next(nullptr), data(nullptr) {}

    template<class... Args>
    explicit node(Args &&... args) : next(nullptr), data(std::forward<Args>(args)...) {}
};

#endif //PROYECTO_BLOCKCHAIN_NODE_HPP
