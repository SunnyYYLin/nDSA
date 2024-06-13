#include "List.hpp"

/*------- Construction ------*/
template <typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

// O(n)
template <typename T>
void List<T>::copyNodes(ListNodePosi<T> p, Rank n) {
    init();
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

// O(n)
template <typename T>
List<T>::~List() {
    clear();
    delete header;
    delete trailer;
}

// O(n)
template <typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (0 < _size) {
        remove(header->succ);
        // 若remove( header->succ )改作remove( trailer->pred )呢？
    }
    return oldSize;
}

// O(r)
template <typename T>
T List<T>::operator[](Rank r) const {
    ListNodePosi<T> p = first();
    while (0 < r--) {
        p = p->succ;
    }
    return p->data;
}

/*------ insert -------*/
template <typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e) {
    ListNodePosi<T> x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e) {
    ListNodePosi<T> x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

template <typename T>
ListNodePosi<T> List<T>::insert(T const& e, ListNodePosi<T> p) {
    _size++;
    return p->insertAsSucc(e);
}

// remove
template <typename T>
T List<T>::remove(ListNodePosi<T> p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

/*----------- Unordered List ----------*/
// O(n)
template <typename T>
ListNodePosi<T> List<T>::find(T const& e, int n, ListNodePosi<T> p) const {
    while (0 < n--) {
        if (e == (p = p->pred)->data) {
            return p;
        }
    }
    return nullptr;
}

// O(n^2)
template <typename T>
int List<T>::dedup() {
    int oldSize = _size;
    ListNodePosi<T> p = first();
    for (Rank r = 0; p != trailer; p = p->succ) {
        if (ListNodePosi<T> q = find(p->data, r, p)) {
            remove(q);
        } else {
            r++;
        }
    }
    return oldSize - _size;
}

template <typename T>
void List<T>::traverse(void (*visit)(T&)) {
    for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) {
        visit(p->data);
    }
}

/*----------- Ordered List ----------*/
// O(n) worst, O(1) best
template <typename T>
ListNodePosi<T> List<T>::search(T const& e, int n, ListNodePosi<T> p) const {
    do {
        p = p->pred;
    } while ((0 <= n--) && (e < p->data));
    return p;
}

// O(n)
template <typename T>
int List<T>::uniquify() {
    if (_size < 2) {
        return 0;
    }
    int oldSize = _size;
    ListNodePosi<T> p = first();
    ListNodePosi<T> q;
    while (trailer != (q = p->succ)) {
        if (p->data != q->data) {
            p = q;
        } else {
            remove(q);
        }
    }
    return oldSize - _size;
}

// Sort
#include <cstdlib> // Add the missing include statement

template <typename T>
void List<T>::sort(ListNodePosi<T> p, Rank n) {
    switch (std::rand() % 3) { // Replace rand() with std::rand()
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            selectionSort(p, n);
            break;
        default:
            mergeSort(p, n);
            break;
    }
}


    // selection sort
        // \Omega(n^2)
template <typename T>
void List<T>::selectionSort(ListNodePosi<T> p, Rank n) {
    ListNodePosi<T> head = p->pred;
    ListNodePosi<T> tail = p;
    for (int i = 0; i < n; i++) {
        tail = tail->succ;
    }
    while (1 < n) {
        insert(remove(selectMax(head->succ, n)), tail);
        tail = tail->pred;
        n--;
    }
}

        // \Omega(n - k)
        // 可以！...利用高级数据结构，selectMax()可改进至O(logn)
        // 当然，如此立即可以得到O(nlogn)的排序算法
template <typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, Rank n) {
    ListNodePosi<T> max = p;
    for (ListNodePosi<T> cur = p; 1 < n; n--) {
        if (!((cur = cur->succ)->data < max->data)) {
            // cur = cur->succ;
            // cur->data < max->data
            max = cur;
        }
    }
    return max;
}

    // insertion sort
    // O(n^2) means; O(1) space
template <typename T>
void List<T>::insertionSort(ListNodePosi<T> p, Rank n) {
    for (int r = 0; r < n; r++) { // O(r+1)
        insert(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

    // merge sort
    // O(nlogn)
template <typename T>
void List<T>::mergeSort(ListNodePosi<T> p, Rank n) {
    if (n < 2) {
        return;
    }
    int m = n >> 1;
    ListNodePosi<T> q = p;
    for (int i = 0; i < m; i++) {
        q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);
}

    // O(n+m)
template <typename T>
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, Rank n, List<T>& L, ListNodePosi<T> q, Rank m) {
    ListNodePosi<T> pp = p->pred;
    while ((0 < m) && (q != p)) {
        if ((0 < n) && (p->data <= q->data)) {
            p = p->succ;
            n--;
        } else {
            insert(L.remove((q = q->succ)->pred), p);
            m--;
        }
    }
    return pp->succ;
}

/*
    任意给定一个序列，如何统计其中逆序对的总数？
    蛮力算法需要\Omega(n^2)时间；而借助归并排序，仅需O(nlogn)时间...
*/