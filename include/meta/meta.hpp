#ifndef META_HPP
#define META_HPP

#include <cstdint>
#include <type_traits>

namespace khan
{

//--------------------------------------------------------------

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
    
//--------------------------------------------------------------

/* Max relative */
template<typename T1, typename T2, bool condition = (sizeof(T1) > sizeof(T2))>
struct TypeMax {
    using type = T1;
};

template<typename T1, typename T2>
struct TypeMax<T1, T2, false> {
    using type = T2;
};

template<typename TypeList>
struct MaxTypeFromList;

template<>
struct MaxTypeFromList<TypeList<>> {
    using type = uint8_t;
};

template<typename Head, typename... Tail>
struct MaxTypeFromList<TypeList<Head, Tail...> > 
    : TypeMax<Head, typename MaxTypeFromList<TypeList<Tail...> >::type > {};

/* is in relative */
template<typename T, typename List>
struct isInList;

template<typename T>
struct isInList<T, TypeList<> > 
    : std::false_type {};

template<typename T, typename Head, typename... Tail>
struct isInList<T, TypeList<Head, Tail...> >
    : std::conditional<
        std::is_same<T, Head>::value,
        std::true_type,
        typename isInList<T, TypeList<Tail...> >::type >::type {};

//--------------------------------------------------------------

template <typename T, typename U>
struct is_same : std::false_type {};

template <typename T>
struct is_same<T, T> : std::true_type {};

template <typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

} // khan

#endif // META_HPP