#pragma once

#include <vector>

struct Graph {
public:
    struct Edge { int y, nxt; Edge(int _y = 0, int _nxt = 0) : y(_y), nxt(_nxt) {} };

    class iterator {
        friend class Graph;

    private:
        Graph * g;
        int _x;

        iterator(Graph * _g, int __x) : g(_g), _x(__x) {}

    public:
        iterator() {}
        iterator(iterator &) = default;
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;

        iterator operator++() { return (this->_x = g->next(_x)), *this; }
        int operator*() { return g->at(_x); }
        bool operator==(const iterator & other) { return (g == other.g) && (_x == other._x); }
        bool operator!=(const iterator & other) { return !((*this) == other); }

        iterator & begin() & { return *this; }
        const iterator & begin() const & { return *this; }
        iterator end() { return std::move(iterator(g, 0)); }
    };

private:
    std::vector<int> _head;
    std::vector<Edge> e;

public:
    Graph() {}
    Graph(int n) : _head(n + 5), e(1) {}
    Graph(int n, int m) : Graph(n) { e.reserve(m + 5); }

    void link(int x, int y) { e.emplace_back(y, _head[x]); _head[x] = e.size() - 1; }

    int & head(int x) & { return _head.at(x); }
    const int & head(int x) const & { return _head.at(x); }

    int & next(int x) & { return e.at(x).nxt; }
    const int & next(int x) const & { return e.at(x).nxt; }

    int & at(int x) & { return e.at(x).y; }
    const int & at(int x) const & { return e.at(x).y; }

    iterator iter(int x) { return std::move(iterator(this, head(x))); }
};
