#ifndef BYTE_PACKER_HPP
#define BYTE_PACKER_HPP

#include <cstdint>
#include <type_traits>

namespace khan {

/// BytePacker<HB, LB> splits a 32-bit word into HB high bytes and LB low bytes,
/// and can recombine them.  HB+LB must be ≤4.
template <size_t HB, size_t LB>
struct BytePacker {
    static_assert(HB + LB <= 4, "BytePacker: HB+LB must be ≤4 bytes");

    // how many bits in each half
    static constexpr size_t HighBits = HB * 8;
    static constexpr size_t LowBits  = LB * 8;

    // masks for each half
    static constexpr uint32_t LowMask  = (LowBits == 32 ? 0xFFFF'FFFFu
                                                        : ((1u << LowBits) - 1));
    static constexpr uint32_t HighMask = (HighBits == 32 ? 0xFFFF'FFFFu
                                                         : ((1u << HighBits) - 1));

    /// Extract the top HB bytes (HighBits), shifted down to bit-0
    static constexpr uint32_t high(uint32_t w) noexcept {
        return (w >> LowBits) & HighMask;
    }

    /// Extract the bottom LB bytes (LowBits)
    static constexpr uint32_t low(uint32_t w) noexcept {
        return w & LowMask;
    }

    /// Recombine a high‐piece and low‐piece into a full 32-bit word
    static constexpr uint32_t combine(uint32_t hi, uint32_t lo) noexcept {
        return ((hi & HighMask) << LowBits) | (lo & LowMask);
    }
};

/*
  Example usage:
    // Alias for the 1-byte / 3-byte splitter you asked for:
    using Splitter1_3 = BytePacker<1,3>;
    
    constexpr uint32_t raw = 0xAB12'3456;

    // high() returns 0xAB
    constexpr auto h = Splitter1_3::high(raw);

    // low() returns 0x123456
    constexpr auto l = Splitter1_3::low(raw);

    // combine them back → 0xAB123456
    constexpr auto back = Splitter1_3::combine(h, l);
*/

} // namespace khan

#endif // BYTE_PACKER_HPP