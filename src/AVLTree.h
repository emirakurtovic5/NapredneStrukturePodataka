template <typename T>
class AVLNode : public DataStructure<T>{
        AVLNode<T>* root;
        size_t nodeCount;
        AVLNode<T>* rotateLeft(AVLNode<T>* node);
        AVLNode<T>* rotateRight(AVLNode<T>* node);
        int getHeight(AVLNode<T>* node);
        int getBalanceFactor(AVLNode<T>* node);
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

};