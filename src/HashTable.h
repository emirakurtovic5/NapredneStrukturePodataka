#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "DataStructure.h"

#include <vector>
#include <list>
#include <functional>
#include <cstddef>
#include <algorithm>

template <typename T>
class HashTable : public DataStructure<T> {
private:
    std::vector<std::list<T>> table;
    std::size_t elementCount;
    double maxLoadFactor;

    std::size_t hashFunction(const T& value) const {
        return std::hash<T>{}(value) % table.size();
    }

    void rehash() {
        std::size_t newCapacity = table.size() * 2;

        std::vector<std::list<T>> newTable(newCapacity);

        for (const auto& bucket : table) {
            for (const T& value : bucket) {
                std::size_t index =
                    std::hash<T>{}(value) % newCapacity;

                newTable[index].push_back(value);
            }
        }

        table.swap(newTable);
    }

public:
    HashTable(std::size_t initialCapacity = 16,
              double maxLoadFactor = 0.75)
        : table(initialCapacity == 0 ? 1 : initialCapacity),
          elementCount(0),
          maxLoadFactor(maxLoadFactor > 0.0 ? maxLoadFactor : 0.75) {
    }

    void insert(T value) override {
        std::size_t index = hashFunction(value);

        std::list<T>& bucket = table[index];

        if (std::find(bucket.begin(), bucket.end(), value) != bucket.end()) {
            return;
        }

        bucket.push_back(value);
        ++elementCount;

        double loadFactor =
            static_cast<double>(elementCount) / table.size();

        if (loadFactor > maxLoadFactor) {
            rehash();
        }
    }

    bool contains(T value) override {
        std::size_t index = hashFunction(value);

        const std::list<T>& bucket = table[index];

        return std::find(bucket.begin(), bucket.end(), value) != bucket.end();
    }

    void remove(T value) override {
        std::size_t index = hashFunction(value);

        std::list<T>& bucket = table[index];

        auto it = std::find(bucket.begin(), bucket.end(), value);

        if (it == bucket.end()) {
            return;
        }

        bucket.erase(it);
        --elementCount;
    }

    std::size_t size() const override {
        return elementCount;
    }

    bool isEmpty() const override {
        return elementCount == 0;
    }

    void clear() override {
        for (auto& bucket : table) {
            bucket.clear();
        }

        elementCount = 0;
    }
};

#endif