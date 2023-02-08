//
// Created by Leonardo Candio on 7/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_FLIST_HPP
#define PROYECTO_BLOCKCHAIN_FLIST_HPP

#include "node.hpp"
#include "stdexcept"
#include "flist_iterator.hpp"

#define top head->next

template<typename T>
class flist {
public:
    flist();

    flist(const flist<T> &);

    flist<T> &operator=(const flist<T> &);

    ~flist();

    void push_front(const T &);

    void pop_front();

    T &front() const;

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    void clear();

    template<typename... Args>
    void emplace_front(Args &&... args);

    using iterator = flist_iterator<T>;

    iterator begin() const;

    iterator end() const;

    iterator before_begin() const;

private:

    basic_node *head;
    size_t count;
};

template<typename T>
typename flist<T>::iterator flist<T>::begin() const {
    return flist::iterator(head->next);
}

template<typename T>
typename flist<T>::iterator flist<T>::end() const {
    return flist::iterator(nullptr);
}

template<typename T>
typename flist<T>::iterator flist<T>::before_begin() const {
    return flist::iterator(head);
}

template<typename T>
flist<T>::flist() {
    count = 0;
    head = new basic_node();
}

template<typename T>
flist<T>::flist(const flist<T> &other) {
    head = other.head;
    count = other.count;
}

template<typename T>
flist<T> &flist<T>::operator=(const flist<T> &other) {
    if (this == &other) {
        return *this;
    }
    flist<T> temp(other);
    std::swap(head, temp.head);
    std::swap(count, temp.count);
    return *this;
}

template<typename T>
flist<T>::~flist() {
    delete head;
}

template<typename T>
void flist<T>::push_front(const T &value) {
    auto *temp = new node<T>;
    temp->data = value;
    if (!empty())
        temp->next = head;
    count++;
    head = temp;
}

template<typename T>
void flist<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Empty list");
    }
    auto *temp = top;
    top = top->next;
    count--;
    delete temp;
}

template<typename T>
T &flist<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Empty list");
    }
    return static_cast<node<T> *>(top)->data;
}

template<typename T>
bool flist<T>::empty() const {
    return top == nullptr;
}

template<typename T>
size_t flist<T>::size() const {
    return count;
}

template<typename T>
void flist<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
template<typename... Args>
void flist<T>::emplace_front(Args &&... args) {
    auto *temp = new node<T>(std::forward<Args>(args)...);
    if (!empty())
        temp->next = top;
    count++;
    top = temp;
}


#endif //PROYECTO_BLOCKCHAIN_FLIST_HPP
