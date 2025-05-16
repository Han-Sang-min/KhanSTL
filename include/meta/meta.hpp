#ifndef META_HPP
#define META_HPP

#include <cstdint>
#include <type_traits>

namespace khan
{

namespace detail
{

/* Utile */
template<typename First, typename Next>
struct TypeList;

struct Nil {};

/* Max relative */
template<typename T1, typename T2, bool condition = (sizeof(T1) > sizeof(T2))>
struct TypeMax {
    using type = T1;
};

template<typename T1, typename T2>
struct TypeMax<T1, T2, false> {
    using type = T2;
};

} // detail

template<typename TypeList>
struct MaxTypeFromList;

template<>
struct MaxTypeFromList<detail::Nil> {
    using type = uint8_t;
};

template<typename First, typename Next>
struct MaxTypeFromList<detail::TypeList<First, Next> > 
    : TypeMax<First, typename MaxTypeFromList<Next>::type > {};

/* is in relative */
template<typename T, typename List>
struct isInList;

template<typename T>
struct isInList<T, detail::Nil> 
    : std::false_type {};

template<typename T, typename First, typename Next>
struct isInList<T, detail::TypeList<First, Next> >
    : std::conditional<
        std::is_same<T, First>::value,
        std::true_type,
        typename isInList<T, Next>::type >::type {};

//--------------------------------------------------------------

template <typename T, typename U>
struct is_same : std::false_type {};

template <typename T>
struct is_same<T, T> : std::true_type {};

template <typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

} // khan

#endif // META_HPP