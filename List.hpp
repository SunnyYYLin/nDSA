#ifndef LIST_HPP
#define LIST_HPP
using Rank = int;

template <typename T>
struct ListNode {
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;
    ListNode() {}
    ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr) : data(e), pred(p), succ(s) {}
    ListNode<T>* insertAsPred(T const& e);
    ListNode<T>* insertAsSucc(T const& e);
};
template <typename T>
using ListNodePosi = ListNode<T>*;

template <typename T>
class List {
private:
    int _size;
    ListNodePosi<T> header; // rank = -1
    ListNodePosi<T> trailer; // rank = n
protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi<T>, Rank);
    ListNodePosi<T> merge(ListNodePosi<T>, Rank, List<T>&, ListNodePosi<T>, Rank);
    void mergeSort(ListNodePosi<T>, Rank);
    void selectionSort(ListNodePosi<T>, Rank);
    void insertionSort(ListNodePosi<T>, Rank);
    void radixSort(ListNodePosi<T>, Rank);
public:
    List() {
        init();
    }
    List(List<T> const& L) {
        copyNodes(L.first(), L._size);
    }
    List(List<T> const& L, Rank r, int n) {
        copyNodes(L[r], n);
    }
    List(ListNodePosi<T> p, int n) {
        copyNodes(p, n);
    }
    // Read-only
    ~List();
    Rank size() const {
        return _size;
    }
    bool empty() const {
        return _size <= 0;
    }
    ListNodePosi<T> first() const {
        return header->succ;
    }
    ListNodePosi<T> last() const {
        return trailer->pred;
    }
    ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const;
    ListNodePosi<T> find(T const& e) const {
        return find(e, _size, trailer);
    }
    ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const;
    ListNodePosi<T> search(T const& e) const {
        return search(e, _size, trailer);
    }
    ListNodePosi<T> selectMax(ListNodePosi<T> p, int n);
    ListNodePosi<T> selectMax() {
        return selectMax(header->succ, _size);
    }
    // Insert
    ListNodePosi<T> insertAsFirst(T const& e) {
        return insert(e, header->succ);
    }
    ListNodePosi<T> insertAsLast(T const& e) {
        return insert(e, trailer);
    }
    ListNodePosi<T> insert(ListNodePosi<T> p, T const& e) {
        return insert(e, p->succ);
    }
    ListNodePosi<T> insert(T const& e, ListNodePosi<T> p);
    T remove(ListNodePosi<T> p);
    // Write
    T operator[](Rank r) const;
    void sort(ListNodePosi<T> p, int n);
    void sort() {
        sort(first(), _size);
    }
    int dedup();
    int uniquify();
    void reverse();
    void traverse(void (*)(T&));
    template <typename VST>
    void traverse(VST&);
};
#endif