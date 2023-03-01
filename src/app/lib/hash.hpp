//
// Created by rvilc on 22/02/2023.
//

#ifndef PROYECTO_BLOCKCHAIN_HASH_HPP
#define PROYECTO_BLOCKCHAIN_HASH_HPP

#include "forward_list.hpp"
#include "iostream"


const int maxColision = 3;
const float maxFillFactor = 0.5;

template<typename TK, typename TV>
class ChainHash {
private:
    class Proxy {
        ChainHash<TK, TV> *hash;
        TK key;

    public:
        Proxy(ChainHash<TK, TV> *hash, TK key) : hash(hash), key(key) {}

        Proxy &operator=(TV value) {
            hash->set(key, value);
            return *this;
        }

        operator TV() {
            return hash->get(key);
        }


        //overload conversion for ostream
        friend std::ostream &operator<<(std::ostream &os, const Proxy &p) {
            os << p.hash->get(p.key);
            return os;
        }
    };


    struct Entry {
        TK first;
        TV second;

        Entry(TK key, TV value) : first(key), second(value) {}
    };

    ForwardList<Entry> *array;
    size_t capacity;//tamanio del array
    size_t size;    //cantidad de elementos totales

public:
    ChainHash() {
        capacity = 10;
        array = new ForwardList<Entry>[capacity];
        size = 0;
    }

    void set(TK key, TV value) {
        if (fillFactor() >= maxFillFactor) {
            rehashing();
        }
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;

        //Completar para el caso cuando el set tiene que actualizar

        for (auto it: array[index]) {
            if (it.first == key) {
                it.second = value;
                return;
            }
        }

        array[index].push_front(Entry(key, value));
        size++;
    }

    TV &get(TK key) {
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;
        for (auto it: array[index]) {
            if (it.first == key) {
                return it.second;
            }
        }
        throw std::out_of_range("Key not found");
    }

    size_t bucket_count() {
        return capacity;
    }

    size_t bucket_size(size_t n) {
        size_t count = 0;
        for (auto i: array[n]) {
            count++;
        }
        return count;
    }

    void remove(TK key) {


        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;

        auto prev = array[index].before_begin();
        for (auto it = array[index].begin(); it != array[index].end(); ++it) {
            if (it->first == key) {
                array[index].erase_after(prev);
                size--;
                return;
            }
            prev++;
        }
    }

    //TODO +1 en el parcial: implementar el operador corchete [ ], read/write

    typename ForwardList<Entry>::iterator begin(size_t n) {
        return array[n].begin();
    }

    typename ForwardList<Entry>::iterator end(size_t n) {
        return array[n].end();
    }

    Proxy operator[](TK key) {
        return Proxy(this, key);
    }

private:
    double fillFactor() {
        return static_cast<double>(size) / (capacity * maxColision);
    }

    size_t getHashCode(TK key) {
        std::hash<TK> ptr_hash;
        return ptr_hash(key);
    }

    void rehashing() {

        auto oldArray = array;
        auto oldCapacity = capacity;
        capacity *= 2;
        array = new ForwardList<Entry>[capacity];
        size = 0;

        for (int i = 0; i < int(oldCapacity); i++) {
            for (auto it: oldArray[i]) {
                set(it.first, it.second);
            }
        }

        delete[] oldArray;
    }
};

#endif