//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_NODE_HPP
#define PROYECTO_BLOCKCHAIN_NODE_HPP

#include "utility"

struct basic_node {
    basic_node *next;
};

template<class T>
struct node : basic_node {
    T data;

    template<class... Args>
    explicit node(Args &&... args) : data(std::forward<Args>(args)...) {}
};

#endif //PROYECTO_BLOCKCHAIN_NODE_HPP
