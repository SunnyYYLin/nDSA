#ifndef TREE_HPP
#define TREE_HPP
using Rank = unsigned int;

template <typename T>
using BinNodePosi = BinNode<T>*;

template <typename T>
struct BinNode {
    BinNodePosi<T> parent, lc, rc;
    T data;
    int height;
    BinNode() : parent(nullptr), lc(nullptr), rc(nullptr), height(0) {}
    BinNode(T e, BinNodePosi<T> p = nullptr, BinNodePosi<T> lc = nullptr, BinNodePosi<T> rc = nullptr, int h = 0) 
    : data(e), parent(p), lc(lc), rc(rc), height(h) {}
    Rank size();
    Rank updateHeight();
    void updateHeightAbove();
    BinNodePosi<T> insertAsLC(T const& e);
    BinNodePosi<T> insertAsRC(T const& e);
    BinNodePosi<T> succ();
    template <typename VST> void travLevel(VST&);
    template <typename VST> void travPre(VST&);
    template <typename VST> void travIn(VST&);
    template <typename VST> void travPost(VST&);
}

template <typename T>
class BinTree {
protected:
    int _size;
    BinNodePosi<T> _root;
public:
    // Read-only
    Rank size() const {
        return _size;
    }
    bool empty() const {
        return !_root;
    }
    BinNodePosi<T> root() const {
        return _root;
    }
    BinNodePosi<T> insert(T const& e);
    BinNodePosi<T> insert(T const&, BinNodePosi<T>);
    BinNodePosi<T> insert(BinNodePosi<T>, T const&);
    BinNodePosi<T> attach(BinTree<T>*&, BinNodePosi<T>);
    BinNodePosi<T> attach(BinNodePosi<T>, BinTree<T>*&);
    Rank remove(BinNodePosi<T>);
    BinTree<T>* secede(BinNodePosi<T>);
}

#endif