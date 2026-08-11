template <typename T>
class AVLNode{
public:
    AVLNode(T value);
    T value;
    AVLNode* left;
    AVLNode* right;
    int height;
};