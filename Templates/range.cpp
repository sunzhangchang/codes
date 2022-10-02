
template<class T, szc::util::require_<std::is_integral<T>> = true>
class Range {
private:
    class iterator {
        T it;
        Range * self_range;

    public:
        iterator(T _it, Range * r) : it{std::move(_it)}, self_range{r} {}

        iterator operator++() {
            auto t = *this;
            it += self_range->step;
            -- self_range->num;
            return t;
        }

        bool operator!=(const iterator & other) const { return self_range->num > 0; }

        const T & operator*() const { return it; }
    };

    iterator bg, ed;
    ssize_t step;
    ssize_t num;

public:
    Range(T _l, T _r, ssize_t _step)
        : bg{_l, this}, ed{_r, this}, step(_step) {
        if (_step < 0) {
            auto _t = std::move(_l);
            _l = std::move(_r);
            _r = std::move(_t);
        }
        _step = ((_step < 0) ? -_step : _step);
        if (_l < _r) {
            num = (_r - _l - 1) / _step;
            num += (_l + num * _step != _r);
        } else {
            num = 0;
        }
    }

    const iterator & begin() const & { return bg; }
    const iterator & end() const & { return ed; }
};

template<class T, szc::util::require_<std::is_integral<T>> = true>
Range<T> range(T && r) {
    return Range<T>{0, std::forward<T>(r), 1};
}

template<class T, szc::util::require_<std::is_integral<T>> = true>
Range<T> range(const T & r) {
    return Range<T>{0, r, 1};
}

template<class T, szc::util::require_<std::is_integral<T>> = true>
Range<T> range(T l, T r, ssize_t step = 1) {
    return Range<T>{std::move(l), std::move(r), std::move(step)};
}
