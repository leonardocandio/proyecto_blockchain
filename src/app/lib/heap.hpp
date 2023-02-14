//
// Created by Leonardo Candio on 13/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_HEAP_HPP
#define PROYECTO_BLOCKCHAIN_HEAP_HPP

#include "functional"
#include "dynamic_array.hpp"

template<class IndexT, class DataT>
class heap : public dynamic_array<std::pair<IndexT, DataT>> {
public:
    std::pair<IndexT, DataT> top() {
        return elements[0];
    }


    heap(dynamic_array<std::pair<IndexT, DataT>> &array, std::function<bool(std::pair<IndexT, DataT>, std::pair<IndexT, DataT>)> comparator) {
        this->elements = array;
        this->comparator = comparator;
        this->_size = array.size();
        buildHeap();
    }

private:

    dynamic_array<std::pair<IndexT, DataT>> elements;
    std::function<bool(std::pair<IndexT, DataT>, std::pair<IndexT, DataT>)> comparator;

    void buildHeap() {
        for (int i = this->_size / 2; i >= 0; --i) {
            heapify_down(i);
        }
    }

    int left(int index) {
        return 2 * index + 1;
    }

    int right(int index) {
        return 2 * index + 2;
    }

    int parent(int index) {
        return (index - 1) / 2;
    }

    void heapify_down(int parent) {
        int hleft = left(parent);
        int hright = right(parent);
        int large = parent;

        if (hleft < this->_size and comparator(elements[hleft].first, elements[large].first)) large = hleft;
        if (hright < this->_size and comparator(elements[hright].first, elements[large].first)) large = hright;
        if (large != parent) {
            swap(elements[large], elements[parent]);
            heapify_down(large);
        }
    }

    void heapify_up(int child) {
        int pp = parent(child);
        if (pp < this->size and comparator(elements[child].first, elements[pp].first)) {
            std::swap(elements[pp], elements[child]);
            heapify_up(pp);
        }
    }


};

#endif //PROYECTO_BLOCKCHAIN_HEAP_HPP
