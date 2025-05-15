#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace khan
{

template<typename T, unsigned N>
class Vector {
public:
    using value_type      = T;
    using size_type       = unsigned;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using iterator        = T*;
    using const_iterator  = const T*;

    Vector() noexcept
      : size_(0)
    {}

    Vector(const Vector& o) = default;
    Vector& operator=(const Vector& o) = default;

    constexpr size_type size()     const { return size_; }
    constexpr size_type capacity() const { return N; }
    constexpr bool      empty()    const { return size_ == 0; }
    constexpr bool      full()     const { return size_ == N; }

    constexpr reference       operator[](size_type i)       { return data_[i]; }
    constexpr const_reference operator[](size_type i) const { return data_[i]; }

    reference at(size_type i) {
        if (i >= size_) 
            error_trap();
        return data_[i];
    }
    const_reference at(size_type i) const {
        if (i >= size_) 
            error_trap();
        return data_[i];
    }

    reference       front()       { return data_[0]; }
    const_reference front() const { return data_[0]; }
    reference       back()        { return data_[size_-1]; }
    const_reference back() const  { return data_[size_-1]; }

    void clear() {
        size_ = 0;
    }

    void push_back(const T& v) {
        if (size_ >= N) 
            error_trap();
        data_[size_++] = v;
    }

    void pop_back() {
        if (size_ == 0) 
            error_trap();
        --size_;
    }

    iterator insert(iterator pos, const T& v) {
        size_type idx = pos - data();
        if (size_ >= N || idx > size_) 
            error_trap();
        for (size_type i = size_; i > idx; --i)
            data_[i] = data_[i-1];
        data_[idx] = v;
        ++size_;
        return &data_[idx];
    }

    iterator erase(iterator pos) {
        size_type idx = pos - data();
        if (idx >= size_) 
            error_trap();
        for (size_type i = idx; i+1 < size_; ++i)
            data_[i] = data_[i+1];
        --size_;
        return &data_[idx];
    }

    pointer       data()       { return data_; }
    const_pointer data() const { return data_; }

    iterator       begin()       { return data(); }
    const_iterator begin() const { return data(); }
    iterator       end()         { return data() + size_; }
    const_iterator end()   const { return data() + size_; }

private:
    T           data_[N];
    size_type   size_;

    [[noreturn]] void error_trap() {
        while(1);
    }
};

} // namespace khan

#endif // VECTOR_HPP