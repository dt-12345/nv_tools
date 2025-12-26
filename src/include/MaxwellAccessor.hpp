#pragma once

#include "Maxwell.hpp"

#include <bit>
#include <limits>

namespace Maxwell {

struct AccessorBase {
  std::uint64_t inst;
  std::uint64_t sched;
  std::uint64_t pc;

  constexpr AccessorBase(std::uint64_t _inst, std::uint64_t _sched, std::uint64_t _pc) noexcept : inst(_inst), sched(_sched), pc(_pc) {}

  using ProcessingFunc = std::uint64_t (*)(std::uint64_t, std::uint64_t);

  static constexpr std::uint64_t _Bool(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return value & 1ull;
  }

  static constexpr std::uint64_t _Reg(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return value & 0xffffull;
  }

  template <std::uint64_t XOR>
  static constexpr std::uint64_t _Xor(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return value ^ XOR;
  }

  template <std::uint64_t ROR, std::size_t SIZE>
  static constexpr std::uint64_t _Rotate(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    static_assert(ROR < SIZE, "Rotation must be less than the size of the field!");
    constexpr std::uint64_t mask = SIZE >= 0x40 ? 0xfffffffffffffff : (1ull << SIZE) - 1;
    return value >> (SIZE - ROR) | value << (ROR) & mask;
  }

  static constexpr std::uint64_t _Pcrel(std::uint64_t value, std::uint64_t programCounter) {
    return value - programCounter - RELATIVE_ADDRESS_BASE;
  }

  template <std::size_t SIZE>
  static constexpr std::uint64_t _Sext(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return static_cast<std::uint64_t>(SEXT<SIZE>(value));
  }

  template <std::uint64_t BIAS>
  static constexpr std::uint64_t _Bias(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return value - BIAS;
  }

  static constexpr std::uint64_t _Invert(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return static_cast<std::uint64_t>(value == 0ull);
  }

  static constexpr std::uint64_t _Negate(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return static_cast<std::uint64_t>(-static_cast<std::int64_t>(value));
  }

  template <std::uint64_t LOG>
  static constexpr std::uint64_t _Log2(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return 1ull << value;
  }

  template <std::uint64_t FACTOR>
  static constexpr std::uint64_t _Multiply(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    static_assert(FACTOR != 0, "Multiplicative factor must be non-zero");
    return value / FACTOR;
  }

  template <std::uint64_t FACTOR>
  static constexpr std::uint64_t _Scale(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    static_assert(FACTOR != 0, "Scale factor must be non-zero");
    constexpr std::uint64_t shift = sizeof(std::uint64_t) * CHAR_BIT - std::countl_zero(FACTOR) - 1;
    return value << shift;
  }

  template <std::size_t SIZE>
  static constexpr std::uint64_t _F16(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    if constexpr (SIZE < 0x10)
      value <<= 0x10 - SIZE;
    value &= 0xffffull;
    const std::uint64_t sign = value >> 0xf & 1ull;
    const std::uint64_t exp = value >> 10 & 0x1full;
    const std::uint64_t mantissa = value & 0x3ffull;
    std::uint32_t v;
    if (exp == 0x1full) {
      v = (mantissa == 0ull ? 0ull : (mantissa << 0xd | 0x400000ull)) | 0xffull << 0x17 | sign << 0x1f;
    } else if (exp == 0ull) {
      std::uint64_t newMantissa = (mantissa << 0xd) * 2;
      std::uint64_t newExp = 0x70;
      while ((newMantissa & 0x400000ull) == 0ull) {
        newMantissa *= 2; --newExp;
      }
      v = newMantissa & 0x7fffffull | newExp << 0x17 | sign << 0x1f;
    } else {
      v = mantissa << 0xd | exp + 0x70ull << 0x17 | sign << 0x1f;
    }
    return std::bit_cast<std::uint64_t, double>(static_cast<double>(std::bit_cast<float, std::uint32_t>(v)));
  }

  template <std::size_t SIZE>
  static constexpr std::uint64_t _F32(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    if constexpr (SIZE < 0x20)
      value <<= 0x20 - SIZE;
    const std::uint32_t v = static_cast<std::uint32_t>(value);
    return std::bit_cast<std::uint64_t, double>(static_cast<double>(std::bit_cast<float, std::uint32_t>(v)));
  }

  template <std::size_t SIZE>
  static constexpr std::uint64_t _F64(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    if ((value & 0x7ff0000000000000ull) == 0x7ff0000000000000ull && (value & 0xfffffffffffffull) != 0ull)
      value != 0x8000000000000ull;
    if constexpr (SIZE < 0x40)
      value <<= 0x40 - SIZE;
    return value;
  }

  static constexpr std::uint64_t _E6M9(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    const std::uint64_t sign = value >> 0xf & 1ull;
    const std::uint64_t exp = value >> 9 & 0x3full;
    const std::uint64_t mantissa = value & 0x1ffull;
    if (exp == 0x3full) {
      return mantissa << 0x2b | 0x7ff0000000000000ull | sign << 0x3f;
    } else if (exp == 0ull) {
      if (mantissa == 0) {
        return sign << 0x3f;
      }
      std::uint64_t newMantissa = (mantissa << 0x2b) * 2;
      std::uint64_t newExp = 0x3e0ull;
      while ((newMantissa >> 0x34 & 1ull) == 0ull) {
        newMantissa *= 2; --newExp;
      }
      return (newMantissa & 0xffefffffffffffffull) | newExp << 0x34 | sign << 0x3f;
    } else {
      return mantissa << 0x2b | (exp + 0x3e0ull) << 0x34 | sign << 0x3f;
    }
  }

  static constexpr std::uint64_t _BF16(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    const std::uint32_t v = static_cast<std::uint32_t>(value << 0x10);
    return std::bit_cast<std::uint64_t, double>(static_cast<double>(std::bit_cast<float, std::uint32_t>(v)));
  }

  static constexpr std::uint64_t _TF32(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    const std::uint32_t v = static_cast<std::uint32_t>(value);
    return std::bit_cast<std::uint64_t, double>(static_cast<double>(std::bit_cast<float, std::uint32_t>(v)));
  }

