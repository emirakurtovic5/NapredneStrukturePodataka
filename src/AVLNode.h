/*template <typename T>
class AVLNode{
public:
    AVLNode(T value);
    T value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};*/

#ifndef AVL_NODE_H
#define AVL_NODE_H

template <typename T>
class AVLNode {
public:
    T value;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    AVLNode(const T& value)
        : value(value),
          left(nullptr),
          right(nullptr),
          height(1) {
    }
};

#endif