#ifndef KHAN_FUNCTION_HPP
#define KHAN_FUNCTION_HPP

#include <cstdint>
#include "meta/utility.hpp"

namespace khan {

template<typename F, typename R, typename... Args>
struct FunctorOps {
    struct Ops {
        R    (*invoke)(void*, Args...);
        void (*destroy)(void*);
        void (*construct)(void*, const void*);
    };

    static const Ops& ops() {
        static const Ops instance = {
            // invoke
            /* 
                I don't know if it is okay to cast `F*`, because as far I know, the C standard 
                doesn't allow casting function pointer to `void*` and vice versa.
                For now, implement it by casting it as a double pointer and referencing it.
            */
            +[](void* buf, Args... a) -> R {
                return (*reinterpret_cast<F*>(buf))(khan::forward<Args>(a)...);
            },
            // destroy
            +[](void* buf) {
                reinterpret_cast<F*>(buf)->~F();
            },
            // construct (copy-construct)
            +[](void* buf, const void* fptr) {
                new (buf) F(*reinterpret_cast<const F*>(fptr));
            }
        };
        return instance;
    }
};

template<typename Signature, uint32_t BufferSize>
class Function;

template<typename R, typename... Args, uint32_t BufferSize>
class Function<R(Args...), BufferSize> {
public:
    Function() : ops_(nullptr) {}
    ~Function() { reset(); }

    R operator()(Args... a) const {
        return ops_->invoke(storage_, khan::forward<Args>(a)...);
    }

    explicit operator bool() const {
        return ops_ != nullptr;
    }

    void reset() {
        if (ops_) {
            ops_->destroy(storage_);
            ops_ = nullptr;
        }
    }

    /* A non-closure type value is being received */
    Function& operator=(R(*fp)(Args...)) {
        reset();
        if (fp) {
            *reinterpret_cast<R(**)(Args...)>(storage_) = fp;
            ops_ = &get_func_ops();
        }
        return *this;
    }

    // construct from any Functor F
    template<typename F>
    Function(F f) {
        assign(khan::move(f));
    }

    template<typename F>
    Function& operator=(F f) {
        assign(khan::move(f));
        return *this;
    }

private:
    struct Ops {
        R    (*invoke)(void*, Args...);
        void (*destroy)(void*);
        void (*construct)(void*, const void*);
    };

    alignas(void*) unsigned char storage_[BufferSize];
    const Ops*           ops_;

    // function-local static for function-pointer Ops
    static const Ops& get_func_ops() {
        static const Ops instance = {
            // invoke through stored function pointer
            +[](void* buf, Args... a) -> R {
                R(*fp)(Args...) = *reinterpret_cast<R(**)(Args...)>(buf);
                return fp(khan::forward<Args>(a)...);
            },
            // destroy: no-op for plain function pointers
            +[](void*) {},
            // construct: copy the function pointer stored at fptr
            +[](void* buf, const void* fptr) {
                *reinterpret_cast<R(**)(Args...)>(buf) =
                    *reinterpret_cast<R(**)(Args...)>(fptr);
            }
        };
        return instance;
    }

    template<typename F>
    void assign(F&& f) {
        reset();
        static_assert(sizeof(F) <= BufferSize,
                      "Functor too large for Function buffer");
        new (storage_) F(khan::forward<F>(f));
        ops_ = &FunctorOps<F, R, Args...>::ops();
    }
};

extern template class Function<void(void), 32>;

} // namespace khan

#endif // KHAN_FUNCTION_HPP
