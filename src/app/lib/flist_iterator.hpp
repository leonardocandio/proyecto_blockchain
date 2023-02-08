//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_FLIST_ITERATOR_HPP
#define PROYECTO_BLOCKCHAIN_FLIST_ITERATOR_HPP

template<class T>
class flist_iterator {
public:
    flist_iterator() : current(nullptr) {}

    explicit flist_iterator(basic_node *p) : current(p) {}

    T &operator*() const { return retrieve(); }

    T *operator->() const { return &retrieve(); }

    flist_iterator &operator++() {
        current = current->next;
        return *this;
    }

    flist_iterator operator++(int) {
        flist_iterator old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const flist_iterator &rhs) const { return current == rhs.current; }

    bool operator!=(const flist_iterator &rhs) const { return current != rhs.current; }

private:
    basic_node *current;

    T &retrieve() const { return static_cast<node<T> *>(current)->data; }
};

#endif //PROYECTO_BLOCKCHAIN_FLIST_ITERATOR_HPP
