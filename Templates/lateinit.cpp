
template<class T, szc::util::require_<std::is_class<T>> = true>
class LateInit : public T {
private:
    T value;
    bool is_inited;

public:
    LateInit() : is_inited(false) {}
    template<class U> LateInit(U && x) : value(std::forward<U>(x)), is_inited(true) {}
    LateInit(const LateInit & other) : value(other.value), is_inited(other.is_inited) {}
    LateInit(LateInit && other) : value(std::move(other.value)), is_inited(std::move(other.is_inited)) {}

    template<class U> LateInit & operator=(U && x) & { value = std::forward<U>(x); is_inited = true; return *this; }
    template<class U> const LateInit & operator=(U && x) const & { value = std::forward<U>(x); is_inited = true; return *this; }

    operator T() & { assert(is_inited); return value; }
    operator T() const & { assert(is_inited); return value; }
};

template<class T, szc::util::require_<std::__not_<std::is_class<T>>> = true>
class LateInit {
private:
    T value;
    bool is_inited;

public:
    LateInit() : is_inited(false) {}
    template<class U> LateInit(U && x) : value(std::forward<U>(x)), is_inited(true) {}
    LateInit(const LateInit & other) : value(other.value), is_inited(other.is_inited) {}
    LateInit(LateInit && other) : value(std::move(other.value)), is_inited(std::move(other.is_inited)) {}

    template<class U> LateInit & operator=(U && x) & { value = std::forward<U>(x); is_inited = true; return *this; }
    template<class U> const LateInit & operator=(U && x) const & { value = std::forward<U>(x); is_inited = true; return *this; }

    operator T() & { assert(is_inited); return value; }
    operator T() const & { assert(is_inited); return value; }
};

// template<class T> LateInit<T> late() { return std::move(LateInit<T>()); }
template<class T> using late = LateInit<T>;
