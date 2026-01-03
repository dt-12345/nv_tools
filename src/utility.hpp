#pragma once

#include <climits>
#include <cstdint>
#include <initializer_list>
#include <type_traits>

template <std::size_t SIZE>
std::int64_t SEXT(std::uint64_t value) {
    static_assert(SIZE < sizeof(std::uint64_t) * CHAR_BIT, "SIZE must fit within a 64-bit integer");
    constexpr std::size_t nbits = sizeof(std::uint64_t) * CHAR_BIT;
    return static_cast<std::int64_t>(value << (nbits - SIZE)) >> (nbits - SIZE);
}

template <std::size_t OFFSET, std::size_t NBITS, typename UnderlyingT = std::uint64_t>
struct BitRange {
    static_assert(std::is_integral_v<UnderlyingT>, "Underlying type must be an integer!");
    static_assert(OFFSET + NBITS <= sizeof(UnderlyingT) * CHAR_BIT, "Range exceeds size of 64-bit integer");

    constexpr operator UnderlyingT() const {
        return value();
    }

    constexpr UnderlyingT value() const {
        return (raw >> OFFSET) & cMask;
    }

    static constexpr std::size_t cOffset = OFFSET;
    static constexpr std::size_t cNBits = NBITS;
    static constexpr UnderlyingT cMask = (1ull << NBITS) - 1;

    UnderlyingT raw;
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

    static constexpr std::size_t cTotalSize = (RANGES::cNBits + ...);

    constexpr Encoding(std::uint64_t _raw) noexcept : raw(_raw) {}

    constexpr operator std::uint64_t() const {
        return value();
    }

    constexpr std::uint64_t value() const {
        std::uint64_t value = 0ull;
        std::size_t offset = 0;
        ([&]<typename RANGE>(RANGE v){
            value |= v << offset;
            offset += RANGE::cNBits;
        }(RANGES{raw}), ...);
        return value;
    }

    static constexpr std::uint64_t Read(std::uint64_t value) {
        return Encoding(value);
    }

private:
    std::uint64_t raw;
};
static_assert(Encoding<BitRange<2, 5>, BitRange<8, 1>>(0x12345ull) == 0x31ull);

#ifdef _MSC_VER
    #define UNREACHABLE_DEFAULT_CASE __assume(0);
#elif defined(__GNUC__)
    #define UNREACHABLE_DEFAULT_CASE __builtin_unreachable();
#else
    #error "Unsupported compiler"
#endif

template <typename EnumT, typename Storage = std::underlying_type_t<EnumT>>
class Flag {
    static_assert(std::is_enum_v<EnumT>, "EnumT must be an enumeration type!");
    static_assert(sizeof(Storage) >= sizeof(EnumT), "Storage type must be at least as large as the enum!");
public:
    constexpr Flag() = default;
    constexpr Flag(EnumT value) noexcept : storage(value) {}
    constexpr Flag(Storage value) noexcept : storage(value) {}
    constexpr Flag(std::initializer_list<EnumT> values) noexcept {
        for (const auto value : values) {
            storage |= static_cast<Storage>(value);
        }
    }

    constexpr explicit operator Storage() const { return storage; }

    constexpr Flag operator|(const EnumT& other) const {
        return storage | static_cast<Storage>(other);
    }

    constexpr Flag operator|=(const EnumT& other) {
        storage |= static_cast<Storage>(other);
        return *this;
    }

    constexpr Flag operator&(const EnumT& other) const {
        return storage & static_cast<Storage>(other);
    }

    constexpr Flag operator&=(const EnumT& other) {
        storage &= static_cast<Storage>(other);
        return *this;
    }

    constexpr Flag operator|(const Flag& other) const {
        return this->storage | other.storage;
    }

    constexpr Flag operator|=(const Flag& other) {
        this->storage |= other.storage;
        return *this;
    }

    constexpr Flag operator&(const Flag& other) const {
        return this->storage & other.storage;
    }

    constexpr Flag operator&=(const Flag& other) {
        this->storage &= other.storage;
        return *this;
    }

    constexpr operator bool() const { return storage != static_cast<Storage>(0); }

    constexpr bool IsOn(EnumT value) const {
        return *this & value;
    }

    constexpr bool IsOff(EnumT value) const {
        return !IsOn(value);
    }

private:
    Storage storage;
};