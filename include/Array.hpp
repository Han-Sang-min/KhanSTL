#ifndef ARRAY_HPP
#define ARRAY_HPP

namespace khan
{

template<typename T, unsigned int N>
class Array {
public:
    using value_type = T;
    using size_type = unsigned int;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    /* Declared as public to follow the STL convention and to allow simple initialization without a constructor. */
    T data_[N];

    Array() = default;

    reference       operator[](size_type index)         { return data_[index]; }
    const reference operator[](size_type index) const   { return data_[index]; }
    
    reference       at(size_type i) {
        if (i >= N) 
            error_trap();
        return data_[i];
    }
    const_reference at(size_type i) const {
        if (i >= N) 
            error_trap();
        return data_[i];
    }

    reference       front()       { return data_[0]; }
    const_reference front() const { return data_[0]; }
    reference       back()        { return data_[N-1]; }
    const_reference back() const  { return data_[N-1]; }

    // iterators
    iterator       begin()       { return data_; }
    const_iterator begin() const { return data_; }
    iterator       end()         { return data_ + N; }
    const_iterator end()   const { return data_ + N; }

    void fill(const T& v) {
        for (size_type i = 0; i < N; ++i)
            data_[i] = v;
    }
    
private:
    [[noreturn]] void error_trap() const {
        while(1);
    }
};

} // namespace khan

#endif // STATIC_ARRAY_HPP