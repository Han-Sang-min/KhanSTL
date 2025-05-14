#ifndef KHAN_FUNCTION_HPP
#define KHAN_FUNCTION_HPP

#include <cstdint>
#include "meta/utility.hpp"

namespace khan {

// 1) A standalone Ops-holder for each signature
template<typename R, typename... Args>
struct FunctionOps {
  struct Ops {
    R    (*invoke)(void*, Args...);
    void (*destroy)(void*);
    void (*construct)(void*, const void*);
  };
};

// 2) FunctorOps fills in that Ops table
template<typename F, typename R, typename... Args>
struct FunctorOps : FunctionOps<R,Args...> {
  static const typename FunctionOps<R,Args...>::Ops& ops() {
    static const typename FunctionOps<R,Args...>::Ops instance = {
      // invoke
      +[](void* buf, Args... a) -> R {
        return (*reinterpret_cast<F*>(buf))(khan::forward<Args>(a)...);
      },
      // destroy
      +[](void* buf) {
        reinterpret_cast<F*>(buf)->~F();
      },
      // construct
      +[](void* buf, const void* fptr) {
        new (buf) F(*reinterpret_cast<const F*>(fptr));
      }
    };
    return instance;
  }
};

// 3) Function uses the *same* Ops type
template<typename Signature, uint32_t BufferSize>
class Function;

template<typename R, typename... Args, uint32_t BufferSize>
class Function<R(Args...),BufferSize> {
  using Ops = typename FunctionOps<R,Args...>::Ops;  // ← exactly the shared type

  alignas(void*) unsigned char storage_[BufferSize];
  const Ops*           ops_ = nullptr;

public:
  Function() = default;
  ~Function() { reset(); }

  // drop const so we can pass a mutable void*
  R operator()(Args... a) {
    return ops_->invoke(storage_, khan::forward<Args>(a)...);
  }

  explicit operator bool() const { return ops_ != nullptr; }

  void reset() {
    if (ops_) {
      ops_->destroy(storage_);
      ops_ = nullptr;
    }
  }

  // assign from any callable
  template<typename F>
  Function(F f) { assign(std::move(f)); }

  template<typename F>
  Function& operator=(F f) {
    assign(std::move(f));
    return *this;
  }

private:
  // Function-pointer specialization
  static const Ops& get_func_ops() {
    static const Ops instance = {
      +[](void* buf, Args... a) -> R {
        auto fp = *reinterpret_cast<R(**)(Args...)>(buf);
        return fp(khan::forward<Args>(a)...);
      },
      +[](void*) {},
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
        using T = std::decay_t<F>;
        static_assert(sizeof(T) <= BufferSize, "Functor too large for buffer");
        new (storage_) T(khan::forward<F>(f));
        ops_ = &FunctorOps<T, R, Args...>::ops();
    }
};

} // namespace khan

#endif // KHAN_FUNCTION_HPP
