//
// Created by Leonardo Candio on 9/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_VECTOR_HPP
#define PROYECTO_BLOCKCHAIN_VECTOR_HPP

#include <utility>
#include <stdexcept>
#include "vector_iterator.hpp"

template<class T>
class vector {
public:
    vector() : _size(0), capacity(5) {
        data = new T[capacity];
    }

    vector(const vector &other) : data(nullptr), _size(0), capacity(5) {
        *this = other;
    }

    vector(vector &&other) noexcept: data(nullptr), _size(0), capacity(5) {
        *this = std::move(other);
    }

    vector &operator=(const vector &other) {
        if (this != &other) {
            delete[] data;
            _size = other._size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < _size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    vector &operator=(vector &&other) noexcept {
        if (this != &other) {
            delete[] data;
            _size = other._size;
            capacity = other.capacity;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    ~vector() {
        delete[] data;
    }

    void push_back(const T &value) {
        if (_size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        data[_size++] = value;
    }

    void push_back(T &&value) {
        if (_size == capacity) {
            reserve(capacity * (3 / 2) + 1);
        }
        data[_size++] = std::move(value);
    }

    template<class... Args>
    void emplace_back(Args &&... args) {
        if (_size == capacity) {
            reserve(capacity * (3 / 2) + 1);
        }
        data[_size++] = T(std::forward<Args>(args)...);
    }

    void pop_back() {
        if (_size <= 0) {
            throw std::out_of_range("Vector is empty");
        }
        --_size;
    }

    void reserve(int newCapacity) {
        if (newCapacity > capacity) {
            T *newData = new T[newCapacity];
            for (int i = 0; i < _size; ++i) {
                newData[i] = std::move(data[i]);
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

    void shrink() {
        if (_size < capacity) {
            T *newData = new T[_size];
            for (int i = 0; i < _size; ++i) {
                newData[i] = std::move(data[i]);
            }
            delete[] data;
            data = newData;
            capacity = _size;
        }
    }

    void resize(int newSize) {
        if (newSize > _size) {
            reserve(newSize);
            for (int i = _size; i < newSize; ++i) {
                data[i] = T();
            }
        }
        _size = newSize;
    }

    void clear() {
        _size = 0;
    }

    T &operator[](int index) {
        return data[index];
    }

    block &operator[](int index) const {
        return data[index];
    }

    T &back() {
        return data[_size - 1];
    }

    size_t size() const {
        return _size;
    }

    using iterator = vector_iterator<T>;
    using const_iterator = vector_iterator<const T>;

    iterator begin() { return iterator(&data[0]); }

    const_iterator begin() const { return const_iterator(&data[0]); }

    iterator end() { return iterator(&data[_size]); }

    const_iterator end() const { return const_iterator(&data[_size]); }


private:
    T *data;
    size_t _size;
    size_t capacity;
};

#endif //PROYECTO_BLOCKCHAIN_VECTOR_HPP
