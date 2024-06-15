#include "Tree.hpp"
#include "Stack.hpp"

/*--------------- BinNode -------------*/
#define stature(p) ((int)((p) ? (p)->height : -1))

template <typename T>
BinNodePosi<T> BinNode<T>::insertAsLC(T const& e) {
    return lc = new BinNode(e, this);
}
template <typename T>
BinNodePosi<T> BinNode<T>::insertAsRC(T const& e) {
    return rc = new BinNode(e, this);
}

template <typename T>
Rank BinNode<T>::updateHeight() {
    return height = 1 + std::max(stature(lc), stature(rc));
}

template <typename T>
void BinNode<T>::updateHeightAbove() {
    while (parent) {
        parent->updateHeight();
        parent = parent->parent;
    }
}
/*--------------- BinTree -------------*/

template <typename T>
BinNodePosi<T> BinTree<T>::insert(BinNodePosi<T> x, T const& e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

// remove
template <typename T>
static BinNodePosi<T> FromParentTo(BinNode<T> x) {
    if (!x->parent) return nullptr;
    if (x->parent->lc == x) {
        return x->parent->lc;
    } else {
        return x->parent->rc;
    }
}

template <typename T>
static int removeAt(BinNodePosi<T> x) {
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data);
    release(x);
    return n;
}

template <typename T>
Rank BinTree<T>::remove(BinNodePosi<T> x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template <typename T>
BinNodePosi<T> BinTree<T>::attach(BinNodePosi<T> x, BinTree<T>*& S) {
    if (x->rc = S->_root) {
        x->rc->parent = x;
    }
    _size += S->_size;
    x->updateHeightAbove();
    S->_root = nullptr;
    S->_size = 0;
    release(S);
    S = nullptr;
}

template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi<T> x) {
    FromParentTo(*x) = nullptr;
    x->parent->updateHeightAbove();
    BinTree<T>* S = new BinTree<T>;
    S->_root = x;
    x->parent = nullptr;
    S->_size = x->size();
    _size -= S->_size;
}

template <typename T>
Rank BinNode<T>::size() {
    Rank s = 1;
    if (lc) {
        s += lc->size();
    }
    if (rc) {
        s += rc->size();
    }
    return s;
}

/*------------------ traverse -----------------*/
template <typename T, typename VST>
void traverse(BinNodePosi<T> x, VST& visit) {
    if (!x) return;
    visit(x->data);
    traverse(x->lc, visit);
    traverse(x->rc, visit);
}

