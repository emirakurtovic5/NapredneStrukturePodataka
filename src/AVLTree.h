/*template <typename T>
class AVLNode : public DataStructure<T>{
        AVLNode<T>* root;
        size_t nodeCount;
        AVLNode<T>* rotateLeft(AVLNode<T>* node);
        AVLNode<T>* rotateRight(AVLNode<T>* node);
        int getHeight(AVLNode<T>* node){
            int hl, hr;
            hl = node && node->left ? node->left->height : 0;
            hr = node && node->right ? node->right->height : 0;
            return std::max(hl, hr) + 1;
        }
        int getBalanceFactor(AVLNode<T>* node){
            int hl, hr;
            hl = node && node->left ? node->left->height : 0;
            hr = node && node->right ? node->right->height : 0;
            return hl - hr;
        }
        AVLNode<T>* balance(AVLNode<T>* node);

        public:
        AVLTree();
        ~AVLTree() override;

        void insert(T value) override;
        void remove(T value) override;
        bool contains(T value) override;
        size_t size() const override;
        bool isEmpty() const override;
        void clear() override;

};*/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstddef>
#include <algorithm>

#include "DataStructure.h"
#include "AVLNode.h"

template <typename T>
class AVLTree : public DataStructure<T> {
private:
    AVLNode<T>* root;
    std::size_t nodeCount;

    int getHeight(AVLNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }

        return node->height;
    }

    int getBalanceFactor(AVLNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode<T>* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(
                getHeight(node->left),
                getHeight(node->right)
            );
        }
    }

    AVLNode<T>* rotateRight(AVLNode<T>* node) {
        AVLNode<T>* newRoot = node->left;
        AVLNode<T>* subtree = newRoot->right;

        newRoot->right = node;
        node->left = subtree;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* node) {
        AVLNode<T>* newRoot = node->right;
        AVLNode<T>* subtree = newRoot->left;

        newRoot->left = node;
        node->right = subtree;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    AVLNode<T>* balance(AVLNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }

        updateHeight(node);

        int balanceFactor = getBalanceFactor(node);

        // LL slučaj
        if (balanceFactor > 1 &&
            getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        // LR slučaj
        if (balanceFactor > 1 &&
            getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RR slučaj
        if (balanceFactor < -1 &&
            getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        // RL slučaj
        if (balanceFactor < -1 &&
            getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode<T>* insertNode(AVLNode<T>* node, const T& value) {
        if (node == nullptr) {
            ++nodeCount;
            return new AVLNode<T>(value);
        }

        if (value < node->value) {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->value) {
            node->right = insertNode(node->right, value);
        }
        else {
            // Duplikati se ne dodaju.
            return node;
        }

        return balance(node);
    }

    AVLNode<T>* findMinimum(AVLNode<T>* node) const {
        AVLNode<T>* current = node;

        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    AVLNode<T>* removeNode(AVLNode<T>* node, const T& value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->value) {
            node->left = removeNode(node->left, value);
        }
        else if (value > node->value) {
            node->right = removeNode(node->right, value);
        }
        else {
            // Čvor nema lijevo dijete.
            if (node->left == nullptr) {
                AVLNode<T>* rightChild = node->right;
                delete node;
                --nodeCount;
                return rightChild;
            }

            // Čvor nema desno dijete.
            if (node->right == nullptr) {
                AVLNode<T>* leftChild = node->left;
                delete node;
                --nodeCount;
                return leftChild;
            }

            // Čvor ima oba djeteta.
            AVLNode<T>* successor = findMinimum(node->right);

            node->value = successor->value;
            node->right = removeNode(node->right, successor->value);
        }

        return balance(node);
    }

    bool containsNode(AVLNode<T>* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }

        if (value == node->value) {
            return true;
        }

        if (value < node->value) {
            return containsNode(node->left, value);
        }

        return containsNode(node->right, value);
    }

    void clearNodes(AVLNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        clearNodes(node->left);
        clearNodes(node->right);

        delete node;
    }
    bool validateAVL(AVLNode<T>* node, int& calculatedHeight) const {
    if (node == nullptr) {
        calculatedHeight = 0;
        return true;
    }

    int leftHeight = 0;
    int rightHeight = 0;

    if (!validateAVL(node->left, leftHeight)) {
        return false;
    }

    if (!validateAVL(node->right, rightHeight)) {
        return false;
    }

    int calculatedBalance = leftHeight - rightHeight;

    if (calculatedBalance < -1 || calculatedBalance > 1) {
        return false;
    }

    int expectedHeight = 1 + std::max(leftHeight, rightHeight);

    if (node->height != expectedHeight) {
        return false;
    }

    calculatedHeight = expectedHeight;

    return true;
}

public:
    AVLTree()
        : root(nullptr),
          nodeCount(0) {
    }

    AVLTree(const AVLTree&) = delete;

    AVLTree& operator=(const AVLTree&) = delete;

    ~AVLTree() override {
        clear();
    }

    void insert(T value) override {
        root = insertNode(root, value);
    }

    void remove(T value) override {
        root = removeNode(root, value);
    }

    bool contains(T value) override {
        return containsNode(root, value);
    }

    std::size_t size() const override {
        return nodeCount;
    }

    int height() const {
    return getHeight(root);
    }

    bool isEmpty() const override {
        return nodeCount == 0;
    }

    void clear() override {
        clearNodes(root);
        root = nullptr;
        nodeCount = 0;
    }
    
    bool isBalanced() const {
    int calculatedHeight = 0;
    return validateAVL(root, calculatedHeight);
}
};

#endif