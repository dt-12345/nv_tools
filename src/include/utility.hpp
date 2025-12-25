#pragma once

#include <cstdint>
#include <climits>
#include <type_traits>

template <std::size_t OFFSET, std::size_t NBITS>
struct BitRange {
    static_assert(OFFSET + NBITS <= sizeof(std::uint64_t) * CHAR_BIT, "Range exceeds size of 64-bit integer");

    constexpr BitRange(std::uint64_t _raw) noexcept : raw(_raw) {}

    constexpr operator std::uint64_t() const {
        return value();
    }

    constexpr std::uint64_t value() const {
        return (raw >> OFFSET) & cMask;
    }

    static constexpr std::size_t cOffset = OFFSET;
    static constexpr std::size_t cNBits = NBITS;

private:
    static constexpr std::uint64_t cMask = (1ull << NBITS) - 1;

    std::uint64_t raw;
};

namespace detail {

template <typename>
struct IsBitRange : public std::false_type {};

template <std::size_t OFFSET, std::size_t NBITS>
struct IsBitRange<BitRange<OFFSET, NBITS>> : std::true_type {};

} // namespace detail

template <typename... RANGES>
struct Encoding {
    static_assert((detail::IsBitRange<RANGES>::value && ... && true), "Only for use with BitRange<OFFSET, NBITS>");

    constexpr Encoding(std::uint64_t _raw) noexcept : raw(_raw) {}

    constexpr operator std::uint64_t() const {
        return value();
    }

    constexpr std::uint64_t value() const {
        std::uint64_t value = 0ull;
        std::size_t offset = 0;
        // damn this is ugly but I kinda love that it works, still generates optimal code too
        ([&]<typename RANGE>(RANGE v){
            value |= v << offset;
            offset += RANGE::cNBits;
        }(RANGES(raw)), ...);
        return value;
    }

    static constexpr std::uint64_t Read(std::uint64_t value) {
        return Encoding(value);
    }

private:
    std::uint64_t raw;
};
static_assert(Encoding<BitRange<2, 5>, BitRange<8, 1>>(0x12345ull) == 0x31ull);