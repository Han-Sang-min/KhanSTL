#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>
#include <type_traits>

namespace khan
{

template<typename T>
using remove_ref_t = typename std::remove_reference<T>::type;

template<typename T>
constexpr remove_ref_t<T>&& move(T&& arg) noexcept {
    return static_cast<remove_ref_t<T>&&>(arg);
}

/* allways called by lvalue reference */
template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

/* allways called by rvalue reference */
template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept {
    static_assert(
        !std::is_lvalue_reference<T>::value,
        "std::forward must not be used to convert an rvalue to an lvalue"
    );
    return static_cast<T&&>(t);
}

//--------------------------------------------------------------

template <size_t... I>
struct index_sequence {};

namespace detail {

template <size_t N, size_t... I>
struct make_index_sequence_impl : make_index_sequence_impl<N - 1, N - 1, I...> {};

template <size_t... I>
struct make_index_sequence_impl<0, I...> {
    using type = index_sequence<I...>;
};

} // namespace detail

template <size_t N>
using make_index_sequence = typename detail::make_index_sequence_impl<N>::type;

//--------------------------------------------------------------

} // namespace khan

#endif // UTILITY_HPP