  template <typename Encoding, ProcessingFunc... FUNCS>
  constexpr std::uint64_t GetImpl(std::uint64_t source) const {
    std::uint64_t value = Encoding(source).value();
    ([&](ProcessingFunc func){
      value = func(value, pc); 
    }(FUNCS), ...);
    return value;
  }

};

template <OpClass CLASS> struct Accessor;

#define TABLE_FIELD(source, name, encoding, type, table, index, ...) \
  type name() const { \
    const std::uint64_t raw = AccessorBase::GetImpl<encoding __VA_OPT__(,) __VA_ARGS__>(source); \
    return static_cast<type>(static_cast<std::uint64_t>(std::get<index>(table(raw).value()))); \
  }
#define INST_TABLE_FIELD(name, encoding, type, table, index, ...) TABLE_FIELD(inst, name, encoding, type, table, index, __VA_ARGS__)
#define SCHED_TABLE_FIELD(name, encoding, type, table, index, ...) TABLE_FIELD(sched, name, encoding, type, table, index, __VA_ARGS__)

#define FIELD(source, name, encoding, type, ...) \
  type name() const { \
    return static_cast<type>(AccessorBase::GetImpl<encoding __VA_OPT__(,) __VA_ARGS__>(source)); \
  }
#define INST_FIELD(name, encoding, type, ...) FIELD(inst, name, encoding, type, __VA_ARGS__)
#define SCHED_FIELD(name, encoding, type, ...) FIELD(sched, name, encoding, type, __VA_ARGS__)

#define SIGNED_FIELD(source, name, encoding, type, ...) \
  type name() const { \
    std::uint64_t value = AccessorBase::GetImpl<encoding __VA_OPT__(,) __VA_ARGS__>(source); \
    if (static_cast<std::int64_t>(value) == std::numeric_limits<std::int64_t>::min()) \
      return static_cast<type>(0ull); \
    const bool is_signed = name ## _sign(); \
    if (value == 0ull) { \
      return static_cast<type>(static_cast<std::uint64_t>(is_signed) + 1); \
    } \
    return static_cast<type>(is_signed ? static_cast<std::uint64_t>(-static_cast<std::int64_t>(value)) : value); \
  }
#define SIGNED_INST_FIELD(name, encoding, type, ...) SIGNED_FIELD(inst, name, encoding, type, __VA_ARGS__)
#define SIGNED_SCHED_FIELD(name, encoding, type, ...) SIGNED_FIELD(sched, name, encoding, type, __VA_ARGS__)

#define FLOAT_FIELD(source, name, encoding, type, ...) \
  type name() const { \
    static_assert(sizeof(type) == 8, "Floating point type must be eight bytes"); \
    return std::bit_cast<type, std::uint64_t>(AccessorBase::GetImpl<encoding __VA_OPT__(,) __VA_ARGS__>(source)); \
  }
#define FLOAT_INST_FIELD(name, encoding, type, ...) FLOAT_FIELD(inst, name, encoding, type, __VA_ARGS__)
#define FLOAT_SCHED_FIELD(name, encoding, type, ...) FLOAT_FIELD(sched, name, encoding, type, __VA_ARGS__)

#define CONSTANT_FIELD(name, type, value) \
  type name() const { \
    return value; \
  }

template <OpClass CLASS> struct Accessor;

template <> struct Accessor<OpClass::NOP_DEFAULT> : public AccessorBase { using AccessorBase::AccessorBase; };

template <> struct Accessor<OpClass::FFMA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110011);
  INST_FIELD(fmz, FMZEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(rnd, RndEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rc_negate, nCEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FFMA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110011);
  INST_FIELD(fmz, FMZEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(rnd, RndEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_TABLE_FIELD(jneg, MultiEncoding<nABEncoding>, UnaryNeg, PSignFFMA, 1, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rc_negate, nCEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FFMA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010011);
  INST_FIELD(fmz, FMZEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(rnd, RndEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(srcConst_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rc_negate, nCEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_FFMA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100011);
  INST_FIELD(fmz, FMZEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(rnd, RndEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nCEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FFMA32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11);
  INST_FIELD(fmz, FMZHighEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_TABLE_FIELD(Rd, MultiEncoding<DestEncoding>, RegisterFAU, IDENTICAL<RegisterFAU>, 0, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nAB2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(fImm, Imm32Encoding, double)
  INST_TABLE_FIELD(Rc, MultiEncoding<DestEncoding>, RegisterFAU, IDENTICAL<RegisterFAU>, 1, Accessor::_Reg)
  INST_FIELD(Rc_negate, nC2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FFMA32I_2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11);
  INST_FIELD(fmz, FMZHighEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nAB2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(fImm, Imm32Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110001011);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110001011);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB2Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110001011);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FADD32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10);
  INST_FIELD(ftz, FTZ3Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nAB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(fImm, Imm32Encoding, double)
  INST_FIELD(jneg, nB3Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, nC2Encoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FCMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110111010);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FCMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110111010);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FCMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010111010);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_FCMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100111010);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FSWZADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011111);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(ndv, NDV2Encoding, NDV, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseCEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, PNWordEncoding, PNWord, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110001101);
  INST_FIELD(fmz, FMZLowEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(scale, ScaleLowEncoding, Scale, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110001101);
  INST_FIELD(fmz, FMZLowEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(scale, ScaleLowEncoding, Scale, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_TABLE_FIELD(jneg, MultiEncoding<nABEncoding>, UnaryNeg, PSignFFMA, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110001101);
  INST_FIELD(fmz, FMZLowEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(scale, ScaleLowEncoding, Scale, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(srcConst_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FMUL32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11110);
  INST_FIELD(fmz, FMZHighEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(fImm, Imm32Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110001100);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110001100);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB2Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110001100);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011000);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ3Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aB2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_FSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011000);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ3Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aB2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11000);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ3Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB3Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aB2Encoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_FSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11000);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ3Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB3Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aB2Encoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1001000);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ3Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB3Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aB2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_FSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1001000);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ3Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB3Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aB2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110111011);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB4Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aB2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_FSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110111011);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB4Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aB2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110111011);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB4Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aB2Encoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_FSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110111011);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB4Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aB2Encoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010111011);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB4Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aB2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_FSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010111011);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(ftz, FTZ2Encoding, FTZ, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB4Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aB2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IPA_1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11100000);
  INST_FIELD(ipaop, IPAOpEncoding, IPAOp, Accessor::_Reg)
  INST_FIELD(msi, MSIEncoding, MSI, Accessor::_Reg)
  INST_FIELD(sat, SatLowEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ps, PredSrcEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ps_not, PredSrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_IPA_1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11100000);
  INST_FIELD(ipaop, IPAOpEncoding, IPAOp, Accessor::_Reg)
  INST_FIELD(msi, MSIEncoding, MSI, Accessor::_Reg)
  INST_FIELD(sat, SatLowEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, IPAImm10Encoding, std::uint16_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ps, PredSrcEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ps_not, PredSrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IPA_2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11100000);
  INST_FIELD(ipaop, IPAOpEncoding, IPAOp, Accessor::_Reg)
  INST_FIELD(msi, MSIEncoding, MSI, Accessor::_Reg)
  INST_FIELD(sat, SatLowEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ps, PredSrcEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ps_not, PredSrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_IPA_2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11100000);
  INST_FIELD(ipaop, IPAOpEncoding, IPAOp, Accessor::_Reg)
  INST_FIELD(msi, MSIEncoding, MSI, Accessor::_Reg)
  INST_FIELD(sat, SatLowEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, IPAImm10Encoding, std::uint16_t)
  INST_FIELD(Ps, PredSrcEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ps_not, PredSrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::RRO> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010010);
  INST_FIELD(rroop, RROOpEncoding, RROOp, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_RRO> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010010);
  INST_FIELD(rroop, RROOpEncoding, RROOp, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_RRO> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010010);
  INST_FIELD(rroop, RROOpEncoding, RROOp, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::MUFU> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010000);
  INST_FIELD(mufu, MufuOpEncoding, MufuOp, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA1Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FCHK> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010001);
  INST_FIELD(mode, ChkModeFEncoding, ChkMode, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FCHK> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010001);
  INST_FIELD(mode, ChkModeFEncoding, ChkMode, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB2Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FCHK> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010001);
  INST_FIELD(mode, ChkModeFEncoding, ChkMode, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DFMA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110111);
  INST_FIELD(rnd, Rnd3Encoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc_negate, nCEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_DFMA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110111);
  INST_FIELD(rnd, Rnd3Encoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_TABLE_FIELD(jneg, MultiEncoding<nABEncoding>, UnaryNeg, PSignFFMA, 1, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc_negate, nCEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_DFMA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110111);
  INST_FIELD(rnd, Rnd3Encoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(srcConst_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc_negate, nCEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_DFMA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100110111);
  INST_FIELD(rnd, Rnd3Encoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nCEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110001110);
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_DADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110001110);
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB2Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_DADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110001110);
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010000);
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_DMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010000);
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_TABLE_FIELD(jneg, MultiEncoding<nABEncoding>, UnaryNeg, PSignFFMA, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_DMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010000);
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(srcConst_negate, MultiEncoding<nABEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110001010);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_DMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110001010);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB2Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_DMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110001010);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nABEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_negate, nB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110010);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_DSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110010);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aB2Encoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_DSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110010);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB3Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aB2Encoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_DSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110010);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB3Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aB2Encoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_DSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010010);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_negate, nB3Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aB2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_DSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010010);
  INST_FIELD(bval, BVal1Encoding, BVal, Accessor::_Reg)
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA3Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_negate, nB3Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aB2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110111000);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB4Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aB2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_DSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110111000);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB4Encoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aB2Encoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_DSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110111000);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB4Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aB2Encoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_DSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110111000);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nB4Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aB2Encoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_DSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010111000);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_negate, nB4Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aB2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_DSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010111000);
  INST_FIELD(fcomp, FCompEncoding, Test, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aA4Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_negate, nB4Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aB2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110100);
  INST_TABLE_FIELD(us32, MultiEncoding<ASigned3Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSigned3Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILO3Encoding, HILO, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<PSign3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(xmode, Xm3Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_IMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110100);
  INST_TABLE_FIELD(us32, MultiEncoding<ASigned3Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSigned3Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILO3Encoding, HILO, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<PSign3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(xmode, Xm3Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_TABLE_FIELD(jneg, MultiEncoding<PSign3Encoding>, UnaryNeg, PSignMAD, 2, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_IMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010100);
  INST_TABLE_FIELD(us32, MultiEncoding<ASigned3Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSigned3Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILO3Encoding, HILO, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<PSign3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(xmode, Xm3Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(srcConst_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_IMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100100);
  INST_TABLE_FIELD(us32, MultiEncoding<ASigned3Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSigned3Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILO3Encoding, HILO, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<PSign3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(xmode, Xm3Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_FIELD(Rb, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_TABLE_FIELD(srcConst_negate, MultiEncoding<PSign3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IMAD32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100);
  INST_TABLE_FIELD(us32, MultiEncoding<ASigned2Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSigned4Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILO2Encoding, HILO, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<PSign2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_TABLE_FIELD(Rd, MultiEncoding<DestEncoding>, Register, IDENTICAL<Register>, 0, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSign2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_FIELD(sImm, Imm32Encoding, std::int32_t)
  INST_TABLE_FIELD(Rc, MultiEncoding<DestEncoding>, Register, IDENTICAL<Register>, 1, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<PSign2Encoding>, bool, PSign, 2, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IMADSP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110101);
  INST_TABLE_FIELD(spa, MultiEncoding<SABCExtEncoding>, IntegerSPA, GetSPExtract, 1, Accessor::_Reg)
  INST_TABLE_FIELD(spb, MultiEncoding<SABCExtEncoding>, IntegerSPB, GetSPExtract, 2, Accessor::_Reg)
  INST_TABLE_FIELD(spc, MultiEncoding<SABCExtEncoding>, IntegerSPC, GetSPExtract, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_IMADSP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110101);
  INST_TABLE_FIELD(spa, MultiEncoding<SABCExtEncoding>, IntegerSPA, GetSPExtract, 1, Accessor::_Reg)
  INST_TABLE_FIELD(spb, MultiEncoding<SABCExtEncoding>, IntegerSPB, GetSPExtract, 2, Accessor::_Reg)
  INST_TABLE_FIELD(spc, MultiEncoding<SABCExtEncoding>, IntegerSPC, GetSPExtract, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_IMADSP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010101);
  INST_TABLE_FIELD(spa, MultiEncoding<SABCExtEncoding>, IntegerSPA, GetSPExtract, 1, Accessor::_Reg)
  INST_TABLE_FIELD(spb, MultiEncoding<SABCExtEncoding>, IntegerSPB, GetSPExtract, 2, Accessor::_Reg)
  INST_TABLE_FIELD(spc, MultiEncoding<SABCExtEncoding>, IntegerSPC, GetSPExtract, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_IMADSP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100101);
  INST_TABLE_FIELD(spa, MultiEncoding<SABCExtEncoding>, IntegerSPA, GetSPExtract, 1, Accessor::_Reg)
  INST_TABLE_FIELD(spb, MultiEncoding<SABCExtEncoding>, IntegerSPB, GetSPExtract, 2, Accessor::_Reg)
  INST_TABLE_FIELD(spc, MultiEncoding<SABCExtEncoding>, IntegerSPC, GetSPExtract, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, Register, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110000111);
  INST_TABLE_FIELD(us32, MultiEncoding<ASignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILOEncoding, HILO, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_IMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110000111);
  INST_TABLE_FIELD(us32, MultiEncoding<ASignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILOEncoding, HILO, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_IMUL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110000111);
  INST_TABLE_FIELD(us32, MultiEncoding<ASignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILOEncoding, HILO, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IMUL32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11111);
  INST_TABLE_FIELD(us32, MultiEncoding<ASigned2Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us32b, MultiEncoding<BSigned2Encoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(hib, HILO2Encoding, HILO, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(sImm, Imm32Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110000010);
  INST_TABLE_FIELD(po, MultiEncoding<PSignEncoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSignEncoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<PSignEncoding>, bool, PSign, 2, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_IADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110000010);
  INST_TABLE_FIELD(po, MultiEncoding<PSignEncoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSignEncoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_TABLE_FIELD(jneg, MultiEncoding<PSignEncoding>, UnaryNeg, PSign, 2, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_IADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110000010);
  INST_TABLE_FIELD(po, MultiEncoding<PSignEncoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSignEncoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(srcConst_negate, MultiEncoding<PSignEncoding>, bool, PSign, 2, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IADD3> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10111001100);
  INST_FIELD(dir, LRSEncoding, DIR, Accessor::_Reg)
  INST_FIELD(xmode, Xm9Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA7Encoding, bool, Accessor::_Bool)
  INST_FIELD(asel, ApartEncoding, Partsel, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nB7Encoding, bool, Accessor::_Bool)
  INST_FIELD(bsel, BpartEncoding, Partsel, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rc_negate, nC7Encoding, bool, Accessor::_Bool)
  INST_FIELD(csel, CpartEncoding, Partsel, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BImm_IADD3> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111001100);
  INST_FIELD(xmode, Xm9Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA7Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm20, BconstEncoding, std::uint32_t)
  INST_FIELD(jneg, nB7Encoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rc_negate, nC7Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BConst_IADD3> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10011001100);
  INST_FIELD(xmode, Xm9Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA7Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nB7Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rc_negate, nC7Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IADD32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110);
  INST_TABLE_FIELD(po, MultiEncoding<PSign2Encoding>, PO, PSign32, 0, Accessor::_Reg)
  INST_FIELD(sat, Sat2Encoding, SAT, Accessor::_Reg)
  INST_FIELD(xmode, Xm2Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSign2Encoding>, bool, PSign32, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm32Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ISCADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110000011);
  INST_TABLE_FIELD(po, MultiEncoding<PSignEncoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSignEncoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<PSignEncoding>, bool, PSign, 2, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(shift, Imm5IEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_ISCADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110000011);
  INST_TABLE_FIELD(po, MultiEncoding<PSignEncoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSignEncoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_TABLE_FIELD(jneg, MultiEncoding<PSignEncoding>, UnaryNeg, PSign, 2, Accessor::_Reg)
  INST_FIELD(shift, Imm5IEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_ISCADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110000011);
  INST_TABLE_FIELD(po, MultiEncoding<PSignEncoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<PSignEncoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(srcConst_negate, MultiEncoding<PSignEncoding>, bool, PSign, 2, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(shift, Imm5IEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ISCADD32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm32Encoding, std::int32_t)
  INST_FIELD(shift, Imm5IbEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110000100);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XModeEncoding, XMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_IMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110000100);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XModeEncoding, XMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_IMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110000100);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XModeEncoding, XMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BFE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110000000);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(brev, BrevEncoding, BREV, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_BFE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110000000);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(brev, BrevEncoding, BREV, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_BFE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110000000);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(brev, BrevEncoding, BREV, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BFI> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101101111110);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_BFI> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111110);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_BFI> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100101111110);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_BFI> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101001111110);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110000101);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(wmode, MEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(xmode, XModeEncoding, XXHI, Accessor::_Reg)
  INST_FIELD(brev, BrevEncoding, BREV, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_SHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110000101);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(wmode, MEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(xmode, XModeEncoding, XXHI, Accessor::_Reg)
  INST_FIELD(brev, BrevEncoding, BREV, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_SHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110000101);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(wmode, MEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(xmode, XModeEncoding, XXHI, Accessor::_Reg)
  INST_FIELD(brev, BrevEncoding, BREV, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110001001);
  INST_FIELD(wmode, MEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_SHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110001001);
  INST_FIELD(wmode, MEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_SHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110001001);
  INST_FIELD(wmode, MEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SHF_L_imm> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111111);
  INST_FIELD(wmode, M_HEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(maxshift, MaxShiftEncoding, maxShift, Accessor::_Reg)
  INST_FIELD(xmode, XmdSHFEncoding, SHFXMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm06_shfEncoding, std::uint32_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SHF_R_imm> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110011111);
  INST_FIELD(wmode, M_HEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(maxshift, MaxShiftEncoding, maxShift, Accessor::_Reg)
  INST_FIELD(xmode, XmdSHFEncoding, SHFXMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm06_shfEncoding, std::uint32_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SHF_L_reg> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101101111111);
  INST_FIELD(wmode, M_HEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(maxshift, MaxShiftEncoding, maxShift, Accessor::_Reg)
  INST_FIELD(xmode, XmdSHFEncoding, SHFXMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SHF_R_reg> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110011111);
  INST_FIELD(wmode, M_HEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(maxshift, MaxShiftEncoding, maxShift, Accessor::_Reg)
  INST_FIELD(xmode, XmdSHFEncoding, SHFXMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LOP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110001000);
  INST_FIELD(lop, LOPEncoding, LOP, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(pop, POPEncoding, POP, Accessor::_Reg)
  INST_FIELD(Pd, PredDstLopEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_invert, nA_LEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_invert, nB_LEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_LOP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110001000);
  INST_FIELD(lop, LOPEncoding, LOP, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(pop, POPEncoding, POP, Accessor::_Reg)
  INST_FIELD(Pd, PredDstLopEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_invert, nA_LEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jinv, nB_LEncoding, UnaryInv, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_LOP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110001000);
  INST_FIELD(lop, LOPEncoding, LOP, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(pop, POPEncoding, POP, Accessor::_Reg)
  INST_FIELD(Pd, PredDstLopEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_invert, nA_LEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_invert, nB_LEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LOP32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1);
  INST_FIELD(lop, LOP_IEncoding, LOP, Accessor::_Reg)
  INST_FIELD(xmode, Xm_IEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCIEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_invert, nA_L2Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm32Encoding, std::uint32_t)
  INST_FIELD(jinv, nB_L2Encoding, UnaryInv, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LOP3_LUT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101101111100);
  INST_FIELD(xmode, Xm5Encoding, X, Accessor::_Reg)
  INST_FIELD(pop, POP2Encoding, POP, Accessor::_Reg)
  INST_FIELD(Pd, PredDstLopEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Imm8, LOPImmEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LOP3_LUT_BImm> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111);
  INST_FIELD(xmode, Xm6Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Imm8, LOPImm2Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LOP3_LUT_BConst> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1);
  INST_FIELD(xmode, Xm10Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Imm8, LOPImm2Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LOP3> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101101111100);
  INST_TABLE_FIELD(lop, MultiEncoding<LOPImmEncoding>, LOP, LutImm8, 0, Accessor::_Reg)
  INST_FIELD(xmode, Xm5Encoding, X, Accessor::_Reg)
  INST_FIELD(pop, POP2Encoding, POP, Accessor::_Reg)
  INST_FIELD(Pd, PredDstLopEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_invert, MultiEncoding<LOPImmEncoding>, bool, LutImm8, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_invert, MultiEncoding<LOPImmEncoding>, bool, LutImm8, 2, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_invert, MultiEncoding<LOPImmEncoding>, bool, LutImm8, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LOP3_BImm> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111);
  INST_TABLE_FIELD(lop, MultiEncoding<LOPImm2Encoding>, LOP, LutImm8, 0, Accessor::_Reg)
  INST_FIELD(xmode, Xm6Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_invert, MultiEncoding<LOPImm2Encoding>, bool, LutImm8, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_TABLE_FIELD(jinv, MultiEncoding<LOPImm2Encoding>, UnaryInv, LutImm8, 2, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_invert, MultiEncoding<LOPImm2Encoding>, bool, LutImm8, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LOP3_Bconst> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1);
  INST_TABLE_FIELD(lop, MultiEncoding<LOPImm2Encoding>, LOP, LutImm8, 0, Accessor::_Reg)
  INST_FIELD(xmode, Xm10Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_invert, MultiEncoding<LOPImm2Encoding>, bool, LutImm8, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(srcConst_invert, MultiEncoding<LOPImm2Encoding>, bool, LutImm8, 2, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_invert, MultiEncoding<LOPImm2Encoding>, bool, LutImm8, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::FLO> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110000110);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(sh, SHEncoding, SH, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_invert, nB_LEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_FLO> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110000110);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(sh, SHEncoding, SH, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jinv, nB_LEncoding, UnaryInv, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_FLO> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110000110);
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(sh, SHEncoding, SH, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_invert, nB_LEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ISET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_ISET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_ISET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_ISET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_ISET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_ISET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ISET_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_ISET_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_ISET_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_ISET_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_ISET_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_ISET_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110101);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ISETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110110);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_ISETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110110);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_ISETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110110);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_ISETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110110);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_ISETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110110);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_ISETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110110);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ISETP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110110);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_ISETP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110110);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_ISETP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110110);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_ISETP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110110);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_ISETP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110110);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_ISETP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110110);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(xmode, XmEncoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ICMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110100);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_ICMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110100);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_ICMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110100);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_ICMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100110100);
  INST_FIELD(icomp, ICompEncoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ICMP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110110100);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_ICMP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110110100);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_ICMP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010110100);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_ICMP_U> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100110100);
  INST_FIELD(icomp, ICompEncoding, ICmpU, Accessor::_Reg)
  INST_TABLE_FIELD(us32, MultiEncoding<SignedEncoding>, Integer32, IsSigned, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::POPC> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110000001);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_invert, nB_LEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_POPC> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110000001);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jinv, nB_LEncoding, UnaryInv, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_POPC> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110000001);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(srcConst_invert, nB_LEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::XMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101101100);
  INST_TABLE_FIELD(us16, MultiEncoding<ASigned5Encoding>, Integer16, IsSigned16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us16b, MultiEncoding<BSigned5Encoding>, Integer16, IsSigned16, 0, Accessor::_Reg)
  INST_FIELD(psl, PSLEncoding, PSL, Accessor::_Reg)
  INST_FIELD(cop, XMADCopEncoding, XMADcop, Accessor::_Reg)
  INST_FIELD(mrg, MRGEncoding, MRG, Accessor::_Reg)
  INST_FIELD(xmode, Xm7Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(asel, HILO2Encoding, H1H0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(bsel, HILO4Encoding, H1H0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ImmB_XMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101100);
  INST_TABLE_FIELD(us16, MultiEncoding<ASigned5Encoding>, Integer16, IsSigned16, 0, Accessor::_Reg)
  CONSTANT_FIELD(us16b, U16, U16::U16)
  INST_FIELD(psl, PSLEncoding, PSL, Accessor::_Reg)
  INST_FIELD(cop, XMADCopEncoding, XMADcop, Accessor::_Reg)
  INST_FIELD(mrg, MRGEncoding, MRG, Accessor::_Reg)
  INST_FIELD(xmode, Xm7Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(asel, HILO2Encoding, H1H0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImmB_XMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101100);
  INST_TABLE_FIELD(us16, MultiEncoding<ASigned5Encoding>, Integer16, IsSigned16, 0, Accessor::_Reg)
  INST_FIELD(psl, PSLEncoding, PSL, Accessor::_Reg)
  INST_FIELD(cop, XMADCopEncoding, XMADcop, Accessor::_Reg)
  INST_FIELD(mrg, MRGEncoding, MRG, Accessor::_Reg)
  INST_FIELD(xmode, Xm7Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(asel, HILO2Encoding, H1H0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ConstB_XMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100111);
  INST_TABLE_FIELD(us16, MultiEncoding<ASigned5Encoding>, Integer16, IsSigned16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us16b, MultiEncoding<BSigned5Encoding>, Integer16, IsSigned16, 0, Accessor::_Reg)
  INST_FIELD(psl, PSL2Encoding, PSL, Accessor::_Reg)
  INST_FIELD(cop, XMADCop2Encoding, XMADcop2, Accessor::_Reg)
  INST_FIELD(mrg, MRG2Encoding, MRG, Accessor::_Reg)
  INST_FIELD(xmode, Xm8Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(asel, HILO2Encoding, H1H0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(bsel, HILO5Encoding, H1H0, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ConstC_XMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100010);
  INST_TABLE_FIELD(us16, MultiEncoding<ASigned5Encoding>, Integer16, IsSigned16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(us16b, MultiEncoding<BSigned5Encoding>, Integer16, IsSigned16, 0, Accessor::_Reg)
  INST_FIELD(cop, XMADCop2Encoding, XMADcop2, Accessor::_Reg)
  INST_FIELD(xmode, Xm8Encoding, X, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(asel, HILO2Encoding, H1H0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, Register, Accessor::_Reg)
  INST_FIELD(bsel, HILO5Encoding, H1H0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_TABLE_FIELD(sImm_sign, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(uImm, Imm16Encoding, std::int32_t)
  INST_TABLE_FIELD(uImm_sign, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_TABLE_FIELD(sImm_sign, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  SIGNED_INST_FIELD(uImm, Imm16Encoding, std::int32_t)
  INST_TABLE_FIELD(uImm_sign, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VMAD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1011111);
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode3Encoding>, PO, PSignMAD, 0, Accessor::_Reg)
  INST_FIELD(vscale, VScaleEncoding, VMadScale, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 1, Accessor::_Bool)
  SIGNED_INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_TABLE_FIELD(sImm_sign, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rc_negate, MultiEncoding<AVGMode3Encoding>, bool, PSignMAD, 3, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(uImm, Imm16Encoding, std::int32_t)
  INST_TABLE_FIELD(uImm_sign, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_TABLE_FIELD(sImm_sign, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(uImm, Imm16Encoding, std::int32_t)
  INST_TABLE_FIELD(uImm_sign, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_TABLE_FIELD(sImm_sign, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(uImm, Imm16Encoding, std::int32_t)
  INST_TABLE_FIELD(uImm_sign, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VADD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1000);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_TABLE_FIELD(po, MultiEncoding<AVGMode2Encoding>, PO, PSign, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<AVGMode2Encoding>, bool, PSign, 1, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  SIGNED_INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_TABLE_FIELD(sImm_sign, MultiEncoding<AVGMode2Encoding>, bool, PSign, 2, Accessor::_Bool)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VABSDIFF> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010100);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VMNMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(mnmx, MN2Encoding, MN, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100000);
  INST_FIELD(icomp, VComp2Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VSETP_bop> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011110);
  INST_FIELD(icomp, VComp3Encoding, ICmpAll, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger16, IntegerSigned, 0, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U16, VFormatU16, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, H1H0, VFormatU16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U16, VFormatU16, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, H1H0, VFormatU16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U16, VFormatU16, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, H1H0, VFormatU16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U8, VFormatU8, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, B1B0, VFormatU8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U8, VFormatU8, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, B1B0, VFormatU8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U8, VFormatU8, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, B1B0, VFormatU8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U32, VFormatU32, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U32, VFormatU32, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U32, VFormatU32, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, UInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, SInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, UInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, SInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, UInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VSHL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010111);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, SInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U16, VFormatU16, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, H1H0, VFormatU16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U16, VFormatU16, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, H1H0, VFormatU16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U16, VFormatU16, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, H1H0, VFormatU16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b8_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U8, VFormatU8, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, B1B0, VFormatU8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b8_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U8, VFormatU8, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, B1B0, VFormatU8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b8_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U8, VFormatU8, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(bsel, MultiEncoding<bSelectUEncoding>, B1B0, VFormatU8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b32_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U32, VFormatU32, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_b32_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U32, VFormatU32, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_b32_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<bSelectUEncoding>, U32, VFormatU32, 0, Accessor::_Reg)
  INST_FIELD(wrap, MVEncoding, CWMode, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, UInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer16, VFormat16, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, SInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, H1H0, VFormat16, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_Imm_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, UInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a8_SImm_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, Integer8, VFormat8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, SInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(asel, MultiEncoding<aSelectEncoding>, B1B0, VFormat8, 1, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_Imm_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, UInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::a32_SImm_VSHR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1010110);
  INST_FIELD(dfmt, DFormat2Encoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<aSelectEncoding>, VInteger32, VFormat32, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<MVEncoding>, SInteger16, SM5vshlCW, 1, Accessor::_Reg)
  INST_TABLE_FIELD(wrap, MultiEncoding<MVEncoding>, CWMode, SM5vshlCW, 0, Accessor::_Reg)
  INST_FIELD(sat, SatHighEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vop, VOPEncoding, VOP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, Imm16Encoding, std::int16_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VABSDIFF4> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100000);
  INST_FIELD(dfmt, DFormatEncoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<safmtEncoding>, Integer8, Integer8Signed, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, Integer8, Integer8Signed, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vred, VRedEncoding, VRed2, Accessor::_Reg)
  INST_FIELD(laneMsk, LaneMask4Encoding, LaneMask4, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(asel, asel4Encoding, ASel4, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(bsel, bsel4Encoding, BSel4, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_VABSDIFF4> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100000);
  INST_FIELD(dfmt, DFormatEncoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<safmtEncoding>, Integer8, Integer8Signed, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, UInteger8, Integer8Signed, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vred, VRedEncoding, VRed2, Accessor::_Reg)
  INST_FIELD(laneMsk, LaneMask4Encoding, LaneMask4, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(asel, asel4Encoding, ASel4, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, RegBEncoding, std::uint8_t)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SImm_VABSDIFF4> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100000);
  INST_FIELD(dfmt, DFormatEncoding, DFormat, Accessor::_Reg)
  INST_TABLE_FIELD(safmt, MultiEncoding<safmtEncoding>, Integer8, Integer8Signed, 0, Accessor::_Reg)
  INST_TABLE_FIELD(sbfmt, MultiEncoding<sbfmtEncoding>, SInteger8, Integer8Signed, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(vred, VRedEncoding, VRed2, Accessor::_Reg)
  INST_FIELD(laneMsk, LaneMask4Encoding, LaneMask4, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(asel, asel4Encoding, ASel4, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(sImm, RegBEncoding, std::int8_t)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2F_1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2F_2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2F_2_64_32> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64_32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2F_1_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1_16, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2F_2_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2F_2_64_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64_16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2F_1_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1_64, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2F_2_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2F_1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2F_2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2F_2_64_32> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64_32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2F_1_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1_16, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2F_2_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2F_2_64_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64_16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2F_1_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1_64, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2F_2_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2F_1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2F_2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2F_2_64_32> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64_32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2F_1_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1_16, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2F_2_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2F_2_64_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64_16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2F_1_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts1_64, Accessor::_Reg)
  INST_FIELD(rnd, IRRndEncoding, F2FRound1, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2F_2_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010101);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(fmts, SrcDstFmtEncoding, F2Ffmts2_64, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, F2FRound2, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerInv8No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2I_I64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, Integer64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2I_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo8, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::F2I_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo8, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float64, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerInv8No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2I_I64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, Integer64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2I_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo8, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_F2I_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo8, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float64, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BconstEncoding, double)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerInv8No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2I_I64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, Integer64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float32, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2I_16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo8, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float16, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_F2I_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010110);
  INST_FIELD(ftz, FTZEncoding, FTZ, Accessor::_Reg)
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo8, IntSize, 0, Accessor::_Reg)
  INST_FIELD(srcfmt, SrcFmtEncoding, Float64, Accessor::_Reg)
  INST_FIELD(rnd, Rnd_1Encoding, Round3, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, SHEncoding, H1H0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I2F> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, FloatNo64, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, IntegerNo16No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I2F_F64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float64, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, IntegerNo16No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I2F64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, Integer64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I2F16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, Integer16, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, ByEncoding, I2XH, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_I2F> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, FloatNo64, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, IntegerNo16No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_I2F_F64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float64, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, IntegerNo16No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_I2F64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, Integer64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_I2F16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, Integer16, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, ByEncoding, I2XH, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_I2F> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, FloatNo64, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, IntegerNo16No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_I2F_F64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float64, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, IntegerNo16No64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_I2F64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, Integer64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_I2F16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010111);
  INST_FIELD(dstfmt, DstFmtEncoding, Float, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<ISrcFmtEncoding>, Integer16, IntSize, 0, Accessor::_Reg)
  INST_FIELD(rnd, RndLowEncoding, Round1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, ByEncoding, I2XH, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I2I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110011100);
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo64, IntSize, 0, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<SrcFmt2Encoding>, IntegerNo16Inv64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I2I16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110011100);
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo64, IntSize, 0, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<SrcFmt2Encoding>, Integer16, IntSize, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBEncoding, bool, Accessor::_Bool)
  INST_FIELD(halfsel, ByEncoding, I2XH, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_I2I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110011100);
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo64, IntSize, 0, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<SrcFmt2Encoding>, IntegerNo16Inv64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_I2I16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110011100);
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo64, IntSize, 0, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<SrcFmt2Encoding>, Integer16, IntSize, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(jneg, nBEncoding, UnaryNeg, Accessor::_Reg)
  INST_FIELD(jabs, aBEncoding, UnaryAbs, Accessor::_Reg)
  INST_FIELD(halfsel, ByEncoding, I2XH, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_I2I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110011100);
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo64, IntSize, 0, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<SrcFmt2Encoding>, IntegerNo16Inv64, IntSize, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(bytesel, ByEncoding, B1B0, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_I2I16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110011100);
  INST_TABLE_FIELD(dstfmt, MultiEncoding<IDstFmtEncoding>, IntegerNo64, IntSize, 0, Accessor::_Reg)
  INST_TABLE_FIELD(srcfmt, MultiEncoding<SrcFmt2Encoding>, Integer16, IntSize, 0, Accessor::_Reg)
  INST_FIELD(sat, SatEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBEncoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(halfsel, ByEncoding, I2XH, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::MOV> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010011);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(quadMask, QuadMaskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_MOV> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010011);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(quadMask, QuadMaskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_MOV> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010011);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(quadMask, QuadMaskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::MOV32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10000);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(uImm, Imm32Encoding, std::uint32_t)
  INST_FIELD(quadMask, QuadMask2Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SEL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110010100);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_SEL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110010100);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_SEL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110010100);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PRMT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110111100);
  INST_FIELD(prmt, PModeEncoding, PMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_PRMT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110111100);
  INST_FIELD(prmt, PModeEncoding, PMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_PRMT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10010111100);
  INST_FIELD(prmt, PModeEncoding, PMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const1_PRMT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100111100);
  INST_FIELD(prmt, PModeEncoding, PMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, RegisterFAU, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SHFL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111100010);
  INST_FIELD(shflmd, ShflmdEncoding, Shflmd, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::b_SHFL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111100010);
  INST_FIELD(shflmd, ShflmdEncoding, Shflmd, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm5, shfl_imm5Encoding, std::uint8_t)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::c_b_SHFL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111100010);
  INST_FIELD(shflmd, ShflmdEncoding, Shflmd, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm5, shfl_imm5Encoding, std::uint8_t)
  INST_FIELD(uImm13, Imm13Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::c_SHFL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111100010);
  INST_FIELD(shflmd, ShflmdEncoding, Shflmd, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm13, Imm13Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::P2R> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110011101);
  INST_FIELD(extract, ByteEncoding, B3B0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pr, CCPREncoding, CCPR, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_P2R> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110011101);
  INST_FIELD(extract, ByteEncoding, B3B0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pr, CCPREncoding, CCPR, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_P2R> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110011101);
  INST_FIELD(extract, ByteEncoding, B3B0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pr, CCPREncoding, CCPR, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Simple_P2R> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110011101);
  INST_FIELD(extract, ByteEncoding, B3B0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pr, CCPREncoding, CCPR, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::R2P> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110011110);
  INST_FIELD(Pr, CCPREncoding, CCPR, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(extract, ByteEncoding, B3B0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_R2P> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110011110);
  INST_FIELD(Pr, CCPREncoding, CCPR, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(extract, ByteEncoding, B3B0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_R2P> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100110011110);
  INST_FIELD(Pr, CCPREncoding, CCPR, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(extract, ByteEncoding, B3B0, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010011);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(CCTest, CCC_2Encoding, Test, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_CSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010011);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(CCTest, CCC_2Encoding, Test, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010100);
  INST_FIELD(CCTest, CCC_2Encoding, Test, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_CSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010100);
  INST_FIELD(CCTest, CCC_2Encoding, Test, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010001);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(bop0, Bop0Encoding, Bop, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Pc, Src2PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pc_not, Src2NotEncoding, bool, Accessor::_Bool)
  INST_FIELD(Pb, Src1PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pb_not, Src1NotEncoding, bool, Accessor::_Bool)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_PSET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010001);
  INST_FIELD(bval, BValEncoding, BVal, Accessor::_Reg)
  INST_FIELD(bop0, Bop0Encoding, Bop, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Pc, Src2PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pc_not, Src2NotEncoding, bool, Accessor::_Bool)
  INST_FIELD(Pb, Src1PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pb_not, Src1NotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010010);
  INST_FIELD(bop0, Bop0Encoding, Bop, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pc, Src2PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pc_not, Src2NotEncoding, bool, Accessor::_Bool)
  INST_FIELD(Pb, Src1PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pb_not, Src1NotEncoding, bool, Accessor::_Bool)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_PSETP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010010);
  INST_FIELD(bop0, Bop0Encoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pc, Src2PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pc_not, Src2NotEncoding, bool, Accessor::_Bool)
  INST_FIELD(Pb, Src1PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pb_not, Src1NotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::STP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111010100);
  INST_FIELD(stpmode, STPModeEncoding, STPMode, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(uImm, Imm8Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TEX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11000);
  INST_FIELD(lod, LODEncoding, LOD, Accessor::_Reg)
  INST_FIELD(lc, LCEncoding, LC, Accessor::_Reg)
  INST_FIELD(toff, AOFFIEncoding, TOFF1, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TEX_legacy_style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11000);
  INST_FIELD(lod, LODEncoding, LOD, Accessor::_Reg)
  INST_FIELD(lc, LCEncoding, LC, Accessor::_Reg)
  INST_FIELD(toff, AOFFIEncoding, TOFF1, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBTEXEncoding, std::uint8_t)
  INST_FIELD(smp, TidBSAMPEncoding, std::uint8_t)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TEX_B> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111010);
  INST_FIELD(lod, LODBEncoding, LOD, Accessor::_Reg)
  INST_FIELD(lc, LCBEncoding, LC, Accessor::_Reg)
  INST_FIELD(toff, AOFFIBEncoding, TOFF1, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TEX_B_legacy_style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111010);
  INST_FIELD(lod, LODBEncoding, LOD, Accessor::_Reg)
  INST_FIELD(lc, LCBEncoding, LC, Accessor::_Reg)
  INST_FIELD(toff, AOFFIBEncoding, TOFF1, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TEXS_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101100);
  INST_TABLE_FIELD(lod, MultiEncoding<tex2d_4Encoding>, LOD2, Tex2D4, 2, Accessor::_Reg)
  INST_TABLE_FIELD(dc, MultiEncoding<tex2d_4Encoding>, DC, Tex2D4, 1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_TABLE_FIELD(paramA, MultiEncoding<tex2d_4Encoding>, ParamA, Tex2D4, 0, Accessor::_Reg)
  INST_FIELD(wmsk, Wmsk3Encoding, TEXWmsk2C, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TEXS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101100);
  INST_TABLE_FIELD(lod, MultiEncoding<tex2d_4Encoding>, LOD2, Tex2D4, 2, Accessor::_Reg)
  INST_TABLE_FIELD(dc, MultiEncoding<tex2d_4Encoding>, DC, Tex2D4, 1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_TABLE_FIELD(paramA, MultiEncoding<tex2d_4Encoding>, ParamA, Tex2D4, 0, Accessor::_Reg)
  INST_FIELD(wmsk, Wmsk3Encoding, TEXWmsk34C, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TEXS_F16_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101000);
  INST_TABLE_FIELD(lod, MultiEncoding<tex2d_4Encoding>, LOD2, Tex2D4, 2, Accessor::_Reg)
  INST_TABLE_FIELD(dc, MultiEncoding<tex2d_4Encoding>, DC, Tex2D4, 1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_TABLE_FIELD(paramA, MultiEncoding<tex2d_4Encoding>, ParamA, Tex2D4, 0, Accessor::_Reg)
  INST_FIELD(wmsk, Wmsk3Encoding, TEXWmsk2C, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TEXS_F16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101000);
  INST_TABLE_FIELD(lod, MultiEncoding<tex2d_4Encoding>, LOD2, Tex2D4, 2, Accessor::_Reg)
  INST_TABLE_FIELD(dc, MultiEncoding<tex2d_4Encoding>, DC, Tex2D4, 1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_TABLE_FIELD(paramA, MultiEncoding<tex2d_4Encoding>, ParamA, Tex2D4, 0, Accessor::_Reg)
  INST_FIELD(wmsk, Wmsk3Encoding, TEXWmsk34C, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLDS_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101101);
  INST_TABLE_FIELD(lod, MultiEncoding<tex2d_4Encoding>, LOD1, Tld2D4, 2, Accessor::_Reg)
  INST_TABLE_FIELD(toff, MultiEncoding<tex2d_4Encoding>, TOFF1, Tld2D4, 3, Accessor::_Reg)
  INST_TABLE_FIELD(ms, MultiEncoding<tex2d_4Encoding>, MS, Tld2D4, 1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_TABLE_FIELD(paramA, MultiEncoding<tex2d_4Encoding>, ParamA, Tld2D4, 0, Accessor::_Reg)
  INST_FIELD(wmsk, Wmsk3Encoding, TEXWmsk2C, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLDS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101101);
  INST_TABLE_FIELD(lod, MultiEncoding<tex2d_4Encoding>, LOD1, Tld2D4, 2, Accessor::_Reg)
  INST_TABLE_FIELD(toff, MultiEncoding<tex2d_4Encoding>, TOFF1, Tld2D4, 3, Accessor::_Reg)
  INST_TABLE_FIELD(ms, MultiEncoding<tex2d_4Encoding>, MS, Tld2D4, 1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_TABLE_FIELD(paramA, MultiEncoding<tex2d_4Encoding>, ParamA, Tld2D4, 0, Accessor::_Reg)
  INST_FIELD(wmsk, Wmsk3Encoding, TEXWmsk34C, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLDS_F16_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101001);
  INST_TABLE_FIELD(lod, MultiEncoding<tex2d_4Encoding>, LOD1, Tld2D4, 2, Accessor::_Reg)
  INST_TABLE_FIELD(toff, MultiEncoding<tex2d_4Encoding>, TOFF1, Tld2D4, 3, Accessor::_Reg)
  INST_TABLE_FIELD(ms, MultiEncoding<tex2d_4Encoding>, MS, Tld2D4, 1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_TABLE_FIELD(paramA, MultiEncoding<tex2d_4Encoding>, ParamA, Tld2D4, 0, Accessor::_Reg)
  INST_FIELD(wmsk, Wmsk3Encoding, TEXWmsk2C, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLDS_F16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101001);
  INST_TABLE_FIELD(lod, MultiEncoding<tex2d_4Encoding>, LOD1, Tld2D4, 2, Accessor::_Reg)
  INST_TABLE_FIELD(toff, MultiEncoding<tex2d_4Encoding>, TOFF1, Tld2D4, 3, Accessor::_Reg)
  INST_TABLE_FIELD(ms, MultiEncoding<tex2d_4Encoding>, MS, Tld2D4, 1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_TABLE_FIELD(paramA, MultiEncoding<tex2d_4Encoding>, ParamA, Tld2D4, 0, Accessor::_Reg)
  INST_FIELD(wmsk, Wmsk3Encoding, TEXWmsk34C, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLD4S> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111100);
  INST_FIELD(tcomp, TexComp2Encoding, TexComp, Accessor::_Reg)
  INST_FIELD(toff, AOFFI2Encoding, TOFF1, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, Register, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLD4S_F16> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111110);
  INST_FIELD(tcomp, TexComp2Encoding, TexComp, Accessor::_Reg)
  INST_FIELD(toff, AOFFI2Encoding, TOFF1, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd2, Dest2Encoding, Register, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11011100);
  INST_FIELD(lod, LOD1Encoding, LOD1, Accessor::_Reg)
  INST_FIELD(toff, TOFF1Encoding, TOFF1, Accessor::_Reg)
  INST_FIELD(ms, MSEncoding, MS, Accessor::_Reg)
  INST_FIELD(clamp, CLEncoding, CL, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLD_B> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11011101);
  INST_FIELD(lod, LOD1Encoding, LOD1, Accessor::_Reg)
  INST_FIELD(toff, TOFF1Encoding, TOFF1, Accessor::_Reg)
  INST_FIELD(ms, MSEncoding, MS, Accessor::_Reg)
  INST_FIELD(clamp, CLEncoding, CL, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLD4> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11001);
  INST_FIELD(tcomp, TexCompEncoding, TexComp, Accessor::_Reg)
  INST_FIELD(toff, TOFF2Encoding, TOFF2, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLD4_B> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111011);
  INST_FIELD(tcomp, TexCompBEncoding, TexComp, Accessor::_Reg)
  INST_FIELD(toff, TOFF2BEncoding, TOFF2, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLD4_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11001);
  INST_FIELD(tcomp, TexCompEncoding, TexComp, Accessor::_Reg)
  INST_FIELD(toff, TOFF2Encoding, TOFF2, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBTEXEncoding, std::uint8_t)
  INST_FIELD(smp, TidBSAMPEncoding, std::uint8_t)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TLD4_B_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111011);
  INST_FIELD(tcomp, TexCompBEncoding, TexComp, Accessor::_Reg)
  INST_FIELD(toff, TOFF2BEncoding, TOFF2, Accessor::_Reg)
  INST_FIELD(dc, DCEncoding, DC, Accessor::_Reg)
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TMML> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101011);
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(Rb, Register, ZeroRegister::RZ)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TMML_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101011);
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(Rb, Register, ZeroRegister::RZ)
  INST_FIELD(tid, TidBTEXEncoding, std::uint8_t)
  INST_FIELD(smp, TidBSAMPEncoding, std::uint8_t)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TMML_B> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101100);
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TMML_B_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101100);
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111000);
  INST_FIELD(lc, LCDEncoding, LC, Accessor::_Reg)
  INST_FIELD(toff, TOFF1Encoding, TOFF1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXD_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111000);
  INST_FIELD(lc, LCDEncoding, LC, Accessor::_Reg)
  INST_FIELD(toff, TOFF1Encoding, TOFF1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBTEXEncoding, std::uint8_t)
  INST_FIELD(smp, TidBSAMPEncoding, std::uint8_t)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXD_B> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111001);
  INST_FIELD(lc, LCDEncoding, LC, Accessor::_Reg)
  INST_FIELD(toff, TOFF1Encoding, TOFF1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXD_B_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111001);
  INST_FIELD(lc, LCDEncoding, LC, Accessor::_Reg)
  INST_FIELD(toff, TOFF1Encoding, TOFF1, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Pd, PredDstEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(paramA, ParamAEncoding, ParamA, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXQ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101001);
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(query, MultiEncoding<TexQueryEncoding>, TXQMode, TXQModeDim, 0, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXQ_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101001);
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(query, MultiEncoding<TexQueryEncoding>, TXQMode, TXQModeDim, 0, Accessor::_Reg)
  INST_FIELD(tid, TidBTEXEncoding, std::uint8_t)
  INST_FIELD(smp, TidBSAMPEncoding, std::uint8_t)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXQ_Imm> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101001);
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(query, MultiEncoding<TexQueryEncoding>, std::uint8_t, TXQModeDim, 0)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXQ_Imm_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101001);
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(query, MultiEncoding<TexQueryEncoding>, std::uint8_t, TXQModeDim, 0)
  INST_FIELD(tid, TidBTEXEncoding, std::uint8_t)
  INST_FIELD(smp, TidBSAMPEncoding, std::uint8_t)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXQ_B> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101010);
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(query, MultiEncoding<TexQueryEncoding>, TXQMode, TXQModeDim, 0, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXQ_B_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101010);
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(query, MultiEncoding<TexQueryEncoding>, TXQMode, TXQModeDim, 0, Accessor::_Reg)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXQ_B_Imm> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101010);
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(query, MultiEncoding<TexQueryEncoding>, std::uint8_t, TXQModeDim, 0)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXQ_B_Imm_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101010);
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_TABLE_FIELD(query, MultiEncoding<TexQueryEncoding>, std::uint8_t, TXQModeDim, 0)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101000);
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::TXA_Legacy_Style> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111101000);
  INST_FIELD(ndv, NDVEncoding, NDV, Accessor::_Reg)
  INST_FIELD(ndp, NODEPEncoding, NODEP, Accessor::_Reg)
  SCHED_FIELD(phase, OETexPhaseEncoding, TPhase, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(tid, TidBTEXEncoding, std::uint8_t)
  INST_FIELD(smp, TidBSAMPEncoding, std::uint8_t)
  INST_FIELD(wmsk, WmskEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DEPBAR_LE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000011110);
  INST_FIELD(sbidx, SBIDEncoding, Scoreboard, Accessor::_Reg)
  INST_FIELD(cnt, PendCntEncoding, std::uint8_t)
  INST_FIELD(dep_scbd, Imm6Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DEPBAR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000011110);
  INST_FIELD(dep_scbd, Imm6Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::DEPBAR_ALL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000011110);
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::AL2P> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110100);
  INST_FIELD(io, AIOEncoding, AIO, Accessor::_Reg)
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Pd, DstPred1Encoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm11Encoding, std::int16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_AL2P> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110100);
  INST_FIELD(io, AIOEncoding, AIO, Accessor::_Reg)
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Pd, DstPred1Encoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(Ra, ZeroRegister, ZeroRegister::RZ)
  INST_FIELD(uImm, Imm10Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ALD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111011);
  INST_FIELD(io, AIOEncoding, AIO, Accessor::_Reg)
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm10Encoding, std::uint16_t)
  INST_FIELD(Rb, RegBALDEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ALD_PATCH> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111011);
  INST_FIELD(io, AIOEncoding, AIO, Accessor::_Reg)
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm10Encoding, std::uint16_t)
  INST_FIELD(Rb, RegBALDEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ALD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111011);
  INST_FIELD(io, AIOEncoding, AIO, Accessor::_Reg)
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm11Encoding, std::int16_t)
  INST_FIELD(Rb, RegBALDEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ALD_PHYS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111011);
  INST_FIELD(io, AIOEncoding, AIO, Accessor::_Reg)
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rb, RegBALDEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_AST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111110);
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm10Encoding, std::uint16_t)
  INST_FIELD(Rb, RegBASTEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_AST_PATCH> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111110);
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm10Encoding, std::uint16_t)
  INST_FIELD(Rb, RegBASTEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::AST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111110);
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm11Encoding, std::int16_t)
  INST_FIELD(Rb, RegBASTEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::AST_PHYS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111110);
  INST_FIELD(size, ALSizeEncoding, AInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rb, RegBASTEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::OUT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111101111100);
  INST_FIELD(out, OutTypeEncoding, OutType, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_OUT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111101111100);
  INST_FIELD(out, OutTypeEncoding, OutType, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, BconstEncoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_OUT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101111100);
  INST_FIELD(out, OutTypeEncoding, OutType, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PIXLD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111101);
  INST_FIELD(pixmode, PixModeEncoding, PixMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pd, DstPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm8Encoding, std::int8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_PIXLD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111101);
  INST_FIELD(pixmode, PixModeEncoding, PixMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pd, DstPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm8Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PIXLD_simple> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111101);
  INST_FIELD(pixmode, PixModeEncoding, PixMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pd, DstPredEncoding, Predicate, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LDC> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110010);
  INST_FIELD(size, LSSize2Encoding, CInteger_n64_n128, Accessor::_Reg)
  INST_FIELD(ad, AdModeEncoding, AdMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegisterFAU, Accessor::_Reg)
  using sImmEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(sImm, sImmEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_LDC> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110010);
  INST_FIELD(size, LSSize2Encoding, CInteger_n64_n128, Accessor::_Reg)
  INST_FIELD(ad, AdModeEncoding, AdMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LDC_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110010);
  INST_FIELD(ad, AdModeEncoding, AdMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegisterFAU, Accessor::_Reg)
  using sImmEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(sImm, sImmEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_LDC_64> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110010);
  INST_FIELD(ad, AdModeEncoding, AdMode, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cop, COPEncoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSizeEncoding, LDInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm32Encoding, std::int32_t)
  INST_FIELD(Ps, PredSrcldstEncoding, Predicate, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_LD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cop, COPEncoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSizeEncoding, LDInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm32Encoding, std::uint32_t)
  INST_FIELD(Ps, PredSrcldstEncoding, Predicate, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LDG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111011010);
  INST_FIELD(e, E2Encoding, E, Accessor::_Reg)
  INST_FIELD(cop, COP4Encoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, LDInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_LDG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111011010);
  INST_FIELD(e, E2Encoding, E, Accessor::_Reg)
  INST_FIELD(cop, COP4Encoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, LDInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm24Encoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LDG_SPARSE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111011001);
  INST_FIELD(e, E2Encoding, E, Accessor::_Reg)
  INST_FIELD(cop, COP4Encoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, LDInteger, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest4Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm20Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_LDG_SPARSE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111011001);
  INST_FIELD(e, E2Encoding, E, Accessor::_Reg)
  INST_FIELD(cop, COP4Encoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, LDInteger, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest4Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm20Encoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LDL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111101000);
  INST_FIELD(cop, COP2Encoding, LLoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, CInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_LDL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111101000);
  INST_FIELD(cop, COP2Encoding, LLoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, CInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm24Encoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LDS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111101001);
  INST_FIELD(size, LDSSizeEncoding, LDSInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_LDS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111101001);
  INST_FIELD(size, LDSSizeEncoding, LDSInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm24Encoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LEA_LO_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101101111010);
  INST_FIELD(xmode, Xm4Encoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm5, ImmU5Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LEA_LO_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1101111010);
  INST_FIELD(xmode, Xm4Encoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm20, BconstEncoding, std::int32_t)
  INST_FIELD(uImm5, ImmU5Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LEA_LO_CONST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b100101111010);
  INST_FIELD(xmode, Xm4Encoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA4Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(uImm5, ImmU5Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LEA_HI_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101101111011);
  INST_FIELD(xmode, Xm5Encoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA5Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm5, ImmU5_2Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LEA_HI_CONST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b110);
  INST_FIELD(xmode, Xm6Encoding, X, Accessor::_Reg)
  INST_FIELD(Pd, PredDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(writeCC, WriteCCEncoding, optCC, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA6Encoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(uImm5, ImmU5_3Encoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cop, COPEncoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSizeEncoding, CInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm32Encoding, std::int32_t)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Plg, PredSrcldstEncoding, Predicate, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cop, COPEncoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSizeEncoding, CInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm32Encoding, std::uint32_t)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Plg, PredSrcldstEncoding, Predicate, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::STG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111011011);
  INST_FIELD(e, E2Encoding, E, Accessor::_Reg)
  INST_FIELD(cop, COP4Encoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, CInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_STG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111011011);
  INST_FIELD(e, E2Encoding, E, Accessor::_Reg)
  INST_FIELD(cop, COP4Encoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, CInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm24Encoding, std::uint32_t)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::STL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111101010);
  INST_FIELD(cop, COP2Encoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, CInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_STL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111101010);
  INST_FIELD(cop, COP2Encoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(size, LSSize2Encoding, CInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm24Encoding, std::uint32_t)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::STS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111101011);
  INST_FIELD(size, LSSize2Encoding, CInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_STS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111101011);
  INST_FIELD(size, LSSize2Encoding, CInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm24Encoding, std::uint32_t)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101101);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(atom, AtomOpEncoding, AtomOp, Accessor::_Reg)
  INST_FIELD(size, AtomSizeEncoding, SQInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm20aEncoding, std::int32_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(Rc, Register, ZeroRegister::RZ)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101101);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(atom, AtomOpEncoding, AtomOp, Accessor::_Reg)
  INST_FIELD(size, AtomSizeEncoding, SQInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm20aEncoding, std::uint32_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(Rc, Register, ZeroRegister::RZ)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOM_CAS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011101111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_TABLE_FIELD(size, MultiEncoding<Size1RegBCEncoding>, CASInteger, ConsecutiveReg8, 2, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm20aEncoding, std::int32_t)
  INST_TABLE_FIELD(Rb, MultiEncoding<Size1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(Rc, MultiEncoding<Size1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOM_CAS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011101111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_TABLE_FIELD(size, MultiEncoding<Size1RegBCEncoding>, CASInteger, ConsecutiveReg8, 2, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm20aEncoding, std::uint32_t)
  INST_TABLE_FIELD(Rb, MultiEncoding<Size1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(Rc, MultiEncoding<Size1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOM_CAS_Rb_and_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011101111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(size, AtomSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm20aEncoding, std::int32_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOM_CAS_Rb_and_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011101111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(size, AtomSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm20aEncoding, std::uint32_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOM_CAS_RZ_and_Rc> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011101111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(size, AtomSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm20aEncoding, std::int32_t)
  INST_FIELD(Rc, RegBEncoding, NonZeroRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOM_CAS_RZ_and_Rc> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011101111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(size, AtomSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm20aEncoding, std::uint32_t)
  INST_FIELD(Rc, RegBEncoding, NonZeroRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOM_SPARSE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011100110);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(atom, AtomOp2Encoding, AtomOp, Accessor::_Reg)
  INST_FIELD(size, AtomSizeEncoding, SQInteger, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest4Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(Rc, Register, ZeroRegister::RZ)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOM_CAS_SPARSE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011100111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_TABLE_FIELD(size, MultiEncoding<Size1RegBCEncoding>, CASInteger, ConsecutiveReg8, 2, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest4Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_TABLE_FIELD(Rb, MultiEncoding<Size1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(Rc, MultiEncoding<Size1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOM_CAS_RZ_and_Rc_SPARSE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011100111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(size, AtomSize1Encoding, CASInteger, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest4Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rc, RegBEncoding, NonZeroRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOM_CAS_Rb_and_RZ_SPARSE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111011100111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(size, AtomSize1Encoding, CASInteger, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest4Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOMS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101100);
  INST_FIELD(atom, AtomOpEncoding, AtomsOp, Accessor::_Reg)
  INST_FIELD(size, AtomsSizeEncoding, AtomsSz, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm22atomsEncoding, std::int32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(Rc, Register, ZeroRegister::RZ)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOMS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101100);
  INST_FIELD(atom, AtomOpEncoding, AtomsOp, Accessor::_Reg)
  INST_FIELD(size, AtomsSizeEncoding, AtomsSz, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm22atomsEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(Rc, Register, ZeroRegister::RZ)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOMS_CAS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101110010);
  INST_TABLE_FIELD(size, MultiEncoding<asSize1RegBCEncoding>, CASInteger, ConsecutiveReg8, 2, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm22atomsEncoding, std::int32_t, Accessor::_Scale<4ull>)
  INST_TABLE_FIELD(Rb, MultiEncoding<asSize1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(Rc, MultiEncoding<asSize1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOMS_CAS> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101110010);
  INST_TABLE_FIELD(size, MultiEncoding<asSize1RegBCEncoding>, CASInteger, ConsecutiveReg8, 2, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm22atomsEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  INST_TABLE_FIELD(Rb, MultiEncoding<asSize1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(Rc, MultiEncoding<asSize1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOMS_CAS_Rb_and_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101110010);
  INST_FIELD(size, AtomsSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm22atomsEncoding, std::int32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOMS_CAS_Rb_and_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101110010);
  INST_FIELD(size, AtomsSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm22atomsEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOMS_CAS_RZ_and_Rc> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101110010);
  INST_FIELD(size, AtomsSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm22atomsEncoding, std::int32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rc, RegBEncoding, NonZeroRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOMS_CAS_RZ_and_Rc> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101110010);
  INST_FIELD(size, AtomsSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm22atomsEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rc, RegBEncoding, NonZeroRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOMS_CAST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111000);
  INST_FIELD(spin, atomscSPINEncoding, AtomsSPIN, Accessor::_Reg)
  INST_TABLE_FIELD(size, MultiEncoding<asSize1RegBCEncoding>, CASInteger, ConsecutiveReg8, 2, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm22atomsEncoding, std::int32_t, Accessor::_Scale<4ull>)
  INST_TABLE_FIELD(Rb, MultiEncoding<asSize1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(Rc, MultiEncoding<asSize1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOMS_CAST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111000);
  INST_FIELD(spin, atomscSPINEncoding, AtomsSPIN, Accessor::_Reg)
  INST_TABLE_FIELD(size, MultiEncoding<asSize1RegBCEncoding>, CASInteger, ConsecutiveReg8, 2, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm22atomsEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  INST_TABLE_FIELD(Rb, MultiEncoding<asSize1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 0, Accessor::_Reg)
  INST_TABLE_FIELD(Rc, MultiEncoding<asSize1RegBCEncoding>, NonZeroRegister, ConsecutiveReg8, 1, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOMS_CAST_Rb_and_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111000);
  INST_FIELD(spin, atomscSPINEncoding, AtomsSPIN, Accessor::_Reg)
  INST_FIELD(size, AtomsSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm22atomsEncoding, std::int32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOMS_CAST_Rb_and_RZ> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111000);
  INST_FIELD(spin, atomscSPINEncoding, AtomsSPIN, Accessor::_Reg)
  INST_FIELD(size, AtomsSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm22atomsEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ATOMS_CAST_RZ_and_Rc> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111000);
  INST_FIELD(spin, atomscSPINEncoding, AtomsSPIN, Accessor::_Reg)
  INST_FIELD(size, AtomsSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm22atomsEncoding, std::int32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rc, RegBEncoding, NonZeroRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_ATOMS_CAST_RZ_and_Rc> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111000);
  INST_FIELD(spin, atomscSPINEncoding, AtomsSPIN, Accessor::_Reg)
  INST_FIELD(size, AtomsSize1Encoding, CASInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm22atomsEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  INST_FIELD(Rc, RegBEncoding, NonZeroRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::RED> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101111111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(redop, RedOpEncoding, RedOp, Accessor::_Reg)
  INST_FIELD(size, RedSizeEncoding, SQInteger, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm20aEncoding, std::int32_t)
  INST_FIELD(Rb, RegBASTEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_RED> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101111111);
  INST_FIELD(e, AtomEEncoding, E, Accessor::_Reg)
  INST_FIELD(redop, RedOpEncoding, RedOp, Accessor::_Reg)
  INST_FIELD(size, RedSizeEncoding, SQInteger, Accessor::_Reg)
  CONSTANT_FIELD(Ra, ZeroRegister, ZeroRegister::RZ)
  INST_FIELD(uImm, Imm20aEncoding, std::uint32_t)
  INST_FIELD(Rb, RegBASTEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101111011);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cache, Cache3Encoding, Cache3, Accessor::_Reg)
  INST_FIELD(cctlop, CCTLOpEncoding, CCTLOp, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm30aEncoding, std::int32_t, Accessor::_Scale<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_CCTL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101111011);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cache, Cache3Encoding, Cache3, Accessor::_Reg)
  INST_FIELD(cctlop, CCTLOpEncoding, CCTLOp, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm30aEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTL_IVALL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101111011);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cache, Cache3Encoding, Cache3NoCI, Accessor::_Reg)
  INST_FIELD(ivall, CCTLOpEncoding, OnlyIvall, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTL_CI_IVALL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101111011);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cache, Cache3Encoding, Cache3CI, Accessor::_Reg)
  INST_FIELD(ivall, CCTLOpEncoding, OnlyIvall, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTL_QRY> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101111011);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cache, Cache3Encoding, Cache3, Accessor::_Reg)
  INST_FIELD(op, CCTLOpEncoding, OnlyQry, Accessor::_Reg)
  CONSTANT_FIELD(Rd, Register, ZeroRegister::RZ)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm30aEncoding, std::int32_t, Accessor::_Scale<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_CCTL_QRY> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101111011);
  INST_FIELD(e, EEncoding, E, Accessor::_Reg)
  INST_FIELD(cache, Cache3Encoding, Cache3, Accessor::_Reg)
  INST_FIELD(op, CCTLOpEncoding, OnlyQry, Accessor::_Reg)
  CONSTANT_FIELD(Rd, Register, ZeroRegister::RZ)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm30aEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTLL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110000);
  INST_FIELD(cache, CacheEncoding, LCache, Accessor::_Reg)
  INST_FIELD(cctllop, CCTLOpEncoding, CCTLOp, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, NonZeroRegister, Accessor::_Reg)
  INST_FIELD(sImm, Imm22aEncoding, std::int32_t, Accessor::_Scale<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::I_CCTLL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110000);
  INST_FIELD(cache, CacheEncoding, LCache, Accessor::_Reg)
  INST_FIELD(cctllop, CCTLOpEncoding, CCTLOp, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, ZeroRegister, Accessor::_Reg)
  INST_FIELD(uImm, Imm22aEncoding, std::uint32_t, Accessor::_Scale<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTLL_IVALL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110000);
  INST_FIELD(cctllop, CCTLOpEncoding, CCTLLOp2, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTLL_CRS_WBALL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110000);
  INST_FIELD(cache, CacheEncoding, CRSOnly, Accessor::_Reg)
  INST_FIELD(cctllop, CCTLOpEncoding, CCTLLOp3, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTLT_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101111101);
  INST_FIELD(cctltop, CCTLTOpEncoding, CCTLTOp, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTLT_IDX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101111110);
  INST_FIELD(cctltop, CCTLTOpEncoding, CCTLTOp, Accessor::_Reg)
  INST_FIELD(uImm, TsIdx13Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CCTLT_IVALL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101111110);
  INST_FIELD(cctltop, CCTLTOpEncoding, CCTLTOpIVALL, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::MEMBAR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111110011);
  INST_FIELD(lvl, MembarLEncoding, MemBarLevel, Accessor::_Reg)
  INST_FIELD(ivall, IvallEncoding, MemBarIvall, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SULD_D_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101100010);
  INST_FIELD(ba, BAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(cop, COP5Encoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, SUSizeEncoding, LDInteger_nU128, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest2Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SULD_D_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101100011);
  INST_FIELD(ba, BAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(cop, COP5Encoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(size, SUSizeEncoding, LDInteger_nU128, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest2Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SULD_P_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101100000);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(cop, COP5Encoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(rgba, SURGBAEncoding, RGBA, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest2Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SULD_P_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101100001);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(cop, COP5Encoding, LoadCacheOp, Accessor::_Reg)
  INST_FIELD(rgba, SURGBAEncoding, RGBA, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest2Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUST_D_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101100110);
  INST_FIELD(ba, BAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(cop, COP5Encoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(size, SUSizeEncoding, LDInteger_nU128, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUST_D_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101100111);
  INST_FIELD(ba, BAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(cop, COP5Encoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(size, SUSizeEncoding, LDInteger_nU128, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUST_P_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101100100);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(cop, COP5Encoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(rgba, SURGBAEncoding, RGBA, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUST_P_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101100101);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(cop, COP5Encoding, StoreCacheOp, Accessor::_Reg)
  INST_FIELD(rgba, SURGBAEncoding, RGBA, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SURED_D_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101101010);
  INST_FIELD(ba, BAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(redop, SURedOpEncoding, RedOp, Accessor::_Reg)
  INST_FIELD(size, SUSizeEncoding, AtomicInteger, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SURED_D_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101101011);
  INST_FIELD(ba, BAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(redop, SURedOpEncoding, RedOp, Accessor::_Reg)
  INST_FIELD(size, SUSizeEncoding, AtomicInteger, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SURED_P_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101101000);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(redop, SURedOpEncoding, RedOp, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SURED_P_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101101001);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(redop, SURedOpEncoding, RedOp, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_D_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101001110);
  INST_FIELD(ba, satmBAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(suatomop, satmOpEncoding, AtomsOp, Accessor::_Reg)
  INST_FIELD(size, satmSize2Encoding, AtomicInteger, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_D_REG_SPARSE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101110);
  INST_FIELD(ba, satmBAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(suatomop, satmOpEncoding, AtomsOp, Accessor::_Reg)
  INST_FIELD(size, satmSize2Encoding, AtomicInteger, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest3Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_D_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101000);
  INST_FIELD(ba, satmBAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(suatomop, satmOpEncoding, AtomsOp, Accessor::_Reg)
  INST_FIELD(size, satmSize1Encoding, AtomicInteger, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_P_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101001100);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(suatomop, satmOpEncoding, AtomsOp, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_P_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101001101);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(suatomop, satmOpEncoding, AtomsOp, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_D_CAS_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101011010);
  INST_FIELD(ba, satmBAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(size, satmSize2Encoding, AtomicInteger, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest2Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_D_CAS_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101010);
  INST_FIELD(ba, satmBAEncoding, BA, Accessor::_Reg)
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(size, satmSize1Encoding, AtomicInteger, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_TABLE_FIELD(Pd, MultiEncoding<PredDest2Encoding>, Predicate, DestPred, 0, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_P_CAS_REG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101011000);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(suatomop, satmOpEncoding, CAS, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rc, RegCEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SUATOM_P_CAS_IMM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110101011001);
  INST_FIELD(dim, SUDimEncoding, Dim1, Accessor::_Reg)
  INST_FIELD(suatomop, satmOpEncoding, CAS, Accessor::_Reg)
  INST_FIELD(clamp, Clamp4Encoding, Clamp1, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(suid, TidBEncoding, std::uint16_t, Accessor::_Scale<4ull>, Accessor::_Multiply<4ull>)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BRA> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100100);
  INST_FIELD(uniform, UEncoding, U, Accessor::_Reg)
  INST_FIELD(lmt, LMTEncoding, LMT, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BRA_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100100);
  INST_FIELD(uniform, UEncoding, U, Accessor::_Reg)
  INST_FIELD(lmt, LMTEncoding, LMT, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BRX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100101);
  INST_FIELD(lmt, LMTEncoding, LMT, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BRX_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100101);
  INST_FIELD(lmt, LMTEncoding, LMT, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  using sImmEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(sImm, sImmEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::JMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100001);
  INST_FIELD(uniform, UEncoding, U, Accessor::_Reg)
  INST_FIELD(lmt, LMTEncoding, LMT, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  INST_FIELD(sImm, Imm32Encoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::JMP_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100001);
  INST_FIELD(uniform, UEncoding, U, Accessor::_Reg)
  INST_FIELD(lmt, LMTEncoding, LMT, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::JMX> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100000);
  INST_FIELD(lmt, LMTEncoding, LMT, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(sImm, Imm32Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::JMX_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100000);
  INST_FIELD(lmt, LMTEncoding, LMT, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  using sImmEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(sImm, sImmEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CAL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100110);
  INST_FIELD(inc, INCEncoding, INC, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CAL_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100110);
  INST_FIELD(inc, INCEncoding, INC, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PRET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100111);
  INST_FIELD(inc, INCEncoding, INC, Accessor::_Reg)
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PRET_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100111);
  INST_FIELD(inc, INCEncoding, INC, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::JCAL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100010);
  INST_FIELD(inc, INCEncoding, INC, Accessor::_Reg)
  INST_FIELD(sImm, Imm32Encoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::JCAL_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100010);
  INST_FIELD(inc, INCEncoding, INC, Accessor::_Reg)
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SSY> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101001);
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SSY_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101001);
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PLONGJMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101000);
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PLONGJMP_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101000);
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PBK> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101010);
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PBK_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101010);
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PCNT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101011);
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PCNT_c> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101011);
  using constBankEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress0<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<CBankEncoding,Imm16Encoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress0<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::RET> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000110010);
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LONGJMP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000110001);
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::KIL> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000110011);
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BRK> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000110100);
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CONT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000110101);
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::EXIT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000110000);
  INST_FIELD(krc, KeepRefCntEncoding, KeepRefCount, Accessor::_Reg)
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::PEXIT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000100011);
  INST_FIELD(sImm, Imm24Encoding, std::int32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SAM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000110111);
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::RAM> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000111000);
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BPT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000111010);
  INST_FIELD(bpt, BptEncoding, BPTMode, Accessor::_Reg)
  INST_FIELD(sImm, Imm20Encoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::RTT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000110110);
  INST_FIELD(rttop, RTTOpEncoding, RTTOp, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IDE_EN> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000111001);
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::IDE_DI> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000111001);
  CONSTANT_FIELD(di, IDEActionDIOnly, IDEActionDIOnly::DI)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SYNC> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000011111);
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(CCTest, CCC_1Encoding, Test, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NOP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010110);
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(fcomp, CCC_2Encoding, Test, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NOP_trig> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000010110);
  CONSTANT_FIELD(TestCC, CC, CC::CC)
  INST_FIELD(fcomp, CCC_2Encoding, Test, Accessor::_Reg)
  INST_FIELD(uImm, Imm16Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::S2R> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000011001);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(SR, SRegEncoding, SpecialRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::CS2R> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011001);
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(SR, SRegEncoding, SpecialRegister, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::B2R_BAR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010111);
  INST_FIELD(barmd, BarmdEncoding, BarmdBAR, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::B2R_RESULT> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010111);
  INST_FIELD(barmd, BarmdEncoding, BarmdRESULT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pd, DstPredEncoding, Predicate, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::B2R_WARP> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010111);
  INST_FIELD(barmd, BarmdEncoding, BarmdWARP, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::R2B> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000011000);
  INST_FIELD(barmd, BarmdEncoding, Barmd, Accessor::_Reg)
  INST_FIELD(uImm, BarNameEncoding, std::uint8_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::LEPC> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011010);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Sync> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSync, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Sync_b> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSync, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, Imm12Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Sync_a_b> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSync, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  INST_FIELD(uImm, Imm12Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Sync_a> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSync, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Arv> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarArv, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Arv_a> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarArv, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Arv_imm> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarArv, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, Imm12Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Arv_imm_a> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarArv, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  INST_FIELD(uImm, Imm12Encoding, std::uint16_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Red> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarRED, Accessor::_Reg)
  INST_FIELD(redmode, BarRedOpEncoding, Red, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Red_b> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarRED, Accessor::_Reg)
  INST_FIELD(redmode, BarRedOpEncoding, Red, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, Imm12Encoding, std::uint16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Red_a_b> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarRED, Accessor::_Reg)
  INST_FIELD(redmode, BarRedOpEncoding, Red, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  INST_FIELD(uImm, Imm12Encoding, std::uint16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Red_a> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarRED, Accessor::_Reg)
  INST_FIELD(redmode, BarRedOpEncoding, Red, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_syncall> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSYNCALL, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Scan> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSCAN, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_Scan_a> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSCAN, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  INST_FIELD(Rb, RegBEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_scan_imm> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSCAN, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  INST_FIELD(uImm, Imm12Encoding, std::uint16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::BAR_scan_imm_a> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000010101);
  INST_FIELD(barmode, BarOpEncoding, BarSCAN, Accessor::_Reg)
  INST_FIELD(barNum, RegAEncoding, std::uint8_t)
  INST_FIELD(uImm, Imm12Encoding, std::uint16_t)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VOTE_VTG> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011100);
  INST_FIELD(vtgmode, VModeEncoding, VTGMode, Accessor::_Reg)
  INST_FIELD(uImm, Imm28Encoding, std::uint32_t)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::VOTE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101000011011);
  INST_FIELD(voteop, VModeEncoding, VoteOp, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Pd, VPDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SETCRSPTR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101110);
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::GETCRSPTR> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101100);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::SETLMEMBASE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101111);
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::GETLMEMBASE> : public AccessorBase {
  using AccessorBase::AccessorBase;
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b111000101101);
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::ISBERD> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1110111111010);
  INST_FIELD(io, AIOEncoding, ISBERDIO, Accessor::_Reg)
  INST_FIELD(base, IBaseEncoding, BASE, Accessor::_Reg)
  INST_FIELD(skew, PEncoding, SKEW, Accessor::_Reg)
  INST_FIELD(size, ALSizeEncoding, ISBERDInteger, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, Register, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, Register, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_bit_set, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hfma2__v2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hfma2__v2_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hfma2__v2_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110100000);
  INST_FIELD(ofmt, hfma2__v2_ofmtEncoding, hfma2__v2_ofmt, Accessor::_Reg)
  INST_FIELD(fmz, hfma2__v2_fmzEncoding, hfma2__v2_fmz, Accessor::_Reg)
  INST_FIELD(sat, hfma2__v2_satEncoding, hfma2__v2_sat, Accessor::_Reg)
  INST_FIELD(Rd, hfma2__v2_RdEncoding, hfma2__v2_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hfma2__v2_RaEncoding, hfma2__v2_Ra, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<hfma2__v2_nABEncoding>, bool, hfma2__v2_nAB, 0, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hfma2__v2_Ra_iswz_Ra_modEncoding, hfma2__v2_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, hfma2__v2_SbEncoding, hfma2__v2_Rb, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<hfma2__v2_nABEncoding>, bool, hfma2__v2_nAB, 1, Accessor::_Bool)
  INST_FIELD(iswz_Rb_mod, hfma2__v2_Sb_iswz_Rb_modEncoding, hfma2__v2_Sb_iswz_Rb_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rc, hfma2__v2_RcEncoding, hfma2__v2_Rc, Accessor::_Reg)
  INST_FIELD(Rc_negate, hfma2__v2_Rc_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rc_reg_mod, hfma2__v2_Rc_iswz_Rc_reg_modEncoding, hfma2__v2_Rc_iswz_Rc_reg_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hfma2__v2_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hfma2__v2_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hfma2__v2_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hfma2__v2_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hfma2__v1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hfma2__v1_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hfma2__v1_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11100);
  INST_FIELD(ofmt, hfma2__v1_ofmtEncoding, hfma2__v1_ofmt, Accessor::_Reg)
  INST_FIELD(fmz, hfma2__v1_fmzEncoding, hfma2__v1_fmz, Accessor::_Reg)
  INST_FIELD(sat, hfma2__v1_satEncoding, hfma2__v1_sat, Accessor::_Reg)
  INST_FIELD(Rd, hfma2__v1_RdEncoding, hfma2__v1_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hfma2__v1_RaEncoding, hfma2__v1_Ra, Accessor::_Reg)
  INST_FIELD(iswz_Ra_mod, hfma2__v1_Ra_iswz_Ra_modEncoding, hfma2__v1_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(Sb, hfma2__v1_SbEncoding, double)
  FLOAT_INST_FIELD(Sb2, hfma2__v1_Sb2Encoding, double)
  INST_FIELD(Rc, hfma2__v1_RcEncoding, hfma2__v1_Rc, Accessor::_Reg)
  INST_FIELD(Rc_negate, hfma2__v1_Rc_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rc_mod, hfma2__v1_Rc_iswz_Rc_modEncoding, hfma2__v1_Rc_iswz_Rc_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hfma2__v1_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hfma2__v1_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hfma2__v1_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hfma2__v1_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hfma2__v0> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hfma2__v0_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hfma2__v0_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11101);
  INST_FIELD(ofmt, hfma2__v0_ofmtEncoding, hfma2__v0_ofmt, Accessor::_Reg)
  INST_FIELD(fmz, hfma2__v0_fmzEncoding, hfma2__v0_fmz, Accessor::_Reg)
  INST_FIELD(sat, hfma2__v0_satEncoding, hfma2__v0_sat, Accessor::_Reg)
  INST_FIELD(Rd, hfma2__v0_RdEncoding, hfma2__v0_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hfma2__v0_RaEncoding, hfma2__v0_Ra, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<hfma2__v0_nABEncoding>, bool, hfma2__v0_nAB, 0, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hfma2__v0_Ra_iswz_Ra_modEncoding, hfma2__v0_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(Sb_negate, MultiEncoding<hfma2__v0_nABEncoding>, bool, hfma2__v0_nAB, 1, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Rc, hfma2__v0_RcEncoding, hfma2__v0_Rc, Accessor::_Reg)
  INST_FIELD(Rc_negate, hfma2__v0_Rc_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rc_mod, hfma2__v0_Rc_iswz_Rc_modEncoding, hfma2__v0_Rc_iswz_Rc_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hfma2__v0_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hfma2__v0_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hfma2__v0_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hfma2__v0_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hset2__v2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hset2__v2_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hset2__v2_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110100011);
  INST_FIELD(bval, hset2__v2_bvalEncoding, hset2__v2_bval, Accessor::_Reg)
  INST_FIELD(cmp, hset2__v2_cmpEncoding, hset2__v2_cmp, Accessor::_Reg)
  INST_FIELD(ftz, hset2__v2_ftzEncoding, hset2__v2_ftz, Accessor::_Reg)
  INST_FIELD(bop, hset2__v2_bopEncoding, hset2__v2_bop, Accessor::_Reg)
  INST_FIELD(Rd, hset2__v2_RdEncoding, hset2__v2_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hset2__v2_RaEncoding, hset2__v2_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hset2__v2_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hset2__v2_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hset2__v2_Ra_iswz_Ra_modEncoding, hset2__v2_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, hset2__v2_SbEncoding, hset2__v2_Rb, Accessor::_Reg)
  INST_FIELD(Rb_negate, hset2__v2_Sb_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, hset2__v2_Sb_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rb_mod, hset2__v2_Sb_iswz_Rb_modEncoding, hset2__v2_Sb_iswz_Rb_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Ps, hset2__v2_PsEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ps_not, hset2__v2_PsNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hset2__v2_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hset2__v2_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hset2__v2_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hset2__v2_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hset2__v1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hset2__v1_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hset2__v1_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111100);
  INST_FIELD(bval, hset2__v1_bvalEncoding, hset2__v1_bval, Accessor::_Reg)
  INST_FIELD(cmp, hset2__v1_cmpEncoding, hset2__v1_cmp, Accessor::_Reg)
  INST_FIELD(ftz, hset2__v1_ftzEncoding, hset2__v1_ftz, Accessor::_Reg)
  INST_FIELD(bop, hset2__v1_bopEncoding, hset2__v1_bop, Accessor::_Reg)
  INST_FIELD(Rd, hset2__v1_RdEncoding, hset2__v1_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hset2__v1_RaEncoding, hset2__v1_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hset2__v1_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hset2__v1_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hset2__v1_Ra_iswz_Ra_modEncoding, hset2__v1_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(Sb, hset2__v1_SbEncoding, double)
  FLOAT_INST_FIELD(Sb2, hset2__v1_Sb2Encoding, double)
  INST_FIELD(Ps, hset2__v1_PsEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ps_not, hset2__v1_PsNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hset2__v1_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hset2__v1_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hset2__v1_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hset2__v1_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hset2__v0> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hset2__v0_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hset2__v0_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111101);
  INST_FIELD(bval, hset2__v0_bvalEncoding, hset2__v0_bval, Accessor::_Reg)
  INST_FIELD(cmp, hset2__v0_cmpEncoding, hset2__v0_cmp, Accessor::_Reg)
  INST_FIELD(ftz, hset2__v0_ftzEncoding, hset2__v0_ftz, Accessor::_Reg)
  INST_FIELD(bop, hset2__v0_bopEncoding, hset2__v0_bop, Accessor::_Reg)
  INST_FIELD(Rd, hset2__v0_RdEncoding, hset2__v0_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hset2__v0_RaEncoding, hset2__v0_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hset2__v0_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hset2__v0_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hset2__v0_Ra_iswz_Ra_modEncoding, hset2__v0_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Sb_negate, hset2__v0_Sb_negateEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Ps, hset2__v0_PsEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ps_not, hset2__v0_PsNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hset2__v0_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hset2__v0_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hset2__v0_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hset2__v0_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hset2_bop__v1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hset2_bop__v1_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hset2_bop__v1_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111100);
  INST_FIELD(bval, hset2_bop__v1_bvalEncoding, hset2_bop__v1_bval, Accessor::_Reg)
  INST_FIELD(cmp, hset2_bop__v1_cmpEncoding, hset2_bop__v1_cmp, Accessor::_Reg)
  INST_FIELD(ftz, hset2_bop__v1_ftzEncoding, hset2_bop__v1_ftz, Accessor::_Reg)
  INST_FIELD(Rd, hset2_bop__v1_RdEncoding, hset2_bop__v1_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hset2_bop__v1_RaEncoding, hset2_bop__v1_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hset2_bop__v1_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hset2_bop__v1_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hset2_bop__v1_Ra_iswz_Ra_modEncoding, hset2_bop__v1_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(Sb, hset2_bop__v1_SbEncoding, double)
  FLOAT_INST_FIELD(Sb2, hset2_bop__v1_Sb2Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hset2_bop__v1_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hset2_bop__v1_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hset2_bop__v1_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hset2_bop__v1_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hset2_bop__v0> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hset2_bop__v0_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hset2_bop__v0_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111101);
  INST_FIELD(bval, hset2_bop__v0_bvalEncoding, hset2_bop__v0_bval, Accessor::_Reg)
  INST_FIELD(cmp, hset2_bop__v0_cmpEncoding, hset2_bop__v0_cmp, Accessor::_Reg)
  INST_FIELD(ftz, hset2_bop__v0_ftzEncoding, hset2_bop__v0_ftz, Accessor::_Reg)
  INST_FIELD(Rd, hset2_bop__v0_RdEncoding, hset2_bop__v0_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hset2_bop__v0_RaEncoding, hset2_bop__v0_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hset2_bop__v0_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hset2_bop__v0_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hset2_bop__v0_Ra_iswz_Ra_modEncoding, hset2_bop__v0_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Sb_negate, hset2_bop__v0_Sb_negateEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hset2_bop__v0_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hset2_bop__v0_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hset2_bop__v0_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hset2_bop__v0_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hmul2_32i_> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hmul2_32i__PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hmul2_32i__PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10101);
  INST_FIELD(fmz, hmul2_32i__fmzEncoding, hmul2_32i__fmz, Accessor::_Reg)
  INST_FIELD(sat, hmul2_32i__satEncoding, hmul2_32i__sat, Accessor::_Reg)
  INST_FIELD(Rd, hmul2_32i__RdEncoding, hmul2_32i__Rd, Accessor::_Reg)
  INST_FIELD(Ra, hmul2_32i__RaEncoding, hmul2_32i__Ra, Accessor::_Reg)
  INST_FIELD(iswz_Ra_32i_mod, hmul2_32i__Ra_iswz_Ra_32i_modEncoding, hmul2_32i__Ra_iswz_Ra_32i_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(imm, hmul2_32i__immEncoding, double)
  FLOAT_INST_FIELD(imm2, hmul2_32i__imm2Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hmul2_32i__req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hmul2_32i__src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hmul2_32i__dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hmul2_32i__usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hset2_bop__v2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hset2_bop__v2_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hset2_bop__v2_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110100011);
  INST_FIELD(bval, hset2_bop__v2_bvalEncoding, hset2_bop__v2_bval, Accessor::_Reg)
  INST_FIELD(cmp, hset2_bop__v2_cmpEncoding, hset2_bop__v2_cmp, Accessor::_Reg)
  INST_FIELD(ftz, hset2_bop__v2_ftzEncoding, hset2_bop__v2_ftz, Accessor::_Reg)
  INST_FIELD(Rd, hset2_bop__v2_RdEncoding, hset2_bop__v2_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hset2_bop__v2_RaEncoding, hset2_bop__v2_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hset2_bop__v2_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hset2_bop__v2_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hset2_bop__v2_Ra_iswz_Ra_modEncoding, hset2_bop__v2_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, hset2_bop__v2_SbEncoding, hset2_bop__v2_Rb, Accessor::_Reg)
  INST_FIELD(Rb_negate, hset2_bop__v2_Sb_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, hset2_bop__v2_Sb_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rb_mod, hset2_bop__v2_Sb_iswz_Rb_modEncoding, hset2_bop__v2_Sb_iswz_Rb_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hset2_bop__v2_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hset2_bop__v2_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hset2_bop__v2_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hset2_bop__v2_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hadd2__v0> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hadd2__v0_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hadd2__v0_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111011);
  INST_FIELD(ofmt, hadd2__v0_ofmtEncoding, hadd2__v0_ofmt, Accessor::_Reg)
  INST_FIELD(ftz, hadd2__v0_ftzEncoding, hadd2__v0_ftz, Accessor::_Reg)
  INST_FIELD(sat, hadd2__v0_satEncoding, hadd2__v0_sat, Accessor::_Reg)
  INST_FIELD(Rd, hadd2__v0_RdEncoding, hadd2__v0_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hadd2__v0_RaEncoding, hadd2__v0_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hadd2__v0_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hadd2__v0_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hadd2__v0_Ra_iswz_Ra_modEncoding, hadd2__v0_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Sb_negate, hadd2__v0_Sb_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Sb_absolute, hadd2__v0_Sb_absoluteEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hadd2__v0_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hadd2__v0_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hadd2__v0_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hadd2__v0_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hadd2__v1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hadd2__v1_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hadd2__v1_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111010);
  INST_FIELD(ofmt, hadd2__v1_ofmtEncoding, hadd2__v1_ofmt, Accessor::_Reg)
  INST_FIELD(ftz, hadd2__v1_ftzEncoding, hadd2__v1_ftz, Accessor::_Reg)
  INST_FIELD(sat, hadd2__v1_satEncoding, hadd2__v1_sat, Accessor::_Reg)
  INST_FIELD(Rd, hadd2__v1_RdEncoding, hadd2__v1_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hadd2__v1_RaEncoding, hadd2__v1_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hadd2__v1_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hadd2__v1_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hadd2__v1_Ra_iswz_Ra_modEncoding, hadd2__v1_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(Sb, hadd2__v1_SbEncoding, double)
  FLOAT_INST_FIELD(Sb2, hadd2__v1_Sb2Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hadd2__v1_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hadd2__v1_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hadd2__v1_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hadd2__v1_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hadd2__v2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hadd2__v2_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hadd2__v2_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110100010);
  INST_FIELD(ofmt, hadd2__v2_ofmtEncoding, hadd2__v2_ofmt, Accessor::_Reg)
  INST_FIELD(ftz, hadd2__v2_ftzEncoding, hadd2__v2_ftz, Accessor::_Reg)
  INST_FIELD(sat, hadd2__v2_satEncoding, hadd2__v2_sat, Accessor::_Reg)
  INST_FIELD(Rd, hadd2__v2_RdEncoding, hadd2__v2_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hadd2__v2_RaEncoding, hadd2__v2_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hadd2__v2_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hadd2__v2_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hadd2__v2_Ra_iswz_Ra_modEncoding, hadd2__v2_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, hadd2__v2_SbEncoding, hadd2__v2_Rb, Accessor::_Reg)
  INST_FIELD(Rb_negate, hadd2__v2_Sb_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, hadd2__v2_Sb_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rb_mod, hadd2__v2_Sb_iswz_Rb_modEncoding, hadd2__v2_Sb_iswz_Rb_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hadd2__v2_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hadd2__v2_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hadd2__v2_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hadd2__v2_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hmul2__v2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hmul2__v2_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hmul2__v2_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110100001);
  INST_FIELD(ofmt, hmul2__v2_ofmtEncoding, hmul2__v2_ofmt, Accessor::_Reg)
  INST_FIELD(fmz, hmul2__v2_fmzEncoding, hmul2__v2_fmz, Accessor::_Reg)
  INST_FIELD(sat, hmul2__v2_satEncoding, hmul2__v2_sat, Accessor::_Reg)
  INST_FIELD(Rd, hmul2__v2_RdEncoding, hmul2__v2_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hmul2__v2_RaEncoding, hmul2__v2_Ra, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<hmul2__v2_nABEncoding>, bool, hmul2__v2_nAB, 0, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hmul2__v2_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hmul2__v2_Ra_iswz_Ra_modEncoding, hmul2__v2_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, hmul2__v2_SbEncoding, hmul2__v2_Rb, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<hmul2__v2_nABEncoding>, bool, hmul2__v2_nAB, 1, Accessor::_Bool)
  INST_FIELD(Rb_absolute, hmul2__v2_Sb_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rb_mod, hmul2__v2_Sb_iswz_Rb_modEncoding, hmul2__v2_Sb_iswz_Rb_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hmul2__v2_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hmul2__v2_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hmul2__v2_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hmul2__v2_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hadd2_32i_> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hadd2_32i__PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hadd2_32i__PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10110);
  INST_FIELD(ftz, hadd2_32i__ftzEncoding, hadd2_32i__ftz, Accessor::_Reg)
  INST_FIELD(sat, hadd2_32i__satEncoding, hadd2_32i__sat, Accessor::_Reg)
  INST_FIELD(Rd, hadd2_32i__RdEncoding, hadd2_32i__Rd, Accessor::_Reg)
  INST_FIELD(Ra, hadd2_32i__RaEncoding, hadd2_32i__Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hadd2_32i__Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_32i_mod, hadd2_32i__Ra_iswz_Ra_32i_modEncoding, hadd2_32i__Ra_iswz_Ra_32i_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(imm, hadd2_32i__immEncoding, double)
  FLOAT_INST_FIELD(imm2, hadd2_32i__imm2Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hadd2_32i__req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hadd2_32i__src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hadd2_32i__dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hadd2_32i__usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hmul2__v1> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hmul2__v1_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hmul2__v1_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111000);
  INST_FIELD(ofmt, hmul2__v1_ofmtEncoding, hmul2__v1_ofmt, Accessor::_Reg)
  INST_FIELD(fmz, hmul2__v1_fmzEncoding, hmul2__v1_fmz, Accessor::_Reg)
  INST_FIELD(sat, hmul2__v1_satEncoding, hmul2__v1_sat, Accessor::_Reg)
  INST_FIELD(Rd, hmul2__v1_RdEncoding, hmul2__v1_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hmul2__v1_RaEncoding, hmul2__v1_Ra, Accessor::_Reg)
  INST_FIELD(Ra_negate, hmul2__v1_Ra_negateEncoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hmul2__v1_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hmul2__v1_Ra_iswz_Ra_modEncoding, hmul2__v1_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(Sb, hmul2__v1_SbEncoding, double)
  FLOAT_INST_FIELD(Sb2, hmul2__v1_Sb2Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hmul2__v1_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hmul2__v1_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hmul2__v1_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hmul2__v1_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::hmul2__v0> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, hmul2__v0_PgEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, hmul2__v0_PgNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111001);
  INST_FIELD(ofmt, hmul2__v0_ofmtEncoding, hmul2__v0_ofmt, Accessor::_Reg)
  INST_FIELD(fmz, hmul2__v0_fmzEncoding, hmul2__v0_fmz, Accessor::_Reg)
  INST_FIELD(sat, hmul2__v0_satEncoding, hmul2__v0_sat, Accessor::_Reg)
  INST_FIELD(Rd, hmul2__v0_RdEncoding, hmul2__v0_Rd, Accessor::_Reg)
  INST_FIELD(Ra, hmul2__v0_RaEncoding, hmul2__v0_Ra, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<hmul2__v0_nABEncoding>, bool, hmul2__v0_nAB, 0, Accessor::_Bool)
  INST_FIELD(Ra_absolute, hmul2__v0_Ra_absoluteEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra_mod, hmul2__v0_Ra_iswz_Ra_modEncoding, hmul2__v0_Ra_iswz_Ra_mod, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_TABLE_FIELD(Sb_negate, MultiEncoding<hmul2__v0_nABEncoding>, bool, hmul2__v0_nAB, 1, Accessor::_Bool)
  INST_FIELD(Sb_absolute, hmul2__v0_Sb_absoluteEncoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, hmul2__v0_req_sb_bitsetEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<hmul2__v0_src_rel_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<hmul2__v0_dst_wr_sbEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, hmul2__v0_usched_infoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::HSETP2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110100100);
  INST_FIELD(fcomp, FComp2Encoding, Test, Accessor::_Reg)
  INST_FIELD(h_and, H_andEncoding, H_AND, Accessor::_Reg)
  INST_FIELD(ftz, FTZHEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aAHEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra, vAmuxEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBHEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBHEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rb, vBmuxEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_HSETP2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b101110100100);
  INST_FIELD(fcomp, FComp2Encoding, Test, Accessor::_Reg)
  INST_FIELD(h_and, H_andEncoding, H_AND, Accessor::_Reg)
  INST_FIELD(ftz, FTZHEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aAHEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra, vAmuxEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegBEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Rb_negate, nBHEncoding, bool, Accessor::_Bool)
  INST_FIELD(Rb_absolute, aBHEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Rb, vBmuxEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Imm_HSETP2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111110);
  INST_FIELD(fcomp, FComp3Encoding, Test, Accessor::_Reg)
  INST_FIELD(h_and, H_and2Encoding, H_AND, Accessor::_Reg)
  INST_FIELD(ftz, FTZHEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aAHEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra, vAmuxEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BimmH1Encoding, double)
  FLOAT_INST_FIELD(uImmH0, BimmH0Encoding, double)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Imm_HSETP2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111110);
  INST_FIELD(fcomp, FComp3Encoding, Test, Accessor::_Reg)
  INST_FIELD(h_and, H_and2Encoding, H_AND, Accessor::_Reg)
  INST_FIELD(ftz, FTZHEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aAHEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra, vAmuxEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(uImm, BimmH1Encoding, double)
  FLOAT_INST_FIELD(uImmH0, BimmH0Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::Const_HSETP2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111111);
  INST_FIELD(fcomp, FComp3Encoding, Test, Accessor::_Reg)
  INST_FIELD(h_and, H_and2Encoding, H_AND, Accessor::_Reg)
  INST_FIELD(ftz, FTZHEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(bopopt, BopEncoding, Bop, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aAHEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra, vAmuxEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBH2Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBH2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  INST_FIELD(Pa, SrcPredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pa_not, SrcNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::NoBop_Const_HSETP2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b1111111);
  INST_FIELD(fcomp, FComp3Encoding, Test, Accessor::_Reg)
  INST_FIELD(h_and, H_and2Encoding, H_AND, Accessor::_Reg)
  INST_FIELD(ftz, FTZHEncoding, FTZ, Accessor::_Reg)
  INST_FIELD(Pd, PDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(nPd, PNDestEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra_negate, nA2Encoding, bool, Accessor::_Bool)
  INST_FIELD(Ra_absolute, aAHEncoding, bool, Accessor::_Bool)
  INST_FIELD(iswz_Ra, vAmuxEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nBH2Encoding, bool, Accessor::_Bool)
  INST_FIELD(srcConst_absolute, aBH2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::HFMA2_32I> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100);
  INST_FIELD(fmz, FMZ_HEncoding, FMZ, Accessor::_Reg)
  INST_TABLE_FIELD(Rd, MultiEncoding<DestEncoding>, RegisterFAU, IDENTICAL<RegisterFAU>, 0, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(iswz_Ra, vAmux_HEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(fImm, FimmH1Encoding, double)
  FLOAT_INST_FIELD(fImm1, FimmH0Encoding, double)
  INST_TABLE_FIELD(Rc, MultiEncoding<DestEncoding>, RegisterFAU, IDENTICAL<RegisterFAU>, 1, Accessor::_Reg)
  INST_FIELD(Rc_negate, nC_HEncoding, bool, Accessor::_Bool)
  SCHED_FIELD(reuse_src_c, OEReuseCEncoding, REUSE, Accessor::_Reg)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::HFMA2_32I_2> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b10100);
  INST_FIELD(fmz, FMZ_HEncoding, FMZ, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(iswz_Ra, vAmux_HEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  FLOAT_INST_FIELD(fImm, FimmH1Encoding, double)
  FLOAT_INST_FIELD(fImm1, FimmH0Encoding, double)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

template <> struct Accessor<OpClass::HFMA2_CCST> : public AccessorBase {
  using AccessorBase::AccessorBase;
  INST_FIELD(Pg, PredEncoding, Predicate, Accessor::_Reg)
  INST_FIELD(Pg_not, PredNotEncoding, bool, Accessor::_Bool)
  CONSTANT_FIELD(Opcode, std::uint64_t, 0b11001);
  INST_FIELD(ofmt, OfmtEncoding, Ofmt_FP16, Accessor::_Reg)
  INST_FIELD(fmz, FMZ_H2Encoding, FMZ, Accessor::_Reg)
  INST_FIELD(sat, sat_HEncoding, SAT, Accessor::_Reg)
  INST_FIELD(Rd, DestEncoding, RegisterFAU, Accessor::_Reg)
  INST_FIELD(Ra, RegAEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Ra_negate, MultiEncoding<nAB_HEncoding>, bool, PSignFFMA, 0, Accessor::_Bool)
  INST_FIELD(iswz_Ra, vAmux_H2Encoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_a, OEReuseAEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(Rb, RegCEncoding, RegisterFAU, Accessor::_Reg)
  INST_TABLE_FIELD(Rb_negate, MultiEncoding<nAB_HEncoding>, bool, PSignFFMA, 1, Accessor::_Bool)
  INST_FIELD(iswz_Rb, vBmux_HEncoding, ISWZ, Accessor::_Reg)
  SCHED_FIELD(reuse_src_b, OEReuseBEncoding, REUSE, Accessor::_Reg)
  INST_FIELD(srcConst_negate, nC_H2Encoding, bool, Accessor::_Bool)
  using constBankEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(constBank, constBankEncoding, std::uint8_t, ConstBankAddress2<17>, 0)
  using immConstOffsetEncoding = MultiEncoding<BcbankEncoding,BcaddrEncoding>;
  INST_TABLE_FIELD(immConstOffset, immConstOffsetEncoding, std::int32_t, ConstBankAddress2<17>, 1)
  CONSTANT_FIELD(req, REQ, REQ::req)
  SCHED_FIELD(req_sb_bitset, OEWaitOnSbEncoding, std::uint8_t)
  CONSTANT_FIELD(rd, RD, RD::rd)
  SCHED_TABLE_FIELD(src_rel_sb, MultiEncoding<OEVarLatSrcEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  CONSTANT_FIELD(wr, WR, WR::wr)
  SCHED_TABLE_FIELD(dst_wr_sb, MultiEncoding<OEVarLatDestEncoding>, std::uint8_t, VarLatOperandEnc, 0)
  SCHED_FIELD(usched_info, OEUSchedInfoEncoding, USCHED_INFO, Accessor::_Reg)
};

} // namespace Maxwell