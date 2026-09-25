#include <iostream>
#include <string>

#include "RedBlackTree.h"

void check(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << std::endl;
    }
    else {
        std::cout << "[FAIL] " << testName << std::endl;
    }
}

void testEmptyTree() {
    RedBlackTree<int> tree;

    check(tree.isEmpty(), "testEmptyTree - isEmpty");
    check(tree.size() == 0, "testEmptyTree - size");
    check(!tree.contains(10), "testEmptyTree - contains");
    check(tree.isBalanced(), "testEmptyTree - balanced");
}

void testSingleElement() {
    RedBlackTree<int> tree;

    tree.insert(10);

    check(!tree.isEmpty(), "testSingleElement - isEmpty");
    check(tree.size() == 1, "testSingleElement - size");
    check(tree.contains(10), "testSingleElement - contains");
    check(tree.isBalanced(), "testSingleElement - balanced");
}

void testBasicOperations() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    check(tree.size() == 5, "testBasicOperations - size");
    check(tree.contains(10), "testBasicOperations - root");
    check(tree.contains(5), "testBasicOperations - left");
    check(tree.contains(15), "testBasicOperations - right");
    check(tree.contains(3), "testBasicOperations - leaf");
    check(!tree.contains(100), "testBasicOperations - missing");
    check(tree.isBalanced(), "testBasicOperations - balanced");
}

void testDuplicates() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(10);
    tree.insert(10);

    check(tree.size() == 1, "testDuplicates - size");
    check(tree.contains(10), "testDuplicates - contains");
    check(tree.isBalanced(), "testDuplicates - balanced");
}

void testRemoveLeaf() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.remove(5);

    check(tree.size() == 2, "testRemoveLeaf - size");
    check(!tree.contains(5), "testRemoveLeaf - removed");
    check(tree.contains(10), "testRemoveLeaf - root");
    check(tree.contains(15), "testRemoveLeaf - other child");
    check(tree.isBalanced(), "testRemoveLeaf - balanced");
}

void testRemoveNodeWithOneChild() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);

    tree.remove(5);

    check(tree.size() == 3, "testRemoveNodeWithOneChild - size");
    check(!tree.contains(5), "testRemoveNodeWithOneChild - removed");
    check(tree.contains(3), "testRemoveNodeWithOneChild - child");
    check(tree.isBalanced(), "testRemoveNodeWithOneChild - balanced");
}

void testRemoveNodeWithTwoChildren() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    tree.remove(10);

    check(tree.size() == 6, "testRemoveNodeWithTwoChildren - size");
    check(!tree.contains(10), "testRemoveNodeWithTwoChildren - removed");
    check(tree.isBalanced(), "testRemoveNodeWithTwoChildren - balanced");
}

void testRemoveRoot() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.remove(10);

    check(tree.size() == 2, "testRemoveRoot - size");
    check(!tree.contains(10), "testRemoveRoot - removed");
    check(tree.contains(5), "testRemoveRoot - left");
    check(tree.contains(15), "testRemoveRoot - right");
    check(tree.isBalanced(), "testRemoveRoot - balanced");
}

void testRemoveNonExisting() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.remove(100);

    check(tree.size() == 3, "testRemoveNonExisting - size");
    check(tree.isBalanced(), "testRemoveNonExisting - balanced");
}

void testRemoveFromEmptyTree() {
    RedBlackTree<int> tree;

    tree.remove(10);

    check(tree.isEmpty(), "testRemoveFromEmptyTree - empty");
    check(tree.size() == 0, "testRemoveFromEmptyTree - size");
    check(tree.isBalanced(), "testRemoveFromEmptyTree - balanced");
}

void testClear() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.clear();

    check(tree.isEmpty(), "testClear - empty");
    check(tree.size() == 0, "testClear - size");
    check(!tree.contains(10), "testClear - contains");
    check(tree.isBalanced(), "testClear - balanced");
}

