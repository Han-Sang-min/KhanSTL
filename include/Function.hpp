#ifndef FUNCTION_HPP
#define FUNCTION_HPP

namespace khan {

//--- 1) Functor 전용 Ops를 분리한 템플릿 ---------------------------------
template<typename F, typename R, typename... Args>
struct FunctorOps {
    static const typename Function<R(Args...),0>::Ops ops;  // BufferSize는 무시
};

// 실제 정의: 한번만 생성된다
template<typename F, typename R, typename... Args>
const typename Function<R(Args...),0>::Ops
FunctorOps<F,R,Args...>::ops = {
    // invoke
    +[](void* buf, Args... a) -> R {
        return (*reinterpret_cast<F*>(buf))(a...);
    },
    // destroy
    +[](void* buf) {
        reinterpret_cast<F*>(buf)->~F();
    },
    // construct
    +[](void* buf, void* fptr) {
        new (buf) F(*reinterpret_cast<F*>(fptr));
    }
};

//--- 2) Function 정의 ---------------------------------------------------
template<typename Signature, unsigned BufferSize>
class Function;

template<typename R, typename... Args, unsigned BufferSize>
class Function<R(Args...), BufferSize> {
public:
    Function(): ops_(nullptr) {}
    ~Function(){ reset(); }

    R operator()(Args... a) const {
        if (!ops_) while(1);
        return ops_->invoke(storage_, a...);
    }
    explicit operator bool() const { return ops_; }

    void reset() {
        if (ops_) ops_->destroy(storage_);
        ops_ = nullptr;
    }

    // 함수포인터 대입
    Function& operator=(R(*fp)(Args...)) {
        reset();
        if (fp) {
            ops_ = &func_ops;
            func_ops.construct(storage_, &fp);
        }
        return *this;
    }

    // 임의의 F 대입
    template<typename F>
    Function(F f) { assign(f); }

    template<typename F>
    Function& operator=(F f) {
        assign(f);
        return *this;
    }

private:
    struct Ops {
        R (*invoke)(void*, Args...);
        void (*destroy)(void*);
        void (*construct)(void*, void*);
    };

    alignas(alignof(void*)) unsigned char storage_[BufferSize];
    const Ops* ops_;

    // assign에서는 FunctorOps<F,R,Args...>::ops만 참조
    template<typename F>
    void assign(F f) {
        reset();
        static_assert(sizeof(F) <= BufferSize, "Too large");

        new (storage_) F(f);
        ops_ = &FunctorOps<F,R,Args...>::ops;
    }

    static const Ops func_ops;
};

// 함수포인터용 v-table (원래대로)
template<typename R, typename... Args, unsigned BufferSize>
const typename Function<R(Args...),BufferSize>::Ops
Function<R(Args...),BufferSize>::func_ops = {
    +[](void* buf, Args... a)->R {
        R(*fp)(Args...)= *reinterpret_cast<R(**)(Args...)>(buf);
        return fp(a...);
    },
    +[](void*){},
    +[](void* buf, void* fptr){
        *reinterpret_cast<R(**)(Args...)>(buf)
          = *reinterpret_cast<R(**)(Args...)>(fptr);
    }
};

} // namespace khan
#endif // FUNCTION_HPP
