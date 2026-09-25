#ifndef RED_BLACK_NODE_H
#define RED_BLACK_NODE_H

enum class Color {
    RED,
    BLACK
};

template <typename T>
class RedBlackNode {
public:
    T value;
    Color color;

    RedBlackNode<T>* left;
    RedBlackNode<T>* right;
    RedBlackNode<T>* parent;

    RedBlackNode(const T& value)
        : value(value),
          color(Color::RED),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {
    }
};

#endif