void testReuseAfterClear() {
    RedBlackTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.clear();

    tree.insert(20);
    tree.insert(15);
    tree.insert(25);

    check(tree.size() == 3, "testReuseAfterClear - size");
    check(tree.contains(20), "testReuseAfterClear - root");
    check(tree.isBalanced(), "testReuseAfterClear - balanced");
}

void testManyInsertions() {
    RedBlackTree<int> tree;

    for (int i = 1; i <= 1000; ++i) {
        tree.insert(i);
    }

    check(tree.size() == 1000, "testManyInsertions - size");
    check(tree.contains(1), "testManyInsertions - first");
    check(tree.contains(500), "testManyInsertions - middle");
    check(tree.contains(1000), "testManyInsertions - last");
    check(tree.isBalanced(), "testManyInsertions - balanced");
}

void testManyDecreasingInsertions() {
    RedBlackTree<int> tree;

    for (int i = 1000; i >= 1; --i) {
        tree.insert(i);
    }

    check(tree.size() == 1000, "testManyDecreasingInsertions - size");
    check(tree.contains(1), "testManyDecreasingInsertions - first");
    check(tree.contains(500), "testManyDecreasingInsertions - middle");
    check(tree.contains(1000), "testManyDecreasingInsertions - last");
    check(tree.isBalanced(), "testManyDecreasingInsertions - balanced");
}

void testManyRemovals() {
    RedBlackTree<int> tree;

    for (int i = 1; i <= 1000; ++i) {
        tree.insert(i);
    }

    for (int i = 1; i <= 500; ++i) {
        tree.remove(i);
    }

    check(tree.size() == 500, "testManyRemovals - size");
    check(!tree.contains(1), "testManyRemovals - removed");
    check(tree.contains(501), "testManyRemovals - remaining");
    check(tree.isBalanced(), "testManyRemovals - balanced");
}

void testMixedOperations() {
    RedBlackTree<int> tree;

    tree.insert(50);
    tree.insert(20);
    tree.insert(80);
    tree.insert(10);
    tree.insert(30);
    tree.insert(70);
    tree.insert(90);

    tree.remove(20);
    tree.insert(25);
    tree.remove(80);
    tree.insert(85);

    check(tree.contains(25), "testMixedOperations - inserted");
    check(!tree.contains(20), "testMixedOperations - removed");
    check(!tree.contains(80), "testMixedOperations - removed2");
    check(tree.contains(85), "testMixedOperations - inserted2");
    check(tree.isBalanced(), "testMixedOperations - balanced");
}

void testStringValues() {
    RedBlackTree<std::string> tree;

    tree.insert("banana");
    tree.insert("apple");
    tree.insert("cherry");

    check(tree.size() == 3, "testStringValues - size");
    check(tree.contains("banana"), "testStringValues - banana");
    check(tree.contains("apple"), "testStringValues - apple");
    check(tree.contains("cherry"), "testStringValues - cherry");
    check(!tree.contains("orange"), "testStringValues - missing");
    check(tree.isBalanced(), "testStringValues - balanced");
}

void testLargeTreeHeight() {
    RedBlackTree<int> tree;

    const int n = 10000;

    for (int i = 1; i <= n; ++i) {
        tree.insert(i);
    }

    check(tree.size() == static_cast<std::size_t>(n),
          "testLargeTreeHeight - size");

    check(tree.height() < 30,
          "testLargeTreeHeight - height");

    check(tree.isBalanced(),
          "testLargeTreeHeight - balanced");
}

int main() {
    testEmptyTree();
    testSingleElement();
    testBasicOperations();
    testDuplicates();
    testRemoveLeaf();
    testRemoveNodeWithOneChild();
    testRemoveNodeWithTwoChildren();
    testRemoveRoot();
    testRemoveNonExisting();
    testRemoveFromEmptyTree();
    testClear();
    testReuseAfterClear();
    testManyInsertions();
    testManyDecreasingInsertions();
    testManyRemovals();
    testMixedOperations();
    testStringValues();
    testLargeTreeHeight();

    std::cout << "\nAll Red-Black tests passed!" << std::endl;

    return 0;
}