#include <iostream>
#include <type_traits>
#include "meta/meta.hpp"
#include "Tuple.hpp"   // your custom tuple header

int main() {
    // 1) Construct a Tuple of three different types
    khan::Tuple<int, double, const char*> t1(42, 3.14, "hello");
    
    // 2) Access elements at runtime via get<I>()
    std::cout << "t1 elements:\n";
    std::cout << "  [0] = " << khan::get<0>(t1) << "\n";
    std::cout << "  [1] = " << khan::get<1>(t1) << "\n";
    std::cout << "  [2] = " << khan::get<2>(t1) << "\n\n";

    // 3) Modify elements (get returns an lvalue reference)
    khan::get<0>(t1) = 100;
    khan::get<2>(t1) = "world";
    std::cout << "t1 after modification:\n";
    std::cout << "  [0] = " << khan::get<0>(t1) << "\n";
    std::cout << "  [1] = " << khan::get<1>(t1) << "\n";
    std::cout << "  [2] = " << khan::get<2>(t1) << "\n\n";

    // 4) Test empty tuple compiles and default‐constructs
    khan::Tuple<> t0;
    (void)t0; // nothing to extract, just ensure it compiles

    // 5) Compile‐time tests using constexpr and static_assert
    constexpr khan::Tuple<int,int> tc(7,8);
    static_assert(khan::is_same<
        typename khan::TupleElement<0, decltype(tc)>::type,
        int
    >::value, "Element 0 must be int");
    static_assert(khan::is_same<
        typename khan::TupleElement<1, decltype(tc)>::type,
        int
    >::value, "Element 1 must be int");

    static_assert(khan::get<0>(tc) == 7, "tc[0] should be 7");
    static_assert(khan::get<1>(tc) == 8, "tc[1] should be 8");

    std::cout << "All static_asserts passed.\n";
    return 0;
}
