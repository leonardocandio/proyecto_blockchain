//
// Created by Leonardo Candio on 9/02/23.
//

#ifndef PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_HPP
#define PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_HPP

#include "dynamic_array_iterator.hpp"
#include "sstream"
#include <stdexcept>
#include <utility>

//class dynamic array
template<class T>
class dynamic_array {
public:
    using iterator = dynamic_array_iterator<T>;
    using const_iterator = dynamic_array_iterator<const T>;

    virtual iterator begin() { return iterator(&array[0]); }

    virtual const_iterator begin() const { return const_iterator(&array[0]); }

    virtual iterator end() { return iterator(&array[_size]); }

    virtual const_iterator end() const { return const_iterator(&array[_size]); }

    dynamic_array() = default;

    dynamic_array(const dynamic_array &other) : _size(other._size), _capacity(other._capacity) {
        array = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            array[i] = other.array[i];
        }
    }
    dynamic_array(iterator begin, iterator end) : _size(end - begin), _capacity(end - begin) {
        array = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            array[i] = *begin;
            ++begin;
        }
    }

    dynamic_array(dynamic_array &&other) noexcept : _size(other._size), _capacity(other._capacity), array(other.array) {
        other.array = nullptr;
    }

    dynamic_array &operator=(const dynamic_array &other) {
        if (this != &other) {
            delete[] array;
            _size = other._size;
            _capacity = other._capacity;
            array = new T[_capacity];
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
            _capacity = other._capacity;
            array = other.array;
            other.array = nullptr;
        }
        return *this;
    }

    ~dynamic_array() {
        delete[] array;
    }

    virtual void push_back(const T &value) {
        if (_size == _capacity) {
            reserve((float) _capacity * (3. / 2.) + 1);
        }
        array[_size++] = value;
    }

    void push_back(T &&value) {
        if (_size == _capacity) {
            reserve((float) _capacity * (3. / 2.) + 1);
        }
        array[_size++] = std::move(value);
    }

    template<class... Args>
    void emplace_back(Args &&...args) {
        if (_size == _capacity) {
            reserve((float) _capacity * (3. / 2.) + 1);
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
        if (newCapacity > _capacity) {
            auto newData = new T[newCapacity];
            for (size_t i = 0; i < _size; ++i) {
                newData[i] = std::move(array[i]);
            }
            delete[] array;
            array = newData;
            _capacity = newCapacity;
        }
    }

    void shrink() {
        if (_size < _capacity) {
            auto newData = new T[_size];
            for (int i = 0; i < _size; ++i) {
                newData[i] = std::move(array[i]);
            }
            delete[] array;
            array = newData;
            _capacity = _size;
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

    [[nodiscard]] size_t capacity() const {
        return _capacity;
    }


protected:
    void increment_size() {
        ++_size;
    }

    void decrement_size() {
        --_size;
    }

private:
    size_t _size = 0;
    size_t _capacity = 1;
    T *array = new T[_capacity];
};

#endif//PROYECTO_BLOCKCHAIN_DYNAMIC_ARRAY_HPP
