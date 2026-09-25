#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cstddef>
#include <algorithm>

#include "DataStructure.h"
#include "RedBlackNode.h"

template <typename T>
class RedBlackTree : public DataStructure<T> {
private:
    RedBlackNode<T>* root;
    std::size_t nodeCount;

    Color getColor(RedBlackNode<T>* node) const {
        if (node == nullptr) {
            return Color::BLACK;
        }

        return node->color;
    }

    int getHeight(RedBlackNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }

        return 1 + std::max(
            getHeight(node->left),
            getHeight(node->right)
        );
    }

    void rotateLeft(RedBlackNode<T>* node) {
        RedBlackNode<T>* newRoot = node->right;

        node->right = newRoot->left;

        if (newRoot->left != nullptr) {
            newRoot->left->parent = node;
        }

        newRoot->parent = node->parent;

        if (node->parent == nullptr) {
            root = newRoot;
        }
        else if (node == node->parent->left) {
            node->parent->left = newRoot;
        }
        else {
            node->parent->right = newRoot;
        }

        newRoot->left = node;
        node->parent = newRoot;
    }

    void rotateRight(RedBlackNode<T>* node) {
        RedBlackNode<T>* newRoot = node->left;

        node->left = newRoot->right;

        if (newRoot->right != nullptr) {
            newRoot->right->parent = node;
        }

        newRoot->parent = node->parent;

        if (node->parent == nullptr) {
            root = newRoot;
        }
        else if (node == node->parent->right) {
            node->parent->right = newRoot;
        }
        else {
            node->parent->left = newRoot;
        }

        newRoot->right = node;
        node->parent = newRoot;
    }

    void insertFixup(RedBlackNode<T>* node) {
        while (node != root &&
               getColor(node->parent) == Color::RED) {

            RedBlackNode<T>* parent = node->parent;
            RedBlackNode<T>* grandparent = parent->parent;

            if (parent == grandparent->left) {
                RedBlackNode<T>* uncle = grandparent->right;

                if (getColor(uncle) == Color::RED) {
                    parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandparent->color = Color::RED;

                    node = grandparent;
                }
                else {
                    if (node == parent->right) {
                        node = parent;
                        rotateLeft(node);

                        parent = node->parent;
                        grandparent = parent->parent;
                    }

                    parent->color = Color::BLACK;
                    grandparent->color = Color::RED;

                    rotateRight(grandparent);
                }
            }
            else {
                RedBlackNode<T>* uncle = grandparent->left;

                if (getColor(uncle) == Color::RED) {
                    parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandparent->color = Color::RED;

                    node = grandparent;
                }
                else {
                    if (node == parent->left) {
                        node = parent;
                        rotateRight(node);

                        parent = node->parent;
                        grandparent = parent->parent;
                    }

                    parent->color = Color::BLACK;
                    grandparent->color = Color::RED;

                    rotateLeft(grandparent);
                }
            }
        }

        root->color = Color::BLACK;
    }

    RedBlackNode<T>* insertNode(const T& value) {
        RedBlackNode<T>* parent = nullptr;
        RedBlackNode<T>* current = root;

        while (current != nullptr) {
            parent = current;

            if (value < current->value) {
                current = current->left;
            }
            else if (value > current->value) {
                current = current->right;
            }
            else {
                return nullptr;
            }
        }

        RedBlackNode<T>* newNode =
            new RedBlackNode<T>(value);

        newNode->parent = parent;

        if (parent == nullptr) {
            root = newNode;
        }
        else if (value < parent->value) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        ++nodeCount;

        return newNode;
    }

    RedBlackNode<T>* findNode(
        RedBlackNode<T>* node,
        const T& value
    ) const {
        while (node != nullptr) {
            if (value == node->value) {
                return node;
            }

            if (value < node->value) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        return nullptr;
    }

    RedBlackNode<T>* findMinimum(
        RedBlackNode<T>* node
    ) const {
        RedBlackNode<T>* current = node;

        while (current != nullptr &&
               current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    void transplant(
        RedBlackNode<T>* oldNode,
        RedBlackNode<T>* newNode
    ) {
        if (oldNode->parent == nullptr) {
            root = newNode;
        }
        else if (oldNode == oldNode->parent->left) {
            oldNode->parent->left = newNode;
        }
        else {
            oldNode->parent->right = newNode;
        }

        if (newNode != nullptr) {
            newNode->parent = oldNode->parent;
        }
    }

    void removeFixup(
        RedBlackNode<T>* node,
        RedBlackNode<T>* parent
    ) {
        while (node != root &&
               getColor(node) == Color::BLACK) {

            if (parent == nullptr) {
                break;
            }

            if (node == parent->left) {
                RedBlackNode<T>* sibling = parent->right;

                if (getColor(sibling) == Color::RED) {
                    sibling->color = Color::BLACK;
                    parent->color = Color::RED;

                    rotateLeft(parent);

                    sibling = parent->right;
                }

                Color siblingLeftColor =
                    getColor(
                        sibling == nullptr
                            ? nullptr
                            : sibling->left
                    );

                Color siblingRightColor =
                    getColor(
                        sibling == nullptr
                            ? nullptr
                            : sibling->right
                    );

                if (siblingLeftColor == Color::BLACK &&
                    siblingRightColor == Color::BLACK) {

                    if (sibling != nullptr) {
                        sibling->color = Color::RED;
                    }

                    node = parent;
                    parent = node->parent;
                }
                else {
                    if (siblingRightColor == Color::BLACK) {

                        if (sibling != nullptr &&
                            sibling->left != nullptr) {
                            sibling->left->color =
                                Color::BLACK;
                        }

                        if (sibling != nullptr) {
                            sibling->color = Color::RED;
                            rotateRight(sibling);
                        }

                        sibling = parent->right;
                    }

                    if (sibling != nullptr) {
                        sibling->color = parent->color;

                        if (sibling->right != nullptr) {
                            sibling->right->color =
                                Color::BLACK;
                        }
                    }

                    parent->color = Color::BLACK;
                    rotateLeft(parent);

                    node = root;
                    parent = nullptr;
                }
            }
            else {
                RedBlackNode<T>* sibling = parent->left;

                if (getColor(sibling) == Color::RED) {
                    sibling->color = Color::BLACK;
                    parent->color = Color::RED;

                    rotateRight(parent);

                    sibling = parent->left;
                }

                Color siblingLeftColor =
                    getColor(
                        sibling == nullptr
                            ? nullptr
                            : sibling->left
                    );

                Color siblingRightColor =
                    getColor(
                        sibling == nullptr
                            ? nullptr
                            : sibling->right
                    );

                if (siblingLeftColor == Color::BLACK &&
                    siblingRightColor == Color::BLACK) {

                    if (sibling != nullptr) {
                        sibling->color = Color::RED;
                    }

                    node = parent;
                    parent = node->parent;
                }
                else {
                    if (siblingLeftColor == Color::BLACK) {

                        if (sibling != nullptr &&
                            sibling->right != nullptr) {
                            sibling->right->color =
                                Color::BLACK;
                        }

                        if (sibling != nullptr) {
                            sibling->color = Color::RED;
                            rotateLeft(sibling);
                        }

                        sibling = parent->left;
                    }

                    if (sibling != nullptr) {
                        sibling->color = parent->color;

                        if (sibling->left != nullptr) {
                            sibling->left->color =
                                Color::BLACK;
                        }
                    }

                    parent->color = Color::BLACK;
                    rotateRight(parent);

                    node = root;
                    parent = nullptr;
                }
            }
        }

        if (node != nullptr) {
            node->color = Color::BLACK;
        }
    }

    void removeNode(const T& value) {
        RedBlackNode<T>* node = findNode(root, value);

        if (node == nullptr) {
            return;
        }

        RedBlackNode<T>* removedNode = node;
        Color removedColor = removedNode->color;

        RedBlackNode<T>* replacement = nullptr;
        RedBlackNode<T>* replacementParent = nullptr;

        if (node->left == nullptr) {
            replacement = node->right;
            replacementParent = node->parent;

            transplant(node, node->right);

            if (replacement != nullptr) {
                replacementParent = replacement->parent;
            }
        }
        else if (node->right == nullptr) {
            replacement = node->left;
            replacementParent = node->parent;

            transplant(node, node->left);

            if (replacement != nullptr) {
                replacementParent = replacement->parent;
            }
        }
        else {
            removedNode = findMinimum(node->right);
            removedColor = removedNode->color;

            replacement = removedNode->right;

            if (removedNode->parent == node) {
                replacementParent = removedNode;

                if (replacement != nullptr) {
                    replacement->parent = removedNode;
                }
            }
            else {
                replacementParent = removedNode->parent;

                transplant(
                    removedNode,
                    removedNode->right
                );

                removedNode->right = node->right;
                removedNode->right->parent = removedNode;
            }

            transplant(node, removedNode);

            removedNode->left = node->left;
            removedNode->left->parent = removedNode;

            removedNode->color = node->color;
        }

        delete node;
        --nodeCount;

        if (removedColor == Color::BLACK) {
            removeFixup(
                replacement,
                replacementParent
            );
        }
    }

    void clearNodes(RedBlackNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        clearNodes(node->left);
        clearNodes(node->right);

        delete node;
    }

    bool validateBlackHeight(
        RedBlackNode<T>* node,
        int& blackHeight
    ) const {
        if (node == nullptr) {
            blackHeight = 1;
            return true;
        }

        int leftBlackHeight = 0;
        int rightBlackHeight = 0;

        if (!validateBlackHeight(
                node->left,
                leftBlackHeight)) {
            return false;
        }

        if (!validateBlackHeight(
                node->right,
                rightBlackHeight)) {
            return false;
        }

        if (leftBlackHeight != rightBlackHeight) {
            return false;
        }

        if (node->color == Color::RED) {
            if (getColor(node->left) == Color::RED ||
                getColor(node->right) == Color::RED) {
                return false;
            }
        }

        blackHeight = leftBlackHeight;

        if (node->color == Color::BLACK) {
            ++blackHeight;
        }

        return true;
    }

public:
    RedBlackTree()
        : root(nullptr),
          nodeCount(0) {
    }

    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(
        const RedBlackTree&
    ) = delete;

    ~RedBlackTree() override {
        clear();
    }

    void insert(T value) override {
        RedBlackNode<T>* newNode = insertNode(value);

        if (newNode != nullptr) {
            insertFixup(newNode);
        }
    }

    void remove(T value) override {
        removeNode(value);
    }

    bool contains(T value) override {
        return findNode(root, value) != nullptr;
    }

    std::size_t size() const override {
        return nodeCount;
    }

    bool isEmpty() const override {
        return nodeCount == 0;
    }

    void clear() override {
        clearNodes(root);

        root = nullptr;
        nodeCount = 0;
    }

    int height() const {
        return getHeight(root);
    }

    bool isBalanced() const {
        if (root == nullptr) {
            return true;
        }

        if (root->color != Color::BLACK) {
            return false;
        }

        int blackHeight = 0;

        return validateBlackHeight(
            root,
            blackHeight
        );
    }
};

#endif