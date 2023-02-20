//
// Created by Leonardo Candio on 16/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_CIRCULAR_ARRAY_HPP
#define PROYECTO_BLOCKCHAIN_CIRCULAR_ARRAY_HPP

#include "dynamic_array.hpp"

//class conteiner main
template<class T>
class circular_array : public dynamic_array<T> {
public:
    circular_array() : dynamic_array<T>() {}

    circular_array(const circular_array &other) : dynamic_array<T>(other) {}

    circular_array(circular_array &&other) noexcept: dynamic_array<T>(std::move(other)) {}

    circular_array &operator=(const circular_array &other) {
        dynamic_array<T>::operator=(other);
        return *this;
    }

    circular_array &operator=(circular_array &&other) noexcept {
        dynamic_array<T>::operator=(std::move(other));
        return *this;
    }

    T &operator[](int index) {
        if (index < 0) {
            index = dynamic_array<T>::_size + index;
        }
        return dynamic_array<T>::array[index % dynamic_array<T>::_size];
    }

    const T &operator[](int index) const {
        if (index < 0) {
            index = dynamic_array<T>::_size + index;
        }
        return dynamic_array<T>::array[index % dynamic_array<T>::_size];
    }

    T &at(int index) {
        if (index < 0) {
            index = dynamic_array<T>::_size + index;
        }
        return dynamic_array<T>::array[index % dynamic_array<T>::_size];
    }

    const T &at(int index) const {
        if (index < 0) {
            index = dynamic_array<T>::_size + index;
        }
        return dynamic_array<T>::array[index % dynamic_array<T>::_size];
    }

    T &front() {
        return dynamic_array<T>::array[0];
    }

    const T &front() const {
        return dynamic_array<T>::array[0];
    }

    T &back() {
        return dynamic_array<T>::array[dynamic_array<T>::_size - 1];
    }

    const T &back() const {
        return dynamic_array<T>::array[dynamic_array<T>::_size - 1];
    }

    void push_back(const T &value) {
        if (dynamic_array<T>::_size == dynamic_array<T>::capacity) {
            dynamic_array<T>::reserve(dynamic_array<T>::capacity * (3 / 2) + 1);
        }
        dynamic_array<T>::array[dynamic_array<T>::_size++] = value;
    }

    void push_front(const T &value) {
        if (dynamic_array<T>::_size == dynamic_array<T>::capacity) {
            dynamic_array<T>::reserve(dynamic_array<T>::capacity * (3 / 2) + 1);
        }
        for (int i = dynamic_array<T>::_size; i > 0; --i) {
            dynamic_array<T>::array[i] = dynamic_array<T>::array[i - 1];
        }
        dynamic_array<T>::array[0] = value;
        ++dynamic_array<T>::_size;
    }

    template<typename ... Args>
    void emplace_back(Args &&... args) {
        if (dynamic_array<T>::_size == dynamic_array<T>::capacity) {
            dynamic_array<T>::reserve(dynamic_array<T>::capacity * (3 / 2) + 1);
        }
        dynamic_array<T>::array[dynamic_array<T>::_size++] = T(std::forward<Args>(args)...);
    }

    template<typename ... Args>
    void emplace_front(Args &&... args) {
        if (dynamic_array<T>::_size == dynamic_array<T>::capacity) {
            dynamic_array<T>::reserve(dynamic_array<T>::capacity * (3 / 2) + 1);
        }
        for (int i = dynamic_array<T>::_size; i > 0; --i) {
            dynamic_array<T>::array[i] = dynamic_array<T>::array[i - 1];
        }
        dynamic_array<T>::array[0] = T(std::forward<Args>(args)...);
        ++dynamic_array<T>::_size;
    }



private:
    int _size;
    int capacity;
    T *array;
};

#endif //PROYECTO_BLOCKCHAIN_CIRCULAR_ARRAY_HPP
