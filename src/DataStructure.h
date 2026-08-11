template <typename T>
class DataStructure{
public:
    DataStructure();
    virtual ~DataStructure();
    virtual void insert(T value) = 0;
    virtual void remove(T value) = 0;
    virtual bool contains(T value) = 0;
    virtual size_t size() const=0;
    virtual bool isEmpty() const=0;
    virtual void clear()=0;
};

