#include <bits/stdc++.h>

namespace szc {

template<typename T, typename Comp = std::less<T>>
class pairing_heap {
private:
    using value_type = T;
    using value_compare = Comp;

    struct Node;

    using pNode = Node *;
    using this_t = pairing_heap;

public:
    struct iterator;

private:
    value_compare cmp;
    pNode _root;
    size_t _size;

    pNode merge(pNode, pNode)
    pNode mergesons(pNode);
    iterator delete_top();
    void _destroy(pNode &);

public:
    pairing_heap() : cmp(), _root(nullptr), _size(0) {}
    pairing_heap(const this_t & o)
        : cmp(o.cmp), _root(o._root), _size(o.size) {
    }
    pairing_heap(this_t && o)
        : cmp(std::move(o.cmp)), _root(std::move(o._root)), _size(std::move(o.size)) {
    }

    ~pairing_heap() { this->destroy(); }

    iterator push(const T &);
    iterator merge(const this_t &);
    iterator join(this_t &);
    iterator pop();
    T top();
    size_t size();
    bool empty();
    void destroy();
    std::pair<iterator, bool> modify(const this_t &, const T &);
}

template<typename T, typename Comp>
struct pairing_heap<T, Comp>::Node {
    Node * prv = nullptr;
    Node * son = nullptr;
    Node * bro = nullptr;
    T val = T();

    Node() = default;
    explicit Node(T & v) : Node(), val(v) {}
    explicit Node(const T & v) : Node(), val(v) {}
    explicit Node(T && v) : Node(), val(std::move(v)) {}
}

template<typename T, typename Comp>
struct pairing_heap<T, Comp>::iterator {
private:
    Node * node = nullptr;

    friend class pairing_heap;

public:
    T operator*() const { return node->val; }

    template<class U> bool operator==(U && o) const { return node == o; }
    template<class U> bool operator!=(U && o) const { return node != o; }

    iterator() = default;
    explicit iterator(iterator & o) : node{o} {}
    explicit iterator(const iterator & o) : node{o} {}
    explicit iterator(iterator && o) : node{std::move(o)} {}
}

// 合并两个配对堆，时间复杂度 O(1)
template<typename T, typename Comp>
typename pairing_heap<T, Comp>::pNode
pairing_heap<T, Comp>::merge(pairing_heap::pNode a, pairing_heap::pNode b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (cmp(a->val, b->val)) {
        std::swap(a, b);
    }
    b->prv = a;
    b->cro = a->son;
    if (a->son != nullptr) {
        a->son->prv = b;
    }
    a->son = b;
    return a;
}

// 插入
template<typename T, typename Comp>
typename pairing_heap<T, Comp>::iterator
pairing_heap<T, Comp>::push(const T & val) {
    ++ _size;
    if (_root == nullptr) {
        _root = new Node(val);
    } else {
        pNode node = new Node(val);
        _root = merge(_root, node);
    }
    return iterator(_root);
}

// 合并两个配对堆，仅合并而不清空加入的配对堆
template<typename T, typename Comp>
typename pairing_heap<T, Comp>::iterator
pairing_heap<T, Comp>::merge(const pairing_heap<T, Comp> * o) {
    _root = merge(_root, o._root);
    _size += o._size;
    return iterator(_root);
}

// 合并两个配对堆，并清空加入的配对堆
template<typename T, typename Comp>
typename pairing_heap<T, Comp>::iterator
pairing_heap<T, Comp>::join(pairing_heap<T, Comp> & o) {
    merge(o);
    o.destroy();
    return iterator(_root);
}

template<typename T, typename Comp>
typename pairing_heap<T, Comp>::pNode
pairing_heap<T, Comp>::mergesons(pairing_heap::pNode x) {
    if (x == nullptr || x->bro == nullptr) {
        return x;
    }
    pNode a = x->bro;
    pNode b = a->bro;
    a->prv = x->prv = x->bro = a->bro = nullptr;
    return merge(merge(x, a), mergesons(b));
}

template<typename T, typename Comp>
typename pairing_heap<T, Comp>::iterator
pairing_heap<T, Comp>::delete_top() {
    -- _size;
    _root = mergesons(_root->son);
    return iterator(_root);
}

template<typename T, typename Comp>
typename pairing_heap<T, comp>::iterator
pairing_heap<T, Comp>::pop() {
    if (_root == nullptr) {
        return;
    }
    pNode rt = _root;
    delete_top();
    delete rt;
    rt = nullptr;
    return iterator(_root);
}

template<typename T,typename Comp>
size_t pairing_heap<T, Comp>::size() {
    return _size;
}

template<typename T, typename Comp>
T pairing_heap<T, Comp>::top() {
    assert(_root != nullptr);
    return _root->val;
}

template<typename T, typename Comp>
bool pairing_heap<T, Comp>::empty() {
    return _root == nullptr;
}

template<typename T, typename Comp>
void
pairing_heap<T, Comp>::_destroy(pairing_heap::pNode & x) {
    if (x == nullptr) {
        return;
    }
    _destroy(x->bro);
    _destroy(x->son);
    -- _size;
    delete x;
    x = nullptr;
}

template<typename T, typename Comp>
void
pairing_heap<T, Comp>::destroy() {
    _destroy(_root);
    assert(_size == 0);
}

template<typename T, typename Comp>
std::pair<typename pairing_heap<T, Comp>::iterator, bool>
pairing_heap<T, Comp>::modify(const pairing_heap::iterator & iter, const T & val)
{
    if (iter.node == nullptr || cmp(val, *iter)) {
        return {iter, false};
    }
    pNode x = iter.node;
    x->val = val;
    if (x == _root) {
        return {iter, true};
    }
    if (x->prv->son == x) {
        x->prv->son = x->bro;
    } else {
        x->prv->bro = x->bro;
    }
    if (x->bro != nullptr) {
        x->bro->prv = x->prv;
    }
    x->prv = x->bro = nullptr;
    _root = merge(_root, x);
    return {iter, true};
}

namespace test {
    int main()
    {
        pairing_heap<int, std::less<>> h;

        for (int i = 1; i <= 100; ++ i) {
            h.push(i);
        }

        h.destroy();
        return 0;
    }
}
}
