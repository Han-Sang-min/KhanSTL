#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <cstdint>

namespace khan {

template<typename T, uint32_t N>
class Array {
public:
    using value_type = T;
    using size_type = uint32_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    T data_[N];

    constexpr Array() = default;

    constexpr reference       operator[](size_type index)         { return data_[index]; }
    constexpr const_reference operator[](size_type index) const   { return data_[index]; }

    constexpr size_type size() const noexcept {
        return N;
    }

    constexpr size_type cnt() const noexcept {
        size_type ret = 0;
        for (size_type i = 0; i < N; ++i)
            if (data_[i] != nullptr)
                ret++;
        return ret;
    }

    constexpr reference       at(size_type i) {
        if (i >= N) error_trap();
        return data_[i];
    }

    constexpr const_reference at(size_type i) const {
        if (i >= N) error_trap();
        return data_[i];
    }

    constexpr reference       front()       { return data_[0]; }
    constexpr const_reference front() const { return data_[0]; }

    constexpr reference       back()        { return data_[N - 1]; }
    constexpr const_reference back() const  { return data_[N - 1]; }

    constexpr iterator       begin()       { return data_; }
    constexpr const_iterator begin() const { return data_; }
    constexpr iterator       end()         { return data_ + N; }
    constexpr const_iterator end()   const { return data_ + N; }

    void fill(const T& v) {
        for (size_type i = 0; i < N; ++i)
            data_[i] = v;
    }

private:
    [[noreturn]] void error_trap() const {
        while (1);
    }
};

} // namespace khan

#endif // ARRAY_HPP
