//
// Created by Leonardo Candio on 9/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_ITERATOR_HPP
#define PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_ITERATOR_HPP

#include "dynamic_array.hpp"

//iterator for dynamic array
template<class T>
class dynamic_array_iterator {
public:
    dynamic_array_iterator() : current(nullptr) {}

    explicit dynamic_array_iterator(T *p) : current(p) {}

    T &operator*() const { return retrieve(); }

    T *operator->() { return &retrieve(); }

    virtual dynamic_array_iterator &operator++() {
        ++current;
        return *this;
    }

    virtual const dynamic_array_iterator operator++(int) {
        dynamic_array_iterator old = *this;
        ++(*this);
        return old;
    }

    virtual dynamic_array_iterator &operator--() {
        --current;
        return *this;
    }

    const dynamic_array_iterator operator--(int) {
        dynamic_array_iterator old = *this;
        --(*this);
        return old;
    }

    virtual dynamic_array_iterator &operator+(int n) {
        current += n;
        return *this;
    }

    virtual dynamic_array_iterator &operator-(int n) {
        current -= n;
        return *this;
    }

    virtual long operator-(dynamic_array_iterator &rhs) {
        return current - rhs.current;
    }

    virtual dynamic_array_iterator &operator+=(int n) {
        current += n;
        return *this;
    }
    bool operator<(const dynamic_array_iterator &rhs) const { return current < rhs.current; }
    bool operator>(const dynamic_array_iterator &rhs) const { return current > rhs.current; }


    bool operator==(const dynamic_array_iterator &rhs) const { return current == rhs.current; }

    bool operator!=(const dynamic_array_iterator &rhs) const { return current != rhs.current; }

private:
    T *current;

    T &retrieve() const { return *current; }
};

#endif//PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_ITERATOR_HPP
