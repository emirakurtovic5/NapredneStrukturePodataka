#include <iostream>
#include <string>

#include "HashTable.h"

void testEmptyTable() {
    HashTable<int> table;

    if (!table.isEmpty()) {
        std::cout << "FAIL: New table should be empty." << std::endl;
        return;
    }

    if (table.size() != 0) {
        std::cout << "FAIL: New table should have size 0." << std::endl;
        return;
    }

    std::cout << "PASS: Empty table test" << std::endl;
}

void testInsert() {
    HashTable<int> table;

    table.insert(10);
    table.insert(20);
    table.insert(30);

    if (table.size() != 3) {
        std::cout << "FAIL: Insert should increase size." << std::endl;
        return;
    }

    if (!table.contains(10) ||
        !table.contains(20) ||
        !table.contains(30)) {
        std::cout << "FAIL: Inserted elements should be found."
                  << std::endl;
        return;
    }

    std::cout << "PASS: Insert test" << std::endl;
}

void testDuplicate() {
    HashTable<int> table;

    table.insert(10);
    table.insert(10);
    table.insert(10);

    if (table.size() != 1) {
        std::cout << "FAIL: Duplicate elements should not be inserted."
                  << std::endl;
        return;
    }

    if (!table.contains(10)) {
        std::cout << "FAIL: Inserted element should be found."
                  << std::endl;
        return;
    }

    std::cout << "PASS: Duplicate test" << std::endl;
}

void testContains() {
    HashTable<int> table;

    table.insert(10);
    table.insert(20);
    table.insert(30);

    if (!table.contains(10)) {
        std::cout << "FAIL: Table should contain 10." << std::endl;
        return;
    }

    if (!table.contains(20)) {
        std::cout << "FAIL: Table should contain 20." << std::endl;
        return;
    }

    if (!table.contains(30)) {
        std::cout << "FAIL: Table should contain 30." << std::endl;
        return;
    }

    if (table.contains(40)) {
        std::cout << "FAIL: Table should not contain 40." << std::endl;
        return;
    }

    std::cout << "PASS: Contains test" << std::endl;
}

void testRemove() {
    HashTable<int> table;

    table.insert(10);
    table.insert(20);
    table.insert(30);

    table.remove(20);

    if (table.contains(20)) {
        std::cout << "FAIL: Removed element should not be found."
                  << std::endl;
        return;
    }

    if (!table.contains(10) || !table.contains(30)) {
        std::cout << "FAIL: Other elements should remain in the table."
                  << std::endl;
        return;
    }

    if (table.size() != 2) {
        std::cout << "FAIL: Size should decrease after remove."
                  << std::endl;
        return;
    }

    table.remove(100);

    if (table.size() != 2) {
        std::cout << "FAIL: Removing a non-existing element should not change size."
                  << std::endl;
        return;
    }

    std::cout << "PASS: Remove test" << std::endl;
}

void testClear() {
    HashTable<int> table;

    table.insert(10);
    table.insert(20);
    table.insert(30);

    table.clear();

    if (!table.isEmpty()) {
        std::cout << "FAIL: Table should be empty after clear."
                  << std::endl;
        return;
    }

    if (table.size() != 0) {
        std::cout << "FAIL: Size should be 0 after clear."
                  << std::endl;
        return;
    }

    if (table.contains(10) ||
        table.contains(20) ||
        table.contains(30)) {
        std::cout << "FAIL: Elements should not exist after clear."
                  << std::endl;
        return;
    }

    // Provjera da se tabela može ponovo koristiti
    table.insert(100);

    if (!table.contains(100) || table.size() != 1) {
        std::cout << "FAIL: Table should work after clear."
                  << std::endl;
        return;
    }

    std::cout << "PASS: Clear test" << std::endl;
}

void testRehash() {
    HashTable<int> table(4, 0.75);

    for (int i = 1; i <= 100; ++i) {
        table.insert(i);
    }

    if (table.size() != 100) {
        std::cout << "FAIL: Table should contain 100 elements after rehash."
                  << std::endl;
        return;
    }

    for (int i = 1; i <= 100; ++i) {
        if (!table.contains(i)) {
            std::cout << "FAIL: Element was lost during rehash."
                      << std::endl;
            return;
        }
    }

    std::cout << "PASS: Rehash test" << std::endl;
}

void testString() {
    HashTable<std::string> table;

    table.insert("apple");
    table.insert("banana");
    table.insert("orange");

    if (table.size() != 3) {
        std::cout << "FAIL: String table should have size 3."
                  << std::endl;
        return;
    }

    if (!table.contains("apple") ||
        !table.contains("banana") ||
        !table.contains("orange")) {
        std::cout << "FAIL: Inserted strings should be found."
                  << std::endl;
        return;
    }

    if (table.contains("grape")) {
        std::cout << "FAIL: Non-existing string should not be found."
                  << std::endl;
        return;
    }

    table.remove("banana");

    if (table.contains("banana")) {
        std::cout << "FAIL: Removed string should not be found."
                  << std::endl;
        return;
    }

    if (table.size() != 2) {
        std::cout << "FAIL: Size should decrease after removing a string."
                  << std::endl;
        return;
    }

    std::cout << "PASS: String test" << std::endl;
}

int main() {
    testEmptyTable();
    testInsert();
    testDuplicate();
    testContains();
    testRemove();
    testClear();
    testRehash();
    testString();

    return 0;
}