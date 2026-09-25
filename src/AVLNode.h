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