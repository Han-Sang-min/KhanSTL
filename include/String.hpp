#ifndef STRING_HPP
#define STRING_HPP

namespace khan
{

template <unsigned N>
class String {
public:
    using size_type = unsigned;

    String() 
        : size_(0)
    {
        data_[0] = '\0';
    }

    String(const char* s) 
        : size_(0)
    {
        assign(s);
    }

    String(const String& o) = default;

    String& operator=(const String& o)  {
        if (this != &o) {
            size_ = o.size_;
            for (size_type i = 0; i <= size_; ++i)
                data_[i] = o.data_[i];
        }
        return *this;
    }

    String& operator=(const char* s)  {
        return assign(s);
    }

    constexpr size_type size()     const  { return size_; }
    constexpr size_type capacity() const  { return N; }
    constexpr bool      empty()    const  { return size_ == 0; }

    constexpr char&       operator[](size_type i)        { return data_[i]; }
    constexpr const char& operator[](size_type i) const  { return data_[i]; }

    char& at(size_type i) {
        if (i >= size_)
            error_trap();
        return data_[i];
    }
    const char& at(size_type i) const {
        if (i >= size_)
            error_trap();
        return data_[i];
    }

    const char* c_str() const  { return data_; }

    void clear()  {
        size_ = 0;
        data_[0] = '\0';
    }

    String& assign(const char* s)  {
        clear();
        while (*s && size_ < N) {
            data_[size_++] = *s++;
        }
        data_[size_] = '\0';
        return *this;
    }

    void push_back(char c)  {
        if (size_ >= N)
            error_trap();
        data_[size_++] = c;
        data_[size_]   = '\0';
    }

    String& append(const char* s)  {
        while (*s) {
            if (size_ >= N) 
                error_trap();
            data_[size_++] = *s++;
        }
        data_[size_] = '\0';
        return *this;
    }

    String& operator+=(const char* s)  { return append(s); }
    String& operator+=(char c)         { push_back(c); return *this; }

private:
    char      data_[N+1];
    size_type size_;

    [[noreturn]] void error_trap() {
        for (;;) {}
    }
};

} // namespace khan

#endif // STRING_HPP