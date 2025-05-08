#ifndef SCENE_META_HPP
#define SCENE_META_HPP

#include <cstdint>
#include <type_traits>

namespace scene
{

namespace meta
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

template<typename TypeList>
struct MaxTypeFromList;

template<>
struct MaxTypeFromList<Nil> {
    using type = uint8_t;
};

template<typename First, typename Next>
struct MaxTypeFromList<TypeList<First, Next> > 
    : TypeMax<First, typename MaxTypeFromList<Next>::type > {};

/* is in relative */
template<typename T, typename List>
struct isInList;

template<typename T>
struct isInList<T, Nil> 
    : std::false_type {};

template<typename T, typename First, typename Next>
struct isInList<T, TypeList<First, Next> >
    : std::conditional<
        std::is_same<T, First>::value,
        std::true_type,
        typename isInList<T, Next>::type >::type {};

} // meta

} // scene

#endif // SCENE_META_HPP