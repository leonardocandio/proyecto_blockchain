//
// Created by Leonardo Candio on 13/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_HEAP_HPP
#define PROYECTO_BLOCKCHAIN_HEAP_HPP

#include "functional"
#include "dynamic_array.hpp"

//heap method for index(max and min values in transactions)
template<class IndexT, class DataT>
class heap : public dynamic_array<std::pair<IndexT, DataT>> {
public:

    heap() = default;

    explicit heap(std::function<bool(IndexT, IndexT)> comparator) : comparator(comparator) {
        this->_size = 0;
        elements = dynamic_array<std::pair<IndexT, DataT>>();

    }

    heap(const heap &other) : comparator(other.comparator), elements(other.elements) {
        this->_size = other._size;
    }

    heap &operator=(const heap &other) {
        if (this != &other) {
            this->_size = other._size;
            elements = other.elements;
            comparator = other.comparator;
        }
        return *this;
    }

    void push(std::pair<IndexT, DataT> element) {
        elements.push_back(element);
        heapify_up(this->_size);
        this->_size++;
    }

    void pop() {
        elements[0] = elements[this->_size - 1];
        elements.pop_back();
        this->_size--;
        heapify_down(0);
    }

    std::pair<IndexT, DataT> top() {
        return elements[0];
    }

private:

    std::function<bool(IndexT, IndexT)> comparator;
    dynamic_array<std::pair<IndexT, DataT>> elements;

    void buildHeap() {
        for (long i = (this->_size / 2); i >= 0; --i) {
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

        if (hleft < this->_size and comparator(elements[hleft].first, elements[large].first)) large = hleft;
        if (hright < this->_size and comparator(elements[hright].first, elements[large].first)) large = hright;
        if (large != parent) {
            swap(elements[large], elements[parent]);
            heapify_down(large);
        }
    }

    void heapify_up(size_t child) {
        size_t pp = parent(child);
        if (pp < this->_size and comparator(elements[child].first, elements[pp].first)) {
            std::swap(elements[pp], elements[child]);
            heapify_up(pp);
        }
    }


};

#endif //PROYECTO_BLOCKCHAIN_HEAP_HPP
