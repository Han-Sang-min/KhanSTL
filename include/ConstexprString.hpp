#ifndef CONSTEXPT_STRING_HPP
#define CONSTEXPT_STRING_HPP

#include <array>
#include <cstdint>

namespace khan {

constexpr size_t const_strlen(const char* s) {
    size_t i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

template <size_t N1, size_t N2>
constexpr auto const_strcat(const char (&s1)[N1], const char (&s2)[N2]) 
{
    std::array<char, N1 + N2 - 1> result{};
    
    for(size_t i = 0; i < N1 - 1; ++i) result[i] = s1[i];
    for(size_t i = 0; i < N2; ++i) result[N1 - 1 + i] = s2[i];
    
    return result;
}

} // khan

#endif // CONSTEXPT_STRING_HPP