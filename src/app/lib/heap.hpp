//
// Created by Leonardo Candio on 13/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_HEAP_HPP
#define PROYECTO_BLOCKCHAIN_HEAP_HPP

#include "dynamic_array.hpp"
#include "functional"

//heap method for index(max and min values in transactions)
template<class IndexT, class DataT>
class heap : private dynamic_array<std::pair<IndexT, DataT>> {
public:
    heap() = default;

    explicit heap(std::function<bool(IndexT, IndexT)> comparator)
        : dynamic_array<std::pair<IndexT, DataT>>(), comparator(comparator) {
    }

    heap(const heap &other) : dynamic_array<std::pair<IndexT, DataT>>(other), comparator(other.comparator) {}

    ~heap() = default;

    heap &operator=(const heap &other) {
        dynamic_array<std::pair<IndexT, DataT>>::operator=(other);
        comparator = other.comparator;
        return *this;
    }

    void push(std::pair<IndexT, DataT> element) {
        this->push_back(element);
        heapify_up(this->size() - 1);
    }

    void pop() {
        this->operator[](0) = this->operator[](this->size() - 1);
        this->pop_back();
        heapify_down(0);
    }

    std::pair<IndexT, DataT> top() {
        return this->operator[](0);
    }

private:
    std::function<bool(IndexT, IndexT)> comparator;

    void buildHeap() {
        for (long i = (this->size() / 2); i >= 0; --i) {
            heapify_down(i);
        }
    }

    size_t left(size_t index) {
        return 2 * index + 1;
    }

    size_t right(size_t index) {
        return 2 * index + 2;
    }

    size_t parent(size_t index) {
        return (index - 1) / 2;
    }

    void heapify_down(size_t parent) {
        size_t hleft = left(parent);
        size_t hright = right(parent);
        size_t large = parent;

        if (hleft < this->size() && comparator(this->operator[](hleft).first, this->operator[](large).first)) large = hleft;
        if (hright < this->size() && comparator(this->operator[](hright).first, this->operator[](large).first)) large = hright;
        if (large != parent) {
            swap(this->operator[](large), this->operator[](parent));
            heapify_down(large);
        }
    }

    void heapify_up(size_t child) {
        size_t pp = parent(child);
        if (pp < this->size() && comparator(this->operator[](child).first, this->operator[](pp).first)) {
            std::swap(this->operator[](pp), this->operator[](child));
            heapify_up(pp);
        }
    }
};

#endif//PROYECTO_BLOCKCHAIN_HEAP_HPP
