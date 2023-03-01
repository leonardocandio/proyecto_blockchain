#ifndef NODE_H
#define NODE_H

template<typename T>
struct NodeList {
    T data;
    NodeList<T> *next;
    NodeList<T> *prev;

    NodeList() : data(0), next(nullptr), prev(nullptr) {}

    NodeList(T _data) : data(_data), next(nullptr), prev(nullptr) {}

    void killSelf() {
        prev->next = next;
        next->prev = prev;
        next = nullptr;
        prev = nullptr;
    }
};

#endif