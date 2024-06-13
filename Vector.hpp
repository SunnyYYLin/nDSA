#ifndef VECTOR_HPP
#define VECTOR_HPP

#define DEFAULT_CAPACITY 3
using Rank = unsigned int;

template <typename T>
class Vector {
protected:
    Rank _size; // 规模
    int _capacity; // 容量
    T* _elem; // 数据区
    void copyFrom(T const* A, Rank lo, Rank hi);
    // memory management
    void expand();
    void shrink();
    // sort
    void bubbleSort(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    Rank partition(Rank lo, Rank hi); // 轴点
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);
    
public:
    // Construction
    Vector (Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) {
        _elem = new T[_capacity = c]; // 初始容量为c, T[c]是一个数组
        for (_size = 0; _size < s; _elem[_size++] = v);
    }
        // by copyFrom
    Vector (T const* A, Rank n) {
        copyFrom(A, 0, n);
    }
    Vector (T const* A, Rank lo, Rank hi) {
        copyFrom(A, lo, hi);
    }
    Vector (Vector<T> const& V) {
        copyFrom(V._elem, 0, V._size);
    }
    Vector (Vector<T> const& V, Rank lo, Rank hi) {
        copyFrom(V._elem, lo, hi);
    }
    // Destruction
    ~Vector() {
        delete [] _elem;
    }
    // Read-only
    Rank size() const {
        return _size;
    }
    bool empty() const {
        return !_size;
    }
        // find
    Rank find(T const& e) const {
        return find(e, 0, _size);
    }
    Rank find(T const& e, Rank lo, Rank hi) const;
        // search
    Rank search(T const& e) const {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const;
    // Write
    T get(Rank r) const;
    T put(Rank r, T const& e);
    T& operator[] (Rank r) const; // left value
    Vector<T>& operator= (Vector<T> const&);
    T remove(Rank r) {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }
    T remove(Rank lo, Rank hi);
        // insert
    Rank insert (Rank r, T const& e);
    Rank insert (T const& e) {
        return insert(_size, e);
    }
        // sort
    void sort(Rank lo, Rank hi);
    void sort() {
        sort(0, _size);
    }
        // unsort
    void unsort(Rank lo, Rank hi);
    void unsort() {
        unsort(0, _size);
    }
        // deduplicate & uniquify
    Rank dedup();
    Rank uniquify();
    // traverse
    void traverse (void (*)(T&)); // (*): function pointer; T&: argument type
    /*
        // 定义一个函数，它接受一个int引用，并打印它
        void print(int& i) {
            std::cout << i << std::endl;
        }

        // 假设vec是一个Vector<int>
        vec.traverse(print); // 调用traverse，传递print函数
    */
    template <typename VST> void traverse (VST&); // VST: function object
    /*
        // 定义一个函数对象
        struct Print {
            void operator() (int& i) {
                std::cout << i << std::endl;
            }
        };

        // 假设vec是一个Vector<int>
        vec.traverse(Print()); // 调用traverse，传递Print函数对象
    */
};

template <typename T>
class Stack: public Vector<T> {
public:
    void push(T const& e) {
        this->insert(e);
    }
    T pop() {
        return this->remove(this->size() - 1);
    }
    T& top() {
        return (*this)[this->size() - 1];
    }
};

#endif