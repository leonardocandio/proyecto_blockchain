//
// Created by Leonardo Candio on 9/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_ITERATOR_HPP
#define PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_ITERATOR_HPP

#include "dynamic_array.hpp"
#include "iterator"

//iterator for dynamic array
template<class T>
struct dynamic_array_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    explicit dynamic_array_iterator(pointer ptr) : ptr(ptr) {}
    dynamic_array_iterator() = default;
    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }
    dynamic_array_iterator &operator++() {
        ++ptr;
        return *this;
    }
    const dynamic_array_iterator operator++(int) {
        dynamic_array_iterator tmp(*this);
        operator++();
        return tmp;
    }
    dynamic_array_iterator &operator--() {
        --ptr;
        return *this;
    }
    const dynamic_array_iterator operator--(int) {
        dynamic_array_iterator tmp(*this);
        operator--();
        return tmp;
    }
    dynamic_array_iterator &operator+=(difference_type n) {
        ptr += n;
        return *this;
    }
    dynamic_array_iterator &operator-=(difference_type n) {
        ptr -= n;
        return *this;
    }
    dynamic_array_iterator operator+(difference_type n) const {
        dynamic_array_iterator tmp(*this);
        return tmp += n;
    }
    dynamic_array_iterator operator-(difference_type n) const {
        dynamic_array_iterator tmp(*this);
        return tmp -= n;
    }
    difference_type operator-(const dynamic_array_iterator &other) const { return ptr - other.ptr; }
    friend bool operator==(const dynamic_array_iterator &lhs, const dynamic_array_iterator &rhs) { return lhs.ptr == rhs.ptr; }
    friend bool operator!=(const dynamic_array_iterator &lhs, const dynamic_array_iterator &rhs) { return lhs.ptr != rhs.ptr; }
    friend bool operator<(const dynamic_array_iterator &lhs, const dynamic_array_iterator &rhs) { return lhs.ptr < rhs.ptr; }
    friend bool operator>(const dynamic_array_iterator &lhs, const dynamic_array_iterator &rhs) { return lhs.ptr > rhs.ptr; }


private:
    pointer ptr;
};

#endif//PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_ITERATOR_HPP
