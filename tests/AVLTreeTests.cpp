#include <cassert>
#include <iostream>
#include <string>

#include "AVLTree.h"


void testBasicOperations() {
    AVLTree<int> tree;

    assert(tree.isEmpty());
    assert(tree.size() == 0);

    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    assert(!tree.isEmpty());
    assert(tree.size() == 3);

    assert(tree.contains(30));
    assert(tree.contains(20));
    assert(tree.contains(10));

    assert(!tree.contains(50));

    std::cout << "testBasicOperations: PASS\n";
}


void testLLRotation() {
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    assert(tree.size() == 3);
    assert(tree.height() == 2);

    assert(tree.contains(10));
    assert(tree.contains(20));
    assert(tree.contains(30));

    std::cout << "testLLRotation: PASS\n";
}


void testRRRotation() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    assert(tree.size() == 3);
    assert(tree.height() == 2);

    assert(tree.contains(10));
    assert(tree.contains(20));
    assert(tree.contains(30));

    std::cout << "testRRRotation: PASS\n";
}


void testLRRotation() {
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(10);
    tree.insert(20);

    assert(tree.size() == 3);
    assert(tree.height() == 2);

    assert(tree.contains(10));
    assert(tree.contains(20));
    assert(tree.contains(30));

    std::cout << "testLRRotation: PASS\n";
}


void testRLRotation() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    assert(tree.size() == 3);
    assert(tree.height() == 2);

    assert(tree.contains(10));
    assert(tree.contains(20));
    assert(tree.contains(30));

    std::cout << "testRLRotation: PASS\n";
}


void testDuplicates() {
    AVLTree<int> tree;

    tree.insert(20);
    tree.insert(20);
    tree.insert(20);

    assert(tree.size() == 1);
    assert(tree.contains(20));

    std::cout << "testDuplicates: PASS\n";
}


void testRemoveLeaf() {
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(40);

    tree.remove(20);

    assert(tree.size() == 2);
    assert(!tree.contains(20));
    assert(tree.contains(30));
    assert(tree.contains(40));

    std::cout << "testRemoveLeaf: PASS\n";
}


void testRemoveNodeWithOneChild() {
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    tree.remove(20);

    assert(tree.size() == 2);
    assert(!tree.contains(20));
    assert(tree.contains(10));
    assert(tree.contains(30));

    std::cout << "testRemoveNodeWithOneChild: PASS\n";
}


void testRemoveNodeWithTwoChildren() {
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(50);

    tree.remove(30);

    assert(tree.size() == 6);
    assert(!tree.contains(30));

    assert(tree.contains(10));
    assert(tree.contains(20));
    assert(tree.contains(25));
    assert(tree.contains(35));
    assert(tree.contains(40));
    assert(tree.contains(50));

    std::cout << "testRemoveNodeWithTwoChildren: PASS\n";
}


void testClear() {
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(40);

    tree.clear();

    assert(tree.isEmpty());
    assert(tree.size() == 0);
    assert(!tree.contains(30));
    assert(!tree.contains(20));
    assert(!tree.contains(40));

    std::cout << "testClear: PASS\n";
}

void testEmptyTree() {
    AVLTree<int> tree;

    assert(tree.isEmpty());
    assert(tree.size() == 0);
    assert(tree.height() == 0);
    assert(tree.isBalanced());

    std::cout << "testEmptyTree: PASS\n";
}

void testSingleElement() {
    AVLTree<int> tree;

    tree.insert(42);

    assert(!tree.isEmpty());
    assert(tree.size() == 1);
    assert(tree.height() == 1);
    assert(tree.contains(42));
    assert(tree.isBalanced());

    std::cout << "testSingleElement: PASS\n";
}

void testManyInsertions() {
    AVLTree<int> tree;

    for (int i = 1; i <= 1000; ++i) {
        tree.insert(i);
    }

    assert(tree.size() == 1000);
    assert(tree.isBalanced());

    for (int i = 1; i <= 1000; ++i) {
        assert(tree.contains(i));
    }

    std::cout << "testManyInsertions: PASS\n";
}

