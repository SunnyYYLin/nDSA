#include "Vector.hpp"

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)]; // Double Expansion. <Why?>
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

// Equivalent Complexity O(1);
// If expanding with a constant length, the complexity is O(n);
template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) {
        return;
    }
    if (_capacity < DEFAULT_CAPACITY) {
        _capacity = DEFAULT_CAPACITY;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) {
        return;
    }
    if (_size << 2 > _capacity) {
        return;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
    expand();
    for (int i = _size; i > r; i--) {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}

// O(m), m is the length of successors
template <typename T>
T Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) {
        return 0;
    }
    while (hi < _size) {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}

/*    unordered vector, needing equivalence definition   */

// O(n)
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

// O(n^2)
template <typename T>
Rank Vector<T>::dedup() {
    Rank oldSize = _size;
    for (Rank i = 1; i < _size; ) {
        if (find(_elem[i], 0, i) == -1) { // O(i)
            i++;
        } else {
            remove(i); // O(n - i)
        }
    }
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

