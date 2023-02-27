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

    circular_array(circular_array &&other) noexcept : dynamic_array<T>(std::move(other)) {}

    ~circular_array() = default;

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
            index = this->size() + index;
        }
        return dynamic_array<T>::operator[](index % this->size());
    }

    const T &operator[](int index) const {
        if (index < 0) {
            index = this->size() + index;
        }
        return dynamic_array<T>::operator[](index % this->size());
    }


    T &front() {
        return operator[](0);
    }

    const T &front() const {
        return operator[](0);
    }

    T &back() {
        return operator[](this->size() - 1);
    }

    const T &back() const {
        return operator[](this->size() - 1);
    }


    void push_front(const T &value) {
        if (this->size() == this->capacity()) {
            this->reserve(((float) this->capacity()) * (3. / 2.) + 1);
        }
        for (int i = this->size(); i > 0; --i) {
            this->operator[](i) = this->operator[](i - 1);
        }
        operator[](0) = value;
        this->increment_size();
    }

    template<typename... Args>
    void emplace_back(Args &&...args) {
        if (this->size() == this->capacity) {
            this->reserve(((float) this->capacity()) * (3. / 2.) + 1);
        }
        operator[](this->size()) = T(std::forward<Args>(args)...);
        this->increment_size();
    }

    template<typename... Args>
    void emplace_front(Args &&...args) {
        if (this->size() == this->capacity) {
            this->reserve(((float) this->capacity()) * (3. / 2.) + 1);
        }
        for (int i = this->size(); i > 0; --i) {
            this->operator[](i) = this->operator[](i - 1);
        }
        operator[](0) = T(std::forward<Args>(args)...);
        this->increment_size();
    }
};

#endif//PROYECTO_BLOCKCHAIN_CIRCULAR_ARRAY_HPP
