#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include <iostream>

// TODO: Implement all methods
template<typename T>
class ForwardList : public List<T> {
private:
    Node<T> *head;
    int nodes;


public:
    class iterator {
    private:
        Node<T> *current;

    public:
        iterator() : current(nullptr) {}

        explicit iterator(Node<T> *node) : current(node) {}

        iterator operator++() {
            current = current->next;
            return *this;
        }

        const iterator operator++(int) {
            iterator temp = *this;
            current = current->next;
            return temp;
        }

        T operator*() {
            return current->data;
        }

        bool operator==(iterator other) {
            return current == other.current;
        }

        bool operator!=(iterator other) {
            return current != other.current;
        }
    };

    ForwardList() : List<T>() {
        head = nullptr;
        nodes = 0;
    }

    ~ForwardList() {
        clear();
    }

    T front() {
        return head->data;
    }

    T back() {
        Node<T> *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(nullptr);
    }
    void push_front(T data) {
        if (is_empty()) {
            Node<T> *temp = new Node<T>(data);
            head = temp;
            nodes++;
        } else {
            Node<T> *temp = new Node<T>(data);
            temp->next = head;
            head = temp;
            nodes++;
        }
    }

    void push_back(T data) {
        if (is_empty()) {
            Node<T> *temp = new Node<T>(data);
            head = temp;
            nodes++;
        } else {
            Node<T> *temp = new Node<T>(data);
            Node<T> *temp2 = head;
            while (temp2->next != nullptr) {
                temp2 = temp2->next;
            }
            temp2->next = temp;
            nodes++;
        }
    }

    T pop_front() {
        if (is_empty()) {
            throw std::runtime_error("List is empty");
        } else {
            Node<T> *temp = head;
            head = head->next;
            nodes--;
            return temp->data;
        }
    }

    T pop_back() {
        if (is_empty()) {
            throw std::runtime_error("List is empty");
        } else {
            Node<T> *temp = head;
            Node<T> *temp2 = head;
            while (temp->next != nullptr) {
                temp2 = temp;
                temp = temp->next;
            }
            temp2->next = nullptr;
            nodes--;
            return temp->data;
        }
    }

    void insert(T data, int pos) {
        if (pos < 0 || pos > size()) {
            throw std::runtime_error("Invalid position");
        } else {
            if (pos == 0) {
                push_front(data);
            } else if (pos == size()) {
                push_back(data);
            } else {
                Node<T> *temp = head;
                Node<T> *temp2 = new Node<T>(data);
                for (int i = 0; i < pos - 1; i++) {
                    temp = temp->next;
                }
                temp2->next = temp->next;
                temp->next = temp2;
                nodes++;
            }
        }
    }

    void remove(int pos) {
        if (pos < 0 || pos > size()) {
            throw std::runtime_error("Invalid position");
        } else {
            if (pos == 0) {
                pop_front();
            } else if (pos == size()) {
                pop_back();
            } else {
                Node<T> *temp = head;
                for (int i = 0; i < pos - 1; i++) {
                    temp = temp->next;
                }
                Node<T> *temp2 = temp->next;
                temp->next = temp2->next;
                nodes--;
            }
        }
    }

    T &operator[](int pos) {
        if (pos < 0 || pos > size()) {
            throw std::runtime_error("Invalid position");
        } else {
            Node<T> *temp = head;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            return temp->data;
        }
    }

    bool is_empty() {
        return nodes == 0;
    }

    int size() {
        return nodes;
    }

    void clear() {
        if (is_empty())
            return;
        Node<T> *temp = head;
        while (temp != nullptr) {
            Node<T> *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
        nodes = 0;
    }


    void reverse() {
        Node<T> *temp = head;
        Node<T> *temp2 = nullptr;
        Node<T> *temp3 = nullptr;
        while (temp != nullptr) {
            temp3 = temp2;
            temp2 = temp;
            temp = temp->next;
            temp2->next = temp3;
        }
        head = temp2;
    }

    std::string name() {
        return "ForwardList";
    }
};

#endif