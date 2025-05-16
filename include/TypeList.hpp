#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP

#include <cstddef>

namespace khan {

template<typename... Ts>
struct TypeList {};

// get the length
template<typename List> 
struct Length;

template<typename... Ts>
struct Length<TypeList<Ts...>> {
    static constexpr std::size_t value = sizeof...(Ts);
};

// get the Nth type
template<typename List, std::size_t N> 
struct TypeAt;

template<typename Head, typename... Tail>
struct TypeAt<TypeList<Head, Tail...>, 0> {
    using type = Head;
};
template<typename Head, typename... Tail, std::size_t N>
struct TypeAt<TypeList<Head, Tail...>, N>
  : TypeAt<TypeList<Tail...>, N-1> {};

// convenience alias
template<typename List, std::size_t N>
using TypeAt_t = typename TypeAt<List, N>::type;

} // namespace khan

#endif // TYPE_LIST_HPP