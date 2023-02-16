//
// Created by Leonardo Candio on 9/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_VECTOR_ITERATOR_HPP
#define PROYECTO_BLOCKCHAIN_VECTOR_ITERATOR_HPP

#include "vector.hpp"

template<class T>
class vector_iterator {
public:
    vector_iterator() : current(nullptr) {}

    explicit vector_iterator(T *p) : current(p) {}

    T &operator*() const { return retrieve(); }

    T *operator->() { return &retrieve(); }

    vector_iterator &operator++() {
        ++current;
        return *this;
    }

    const vector_iterator operator++(int) {
        vector_iterator old = *this;
        ++(*this);
        return old;
    }

    vector_iterator &operator--() {
        --current;
        return *this;
    }

    const vector_iterator operator--(int) {
        vector_iterator old = *this;
        --(*this);
        return old;
    }

    vector_iterator &operator+(int n) {
        current += n;
        return *this;
    }

    vector_iterator &operator-(int n) {
        current -= n;
        return *this;
    }


    bool operator==(const vector_iterator &rhs) const { return current == rhs.current; }

    bool operator!=(const vector_iterator &rhs) const { return current != rhs.current; }

private:
    T *current;

    T &retrieve() const { return *current; }
};

#endif //PROYECTO_BLOCKCHAIN_VECTOR_ITERATOR_HPP
