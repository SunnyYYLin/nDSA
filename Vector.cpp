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

// 练习：模仿此例，实现统一的减一、加倍、求和等更多的遍历功能
template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

/*        ordered vector, needing ordering relationship         */
// adjacent inversions
template <typename T>
void checkOrder (Vector<T>& V) {
    struct CheckOrder {
        int& unsorted;
        T pred; // ???
        CheckOrder(int& u, T& first) : unsorted(u), pred(first) {}
        void operator() (T& e) {
            if (pred > e) {
                unsorted++;
            }
            pred = e;
        }
    };

    int unsorted = 0;
    V.traverse(CheckOrder<T>(unsorted, V[0]));
    if (unsorted > 0) {
        printf("Unsorted with %d adjacent inversion(s)\n", unsorted);
    } else {
        printf("Sorted\n")
    }
}

// O(n)
// If shifting occurs at each removal of an element, the complexity is O(n^2);
template <typename T>
Rank Vector<T>::uniquify() {
    Rank i = 0, j = 0;
    while (++j < _size) {
        if (_elem[i] != _elem[j]) {
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    shrink();
    return j - i;
}

/*--- Search ---*/
// 轴点 mi：e<S[mi]? [lo, mi) : [mi, hi)
template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

// template <typename T>
// Rank Vector<T>::search_by_pivot(T const& e, Rank lo, Rank hi) const {
//     while (lo < hi) {
//         Rank mi = pivot(lo, hi);
//         (e < _elem[mi]) ? hi = mi : lo = mi + 1;
//     }
//     return --lo;
// }

// Version A
// O(logn); O(1) for each frame of recursion; O(1.50n)
// 3-branch
// pivot(lo, hi) := (lo + hi) >> 1
template <typename T>
static Rank binSearch(T* S, T const& e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if (e < S[mi]) {
            hi = mi;
        } else if (S[mi] < e) {
            lo = mi + 1;
        } else {
            return mi;
        }
    }
    return -1;
}

// Version B
// Only 2-branch: more balanced, better better, worse worse
template <typename T>
static Rank binSearch(T* S, T const& e, Rank lo, Rank hi) {
    while (hi - lo > 1) {
        Rank mi = (lo + hi) >> 1;
        (e < S[mi]) ? hi = mi : lo = mi;
    }
    return (e == S[lo]) ? lo : -1;
    // return (e < S[lo]) ? lo-1 : lo; can return the last one
}// ???????

// Version C
// Always return the last one
template <typename T>
static Rank binSearch(T* S, T const& e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        (e < S[mi]) ? hi = mi : lo = mi + 1;
    }
    return lo - 1;
}
// 122234
// 122(2)34
// 1222

// pivot(lo, hi) := lo + lambda * (hi - lo)
// then lambda = (sqrt(5) - 1) / 2 is the best
class Fib {
private:
    Rank f, g;
public:
    Fib(Rank n) {
        f = 1; g = 0;
        while (g < n) {
            next();
        }
    }
    Rank get() {
        return g;
    }
    Rank next() {
        g += f;
        f = g - f;
        return g;
    }
    Rank prev() {
        f = g - f;
        g -= f;
        return g;
    }
}

template <typename T>
static Rank fibSearch(T* S, T const& e, Rank lo, Rank hi) {
    for (Fib fib(hi - lo); lo < hi; ) {
        while (hi - lo < fib.get()) {
            fib.prev();

        }
    }
}
