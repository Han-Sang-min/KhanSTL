#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <cstddef>  // for std::size_t

namespace khan {

template<typename... Ts>
class Tuple;

template<>
class Tuple<> {
public:
    constexpr Tuple() noexcept = default;
};

template<typename Head, typename... Tail>
class Tuple<Head, Tail...> {
public:
    using tail_type = Tuple<Tail...>;

    Head head;
    tail_type tail;

    constexpr Tuple() noexcept = default;
    constexpr Tuple(const Head& h, const Tail&... t) noexcept
        : head(h), tail(t...) {}
};

// Primary Template
template<std::size_t I, typename TupleT>
struct TupleElement;

// Base Case: I == 0
template<typename Head, typename... Tail>
struct TupleElement<0, Tuple<Head, Tail...>> {
    using type = Head;

    static constexpr type& get(Tuple<Head, Tail...>& t) noexcept {
        return t.head;
    }

    static constexpr const type& get(const Tuple<Head, Tail...>& t) noexcept {
        return t.head;
    }
};

// Recursive Case: I > 0
template<std::size_t I, typename Head, typename... Tail>
struct TupleElement<I, Tuple<Head, Tail...>> {
    using type = typename TupleElement<I - 1, Tuple<Tail...>>::type;

    static constexpr type& get(Tuple<Head, Tail...>& t) noexcept {
        return TupleElement<I - 1, Tuple<Tail...>>::get(t.tail);
    }

    static constexpr const type& get(const Tuple<Head, Tail...>& t) noexcept {
        return TupleElement<I - 1, Tuple<Tail...>>::get(t.tail);
    }
};

// Const Tuple Specialization (Preserves const-correctness)
template<std::size_t I, typename TupleT>
struct TupleElement<I, const TupleT> {
    using type = typename TupleElement<I, TupleT>::type;
    using const_type = const type;

    static constexpr const_type& get(const TupleT& t) noexcept {
        return TupleElement<I, TupleT>::get(t);
    }
};

// get<I>(tuple) function
template<std::size_t I, typename... Ts>
constexpr auto& get(Tuple<Ts...>& t) noexcept {
    return TupleElement<I, Tuple<Ts...>>::get(t);
}

template<std::size_t I, typename... Ts>
constexpr const auto& get(const Tuple<Ts...>& t) noexcept {
    return TupleElement<I, const Tuple<Ts...>>::get(t);
}

} // namespace khan

#endif // TUPLE_HPP
