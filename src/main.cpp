#include <iostream>

#include "HashTable.h"

int main() {
    HashTable<int> table;

    for (int i = 1; i <= 100; ++i) {
        table.insert(i);
    }

    std::cout << "Size after inserting 100 elements: "
              << table.size()
              << std::endl;

    std::cout << "Contains 1: "
              << table.contains(1)
              << std::endl;

    std::cout << "Contains 50: "
              << table.contains(50)
              << std::endl;

    std::cout << "Contains 100: "
              << table.contains(100)
              << std::endl;

    std::cout << "Contains 101: "
              << table.contains(101)
              << std::endl;

    table.remove(50);

    std::cout << "Contains 50 after remove: "
              << table.contains(50)
              << std::endl;

    std::cout << "Size after remove: "
              << table.size()
              << std::endl;

    table.clear();

    std::cout << "Size after clear: "
              << table.size()
              << std::endl;

    std::cout << "Is empty after clear: "
              << table.isEmpty()
              << std::endl;

    return 0;
}