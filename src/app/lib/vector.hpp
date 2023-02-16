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
        array = new T[capacity];
    }

    vector(const vector &other) : array(nullptr), _size(0), capacity(5) {
        *this = other;
    }

    vector(vector &&other) noexcept: array(nullptr), _size(0), capacity(5) {
        *this = std::move(other);
    }

    vector &operator=(const vector &other) {
        if (this != &other) {
            delete[] array;
            _size = other._size;
            capacity = other.capacity;
            array = new T[capacity];
            for (int i = 0; i < _size; ++i) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    vector &operator=(vector &&other) noexcept {
        if (this != &other) {
            delete[] array;
            _size = other._size;
            capacity = other.capacity;
            array = other.array;
            other.array = nullptr;
        }
        return *this;
    }

    ~vector() {
        delete[] array;
    }

    void push_back(const T &value) {
        if (_size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
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

    void reserve(int newCapacity) {
        if (newCapacity > capacity) {
            T *newData = new T[newCapacity];
            for (int i = 0; i < _size; ++i) {
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

    T &operator[](int index) {
        return array[index];
    }

    T &operator[](int index) const {
        return array[index];
    }

    T &back() {
        return array[_size - 1];
    }

    size_t size() const {
        return _size;
    }

    static std::string jsonify(const vector<T*> &vec) {
        std::stringstream ss;
        ss << "[";
    for (int i = 0; i < vec.size(); ++i) {
            ss << vec[i]->jsonify();
            if (i != vec.size() - 1) {
                ss << ",";
            }
        }
        ss << "]";
        return ss.str();
    }

    static std::string serialize(const vector<T*> &vec) {
        std::stringstream ss;
        for (int i = 0; i < vec.size(); ++i) {
            ss << vec[i]->serialize();
        }
        return ss.str();
    }


    using iterator = vector_iterator<T>;
    using const_iterator = vector_iterator<const T>;

    iterator begin() { return iterator(&array[0]); }

    const_iterator begin() const { return const_iterator(&array[0]); }

    iterator end() { return iterator(&array[_size]); }

    const_iterator end() const { return const_iterator(&array[_size]); }


private:
    T *array;
    size_t _size;
    size_t capacity;
};

#endif //PROYECTO_BLOCKCHAIN_VECTOR_HPP