void testManyDecreasingInsertions() {
    AVLTree<int> tree;

    for (int i = 1000; i >= 1; --i) {
        tree.insert(i);
    }

    assert(tree.size() == 1000);
    assert(tree.isBalanced());

    for (int i = 1; i <= 1000; ++i) {
        assert(tree.contains(i));
    }

    std::cout << "testManyDecreasingInsertions: PASS\n";
}

void testManyRemovals() {
    AVLTree<int> tree;

    for (int i = 1; i <= 1000; ++i) {
        tree.insert(i);
    }

    for (int i = 1; i <= 500; ++i) {
        tree.remove(i);

        assert(tree.isBalanced());
    }

    assert(tree.size() == 500);

    for (int i = 1; i <= 500; ++i) {
        assert(!tree.contains(i));
    }

    for (int i = 501; i <= 1000; ++i) {
        assert(tree.contains(i));
    }

    std::cout << "testManyRemovals: PASS\n";
}

void testRemoveRoot() {
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(50);

    tree.remove(30);

    assert(!tree.contains(30));
    assert(tree.size() == 6);
    assert(tree.isBalanced());

    assert(tree.contains(10));
    assert(tree.contains(20));
    assert(tree.contains(25));
    assert(tree.contains(35));
    assert(tree.contains(40));
    assert(tree.contains(50));

    std::cout << "testRemoveRoot: PASS\n";
}

void testReuseAfterClear() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    tree.clear();

    assert(tree.isEmpty());
    assert(tree.size() == 0);
    assert(tree.height() == 0);
    assert(tree.isBalanced());

    tree.insert(100);
    tree.insert(50);
    tree.insert(150);

    assert(tree.size() == 3);
    assert(tree.contains(100));
    assert(tree.contains(50));
    assert(tree.contains(150));
    assert(tree.isBalanced());

    std::cout << "testReuseAfterClear: PASS\n";
}

void testMixedOperations() {
    AVLTree<int> tree;

    for (int i = 1; i <= 100; ++i) {
        tree.insert(i);
    }

    for (int i = 1; i <= 100; i += 2) {
        tree.remove(i);
    }

    assert(tree.size() == 50);
    assert(tree.isBalanced());

    for (int i = 2; i <= 100; i += 2) {
        assert(tree.contains(i));
    }

    for (int i = 101; i <= 150; ++i) {
        tree.insert(i);
    }

    assert(tree.size() == 100);
    assert(tree.isBalanced());

    std::cout << "testMixedOperations: PASS\n";
}

void testRemoveNonExisting() {
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(40);

    tree.remove(100);

    assert(tree.size() == 3);

    assert(tree.contains(20));
    assert(tree.contains(30));
    assert(tree.contains(40));

    assert(tree.isBalanced());

    std::cout << "testRemoveNonExisting: PASS\n";
}

void testRemoveFromEmptyTree() {
    AVLTree<int> tree;

    tree.remove(10);

    assert(tree.isEmpty());
    assert(tree.size() == 0);
    assert(tree.height() == 0);
    assert(tree.isBalanced());

    std::cout << "testRemoveFromEmptyTree: PASS\n";
}

void testStringValues() {
    AVLTree<std::string> tree;

    tree.insert("banana");
    tree.insert("apple");
    tree.insert("cherry");

    assert(tree.size() == 3);

    assert(tree.contains("apple"));
    assert(tree.contains("banana"));
    assert(tree.contains("cherry"));

    assert(!tree.contains("orange"));

    assert(tree.isBalanced());

    std::cout << "testStringValues: PASS\n";
}

void testLargeTreeHeight() {
    AVLTree<int> tree;

    for (int i = 1; i <= 100000; ++i) {
        tree.insert(i);
    }

    assert(tree.isBalanced());

    std::cout << "testLargeTreeHeight: PASS\n";
}

/*int main() {
    testBasicOperations();

    testLLRotation();
    testRRRotation();
    testLRRotation();
    testRLRotation();

    testDuplicates();

    testRemoveLeaf();
    testRemoveNodeWithOneChild();
    testRemoveNodeWithTwoChildren();

    testClear();

    std::cout << "\nAll AVL tests passed!\n";

    return 0;
}*/
int main() {
    testEmptyTree();
    testSingleElement();

    testBasicOperations();

    testLLRotation();
    testRRRotation();
    testLRRotation();
    testRLRotation();

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

    std::cout << "\nAll AVL tests passed!\n";

    return 0;
}