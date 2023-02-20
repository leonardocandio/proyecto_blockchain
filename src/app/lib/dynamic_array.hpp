//
// Created by Leonardo Candio on 9/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_HPP
#define PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_HPP

#include <utility>
#include <stdexcept>
#include "sstream"
#include "dynamic_array_iterator.hpp"

//class dynamic array
template<class T>
class dynamic_array {
public:
    dynamic_array() : _size(0), capacity(5) {
        array = new T[capacity];
    }

    dynamic_array(const dynamic_array &other) : array(nullptr), _size(0), capacity(5) {
        *this = other;
    }

    dynamic_array(dynamic_array &&other) noexcept: array(nullptr), _size(0), capacity(5) {
        *this = std::move(other);
    }

    dynamic_array &operator=(const dynamic_array &other) {
        if (this != &other) {
            delete[] array;
            _size = other._size;
            capacity = other.capacity;
            array = new T[capacity];
            for (size_t i = 0; i < _size; ++i) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    dynamic_array &operator=(dynamic_array &&other) noexcept {
        if (this != &other) {
            delete[] array;
            _size = other._size;
            capacity = other.capacity;
            array = other.array;
            other.array = nullptr;
        }
        return *this;
    }

    ~dynamic_array() {
        delete[] array;
    }

    virtual void push_back(const T &value) {
        if (_size == capacity) {
            reserve(capacity * (3 / 2) + 1);
        }
        array[_size++] = value;
    }

    void push_back(T &&value) {
        if (_size == capacity) {
            reserve(capacity * (3 / 2) + 1);
        }
        array[_size++] = std::move(value);
    }

    template<class... Args>
    void emplace_back(Args &&... args) {
        if (_size == capacity) {
            reserve(capacity * (3 / 2) + 1);
        }
        array[_size++] = T(std::forward<Args>(args)...);
    }

    void pop_back() {
        if (_size <= 0) {
            throw std::out_of_range("Vector is empty");
        }
        --_size;
    }

    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            T *newData = new T[newCapacity];
            for (size_t i = 0; i < _size; ++i) {
                newData[i] = std::move(array[i]);
            }
            delete[] array;
            array = newData;
            capacity = newCapacity;
        }
    }

    void shrink() {
        if (_size < capacity) {
            T *newData = new T[_size];
            for (int i = 0; i < _size; ++i) {
                newData[i] = std::move(array[i]);
            }
            delete[] array;
            array = newData;
            capacity = _size;
        }
    }

    void resize(int newSize) {
        if (newSize > _size) {
            reserve(newSize);
            for (int i = _size; i < newSize; ++i) {
                array[i] = T();
            }
        }
        _size = newSize;
    }

    void clear() {
        _size = 0;
    }

    virtual T &operator[](size_t index) {
        return array[index];
    }

    virtual const T &operator[](size_t index) const {
        return array[index];
    }

    virtual T &back() {
        return array[_size - 1];
    }

    [[nodiscard]] size_t size() const {
        return _size;
    }


    using iterator = dynamic_array_iterator<T>;
    using const_iterator = dynamic_array_iterator<const T>;

    virtual iterator begin() { return iterator(&array[0]); }

    virtual const_iterator begin() const { return const_iterator(&array[0]); }

    virtual iterator end() { return iterator(&array[_size]); }

    virtual const_iterator end() const { return const_iterator(&array[_size]); }


protected:
    T *array;
    size_t _size;
    size_t capacity;
};

#endif //PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_HPP
