#ifndef LIST_H
#define LIST_H

// TODO: Implement all methods
#include "node.h"
template<typename T>
class List {
public:
    virtual ~List() = default;
    //Contrato
    virtual T front() = 0;
    virtual T back() = 0;
    virtual void push_front(T) = 0;
    virtual void push_back(T) = 0;
    virtual T pop_front() = 0;
    virtual T pop_back() = 0;
    virtual void insert(T, int) = 0;
    virtual void remove(int) = 0;
    virtual T &operator[](int) = 0;//debe ser declarado en cada clase hija
    virtual bool is_empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual void reverse() = 0;
    virtual std::string name() = 0;
};

#endif
