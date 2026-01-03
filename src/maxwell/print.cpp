#include "maxwell/print.hpp"

#include <format>

namespace maxwell {

const std::string_view ToString(A value) {
  switch (value) {
    case A::A: return "A";
    default: return std::format("A::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(AIO value) {
  switch (value) {
    case AIO::I: return "I";
    case AIO::O: return "O";
    default: return std::format("AIO::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(AInteger value) {
  switch (value) {
    case AInteger::_32: return "32";
    case AInteger::_64: return "64";
    case AInteger::_96: return "96";
    case AInteger::_128: return "128";
    default: return std::format("AInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ALLOnly value) {
  switch (value) {
    case ALLOnly::ALL: return "ALL";
    default: return std::format("ALLOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ASel4 value) {
  switch (value) {
    case ASel4::_0000: return "0000";
    case ASel4::_1111: return "1111";
    case ASel4::_2222: return "2222";
    case ASel4::_3333: return "3333";
    case ASel4::_3210: return "3210";
    case ASel4::_4321: return "4321";
    case ASel4::_5432: return "5432";
    case ASel4::_6543: return "6543";
    case ASel4::_3201: return "3201";
    case ASel4::_3012: return "3012";
    case ASel4::_0213: return "0213";
    case ASel4::_3120: return "3120";
    case ASel4::_1230: return "1230";
    case ASel4::_2310: return "2310";
    case ASel4::ASEL4E: return "ASEL4E";
    case ASel4::ASEL4F: return "ASEL4F";
    default: return std::format("ASel4::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(AdMode value) {
  switch (value) {
    case AdMode::IA: return "IA";
    case AdMode::IL: return "IL";
    case AdMode::IS: return "IS";
    case AdMode::ISL: return "ISL";
    default: return std::format("AdMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(AtomOp value) {
  switch (value) {
    case AtomOp::INVALIDATOMOP0: return "INVALIDATOMOP0";
    case AtomOp::INVALIDATOMOP1: return "INVALIDATOMOP1";
    case AtomOp::INVALIDATOMOP2: return "INVALIDATOMOP2";
    case AtomOp::INVALIDATOMOP3: return "INVALIDATOMOP3";
    case AtomOp::INVALIDATOMOP4: return "INVALIDATOMOP4";
    case AtomOp::INVALIDATOMOP5: return "INVALIDATOMOP5";
    case AtomOp::INVALIDATOMOP6: return "INVALIDATOMOP6";
    case AtomOp::INVALIDATOMOP7: return "INVALIDATOMOP7";
    case AtomOp::INVALIDATOMOP8: return "INVALIDATOMOP8";
    case AtomOp::INVALIDATOMOP9: return "INVALIDATOMOP9";
    case AtomOp::INVALIDATOMOP10: return "INVALIDATOMOP10";
    case AtomOp::INVALIDATOMOP11: return "INVALIDATOMOP11";
    case AtomOp::INVALIDATOMOP12: return "INVALIDATOMOP12";
    case AtomOp::INVALIDATOMOP13: return "INVALIDATOMOP13";
    case AtomOp::INVALIDATOMOP14: return "INVALIDATOMOP14";
    case AtomOp::INVALIDATOMOP15: return "INVALIDATOMOP15";
    default: return std::format("AtomOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(AtomicInteger value) {
  switch (value) {
    case AtomicInteger::_32: return "32";
    case AtomicInteger::_64: return "64";
    case AtomicInteger::F32: return "F32";
    case AtomicInteger::S32: return "S32";
    case AtomicInteger::F16x2_FTZ_RN: return "F16x2.FTZ.RN";
    case AtomicInteger::S64: return "S64";
    case AtomicInteger::SD32: return "SD32";
    case AtomicInteger::SD64: return "SD64";
    default: return std::format("AtomicInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(AtomsOp value) {
  switch (value) {
    case AtomsOp::INVALIDATOMSOP0: return "INVALIDATOMSOP0";
    case AtomsOp::INVALIDATOMSOP1: return "INVALIDATOMSOP1";
    case AtomsOp::INVALIDATOMSOP2: return "INVALIDATOMSOP2";
    case AtomsOp::INVALIDATOMSOP3: return "INVALIDATOMSOP3";
    case AtomsOp::INVALIDATOMSOP4: return "INVALIDATOMSOP4";
    case AtomsOp::INVALIDATOMSOP5: return "INVALIDATOMSOP5";
    case AtomsOp::INVALIDATOMSOP6: return "INVALIDATOMSOP6";
    case AtomsOp::INVALIDATOMSOP7: return "INVALIDATOMSOP7";
    case AtomsOp::INVALIDATOMSOP8: return "INVALIDATOMSOP8";
    case AtomsOp::INVALIDATOMSOP9: return "INVALIDATOMSOP9";
    case AtomsOp::INVALIDATOMSOP10: return "INVALIDATOMSOP10";
    case AtomsOp::INVALIDATOMSOP11: return "INVALIDATOMSOP11";
    case AtomsOp::INVALIDATOMSOP12: return "INVALIDATOMSOP12";
    case AtomsOp::INVALIDATOMSOP13: return "INVALIDATOMSOP13";
    case AtomsOp::INVALIDATOMSOP14: return "INVALIDATOMSOP14";
    case AtomsOp::INVALIDATOMSOP15: return "INVALIDATOMSOP15";
    default: return std::format("AtomsOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(AtomsSPIN value) {
  switch (value) {
    case AtomsSPIN::noSPIN: return "noSPIN";
    case AtomsSPIN::SPIN: return "SPIN";
    default: return std::format("AtomsSPIN::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(AtomsSz value) {
  switch (value) {
    case AtomsSz::_32: return "32";
    case AtomsSz::S32: return "S32";
    case AtomsSz::_64: return "64";
    case AtomsSz::S64: return "S64";
    default: return std::format("AtomsSz::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(B1B0 value) {
  switch (value) {
    case B1B0::H0: return "H0";
    case B1B0::H1: return "H1";
    case B1B0::B1: return "B1";
    case B1B0::B3: return "B3";
    default: return std::format("B1B0::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(B3B0 value) {
  switch (value) {
    case B3B0::B0: return "B0";
    case B3B0::B1: return "B1";
    case B3B0::B2: return "B2";
    case B3B0::B3: return "B3";
    default: return std::format("B3B0::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BA value) {
  switch (value) {
    case BA::noBA: return "noBA";
    case BA::BA: return "BA";
    default: return std::format("BA::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BASE value) {
  switch (value) {
    case BASE::MAP: return "MAP";
    case BASE::PATCH: return "PATCH";
    case BASE::PRIM: return "PRIM";
    case BASE::ATTR: return "ATTR";
    default: return std::format("BASE::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BOnly value) {
  switch (value) {
    case BOnly::B: return "B";
    default: return std::format("BOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BPTMode value) {
  switch (value) {
    case BPTMode::DRAIN_ILLEGAL: return "DRAIN_ILLEGAL";
    case BPTMode::CAL: return "CAL";
    case BPTMode::PAUSE: return "PAUSE";
    case BPTMode::TRAP: return "TRAP";
    case BPTMode::INT: return "INT";
    case BPTMode::DRAIN: return "DRAIN";
    default: return std::format("BPTMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BREV value) {
  switch (value) {
    case BREV::noBREV: return "noBREV";
    case BREV::BREV: return "BREV";
    default: return std::format("BREV::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BSel4 value) {
  switch (value) {
    case BSel4::_4444: return "4444";
    case BSel4::_5555: return "5555";
    case BSel4::_6666: return "6666";
    case BSel4::_7777: return "7777";
    case BSel4::_7654: return "7654";
    case BSel4::_6543: return "6543";
    case BSel4::_5432: return "5432";
    case BSel4::_4321: return "4321";
    case BSel4::_4567: return "4567";
    case BSel4::_6745: return "6745";
    case BSel4::_5476: return "5476";
    case BSel4::BSEL4B: return "BSEL4B";
    case BSel4::BSEL4C: return "BSEL4C";
    case BSel4::BSEL4D: return "BSEL4D";
    case BSel4::BSEL4E: return "BSEL4E";
    default: return std::format("BSel4::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BVal value) {
  switch (value) {
    case BVal::BM: return "BM";
    case BVal::BF: return "BF";
    default: return std::format("BVal::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BarArv value) {
  switch (value) {
    case BarArv::ARV: return "ARV";
    default: return std::format("BarArv::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BarRED value) {
  switch (value) {
    case BarRED::RED: return "RED";
    default: return std::format("BarRED::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BarSCAN value) {
  switch (value) {
    case BarSCAN::SCAN: return "SCAN";
    default: return std::format("BarSCAN::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BarSYNCALL value) {
  switch (value) {
    case BarSYNCALL::SYNCALL: return "SYNCALL";
    default: return std::format("BarSYNCALL::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BarSync value) {
  switch (value) {
    case BarSync::SYNC: return "SYNC";
    default: return std::format("BarSync::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Barmd value) {
  switch (value) {
    case Barmd::BAR: return "BAR";
    case Barmd::RESULT: return "RESULT";
    case Barmd::WARP: return "WARP";
    case Barmd::INVALID: return "INVALID";
    default: return std::format("Barmd::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BarmdBAR value) {
  switch (value) {
    case BarmdBAR::BAR: return "BAR";
    case BarmdBAR::INVALID: return "INVALID";
    default: return std::format("BarmdBAR::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BarmdRESULT value) {
  switch (value) {
    case BarmdRESULT::RESULT: return "RESULT";
    default: return std::format("BarmdRESULT::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(BarmdWARP value) {
  switch (value) {
    case BarmdWARP::WARP: return "WARP";
    default: return std::format("BarmdWARP::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Bop value) {
  switch (value) {
    case Bop::AND: return "AND";
    case Bop::OR: return "OR";
    case Bop::XOR: return "XOR";
    case Bop::INVALIDBOP03: return "INVALIDBOP03";
    default: return std::format("Bop::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(C value) {
  switch (value) {
    case C::C: return "C";
    default: return std::format("C::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CAS value) {
  switch (value) {
    case CAS::CAS: return "CAS";
    default: return std::format("CAS::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CASInteger value) {
  switch (value) {
    case CASInteger::U32: return "U32";
    case CASInteger::U64: return "U64";
    default: return std::format("CASInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CAST value) {
  switch (value) {
    case CAST::CAST: return "CAST";
    default: return std::format("CAST::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CC value) {
  switch (value) {
    case CC::CC: return "CC";
    default: return std::format("CC::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CCPR value) {
  switch (value) {
    case CCPR::PR: return "PR";
    case CCPR::CC: return "CC";
    default: return std::format("CCPR::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CCTLLOp2 value) {
  switch (value) {
    case CCTLLOp2::IVALL: return "IVALL";
    default: return std::format("CCTLLOp2::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CCTLLOp3 value) {
  switch (value) {
    case CCTLLOp3::WBALL: return "WBALL";
    default: return std::format("CCTLLOp3::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CCTLOp value) {
  switch (value) {
    case CCTLOp::PF1: return "PF1";
    case CCTLOp::PF1_5: return "PF1.5";
    case CCTLOp::PF2: return "PF2";
    case CCTLOp::WB: return "WB";
    case CCTLOp::IV: return "IV";
    case CCTLOp::RS: return "RS";
    case CCTLOp::RSLB: return "RSLB";
    case CCTLOp::INVALIDCCTLOP10: return "INVALIDCCTLOP10";
    case CCTLOp::INVALIDCCTLOP11: return "INVALIDCCTLOP11";
    case CCTLOp::INVALIDCCTLOP12: return "INVALIDCCTLOP12";
    case CCTLOp::INVALIDCCTLOP13: return "INVALIDCCTLOP13";
    case CCTLOp::INVALIDCCTLOP14: return "INVALIDCCTLOP14";
    case CCTLOp::INVALIDCCTLOP15: return "INVALIDCCTLOP15";
    default: return std::format("CCTLOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CCTLTOp value) {
  switch (value) {
    case CCTLTOp::IVTH: return "IVTH";
    case CCTLTOp::INVALIDCCTLTOP2: return "INVALIDCCTLTOP2";
    case CCTLTOp::INVALIDCCTLTOP3: return "INVALIDCCTLTOP3";
    default: return std::format("CCTLTOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CCTLTOpIVALL value) {
  switch (value) {
    case CCTLTOpIVALL::IVALL: return "IVALL";
    default: return std::format("CCTLTOpIVALL::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CInteger value) {
  switch (value) {
    case CInteger::SD: return "SD";
    case CInteger::_16: return "16";
    case CInteger::S8: return "S8";
    case CInteger::S16: return "S16";
    case CInteger::_32: return "32";
    case CInteger::_64: return "64";
    case CInteger::_128: return "128";
    case CInteger::INVALIDSIZE7: return "INVALIDSIZE7";
    default: return std::format("CInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CInteger_64 value) {
  switch (value) {
    case CInteger_64::_64: return "64";
    default: return std::format("CInteger_64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CInteger_n64_n128 value) {
  switch (value) {
    case CInteger_n64_n128::SD: return "SD";
    case CInteger_n64_n128::_16: return "16";
    case CInteger_n64_n128::S8: return "S8";
    case CInteger_n64_n128::S16: return "S16";
    case CInteger_n64_n128::_32: return "32";
    case CInteger_n64_n128::INVALIDSIZE6: return "INVALIDSIZE6";
    case CInteger_n64_n128::INVALIDSIZE7: return "INVALIDSIZE7";
    default: return std::format("CInteger_n64_n128::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CL value) {
  switch (value) {
    case CL::noCL: return "noCL";
    case CL::CL: return "CL";
    default: return std::format("CL::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CRSOnly value) {
  switch (value) {
    case CRSOnly::CRS: return "CRS";
    default: return std::format("CRSOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(CWMode value) {
  switch (value) {
    case CWMode::C: return "C";
    case CWMode::W: return "W";
    default: return std::format("CWMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Cache3 value) {
  switch (value) {
    case Cache3::D: return "D";
    case Cache3::U: return "U";
    case Cache3::C: return "C";
    case Cache3::I: return "I";
    case Cache3::CRS: return "CRS";
    case Cache3::INVALIDCCTLCACHEOP5: return "INVALIDCCTLCACHEOP5";
    case Cache3::INVALIDCCTLCACHEOP6: return "INVALIDCCTLCACHEOP6";
    case Cache3::INVALIDCCTLCACHEOP7: return "INVALIDCCTLCACHEOP7";
    default: return std::format("Cache3::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Cache3CI value) {
  switch (value) {
    case Cache3CI::C: return "C";
    case Cache3CI::I: return "I";
    default: return std::format("Cache3CI::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Cache3NoCI value) {
  switch (value) {
    case Cache3NoCI::D: return "D";
    case Cache3NoCI::U: return "U";
    case Cache3NoCI::CRS: return "CRS";
    case Cache3NoCI::INVALIDCCTLCACHEOP5: return "INVALIDCCTLCACHEOP5";
    case Cache3NoCI::INVALIDCCTLCACHEOP6: return "INVALIDCCTLCACHEOP6";
    case Cache3NoCI::INVALIDCCTLCACHEOP7: return "INVALIDCCTLCACHEOP7";
    default: return std::format("Cache3NoCI::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ChkMode value) {
  switch (value) {
    case ChkMode::DIVIDE: return "DIVIDE";
    case ChkMode::INVALIDCHKMODE1: return "INVALIDCHKMODE1";
    case ChkMode::INVALIDCHKMODE2: return "INVALIDCHKMODE2";
    case ChkMode::INVALIDCHKMODE3: return "INVALIDCHKMODE3";
    case ChkMode::INVALIDCHKMODE4: return "INVALIDCHKMODE4";
    case ChkMode::INVALIDCHKMODE5: return "INVALIDCHKMODE5";
    case ChkMode::INVALIDCHKMODE6: return "INVALIDCHKMODE6";
    case ChkMode::INVALIDCHKMODE7: return "INVALIDCHKMODE7";
    case ChkMode::INVALIDCHKMODE8: return "INVALIDCHKMODE8";
    case ChkMode::INVALIDCHKMODE9: return "INVALIDCHKMODE9";
    case ChkMode::INVALIDCHKMODE10: return "INVALIDCHKMODE10";
    case ChkMode::INVALIDCHKMODE11: return "INVALIDCHKMODE11";
    case ChkMode::INVALIDCHKMODE12: return "INVALIDCHKMODE12";
    case ChkMode::INVALIDCHKMODE13: return "INVALIDCHKMODE13";
    case ChkMode::INVALIDCHKMODE14: return "INVALIDCHKMODE14";
    case ChkMode::INVALIDCHKMODE15: return "INVALIDCHKMODE15";
    case ChkMode::INVALIDCHKMODE16: return "INVALIDCHKMODE16";
    case ChkMode::INVALIDCHKMODE17: return "INVALIDCHKMODE17";
    case ChkMode::INVALIDCHKMODE18: return "INVALIDCHKMODE18";
    case ChkMode::INVALIDCHKMODE19: return "INVALIDCHKMODE19";
    case ChkMode::INVALIDCHKMODE20: return "INVALIDCHKMODE20";
    case ChkMode::INVALIDCHKMODE21: return "INVALIDCHKMODE21";
    case ChkMode::INVALIDCHKMODE22: return "INVALIDCHKMODE22";
    case ChkMode::INVALIDCHKMODE23: return "INVALIDCHKMODE23";
    case ChkMode::INVALIDCHKMODE24: return "INVALIDCHKMODE24";
    case ChkMode::INVALIDCHKMODE25: return "INVALIDCHKMODE25";
    case ChkMode::INVALIDCHKMODE26: return "INVALIDCHKMODE26";
    case ChkMode::INVALIDCHKMODE27: return "INVALIDCHKMODE27";
    case ChkMode::INVALIDCHKMODE28: return "INVALIDCHKMODE28";
    case ChkMode::INVALIDCHKMODE29: return "INVALIDCHKMODE29";
    case ChkMode::INVALIDCHKMODE30: return "INVALIDCHKMODE30";
    case ChkMode::INVALIDCHKMODE31: return "INVALIDCHKMODE31";
    case ChkMode::INVALIDCHKMODE32: return "INVALIDCHKMODE32";
    case ChkMode::INVALIDCHKMODE33: return "INVALIDCHKMODE33";
    case ChkMode::INVALIDCHKMODE34: return "INVALIDCHKMODE34";
    case ChkMode::INVALIDCHKMODE35: return "INVALIDCHKMODE35";
    case ChkMode::INVALIDCHKMODE36: return "INVALIDCHKMODE36";
    case ChkMode::INVALIDCHKMODE37: return "INVALIDCHKMODE37";
    case ChkMode::INVALIDCHKMODE38: return "INVALIDCHKMODE38";
    case ChkMode::INVALIDCHKMODE39: return "INVALIDCHKMODE39";
    case ChkMode::INVALIDCHKMODE40: return "INVALIDCHKMODE40";
    case ChkMode::INVALIDCHKMODE41: return "INVALIDCHKMODE41";
    case ChkMode::INVALIDCHKMODE42: return "INVALIDCHKMODE42";
    case ChkMode::INVALIDCHKMODE43: return "INVALIDCHKMODE43";
    case ChkMode::INVALIDCHKMODE44: return "INVALIDCHKMODE44";
    case ChkMode::INVALIDCHKMODE45: return "INVALIDCHKMODE45";
    case ChkMode::INVALIDCHKMODE46: return "INVALIDCHKMODE46";
    case ChkMode::INVALIDCHKMODE47: return "INVALIDCHKMODE47";
    case ChkMode::INVALIDCHKMODE48: return "INVALIDCHKMODE48";
    case ChkMode::INVALIDCHKMODE49: return "INVALIDCHKMODE49";
    case ChkMode::INVALIDCHKMODE50: return "INVALIDCHKMODE50";
    case ChkMode::INVALIDCHKMODE51: return "INVALIDCHKMODE51";
    case ChkMode::INVALIDCHKMODE52: return "INVALIDCHKMODE52";
    case ChkMode::INVALIDCHKMODE53: return "INVALIDCHKMODE53";
    case ChkMode::INVALIDCHKMODE54: return "INVALIDCHKMODE54";
    case ChkMode::INVALIDCHKMODE55: return "INVALIDCHKMODE55";
    case ChkMode::INVALIDCHKMODE56: return "INVALIDCHKMODE56";
    case ChkMode::INVALIDCHKMODE57: return "INVALIDCHKMODE57";
    case ChkMode::INVALIDCHKMODE58: return "INVALIDCHKMODE58";
    case ChkMode::INVALIDCHKMODE59: return "INVALIDCHKMODE59";
    case ChkMode::INVALIDCHKMODE60: return "INVALIDCHKMODE60";
    case ChkMode::INVALIDCHKMODE61: return "INVALIDCHKMODE61";
    case ChkMode::INVALIDCHKMODE62: return "INVALIDCHKMODE62";
    case ChkMode::INVALIDCHKMODE63: return "INVALIDCHKMODE63";
    default: return std::format("ChkMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Clamp1 value) {
  switch (value) {
    case Clamp1::IGN: return "IGN";
    case Clamp1::NEAR: return "NEAR";
    case Clamp1::TRAP: return "TRAP";
    case Clamp1::INVALIDSURFACECLAMP3: return "INVALIDSURFACECLAMP3";
    default: return std::format("Clamp1::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(DC value) {
  switch (value) {
    case DC::noDC: return "noDC";
    case DC::DC: return "DC";
    default: return std::format("DC::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(DFormat value) {
  switch (value) {
    case DFormat::UD: return "UD";
    case DFormat::SD: return "SD";
    default: return std::format("DFormat::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(DIR value) {
  switch (value) {
    case DIR::NS: return "NS";
    case DIR::RS: return "RS";
    case DIR::LS: return "LS";
    default: return std::format("DIR::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(DOnly value) {
  switch (value) {
    case DOnly::D: return "D";
    default: return std::format("DOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Dim1 value) {
  switch (value) {
    case Dim1::_1D: return "1D";
    case Dim1::_1D_BUFFER: return "1D_BUFFER";
    case Dim1::_1D_ARRAY: return "1D_ARRAY";
    case Dim1::_2D: return "2D";
    case Dim1::_2D_ARRAY: return "2D_ARRAY";
    case Dim1::_3D: return "3D";
    case Dim1::INVALIDSURFACEDIM6: return "INVALIDSURFACEDIM6";
    case Dim1::INVALIDSURFACEDIM7: return "INVALIDSURFACEDIM7";
    default: return std::format("Dim1::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(E value) {
  switch (value) {
    case E::noE: return "noE";
    case E::E: return "E";
    default: return std::format("E::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2FRound1 value) {
  switch (value) {
    case F2FRound1::PASS: return "PASS";
    case F2FRound1::RN: return "RN";
    case F2FRound1::RM: return "RM";
    case F2FRound1::RP: return "RP";
    case F2FRound1::RZ: return "RZ";
    default: return std::format("F2FRound1::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2FRound2 value) {
  switch (value) {
    case F2FRound2::PASS: return "PASS";
    case F2FRound2::FLOOR: return "FLOOR";
    case F2FRound2::CEIL: return "CEIL";
    case F2FRound2::TRUNC: return "TRUNC";
    default: return std::format("F2FRound2::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2Ffmts1 value) {
  switch (value) {
    case F2Ffmts1::INVALIDFPDEST0_INVALIDFPSRC0: return "INVALIDFPDEST0.INVALIDFPSRC0";
    case F2Ffmts1::F32_F32: return "F32.F32";
    default: return std::format("F2Ffmts1::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2Ffmts1_16 value) {
  switch (value) {
    case F2Ffmts1_16::F16_F16: return "F16.F16";
    default: return std::format("F2Ffmts1_16::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2Ffmts1_64 value) {
  switch (value) {
    case F2Ffmts1_64::F64_F64: return "F64.F64";
    default: return std::format("F2Ffmts1_64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2Ffmts2 value) {
  switch (value) {
    case F2Ffmts2::F16_INVALIDFPSRC0: return "F16.INVALIDFPSRC0";
    case F2Ffmts2::F32_INVALIDFPSRC0: return "F32.INVALIDFPSRC0";
    case F2Ffmts2::F64_INVALIDFPSRC0: return "F64.INVALIDFPSRC0";
    case F2Ffmts2::INVALIDFPDEST0_F32: return "INVALIDFPDEST0.F32";
    case F2Ffmts2::F16_F32: return "F16.F32";
    default: return std::format("F2Ffmts2::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2Ffmts2_16 value) {
  switch (value) {
    case F2Ffmts2_16::INVALIDFPDEST0_F16: return "INVALIDFPDEST0.F16";
    case F2Ffmts2_16::F32_F16: return "F32.F16";
    default: return std::format("F2Ffmts2_16::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2Ffmts2_64 value) {
  switch (value) {
    case F2Ffmts2_64::INVALIDFPDEST0_F64: return "INVALIDFPDEST0.F64";
    case F2Ffmts2_64::F16_F64: return "F16.F64";
    case F2Ffmts2_64::F32_F64: return "F32.F64";
    default: return std::format("F2Ffmts2_64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2Ffmts2_64_16 value) {
  switch (value) {
    case F2Ffmts2_64_16::F64_F16: return "F64.F16";
    default: return std::format("F2Ffmts2_64_16::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(F2Ffmts2_64_32 value) {
  switch (value) {
    case F2Ffmts2_64_32::F64_F32: return "F64.F32";
    default: return std::format("F2Ffmts2_64_32::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(FMZ value) {
  switch (value) {
    case FMZ::noFTZ: return "noFTZ";
    case FMZ::FTZ: return "FTZ";
    case FMZ::FMZ: return "FMZ";
    case FMZ::INVALIDFMZ3: return "INVALIDFMZ3";
    default: return std::format("FMZ::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(FTZ value) {
  switch (value) {
    case FTZ::noFTZ: return "noFTZ";
    case FTZ::FTZ: return "FTZ";
    default: return std::format("FTZ::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Float value) {
  switch (value) {
    case Float::INVALIDFPDEST0: return "INVALIDFPDEST0";
    case Float::F16: return "F16";
    case Float::F32: return "F32";
    case Float::F64: return "F64";
    default: return std::format("Float::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Float16 value) {
  switch (value) {
    case Float16::F16: return "F16";
    default: return std::format("Float16::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Float32 value) {
  switch (value) {
    case Float32::INVALIDFPDEST0: return "INVALIDFPDEST0";
    case Float32::F32: return "F32";
    default: return std::format("Float32::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Float64 value) {
  switch (value) {
    case Float64::F64: return "F64";
    default: return std::format("Float64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(FloatNo64 value) {
  switch (value) {
    case FloatNo64::INVALIDFPDEST0: return "INVALIDFPDEST0";
    case FloatNo64::F16: return "F16";
    case FloatNo64::F32: return "F32";
    default: return std::format("FloatNo64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(H1H0 value) {
  switch (value) {
    case H1H0::H0: return "H0";
    case H1H0::H1: return "H1";
    default: return std::format("H1H0::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(HILO value) {
  switch (value) {
    case HILO::LO: return "LO";
    case HILO::HI: return "HI";
    default: return std::format("HILO::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(HIOnly value) {
  switch (value) {
    case HIOnly::HI: return "HI";
    default: return std::format("HIOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(H_AND value) {
  switch (value) {
    case H_AND::noH_AND: return "noH_AND";
    case H_AND::H_AND: return "H_AND";
    default: return std::format("H_AND::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(I2XH value) {
  switch (value) {
    case I2XH::H0: return "H0";
    case I2XH::INVALIDSIZE1: return "INVALIDSIZE1";
    case I2XH::H1: return "H1";
    case I2XH::INVALIDSIZE3: return "INVALIDSIZE3";
    default: return std::format("I2XH::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ICmpAll value) {
  switch (value) {
    case ICmpAll::F: return "F";
    case ICmpAll::LT: return "LT";
    case ICmpAll::EQ: return "EQ";
    case ICmpAll::LE: return "LE";
    case ICmpAll::GT: return "GT";
    case ICmpAll::NE: return "NE";
    case ICmpAll::GE: return "GE";
    case ICmpAll::T: return "T";
    default: return std::format("ICmpAll::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ICmpU value) {
  switch (value) {
    case ICmpU::LO: return "LO";
    case ICmpU::LS: return "LS";
    case ICmpU::HI: return "HI";
    case ICmpU::HS: return "HS";
    default: return std::format("ICmpU::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IDEActionDIOnly value) {
  switch (value) {
    case IDEActionDIOnly::DI: return "DI";
    default: return std::format("IDEActionDIOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IDEActionENOnly value) {
  switch (value) {
    case IDEActionENOnly::EN: return "EN";
    default: return std::format("IDEActionENOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IDXOnly value) {
  switch (value) {
    case IDXOnly::IDX: return "IDX";
    default: return std::format("IDXOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(INC value) {
  switch (value) {
    case INC::NOINC: return "NOINC";
    case INC::INC: return "INC";
    default: return std::format("INC::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IPAOp value) {
  switch (value) {
    case IPAOp::PASS: return "PASS";
    case IPAOp::MUL: return "MUL";
    case IPAOp::CONSTANT: return "CONSTANT";
    case IPAOp::SC: return "SC";
    default: return std::format("IPAOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ISBERDInteger value) {
  switch (value) {
    case ISBERDInteger::U8: return "U8";
    case ISBERDInteger::U16: return "U16";
    case ISBERDInteger::_32: return "32";
    default: return std::format("ISBERDInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ISWZ value) {
  switch (value) {
    case ISWZ::H1_H0: return "H1_H0";
    case ISWZ::F32: return "F32";
    case ISWZ::H0_H0: return "H0_H0";
    case ISWZ::H1_H1: return "H1_H1";
    default: return std::format("ISWZ::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Integer value) {
  switch (value) {
    case static_cast<Integer>(Integer64::U64): return "U64";
    case static_cast<Integer>(Integer64::S64): return "S64";
    case static_cast<Integer>(Integer8::U8): return "U8";
    case static_cast<Integer>(Integer8::S8): return "S8";
    case static_cast<Integer>(Integer16::U16): return "U16";
    case static_cast<Integer>(Integer16::S16): return "S16";
    case static_cast<Integer>(Integer32::U32): return "U32";
    case static_cast<Integer>(Integer32::S32): return "S32";
    default: return std::format("Integer::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Integer16 value) {
  switch (value) {
    case Integer16::U16: return "U16";
    case Integer16::S16: return "S16";
    default: return std::format("Integer16::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Integer32 value) {
  switch (value) {
    case Integer32::U32: return "U32";
    case Integer32::S32: return "S32";
    default: return std::format("Integer32::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Integer64 value) {
  switch (value) {
    case Integer64::U64: return "U64";
    case Integer64::S64: return "S64";
    default: return std::format("Integer64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Integer8 value) {
  switch (value) {
    case Integer8::U8: return "U8";
    case Integer8::S8: return "S8";
    default: return std::format("Integer8::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IntegerInv8No64 value) {
  switch (value) {
    case static_cast<IntegerInv8No64>(Invalid8::INVALID0): return "INVALID0";
    case static_cast<IntegerInv8No64>(Invalid8::INVALID1): return "INVALID1";
    case static_cast<IntegerInv8No64>(Integer32::U32): return "U32";
    case static_cast<IntegerInv8No64>(Integer32::S32): return "S32";
    case static_cast<IntegerInv8No64>(Integer16::U16): return "U16";
    case static_cast<IntegerInv8No64>(Integer16::S16): return "S16";
    default: return std::format("IntegerInv8No64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IntegerNo16Inv64 value) {
  switch (value) {
    case static_cast<IntegerNo16Inv64>(Integer8::U8): return "U8";
    case static_cast<IntegerNo16Inv64>(Integer8::S8): return "S8";
    case static_cast<IntegerNo16Inv64>(Invalid64::INVALID6): return "INVALID6";
    case static_cast<IntegerNo16Inv64>(Invalid64::INVALID7): return "INVALID7";
    case static_cast<IntegerNo16Inv64>(Integer32::U32): return "U32";
    case static_cast<IntegerNo16Inv64>(Integer32::S32): return "S32";
    default: return std::format("IntegerNo16Inv64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IntegerNo16No64 value) {
  switch (value) {
    case static_cast<IntegerNo16No64>(Integer8::U8): return "U8";
    case static_cast<IntegerNo16No64>(Integer8::S8): return "S8";
    case static_cast<IntegerNo16No64>(Integer32::U32): return "U32";
    case static_cast<IntegerNo16No64>(Integer32::S32): return "S32";
    default: return std::format("IntegerNo16No64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IntegerNo64 value) {
  switch (value) {
    case static_cast<IntegerNo64>(Integer8::U8): return "U8";
    case static_cast<IntegerNo64>(Integer8::S8): return "S8";
    case static_cast<IntegerNo64>(Integer16::U16): return "U16";
    case static_cast<IntegerNo64>(Integer16::S16): return "S16";
    case static_cast<IntegerNo64>(Integer32::U32): return "U32";
    case static_cast<IntegerNo64>(Integer32::S32): return "S32";
    default: return std::format("IntegerNo64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IntegerNo8 value) {
  switch (value) {
    case static_cast<IntegerNo8>(Integer64::U64): return "U64";
    case static_cast<IntegerNo8>(Integer64::S64): return "S64";
    case static_cast<IntegerNo8>(Invalid8::INVALID0): return "INVALID0";
    case static_cast<IntegerNo8>(Invalid8::INVALID1): return "INVALID1";
    case static_cast<IntegerNo8>(Integer32::U32): return "U32";
    case static_cast<IntegerNo8>(Integer32::S32): return "S32";
    case static_cast<IntegerNo8>(Integer16::U16): return "U16";
    case static_cast<IntegerNo8>(Integer16::S16): return "S16";
    default: return std::format("IntegerNo8::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IntegerSPA value) {
  switch (value) {
    case IntegerSPA::U32: return "U32";
    case IntegerSPA::S32: return "S32";
    case IntegerSPA::U24: return "U24";
    case IntegerSPA::S24: return "S24";
    case IntegerSPA::U16H0: return "U16H0";
    case IntegerSPA::S16H0: return "S16H0";
    case IntegerSPA::U16H1: return "U16H1";
    case IntegerSPA::S16H1: return "S16H1";
    default: return std::format("IntegerSPA::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IntegerSPB value) {
  switch (value) {
    case IntegerSPB::U16H0: return "U16H0";
    case IntegerSPB::S16H0: return "S16H0";
    case IntegerSPB::U24: return "U24";
    case IntegerSPB::S24: return "S24";
    default: return std::format("IntegerSPB::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(IntegerSPC value) {
  switch (value) {
    case IntegerSPC::U32: return "U32";
    case IntegerSPC::S32: return "S32";
    case IntegerSPC::U24: return "U24";
    case IntegerSPC::S24: return "S24";
    case IntegerSPC::U16H0: return "U16H0";
    case IntegerSPC::S16H0: return "S16H0";
    default: return std::format("IntegerSPC::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Invalid64 value) {
  switch (value) {
    case Invalid64::INVALID6: return "INVALID6";
    case Invalid64::INVALID7: return "INVALID7";
    default: return std::format("Invalid64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Invalid8 value) {
  switch (value) {
    case Invalid8::INVALID0: return "INVALID0";
    case Invalid8::INVALID1: return "INVALID1";
    default: return std::format("Invalid8::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(KeepRefCount value) {
  switch (value) {
    case KeepRefCount::noKEEPREFCOUNT: return "noKEEPREFCOUNT";
    case KeepRefCount::KEEPREFCOUNT: return "KEEPREFCOUNT";
    default: return std::format("KeepRefCount::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LC value) {
  switch (value) {
    case LC::noLC: return "noLC";
    case LC::LC: return "LC";
    default: return std::format("LC::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LCache value) {
  switch (value) {
    case LCache::D: return "D";
    case LCache::INVALIDLCACHETYPE2: return "INVALIDLCACHETYPE2";
    case LCache::INVALIDLCACHETYPE3: return "INVALIDLCACHETYPE3";
    default: return std::format("LCache::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LDInteger value) {
  switch (value) {
    case LDInteger::_8: return "8";
    case LDInteger::_16: return "16";
    case LDInteger::S8: return "S8";
    case LDInteger::S16: return "S16";
    case LDInteger::_32: return "32";
    case LDInteger::_64: return "64";
    case LDInteger::_128: return "128";
    case LDInteger::U_128: return "U.128";
    default: return std::format("LDInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LDInteger_nU128 value) {
  switch (value) {
    case LDInteger_nU128::_8: return "8";
    case LDInteger_nU128::_16: return "16";
    case LDInteger_nU128::S8: return "S8";
    case LDInteger_nU128::S16: return "S16";
    case LDInteger_nU128::_32: return "32";
    case LDInteger_nU128::_64: return "64";
    case LDInteger_nU128::_128: return "128";
    case LDInteger_nU128::INVALIDSIZE7: return "INVALIDSIZE7";
    default: return std::format("LDInteger_nU128::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LDSInteger value) {
  switch (value) {
    case LDSInteger::_8: return "8";
    case LDSInteger::U_8: return "U.8";
    case LDSInteger::_16: return "16";
    case LDSInteger::U_16: return "U.16";
    case LDSInteger::S8: return "S8";
    case LDSInteger::U_S8: return "U.S8";
    case LDSInteger::S16: return "S16";
    case LDSInteger::U_S16: return "U.S16";
    case LDSInteger::_32: return "32";
    case LDSInteger::U_32: return "U.32";
    case LDSInteger::_64: return "64";
    case LDSInteger::U_64: return "U.64";
    case LDSInteger::_128: return "128";
    case LDSInteger::U_128: return "U.128";
    case LDSInteger::INVALIDSIZE7: return "INVALIDSIZE7";
    case LDSInteger::U_INVALIDSIZE7: return "U.INVALIDSIZE7";
    default: return std::format("LDSInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LEOnly value) {
  switch (value) {
    case LEOnly::LE: return "LE";
    default: return std::format("LEOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LLoadCacheOp value) {
  switch (value) {
    case LLoadCacheOp::CS: return "CS";
    case LLoadCacheOp::LU: return "LU";
    case LLoadCacheOp::CI: return "CI";
    case LLoadCacheOp::CV: return "CV";
    default: return std::format("LLoadCacheOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LMT value) {
  switch (value) {
    case LMT::noLMT: return "noLMT";
    case LMT::LMT: return "LMT";
    default: return std::format("LMT::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LOD value) {
  switch (value) {
    case LOD::noLOD: return "noLOD";
    case LOD::LZ: return "LZ";
    case LOD::LB: return "LB";
    case LOD::LL: return "LL";
    case LOD::INVALIDBLOD4: return "INVALIDBLOD4";
    case LOD::INVALIDBLOD5: return "INVALIDBLOD5";
    case LOD::LBA: return "LBA";
    case LOD::LLA: return "LLA";
    default: return std::format("LOD::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LOD1 value) {
  switch (value) {
    case LOD1::LZ: return "LZ";
    case LOD1::LL: return "LL";
    default: return std::format("LOD1::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LOD2 value) {
  switch (value) {
    case LOD2::noLOD: return "noLOD";
    case LOD2::LZ: return "LZ";
    case LOD2::LL: return "LL";
    default: return std::format("LOD2::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LODOnly value) {
  switch (value) {
    case LODOnly::LOD: return "LOD";
    default: return std::format("LODOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LOOnly value) {
  switch (value) {
    case LOOnly::LO: return "LO";
    default: return std::format("LOOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LOP value) {
  switch (value) {
    case LOP::AND: return "AND";
    case LOP::OR: return "OR";
    case LOP::XOR: return "XOR";
    case LOP::PASS_B: return "PASS_B";
    default: return std::format("LOP::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LUTOnly value) {
  switch (value) {
    case LUTOnly::LUT: return "LUT";
    default: return std::format("LUTOnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LaneMask4 value) {
  switch (value) {
    case LaneMask4::X: return "X";
    case LaneMask4::Y: return "Y";
    case LaneMask4::Z: return "Z";
    case LaneMask4::W: return "W";
    case LaneMask4::XW: return "XW";
    case LaneMask4::YW: return "YW";
    case LaneMask4::ZW: return "ZW";
    case LaneMask4::XZ: return "XZ";
    case LaneMask4::YZ: return "YZ";
    case LaneMask4::XY: return "XY";
    case LaneMask4::YZW: return "YZW";
    case LaneMask4::XZW: return "XZW";
    case LaneMask4::XYW: return "XYW";
    case LaneMask4::XYZ: return "XYZ";
    case LaneMask4::XYZW: return "XYZW";
    default: return std::format("LaneMask4::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(LoadCacheOp value) {
  switch (value) {
    case LoadCacheOp::CS: return "CS";
    case LoadCacheOp::LU: return "LU";
    case LoadCacheOp::CI: return "CI";
    case LoadCacheOp::CV: return "CV";
    default: return std::format("LoadCacheOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(MN value) {
  switch (value) {
    case MN::MN: return "MN";
    case MN::MX: return "MX";
    default: return std::format("MN::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(MRG value) {
  switch (value) {
    case MRG::noMRG: return "noMRG";
    case MRG::MRG: return "MRG";
    default: return std::format("MRG::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(MS value) {
  switch (value) {
    case MS::noMS: return "noMS";
    case MS::MS: return "MS";
    default: return std::format("MS::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(MSI value) {
  switch (value) {
    case MSI::C: return "C";
    case MSI::INVALIDMSI3: return "INVALIDMSI3";
    case MSI::CENTROID: return "CENTROID";
    case MSI::OFFSET: return "OFFSET";
    default: return std::format("MSI::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(MemBarIvall value) {
  switch (value) {
    case MemBarIvall::NOIVALL: return "NOIVALL";
    case MemBarIvall::IVALLD: return "IVALLD";
    case MemBarIvall::IVALLT: return "IVALLT";
    case MemBarIvall::IVALLTD: return "IVALLTD";
    default: return std::format("MemBarIvall::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(MemBarLevel value) {
  switch (value) {
    case MemBarLevel::CTA: return "CTA";
    case MemBarLevel::GL: return "GL";
    case MemBarLevel::SYS: return "SYS";
    case MemBarLevel::VC: return "VC";
    default: return std::format("MemBarLevel::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(MufuOp value) {
  switch (value) {
    case MufuOp::COS: return "COS";
    case MufuOp::SIN: return "SIN";
    case MufuOp::EX2: return "EX2";
    case MufuOp::LG2: return "LG2";
    case MufuOp::RCP: return "RCP";
    case MufuOp::RSQ: return "RSQ";
    case MufuOp::RCP64H: return "RCP64H";
    case MufuOp::RSQ64H: return "RSQ64H";
    case MufuOp::SQRT: return "SQRT";
    case MufuOp::INVALIDMUFUOPCODE9: return "INVALIDMUFUOPCODE9";
    case MufuOp::INVALIDMUFUOPCODEA: return "INVALIDMUFUOPCODEA";
    case MufuOp::INVALIDMUFUOPCODEB: return "INVALIDMUFUOPCODEB";
    case MufuOp::INVALIDMUFUOPCODEC: return "INVALIDMUFUOPCODEC";
    case MufuOp::INVALIDMUFUOPCODED: return "INVALIDMUFUOPCODED";
    case MufuOp::INVALIDMUFUOPCODEE: return "INVALIDMUFUOPCODEE";
    case MufuOp::INVALIDMUFUOPCODEF: return "INVALIDMUFUOPCODEF";
    default: return std::format("MufuOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(NDV value) {
  switch (value) {
    case NDV::noNDV: return "noNDV";
    case NDV::NDV: return "NDV";
    default: return std::format("NDV::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(NODEP value) {
  switch (value) {
    case NODEP::noNODEP: return "noNODEP";
    case NODEP::NODEP: return "NODEP";
    default: return std::format("NODEP::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(NonZeroRegister value) {
  switch (value) {
    case NonZeroRegister::R00: return "R00";
    case NonZeroRegister::R01: return "R01";
    case NonZeroRegister::R02: return "R02";
    case NonZeroRegister::R03: return "R03";
    case NonZeroRegister::R04: return "R04";
    case NonZeroRegister::R05: return "R05";
    case NonZeroRegister::R06: return "R06";
    case NonZeroRegister::R07: return "R07";
    case NonZeroRegister::R08: return "R08";
    case NonZeroRegister::R09: return "R09";
    case NonZeroRegister::R10: return "R10";
    case NonZeroRegister::R11: return "R11";
    case NonZeroRegister::R12: return "R12";
    case NonZeroRegister::R13: return "R13";
    case NonZeroRegister::R14: return "R14";
    case NonZeroRegister::R15: return "R15";
    case NonZeroRegister::R16: return "R16";
    case NonZeroRegister::R17: return "R17";
    case NonZeroRegister::R18: return "R18";
    case NonZeroRegister::R19: return "R19";
    case NonZeroRegister::R20: return "R20";
    case NonZeroRegister::R21: return "R21";
    case NonZeroRegister::R22: return "R22";
    case NonZeroRegister::R23: return "R23";
    case NonZeroRegister::R24: return "R24";
    case NonZeroRegister::R25: return "R25";
    case NonZeroRegister::R26: return "R26";
    case NonZeroRegister::R27: return "R27";
    case NonZeroRegister::R28: return "R28";
    case NonZeroRegister::R29: return "R29";
    case NonZeroRegister::R30: return "R30";
    case NonZeroRegister::R31: return "R31";
    case NonZeroRegister::R32: return "R32";
    case NonZeroRegister::R33: return "R33";
    case NonZeroRegister::R34: return "R34";
    case NonZeroRegister::R35: return "R35";
    case NonZeroRegister::R36: return "R36";
    case NonZeroRegister::R37: return "R37";
    case NonZeroRegister::R38: return "R38";
    case NonZeroRegister::R39: return "R39";
    case NonZeroRegister::R40: return "R40";
    case NonZeroRegister::R41: return "R41";
    case NonZeroRegister::R42: return "R42";
    case NonZeroRegister::R43: return "R43";
    case NonZeroRegister::R44: return "R44";
    case NonZeroRegister::R45: return "R45";
    case NonZeroRegister::R46: return "R46";
    case NonZeroRegister::R47: return "R47";
    case NonZeroRegister::R48: return "R48";
    case NonZeroRegister::R49: return "R49";
    case NonZeroRegister::R50: return "R50";
    case NonZeroRegister::R51: return "R51";
    case NonZeroRegister::R52: return "R52";
    case NonZeroRegister::R53: return "R53";
    case NonZeroRegister::R54: return "R54";
    case NonZeroRegister::R55: return "R55";
    case NonZeroRegister::R56: return "R56";
    case NonZeroRegister::R57: return "R57";
    case NonZeroRegister::R58: return "R58";
    case NonZeroRegister::R59: return "R59";
    case NonZeroRegister::R60: return "R60";
    case NonZeroRegister::R61: return "R61";
    case NonZeroRegister::R62: return "R62";
    case NonZeroRegister::R63: return "R63";
    case NonZeroRegister::R64: return "R64";
    case NonZeroRegister::R65: return "R65";
    case NonZeroRegister::R66: return "R66";
    case NonZeroRegister::R67: return "R67";
    case NonZeroRegister::R68: return "R68";
    case NonZeroRegister::R69: return "R69";
    case NonZeroRegister::R70: return "R70";
    case NonZeroRegister::R71: return "R71";
    case NonZeroRegister::R72: return "R72";
    case NonZeroRegister::R73: return "R73";
    case NonZeroRegister::R74: return "R74";
    case NonZeroRegister::R75: return "R75";
    case NonZeroRegister::R76: return "R76";
    case NonZeroRegister::R77: return "R77";
    case NonZeroRegister::R78: return "R78";
    case NonZeroRegister::R79: return "R79";
    case NonZeroRegister::R80: return "R80";
    case NonZeroRegister::R81: return "R81";
    case NonZeroRegister::R82: return "R82";
    case NonZeroRegister::R83: return "R83";
    case NonZeroRegister::R84: return "R84";
    case NonZeroRegister::R85: return "R85";
    case NonZeroRegister::R86: return "R86";
    case NonZeroRegister::R87: return "R87";
    case NonZeroRegister::R88: return "R88";
    case NonZeroRegister::R89: return "R89";
    case NonZeroRegister::R90: return "R90";
    case NonZeroRegister::R91: return "R91";
    case NonZeroRegister::R92: return "R92";
    case NonZeroRegister::R93: return "R93";
    case NonZeroRegister::R94: return "R94";
    case NonZeroRegister::R95: return "R95";
    case NonZeroRegister::R96: return "R96";
    case NonZeroRegister::R97: return "R97";
    case NonZeroRegister::R98: return "R98";
    case NonZeroRegister::R99: return "R99";
    case NonZeroRegister::R100: return "R100";
    case NonZeroRegister::R101: return "R101";
    case NonZeroRegister::R102: return "R102";
    case NonZeroRegister::R103: return "R103";
    case NonZeroRegister::R104: return "R104";
    case NonZeroRegister::R105: return "R105";
    case NonZeroRegister::R106: return "R106";
    case NonZeroRegister::R107: return "R107";
    case NonZeroRegister::R108: return "R108";
    case NonZeroRegister::R109: return "R109";
    case NonZeroRegister::R110: return "R110";
    case NonZeroRegister::R111: return "R111";
    case NonZeroRegister::R112: return "R112";
    case NonZeroRegister::R113: return "R113";
    case NonZeroRegister::R114: return "R114";
    case NonZeroRegister::R115: return "R115";
    case NonZeroRegister::R116: return "R116";
    case NonZeroRegister::R117: return "R117";
    case NonZeroRegister::R118: return "R118";
    case NonZeroRegister::R119: return "R119";
    case NonZeroRegister::R120: return "R120";
    case NonZeroRegister::R121: return "R121";
    case NonZeroRegister::R122: return "R122";
    case NonZeroRegister::R123: return "R123";
    case NonZeroRegister::R124: return "R124";
    case NonZeroRegister::R125: return "R125";
    case NonZeroRegister::R126: return "R126";
    case NonZeroRegister::R127: return "R127";
    case NonZeroRegister::R128: return "R128";
    case NonZeroRegister::R129: return "R129";
    case NonZeroRegister::R130: return "R130";
    case NonZeroRegister::R131: return "R131";
    case NonZeroRegister::R132: return "R132";
    case NonZeroRegister::R133: return "R133";
    case NonZeroRegister::R134: return "R134";
    case NonZeroRegister::R135: return "R135";
    case NonZeroRegister::R136: return "R136";
    case NonZeroRegister::R137: return "R137";
    case NonZeroRegister::R138: return "R138";
    case NonZeroRegister::R139: return "R139";
    case NonZeroRegister::R140: return "R140";
    case NonZeroRegister::R141: return "R141";
    case NonZeroRegister::R142: return "R142";
    case NonZeroRegister::R143: return "R143";
    case NonZeroRegister::R144: return "R144";
    case NonZeroRegister::R145: return "R145";
    case NonZeroRegister::R146: return "R146";
    case NonZeroRegister::R147: return "R147";
    case NonZeroRegister::R148: return "R148";
    case NonZeroRegister::R149: return "R149";
    case NonZeroRegister::R150: return "R150";
    case NonZeroRegister::R151: return "R151";
    case NonZeroRegister::R152: return "R152";
    case NonZeroRegister::R153: return "R153";
    case NonZeroRegister::R154: return "R154";
    case NonZeroRegister::R155: return "R155";
    case NonZeroRegister::R156: return "R156";
    case NonZeroRegister::R157: return "R157";
    case NonZeroRegister::R158: return "R158";
    case NonZeroRegister::R159: return "R159";
    case NonZeroRegister::R160: return "R160";
    case NonZeroRegister::R161: return "R161";
    case NonZeroRegister::R162: return "R162";
    case NonZeroRegister::R163: return "R163";
    case NonZeroRegister::R164: return "R164";
    case NonZeroRegister::R165: return "R165";
    case NonZeroRegister::R166: return "R166";
    case NonZeroRegister::R167: return "R167";
    case NonZeroRegister::R168: return "R168";
    case NonZeroRegister::R169: return "R169";
    case NonZeroRegister::R170: return "R170";
    case NonZeroRegister::R171: return "R171";
    case NonZeroRegister::R172: return "R172";
    case NonZeroRegister::R173: return "R173";
    case NonZeroRegister::R174: return "R174";
    case NonZeroRegister::R175: return "R175";
    case NonZeroRegister::R176: return "R176";
    case NonZeroRegister::R177: return "R177";
    case NonZeroRegister::R178: return "R178";
    case NonZeroRegister::R179: return "R179";
    case NonZeroRegister::R180: return "R180";
    case NonZeroRegister::R181: return "R181";
    case NonZeroRegister::R182: return "R182";
    case NonZeroRegister::R183: return "R183";
    case NonZeroRegister::R184: return "R184";
    case NonZeroRegister::R185: return "R185";
    case NonZeroRegister::R186: return "R186";
    case NonZeroRegister::R187: return "R187";
    case NonZeroRegister::R188: return "R188";
    case NonZeroRegister::R189: return "R189";
    case NonZeroRegister::R190: return "R190";
    case NonZeroRegister::R191: return "R191";
    case NonZeroRegister::R192: return "R192";
    case NonZeroRegister::R193: return "R193";
    case NonZeroRegister::R194: return "R194";
    case NonZeroRegister::R195: return "R195";
    case NonZeroRegister::R196: return "R196";
    case NonZeroRegister::R197: return "R197";
    case NonZeroRegister::R198: return "R198";
    case NonZeroRegister::R199: return "R199";
    case NonZeroRegister::R200: return "R200";
    case NonZeroRegister::R201: return "R201";
    case NonZeroRegister::R202: return "R202";
    case NonZeroRegister::R203: return "R203";
    case NonZeroRegister::R204: return "R204";
    case NonZeroRegister::R205: return "R205";
    case NonZeroRegister::R206: return "R206";
    case NonZeroRegister::R207: return "R207";
    case NonZeroRegister::R208: return "R208";
    case NonZeroRegister::R209: return "R209";
    case NonZeroRegister::R210: return "R210";
    case NonZeroRegister::R211: return "R211";
    case NonZeroRegister::R212: return "R212";
    case NonZeroRegister::R213: return "R213";
    case NonZeroRegister::R214: return "R214";
    case NonZeroRegister::R215: return "R215";
    case NonZeroRegister::R216: return "R216";
    case NonZeroRegister::R217: return "R217";
    case NonZeroRegister::R218: return "R218";
    case NonZeroRegister::R219: return "R219";
    case NonZeroRegister::R220: return "R220";
    case NonZeroRegister::R221: return "R221";
    case NonZeroRegister::R222: return "R222";
    case NonZeroRegister::R223: return "R223";
    case NonZeroRegister::R224: return "R224";
    case NonZeroRegister::R225: return "R225";
    case NonZeroRegister::R226: return "R226";
    case NonZeroRegister::R227: return "R227";
    case NonZeroRegister::R228: return "R228";
    case NonZeroRegister::R229: return "R229";
    case NonZeroRegister::R230: return "R230";
    case NonZeroRegister::R231: return "R231";
    case NonZeroRegister::R232: return "R232";
    case NonZeroRegister::R233: return "R233";
    case NonZeroRegister::R234: return "R234";
    case NonZeroRegister::R235: return "R235";
    case NonZeroRegister::R236: return "R236";
    case NonZeroRegister::R237: return "R237";
    case NonZeroRegister::R238: return "R238";
    case NonZeroRegister::R239: return "R239";
    case NonZeroRegister::R240: return "R240";
    case NonZeroRegister::R241: return "R241";
    case NonZeroRegister::R242: return "R242";
    case NonZeroRegister::R243: return "R243";
    case NonZeroRegister::R244: return "R244";
    case NonZeroRegister::R245: return "R245";
    case NonZeroRegister::R246: return "R246";
    case NonZeroRegister::R247: return "R247";
    case NonZeroRegister::R248: return "R248";
    case NonZeroRegister::R249: return "R249";
    case NonZeroRegister::R250: return "R250";
    case NonZeroRegister::R251: return "R251";
    case NonZeroRegister::R252: return "R252";
    case NonZeroRegister::R253: return "R253";
    case NonZeroRegister::R254: return "R254";
    default: return std::format("NonZeroRegister::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Ofmt_FP16 value) {
  switch (value) {
    case Ofmt_FP16::F16_V2: return "F16_V2";
    case Ofmt_FP16::F32: return "F32";
    case Ofmt_FP16::MRG_H0: return "MRG_H0";
    case Ofmt_FP16::MRG_H1: return "MRG_H1";
    default: return std::format("Ofmt_FP16::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(OnlyQry value) {
  switch (value) {
    case OnlyQry::QRY1: return "QRY1";
    default: return std::format("OnlyQry::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(OutType value) {
  switch (value) {
    case OutType::INVALIDOUTSTYPE0: return "INVALIDOUTSTYPE0";
    case OutType::EMIT: return "EMIT";
    case OutType::CUT: return "CUT";
    case OutType::EMIT_THEN_CUT: return "EMIT_THEN_CUT";
    default: return std::format("OutType::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(PMode value) {
  switch (value) {
    case PMode::IDX: return "IDX";
    case PMode::F4E: return "F4E";
    case PMode::B4E: return "B4E";
    case PMode::RC8: return "RC8";
    case PMode::ECL: return "ECL";
    case PMode::ECR: return "ECR";
    case PMode::RC16: return "RC16";
    case PMode::INVALIDPMODE7: return "INVALIDPMODE7";
    default: return std::format("PMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(PNWord value) {
  switch (value) {
    case PNWord::PPPPPPPP: return "PPPPPPPP";
    case PNWord::PPPPPPNP: return "PPPPPPNP";
    case PNWord::PPPPPPPN: return "PPPPPPPN";
    case PNWord::PPPPPPZP: return "PPPPPPZP";
    case PNWord::PPPPNPPP: return "PPPPNPPP";
    case PNWord::PPPPNPNP: return "PPPPNPNP";
    case PNWord::PPPPNPPN: return "PPPPNPPN";
    case PNWord::PPPPNPZP: return "PPPPNPZP";
    case PNWord::PPPPPNPP: return "PPPPPNPP";
    case PNWord::PPPPPNNP: return "PPPPPNNP";
    case PNWord::PPPPPNPN: return "PPPPPNPN";
    case PNWord::PPPPPNZP: return "PPPPPNZP";
    case PNWord::PPPPZPPP: return "PPPPZPPP";
    case PNWord::PPPPZPNP: return "PPPPZPNP";
    case PNWord::PPPPZPPN: return "PPPPZPPN";
    case PNWord::PPPPZPZP: return "PPPPZPZP";
    case PNWord::PPNPPPPP: return "PPNPPPPP";
    case PNWord::PPNPPPNP: return "PPNPPPNP";
    case PNWord::PPNPPPPN: return "PPNPPPPN";
    case PNWord::PPNPPPZP: return "PPNPPPZP";
    case PNWord::PPNPNPPP: return "PPNPNPPP";
    case PNWord::PPNPNPNP: return "PPNPNPNP";
    case PNWord::PPNPNPPN: return "PPNPNPPN";
    case PNWord::PPNPNPZP: return "PPNPNPZP";
    case PNWord::PPNPPNPP: return "PPNPPNPP";
    case PNWord::PPNPPNNP: return "PPNPPNNP";
    case PNWord::PPNPPNPN: return "PPNPPNPN";
    case PNWord::PPNPPNZP: return "PPNPPNZP";
    case PNWord::PPNPZPPP: return "PPNPZPPP";
    case PNWord::PPNPZPNP: return "PPNPZPNP";
    case PNWord::PPNPZPPN: return "PPNPZPPN";
    case PNWord::PPNPZPZP: return "PPNPZPZP";
    case PNWord::PPPNPPPP: return "PPPNPPPP";
    case PNWord::PPPNPPNP: return "PPPNPPNP";
    case PNWord::PPPNPPPN: return "PPPNPPPN";
    case PNWord::PPPNPPZP: return "PPPNPPZP";
    case PNWord::PPPNNPPP: return "PPPNNPPP";
    case PNWord::PPPNNPNP: return "PPPNNPNP";
    case PNWord::PPPNNPPN: return "PPPNNPPN";
    case PNWord::PPPNNPZP: return "PPPNNPZP";
    case PNWord::PPPNPNPP: return "PPPNPNPP";
    case PNWord::PPPNPNNP: return "PPPNPNNP";
    case PNWord::PPPNPNPN: return "PPPNPNPN";
    case PNWord::PPPNPNZP: return "PPPNPNZP";
    case PNWord::PPPNZPPP: return "PPPNZPPP";
    case PNWord::PPPNZPNP: return "PPPNZPNP";
    case PNWord::PPPNZPPN: return "PPPNZPPN";
    case PNWord::PPPNZPZP: return "PPPNZPZP";
    case PNWord::PPZPPPPP: return "PPZPPPPP";
    case PNWord::PPZPPPNP: return "PPZPPPNP";
    case PNWord::PPZPPPPN: return "PPZPPPPN";
    case PNWord::PPZPPPZP: return "PPZPPPZP";
    case PNWord::PPZPNPPP: return "PPZPNPPP";
    case PNWord::PPZPNPNP: return "PPZPNPNP";
    case PNWord::PPZPNPPN: return "PPZPNPPN";
    case PNWord::PPZPNPZP: return "PPZPNPZP";
    case PNWord::PPZPPNPP: return "PPZPPNPP";
    case PNWord::PPZPPNNP: return "PPZPPNNP";
    case PNWord::PPZPPNPN: return "PPZPPNPN";
    case PNWord::PPZPPNZP: return "PPZPPNZP";
    case PNWord::PPZPZPPP: return "PPZPZPPP";
    case PNWord::PPZPZPNP: return "PPZPZPNP";
    case PNWord::PPZPZPPN: return "PPZPZPPN";
    case PNWord::PPZPZPZP: return "PPZPZPZP";
    case PNWord::NPPPPPPP: return "NPPPPPPP";
    case PNWord::NPPPPPNP: return "NPPPPPNP";
    case PNWord::NPPPPPPN: return "NPPPPPPN";
    case PNWord::NPPPPPZP: return "NPPPPPZP";
    case PNWord::NPPPNPPP: return "NPPPNPPP";
    case PNWord::NPPPNPNP: return "NPPPNPNP";
    case PNWord::NPPPNPPN: return "NPPPNPPN";
    case PNWord::NPPPNPZP: return "NPPPNPZP";
    case PNWord::NPPPPNPP: return "NPPPPNPP";
    case PNWord::NPPPPNNP: return "NPPPPNNP";
    case PNWord::NPPPPNPN: return "NPPPPNPN";
    case PNWord::NPPPPNZP: return "NPPPPNZP";
    case PNWord::NPPPZPPP: return "NPPPZPPP";
    case PNWord::NPPPZPNP: return "NPPPZPNP";
    case PNWord::NPPPZPPN: return "NPPPZPPN";
    case PNWord::NPPPZPZP: return "NPPPZPZP";
    case PNWord::NPNPPPPP: return "NPNPPPPP";
    case PNWord::NPNPPPNP: return "NPNPPPNP";
    case PNWord::NPNPPPPN: return "NPNPPPPN";
    case PNWord::NPNPPPZP: return "NPNPPPZP";
    case PNWord::NPNPNPPP: return "NPNPNPPP";
    case PNWord::NPNPNPNP: return "NPNPNPNP";
    case PNWord::NPNPNPPN: return "NPNPNPPN";
    case PNWord::NPNPNPZP: return "NPNPNPZP";
    case PNWord::NPNPPNPP: return "NPNPPNPP";
    case PNWord::NPNPPNNP: return "NPNPPNNP";
    case PNWord::NPNPPNPN: return "NPNPPNPN";
    case PNWord::NPNPPNZP: return "NPNPPNZP";
    case PNWord::NPNPZPPP: return "NPNPZPPP";
    case PNWord::NPNPZPNP: return "NPNPZPNP";
    case PNWord::NPNPZPPN: return "NPNPZPPN";
    case PNWord::NPNPZPZP: return "NPNPZPZP";
    case PNWord::NPPNPPPP: return "NPPNPPPP";
    case PNWord::NPPNPPNP: return "NPPNPPNP";
    case PNWord::NPPNPPPN: return "NPPNPPPN";
    case PNWord::NPPNPPZP: return "NPPNPPZP";
    case PNWord::NPPNNPPP: return "NPPNNPPP";
    case PNWord::NPPNNPNP: return "NPPNNPNP";
    case PNWord::NPPNNPPN: return "NPPNNPPN";
    case PNWord::NPPNNPZP: return "NPPNNPZP";
    case PNWord::NPPNPNPP: return "NPPNPNPP";
    case PNWord::NPPNPNNP: return "NPPNPNNP";
    case PNWord::NPPNPNPN: return "NPPNPNPN";
    case PNWord::NPPNPNZP: return "NPPNPNZP";
    case PNWord::NPPNZPPP: return "NPPNZPPP";
    case PNWord::NPPNZPNP: return "NPPNZPNP";
    case PNWord::NPPNZPPN: return "NPPNZPPN";
    case PNWord::NPPNZPZP: return "NPPNZPZP";
    case PNWord::NPZPPPPP: return "NPZPPPPP";
    case PNWord::NPZPPPNP: return "NPZPPPNP";
    case PNWord::NPZPPPPN: return "NPZPPPPN";
    case PNWord::NPZPPPZP: return "NPZPPPZP";
    case PNWord::NPZPNPPP: return "NPZPNPPP";
    case PNWord::NPZPNPNP: return "NPZPNPNP";
    case PNWord::NPZPNPPN: return "NPZPNPPN";
    case PNWord::NPZPNPZP: return "NPZPNPZP";
    case PNWord::NPZPPNPP: return "NPZPPNPP";
    case PNWord::NPZPPNNP: return "NPZPPNNP";
    case PNWord::NPZPPNPN: return "NPZPPNPN";
    case PNWord::NPZPPNZP: return "NPZPPNZP";
    case PNWord::NPZPZPPP: return "NPZPZPPP";
    case PNWord::NPZPZPNP: return "NPZPZPNP";
    case PNWord::NPZPZPPN: return "NPZPZPPN";
    case PNWord::NPZPZPZP: return "NPZPZPZP";
    case PNWord::PNPPPPPP: return "PNPPPPPP";
    case PNWord::PNPPPPNP: return "PNPPPPNP";
    case PNWord::PNPPPPPN: return "PNPPPPPN";
    case PNWord::PNPPPPZP: return "PNPPPPZP";
    case PNWord::PNPPNPPP: return "PNPPNPPP";
    case PNWord::PNPPNPNP: return "PNPPNPNP";
    case PNWord::PNPPNPPN: return "PNPPNPPN";
    case PNWord::PNPPNPZP: return "PNPPNPZP";
    case PNWord::PNPPPNPP: return "PNPPPNPP";
    case PNWord::PNPPPNNP: return "PNPPPNNP";
    case PNWord::PNPPPNPN: return "PNPPPNPN";
    case PNWord::PNPPPNZP: return "PNPPPNZP";
    case PNWord::PNPPZPPP: return "PNPPZPPP";
    case PNWord::PNPPZPNP: return "PNPPZPNP";
    case PNWord::PNPPZPPN: return "PNPPZPPN";
    case PNWord::PNPPZPZP: return "PNPPZPZP";
    case PNWord::PNNPPPPP: return "PNNPPPPP";
    case PNWord::PNNPPPNP: return "PNNPPPNP";
    case PNWord::PNNPPPPN: return "PNNPPPPN";
    case PNWord::PNNPPPZP: return "PNNPPPZP";
    case PNWord::PNNPNPPP: return "PNNPNPPP";
    case PNWord::PNNPNPNP: return "PNNPNPNP";
    case PNWord::PNNPNPPN: return "PNNPNPPN";
    case PNWord::PNNPNPZP: return "PNNPNPZP";
    case PNWord::PNNPPNPP: return "PNNPPNPP";
    case PNWord::PNNPPNNP: return "PNNPPNNP";
    case PNWord::PNNPPNPN: return "PNNPPNPN";
    case PNWord::PNNPPNZP: return "PNNPPNZP";
    case PNWord::PNNPZPPP: return "PNNPZPPP";
    case PNWord::PNNPZPNP: return "PNNPZPNP";
    case PNWord::PNNPZPPN: return "PNNPZPPN";
    case PNWord::PNNPZPZP: return "PNNPZPZP";
    case PNWord::PNPNPPPP: return "PNPNPPPP";
    case PNWord::PNPNPPNP: return "PNPNPPNP";
    case PNWord::PNPNPPPN: return "PNPNPPPN";
    case PNWord::PNPNPPZP: return "PNPNPPZP";
    case PNWord::PNPNNPPP: return "PNPNNPPP";
    case PNWord::PNPNNPNP: return "PNPNNPNP";
    case PNWord::PNPNNPPN: return "PNPNNPPN";
    case PNWord::PNPNNPZP: return "PNPNNPZP";
    case PNWord::PNPNPNPP: return "PNPNPNPP";
    case PNWord::PNPNPNNP: return "PNPNPNNP";
    case PNWord::PNPNPNPN: return "PNPNPNPN";
    case PNWord::PNPNPNZP: return "PNPNPNZP";
    case PNWord::PNPNZPPP: return "PNPNZPPP";
    case PNWord::PNPNZPNP: return "PNPNZPNP";
    case PNWord::PNPNZPPN: return "PNPNZPPN";
    case PNWord::PNPNZPZP: return "PNPNZPZP";
    case PNWord::PNZPPPPP: return "PNZPPPPP";
    case PNWord::PNZPPPNP: return "PNZPPPNP";
    case PNWord::PNZPPPPN: return "PNZPPPPN";
    case PNWord::PNZPPPZP: return "PNZPPPZP";
    case PNWord::PNZPNPPP: return "PNZPNPPP";
    case PNWord::PNZPNPNP: return "PNZPNPNP";
    case PNWord::PNZPNPPN: return "PNZPNPPN";
    case PNWord::PNZPNPZP: return "PNZPNPZP";
    case PNWord::PNZPPNPP: return "PNZPPNPP";
    case PNWord::PNZPPNNP: return "PNZPPNNP";
    case PNWord::PNZPPNPN: return "PNZPPNPN";
    case PNWord::PNZPPNZP: return "PNZPPNZP";
    case PNWord::PNZPZPPP: return "PNZPZPPP";
    case PNWord::PNZPZPNP: return "PNZPZPNP";
    case PNWord::PNZPZPPN: return "PNZPZPPN";
    case PNWord::PNZPZPZP: return "PNZPZPZP";
    case PNWord::ZPPPPPPP: return "ZPPPPPPP";
    case PNWord::ZPPPPPNP: return "ZPPPPPNP";
    case PNWord::ZPPPPPPN: return "ZPPPPPPN";
    case PNWord::ZPPPPPZP: return "ZPPPPPZP";
    case PNWord::ZPPPNPPP: return "ZPPPNPPP";
    case PNWord::ZPPPNPNP: return "ZPPPNPNP";
    case PNWord::ZPPPNPPN: return "ZPPPNPPN";
    case PNWord::ZPPPNPZP: return "ZPPPNPZP";
    case PNWord::ZPPPPNPP: return "ZPPPPNPP";
    case PNWord::ZPPPPNNP: return "ZPPPPNNP";
    case PNWord::ZPPPPNPN: return "ZPPPPNPN";
    case PNWord::ZPPPPNZP: return "ZPPPPNZP";
    case PNWord::ZPPPZPPP: return "ZPPPZPPP";
    case PNWord::ZPPPZPNP: return "ZPPPZPNP";
    case PNWord::ZPPPZPPN: return "ZPPPZPPN";
    case PNWord::ZPPPZPZP: return "ZPPPZPZP";
    case PNWord::ZPNPPPPP: return "ZPNPPPPP";
    case PNWord::ZPNPPPNP: return "ZPNPPPNP";
    case PNWord::ZPNPPPPN: return "ZPNPPPPN";
    case PNWord::ZPNPPPZP: return "ZPNPPPZP";
    case PNWord::ZPNPNPPP: return "ZPNPNPPP";
    case PNWord::ZPNPNPNP: return "ZPNPNPNP";
    case PNWord::ZPNPNPPN: return "ZPNPNPPN";
    case PNWord::ZPNPNPZP: return "ZPNPNPZP";
    case PNWord::ZPNPPNPP: return "ZPNPPNPP";
    case PNWord::ZPNPPNNP: return "ZPNPPNNP";
    case PNWord::ZPNPPNPN: return "ZPNPPNPN";
    case PNWord::ZPNPPNZP: return "ZPNPPNZP";
    case PNWord::ZPNPZPPP: return "ZPNPZPPP";
    case PNWord::ZPNPZPNP: return "ZPNPZPNP";
    case PNWord::ZPNPZPPN: return "ZPNPZPPN";
    case PNWord::ZPNPZPZP: return "ZPNPZPZP";
    case PNWord::ZPPNPPPP: return "ZPPNPPPP";
    case PNWord::ZPPNPPNP: return "ZPPNPPNP";
    case PNWord::ZPPNPPPN: return "ZPPNPPPN";
    case PNWord::ZPPNPPZP: return "ZPPNPPZP";
    case PNWord::ZPPNNPPP: return "ZPPNNPPP";
    case PNWord::ZPPNNPNP: return "ZPPNNPNP";
    case PNWord::ZPPNNPPN: return "ZPPNNPPN";
    case PNWord::ZPPNNPZP: return "ZPPNNPZP";
    case PNWord::ZPPNPNPP: return "ZPPNPNPP";
    case PNWord::ZPPNPNNP: return "ZPPNPNNP";
    case PNWord::ZPPNPNPN: return "ZPPNPNPN";
    case PNWord::ZPPNPNZP: return "ZPPNPNZP";
    case PNWord::ZPPNZPPP: return "ZPPNZPPP";
    case PNWord::ZPPNZPNP: return "ZPPNZPNP";
    case PNWord::ZPPNZPPN: return "ZPPNZPPN";
    case PNWord::ZPPNZPZP: return "ZPPNZPZP";
    case PNWord::ZPZPPPPP: return "ZPZPPPPP";
    case PNWord::ZPZPPPNP: return "ZPZPPPNP";
    case PNWord::ZPZPPPPN: return "ZPZPPPPN";
    case PNWord::ZPZPPPZP: return "ZPZPPPZP";
    case PNWord::ZPZPNPPP: return "ZPZPNPPP";
    case PNWord::ZPZPNPNP: return "ZPZPNPNP";
    case PNWord::ZPZPNPPN: return "ZPZPNPPN";
    case PNWord::ZPZPNPZP: return "ZPZPNPZP";
    case PNWord::ZPZPPNPP: return "ZPZPPNPP";
    case PNWord::ZPZPPNNP: return "ZPZPPNNP";
    case PNWord::ZPZPPNPN: return "ZPZPPNPN";
    case PNWord::ZPZPPNZP: return "ZPZPPNZP";
    case PNWord::ZPZPZPPP: return "ZPZPZPPP";
    case PNWord::ZPZPZPNP: return "ZPZPZPNP";
    case PNWord::ZPZPZPPN: return "ZPZPZPPN";
    case PNWord::ZPZPZPZP: return "ZPZPZPZP";
    default: return std::format("PNWord::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(PO value) {
  switch (value) {
    case PO::noPO: return "noPO";
    case PO::PO: return "PO";
    default: return std::format("PO::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(POP value) {
  switch (value) {
    case POP::F: return "F";
    case POP::T: return "T";
    case POP::Z: return "Z";
    case POP::NZ: return "NZ";
    default: return std::format("POP::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(POnly value) {
  switch (value) {
    case POnly::P: return "P";
    default: return std::format("POnly::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(PSL value) {
  switch (value) {
    case PSL::noPSL: return "noPSL";
    case PSL::PSL: return "PSL";
    default: return std::format("PSL::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ParamA value) {
  switch (value) {
    case ParamA::_1D: return "_1D";
    case ParamA::RECT: return "RECT";
    case ParamA::_3D: return "_3D";
    case ParamA::CUBE: return "CUBE";
    case ParamA::ARRAY_1D: return "ARRAY_1D";
    case ParamA::ARRAY_RECT: return "ARRAY_RECT";
    case ParamA::ARRAY_3D: return "ARRAY_3D";
    case ParamA::CUBEARRAY: return "CUBEARRAY";
    default: return std::format("ParamA::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Partsel value) {
  switch (value) {
    case Partsel::_32: return "32";
    case Partsel::H0: return "H0";
    case Partsel::H1: return "H1";
    default: return std::format("Partsel::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Phys value) {
  switch (value) {
    case Phys::PHYS: return "PHYS";
    default: return std::format("Phys::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(PixMode value) {
  switch (value) {
    case PixMode::MSCOUNT: return "MSCOUNT";
    case PixMode::COVMASK: return "COVMASK";
    case PixMode::COVERED: return "COVERED";
    case PixMode::OFFSET: return "OFFSET";
    case PixMode::CENTROID_OFFSET: return "CENTROID_OFFSET";
    case PixMode::MY_INDEX: return "MY_INDEX";
    case PixMode::INVALIDPIXMODE6: return "INVALIDPIXMODE6";
    case PixMode::INVALIDPIXMODE7: return "INVALIDPIXMODE7";
    default: return std::format("PixMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Predicate value) {
  switch (value) {
    case Predicate::P0: return "P0";
    case Predicate::P1: return "P1";
    case Predicate::P2: return "P2";
    case Predicate::P3: return "P3";
    case Predicate::P4: return "P4";
    case Predicate::P5: return "P5";
    case Predicate::P6: return "P6";
    case Predicate::P7: return "P7";
    default: return std::format("Predicate::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(RD value) {
  switch (value) {
    case RD::rd: return "rd";
    default: return std::format("RD::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(REQ value) {
  switch (value) {
    case REQ::req: return "req";
    default: return std::format("REQ::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(REUSE value) {
  switch (value) {
    case REUSE::reuse: return "reuse";
    case REUSE::noreuse: return "noreuse";
    default: return std::format("REUSE::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(RGBA value) {
  switch (value) {
    case RGBA::INVALIDRGBAMASK1: return "INVALIDRGBAMASK1";
    case RGBA::INVALIDRGBAMASK2: return "INVALIDRGBAMASK2";
    case RGBA::INVALIDRGBAMASK3: return "INVALIDRGBAMASK3";
    case RGBA::INVALIDRGBAMASK4: return "INVALIDRGBAMASK4";
    case RGBA::INVALIDRGBAMASK5: return "INVALIDRGBAMASK5";
    case RGBA::INVALIDRGBAMASK6: return "INVALIDRGBAMASK6";
    case RGBA::INVALIDRGBAMASK7: return "INVALIDRGBAMASK7";
    case RGBA::INVALIDRGBAMASK8: return "INVALIDRGBAMASK8";
    case RGBA::INVALIDRGBAMASK9: return "INVALIDRGBAMASK9";
    case RGBA::INVALIDRGBAMASK10: return "INVALIDRGBAMASK10";
    case RGBA::INVALIDRGBAMASK11: return "INVALIDRGBAMASK11";
    case RGBA::INVALIDRGBAMASK12: return "INVALIDRGBAMASK12";
    case RGBA::INVALIDRGBAMASK13: return "INVALIDRGBAMASK13";
    case RGBA::INVALIDRGBAMASK14: return "INVALIDRGBAMASK14";
    case RGBA::INVALIDRGBAMASK15: return "INVALIDRGBAMASK15";
    default: return std::format("RGBA::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(RROOp value) {
  switch (value) {
    case RROOp::SINCOS: return "SINCOS";
    case RROOp::EX2: return "EX2";
    default: return std::format("RROOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(RTTOp value) {
  switch (value) {
    case RTTOp::POPCRS: return "POPCRS";
    case RTTOp::TERMINATE: return "TERMINATE";
    case RTTOp::FALLTHROUGH: return "FALLTHROUGH";
    case RTTOp::PREEMPTED: return "PREEMPTED";
    default: return std::format("RTTOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Red value) {
  switch (value) {
    case Red::POPC: return "POPC";
    case Red::AND: return "AND";
    case Red::OR: return "OR";
    case Red::INVALIDBARMODE3: return "INVALIDBARMODE3";
    default: return std::format("Red::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(RedOp value) {
  switch (value) {
    case RedOp::INVALIDREDOP0: return "INVALIDREDOP0";
    case RedOp::INVALIDREDOP1: return "INVALIDREDOP1";
    case RedOp::INVALIDREDOP2: return "INVALIDREDOP2";
    case RedOp::INVALIDREDOP3: return "INVALIDREDOP3";
    case RedOp::INVALIDREDOP4: return "INVALIDREDOP4";
    case RedOp::INVALIDREDOP5: return "INVALIDREDOP5";
    case RedOp::INVALIDREDOP6: return "INVALIDREDOP6";
    case RedOp::INVALIDREDOP7: return "INVALIDREDOP7";
    case RedOp::INVALIDREDOP8: return "INVALIDREDOP8";
    case RedOp::INVALIDREDOP9: return "INVALIDREDOP9";
    case RedOp::INVALIDREDOP10: return "INVALIDREDOP10";
    case RedOp::INVALIDREDOP11: return "INVALIDREDOP11";
    case RedOp::INVALIDREDOP12: return "INVALIDREDOP12";
    case RedOp::INVALIDREDOP13: return "INVALIDREDOP13";
    case RedOp::INVALIDREDOP14: return "INVALIDREDOP14";
    case RedOp::INVALIDREDOP15: return "INVALIDREDOP15";
    default: return std::format("RedOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Register value) {
  switch (value) {
    case static_cast<Register>(NonZeroRegister::R00): return "R00";
    case static_cast<Register>(NonZeroRegister::R01): return "R01";
    case static_cast<Register>(NonZeroRegister::R02): return "R02";
    case static_cast<Register>(NonZeroRegister::R03): return "R03";
    case static_cast<Register>(NonZeroRegister::R04): return "R04";
    case static_cast<Register>(NonZeroRegister::R05): return "R05";
    case static_cast<Register>(NonZeroRegister::R06): return "R06";
    case static_cast<Register>(NonZeroRegister::R07): return "R07";
    case static_cast<Register>(NonZeroRegister::R08): return "R08";
    case static_cast<Register>(NonZeroRegister::R09): return "R09";
    case static_cast<Register>(NonZeroRegister::R10): return "R10";
    case static_cast<Register>(NonZeroRegister::R11): return "R11";
    case static_cast<Register>(NonZeroRegister::R12): return "R12";
    case static_cast<Register>(NonZeroRegister::R13): return "R13";
    case static_cast<Register>(NonZeroRegister::R14): return "R14";
    case static_cast<Register>(NonZeroRegister::R15): return "R15";
    case static_cast<Register>(NonZeroRegister::R16): return "R16";
    case static_cast<Register>(NonZeroRegister::R17): return "R17";
    case static_cast<Register>(NonZeroRegister::R18): return "R18";
    case static_cast<Register>(NonZeroRegister::R19): return "R19";
    case static_cast<Register>(NonZeroRegister::R20): return "R20";
    case static_cast<Register>(NonZeroRegister::R21): return "R21";
    case static_cast<Register>(NonZeroRegister::R22): return "R22";
    case static_cast<Register>(NonZeroRegister::R23): return "R23";
    case static_cast<Register>(NonZeroRegister::R24): return "R24";
    case static_cast<Register>(NonZeroRegister::R25): return "R25";
    case static_cast<Register>(NonZeroRegister::R26): return "R26";
    case static_cast<Register>(NonZeroRegister::R27): return "R27";
    case static_cast<Register>(NonZeroRegister::R28): return "R28";
    case static_cast<Register>(NonZeroRegister::R29): return "R29";
    case static_cast<Register>(NonZeroRegister::R30): return "R30";
    case static_cast<Register>(NonZeroRegister::R31): return "R31";
    case static_cast<Register>(NonZeroRegister::R32): return "R32";
    case static_cast<Register>(NonZeroRegister::R33): return "R33";
    case static_cast<Register>(NonZeroRegister::R34): return "R34";
    case static_cast<Register>(NonZeroRegister::R35): return "R35";
    case static_cast<Register>(NonZeroRegister::R36): return "R36";
    case static_cast<Register>(NonZeroRegister::R37): return "R37";
    case static_cast<Register>(NonZeroRegister::R38): return "R38";
    case static_cast<Register>(NonZeroRegister::R39): return "R39";
    case static_cast<Register>(NonZeroRegister::R40): return "R40";
    case static_cast<Register>(NonZeroRegister::R41): return "R41";
    case static_cast<Register>(NonZeroRegister::R42): return "R42";
    case static_cast<Register>(NonZeroRegister::R43): return "R43";
    case static_cast<Register>(NonZeroRegister::R44): return "R44";
    case static_cast<Register>(NonZeroRegister::R45): return "R45";
    case static_cast<Register>(NonZeroRegister::R46): return "R46";
    case static_cast<Register>(NonZeroRegister::R47): return "R47";
    case static_cast<Register>(NonZeroRegister::R48): return "R48";
    case static_cast<Register>(NonZeroRegister::R49): return "R49";
    case static_cast<Register>(NonZeroRegister::R50): return "R50";
    case static_cast<Register>(NonZeroRegister::R51): return "R51";
    case static_cast<Register>(NonZeroRegister::R52): return "R52";
    case static_cast<Register>(NonZeroRegister::R53): return "R53";
    case static_cast<Register>(NonZeroRegister::R54): return "R54";
    case static_cast<Register>(NonZeroRegister::R55): return "R55";
    case static_cast<Register>(NonZeroRegister::R56): return "R56";
    case static_cast<Register>(NonZeroRegister::R57): return "R57";
    case static_cast<Register>(NonZeroRegister::R58): return "R58";
    case static_cast<Register>(NonZeroRegister::R59): return "R59";
    case static_cast<Register>(NonZeroRegister::R60): return "R60";
    case static_cast<Register>(NonZeroRegister::R61): return "R61";
    case static_cast<Register>(NonZeroRegister::R62): return "R62";
    case static_cast<Register>(NonZeroRegister::R63): return "R63";
    case static_cast<Register>(NonZeroRegister::R64): return "R64";
    case static_cast<Register>(NonZeroRegister::R65): return "R65";
    case static_cast<Register>(NonZeroRegister::R66): return "R66";
    case static_cast<Register>(NonZeroRegister::R67): return "R67";
    case static_cast<Register>(NonZeroRegister::R68): return "R68";
    case static_cast<Register>(NonZeroRegister::R69): return "R69";
    case static_cast<Register>(NonZeroRegister::R70): return "R70";
    case static_cast<Register>(NonZeroRegister::R71): return "R71";
    case static_cast<Register>(NonZeroRegister::R72): return "R72";
    case static_cast<Register>(NonZeroRegister::R73): return "R73";
    case static_cast<Register>(NonZeroRegister::R74): return "R74";
    case static_cast<Register>(NonZeroRegister::R75): return "R75";
    case static_cast<Register>(NonZeroRegister::R76): return "R76";
    case static_cast<Register>(NonZeroRegister::R77): return "R77";
    case static_cast<Register>(NonZeroRegister::R78): return "R78";
    case static_cast<Register>(NonZeroRegister::R79): return "R79";
    case static_cast<Register>(NonZeroRegister::R80): return "R80";
    case static_cast<Register>(NonZeroRegister::R81): return "R81";
    case static_cast<Register>(NonZeroRegister::R82): return "R82";
    case static_cast<Register>(NonZeroRegister::R83): return "R83";
    case static_cast<Register>(NonZeroRegister::R84): return "R84";
    case static_cast<Register>(NonZeroRegister::R85): return "R85";
    case static_cast<Register>(NonZeroRegister::R86): return "R86";
    case static_cast<Register>(NonZeroRegister::R87): return "R87";
    case static_cast<Register>(NonZeroRegister::R88): return "R88";
    case static_cast<Register>(NonZeroRegister::R89): return "R89";
    case static_cast<Register>(NonZeroRegister::R90): return "R90";
    case static_cast<Register>(NonZeroRegister::R91): return "R91";
    case static_cast<Register>(NonZeroRegister::R92): return "R92";
    case static_cast<Register>(NonZeroRegister::R93): return "R93";
    case static_cast<Register>(NonZeroRegister::R94): return "R94";
    case static_cast<Register>(NonZeroRegister::R95): return "R95";
    case static_cast<Register>(NonZeroRegister::R96): return "R96";
    case static_cast<Register>(NonZeroRegister::R97): return "R97";
    case static_cast<Register>(NonZeroRegister::R98): return "R98";
    case static_cast<Register>(NonZeroRegister::R99): return "R99";
    case static_cast<Register>(NonZeroRegister::R100): return "R100";
    case static_cast<Register>(NonZeroRegister::R101): return "R101";
    case static_cast<Register>(NonZeroRegister::R102): return "R102";
    case static_cast<Register>(NonZeroRegister::R103): return "R103";
    case static_cast<Register>(NonZeroRegister::R104): return "R104";
    case static_cast<Register>(NonZeroRegister::R105): return "R105";
    case static_cast<Register>(NonZeroRegister::R106): return "R106";
    case static_cast<Register>(NonZeroRegister::R107): return "R107";
    case static_cast<Register>(NonZeroRegister::R108): return "R108";
    case static_cast<Register>(NonZeroRegister::R109): return "R109";
    case static_cast<Register>(NonZeroRegister::R110): return "R110";
    case static_cast<Register>(NonZeroRegister::R111): return "R111";
    case static_cast<Register>(NonZeroRegister::R112): return "R112";
    case static_cast<Register>(NonZeroRegister::R113): return "R113";
    case static_cast<Register>(NonZeroRegister::R114): return "R114";
    case static_cast<Register>(NonZeroRegister::R115): return "R115";
    case static_cast<Register>(NonZeroRegister::R116): return "R116";
    case static_cast<Register>(NonZeroRegister::R117): return "R117";
    case static_cast<Register>(NonZeroRegister::R118): return "R118";
    case static_cast<Register>(NonZeroRegister::R119): return "R119";
    case static_cast<Register>(NonZeroRegister::R120): return "R120";
    case static_cast<Register>(NonZeroRegister::R121): return "R121";
    case static_cast<Register>(NonZeroRegister::R122): return "R122";
    case static_cast<Register>(NonZeroRegister::R123): return "R123";
    case static_cast<Register>(NonZeroRegister::R124): return "R124";
    case static_cast<Register>(NonZeroRegister::R125): return "R125";
    case static_cast<Register>(NonZeroRegister::R126): return "R126";
    case static_cast<Register>(NonZeroRegister::R127): return "R127";
    case static_cast<Register>(NonZeroRegister::R128): return "R128";
    case static_cast<Register>(NonZeroRegister::R129): return "R129";
    case static_cast<Register>(NonZeroRegister::R130): return "R130";
    case static_cast<Register>(NonZeroRegister::R131): return "R131";
    case static_cast<Register>(NonZeroRegister::R132): return "R132";
    case static_cast<Register>(NonZeroRegister::R133): return "R133";
    case static_cast<Register>(NonZeroRegister::R134): return "R134";
    case static_cast<Register>(NonZeroRegister::R135): return "R135";
    case static_cast<Register>(NonZeroRegister::R136): return "R136";
    case static_cast<Register>(NonZeroRegister::R137): return "R137";
    case static_cast<Register>(NonZeroRegister::R138): return "R138";
    case static_cast<Register>(NonZeroRegister::R139): return "R139";
    case static_cast<Register>(NonZeroRegister::R140): return "R140";
    case static_cast<Register>(NonZeroRegister::R141): return "R141";
    case static_cast<Register>(NonZeroRegister::R142): return "R142";
    case static_cast<Register>(NonZeroRegister::R143): return "R143";
    case static_cast<Register>(NonZeroRegister::R144): return "R144";
    case static_cast<Register>(NonZeroRegister::R145): return "R145";
    case static_cast<Register>(NonZeroRegister::R146): return "R146";
    case static_cast<Register>(NonZeroRegister::R147): return "R147";
    case static_cast<Register>(NonZeroRegister::R148): return "R148";
    case static_cast<Register>(NonZeroRegister::R149): return "R149";
    case static_cast<Register>(NonZeroRegister::R150): return "R150";
    case static_cast<Register>(NonZeroRegister::R151): return "R151";
    case static_cast<Register>(NonZeroRegister::R152): return "R152";
    case static_cast<Register>(NonZeroRegister::R153): return "R153";
    case static_cast<Register>(NonZeroRegister::R154): return "R154";
    case static_cast<Register>(NonZeroRegister::R155): return "R155";
    case static_cast<Register>(NonZeroRegister::R156): return "R156";
    case static_cast<Register>(NonZeroRegister::R157): return "R157";
    case static_cast<Register>(NonZeroRegister::R158): return "R158";
    case static_cast<Register>(NonZeroRegister::R159): return "R159";
    case static_cast<Register>(NonZeroRegister::R160): return "R160";
    case static_cast<Register>(NonZeroRegister::R161): return "R161";
    case static_cast<Register>(NonZeroRegister::R162): return "R162";
    case static_cast<Register>(NonZeroRegister::R163): return "R163";
    case static_cast<Register>(NonZeroRegister::R164): return "R164";
    case static_cast<Register>(NonZeroRegister::R165): return "R165";
    case static_cast<Register>(NonZeroRegister::R166): return "R166";
    case static_cast<Register>(NonZeroRegister::R167): return "R167";
    case static_cast<Register>(NonZeroRegister::R168): return "R168";
    case static_cast<Register>(NonZeroRegister::R169): return "R169";
    case static_cast<Register>(NonZeroRegister::R170): return "R170";
    case static_cast<Register>(NonZeroRegister::R171): return "R171";
    case static_cast<Register>(NonZeroRegister::R172): return "R172";
    case static_cast<Register>(NonZeroRegister::R173): return "R173";
    case static_cast<Register>(NonZeroRegister::R174): return "R174";
    case static_cast<Register>(NonZeroRegister::R175): return "R175";
    case static_cast<Register>(NonZeroRegister::R176): return "R176";
    case static_cast<Register>(NonZeroRegister::R177): return "R177";
    case static_cast<Register>(NonZeroRegister::R178): return "R178";
    case static_cast<Register>(NonZeroRegister::R179): return "R179";
    case static_cast<Register>(NonZeroRegister::R180): return "R180";
    case static_cast<Register>(NonZeroRegister::R181): return "R181";
    case static_cast<Register>(NonZeroRegister::R182): return "R182";
    case static_cast<Register>(NonZeroRegister::R183): return "R183";
    case static_cast<Register>(NonZeroRegister::R184): return "R184";
    case static_cast<Register>(NonZeroRegister::R185): return "R185";
    case static_cast<Register>(NonZeroRegister::R186): return "R186";
    case static_cast<Register>(NonZeroRegister::R187): return "R187";
    case static_cast<Register>(NonZeroRegister::R188): return "R188";
    case static_cast<Register>(NonZeroRegister::R189): return "R189";
    case static_cast<Register>(NonZeroRegister::R190): return "R190";
    case static_cast<Register>(NonZeroRegister::R191): return "R191";
    case static_cast<Register>(NonZeroRegister::R192): return "R192";
    case static_cast<Register>(NonZeroRegister::R193): return "R193";
    case static_cast<Register>(NonZeroRegister::R194): return "R194";
    case static_cast<Register>(NonZeroRegister::R195): return "R195";
    case static_cast<Register>(NonZeroRegister::R196): return "R196";
    case static_cast<Register>(NonZeroRegister::R197): return "R197";
    case static_cast<Register>(NonZeroRegister::R198): return "R198";
    case static_cast<Register>(NonZeroRegister::R199): return "R199";
    case static_cast<Register>(NonZeroRegister::R200): return "R200";
    case static_cast<Register>(NonZeroRegister::R201): return "R201";
    case static_cast<Register>(NonZeroRegister::R202): return "R202";
    case static_cast<Register>(NonZeroRegister::R203): return "R203";
    case static_cast<Register>(NonZeroRegister::R204): return "R204";
    case static_cast<Register>(NonZeroRegister::R205): return "R205";
    case static_cast<Register>(NonZeroRegister::R206): return "R206";
    case static_cast<Register>(NonZeroRegister::R207): return "R207";
    case static_cast<Register>(NonZeroRegister::R208): return "R208";
    case static_cast<Register>(NonZeroRegister::R209): return "R209";
    case static_cast<Register>(NonZeroRegister::R210): return "R210";
    case static_cast<Register>(NonZeroRegister::R211): return "R211";
    case static_cast<Register>(NonZeroRegister::R212): return "R212";
    case static_cast<Register>(NonZeroRegister::R213): return "R213";
    case static_cast<Register>(NonZeroRegister::R214): return "R214";
    case static_cast<Register>(NonZeroRegister::R215): return "R215";
    case static_cast<Register>(NonZeroRegister::R216): return "R216";
    case static_cast<Register>(NonZeroRegister::R217): return "R217";
    case static_cast<Register>(NonZeroRegister::R218): return "R218";
    case static_cast<Register>(NonZeroRegister::R219): return "R219";
    case static_cast<Register>(NonZeroRegister::R220): return "R220";
    case static_cast<Register>(NonZeroRegister::R221): return "R221";
    case static_cast<Register>(NonZeroRegister::R222): return "R222";
    case static_cast<Register>(NonZeroRegister::R223): return "R223";
    case static_cast<Register>(NonZeroRegister::R224): return "R224";
    case static_cast<Register>(NonZeroRegister::R225): return "R225";
    case static_cast<Register>(NonZeroRegister::R226): return "R226";
    case static_cast<Register>(NonZeroRegister::R227): return "R227";
    case static_cast<Register>(NonZeroRegister::R228): return "R228";
    case static_cast<Register>(NonZeroRegister::R229): return "R229";
    case static_cast<Register>(NonZeroRegister::R230): return "R230";
    case static_cast<Register>(NonZeroRegister::R231): return "R231";
    case static_cast<Register>(NonZeroRegister::R232): return "R232";
    case static_cast<Register>(NonZeroRegister::R233): return "R233";
    case static_cast<Register>(NonZeroRegister::R234): return "R234";
    case static_cast<Register>(NonZeroRegister::R235): return "R235";
    case static_cast<Register>(NonZeroRegister::R236): return "R236";
    case static_cast<Register>(NonZeroRegister::R237): return "R237";
    case static_cast<Register>(NonZeroRegister::R238): return "R238";
    case static_cast<Register>(NonZeroRegister::R239): return "R239";
    case static_cast<Register>(NonZeroRegister::R240): return "R240";
    case static_cast<Register>(NonZeroRegister::R241): return "R241";
    case static_cast<Register>(NonZeroRegister::R242): return "R242";
    case static_cast<Register>(NonZeroRegister::R243): return "R243";
    case static_cast<Register>(NonZeroRegister::R244): return "R244";
    case static_cast<Register>(NonZeroRegister::R245): return "R245";
    case static_cast<Register>(NonZeroRegister::R246): return "R246";
    case static_cast<Register>(NonZeroRegister::R247): return "R247";
    case static_cast<Register>(NonZeroRegister::R248): return "R248";
    case static_cast<Register>(NonZeroRegister::R249): return "R249";
    case static_cast<Register>(NonZeroRegister::R250): return "R250";
    case static_cast<Register>(NonZeroRegister::R251): return "R251";
    case static_cast<Register>(NonZeroRegister::R252): return "R252";
    case static_cast<Register>(NonZeroRegister::R253): return "R253";
    case static_cast<Register>(NonZeroRegister::R254): return "R254";
    case static_cast<Register>(ZeroRegister::RZ): return "RZ";
    default: return std::format("Register::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Round1 value) {
  switch (value) {
    case Round1::RN: return "RN";
    case Round1::RM: return "RM";
    case Round1::RP: return "RP";
    case Round1::RZ: return "RZ";
    default: return std::format("Round1::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Round3 value) {
  switch (value) {
    case Round3::ROUND: return "ROUND";
    case Round3::FLOOR: return "FLOOR";
    case Round3::CEIL: return "CEIL";
    case Round3::TRUNC: return "TRUNC";
    default: return std::format("Round3::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(S16 value) {
  switch (value) {
    case S16::S16: return "S16";
    default: return std::format("S16::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SAT value) {
  switch (value) {
    case SAT::noSAT: return "noSAT";
    case SAT::SAT: return "SAT";
    default: return std::format("SAT::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SH value) {
  switch (value) {
    case SH::noSH: return "noSH";
    case SH::SH: return "SH";
    default: return std::format("SH::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SHFXMode value) {
  switch (value) {
    case SHFXMode::NONE: return "NONE";
    case SHFXMode::HI: return "HI";
    case SHFXMode::X: return "X";
    case SHFXMode::XHI: return "XHI";
    default: return std::format("SHFXMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SHF_L value) {
  switch (value) {
    case SHF_L::L: return "L";
    default: return std::format("SHF_L::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SHF_R value) {
  switch (value) {
    case SHF_R::R: return "R";
    default: return std::format("SHF_R::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SInteger value) {
  switch (value) {
    case static_cast<SInteger>(SInteger16::S16): return "S16";
    case static_cast<SInteger>(SInteger64::S64): return "S64";
    case static_cast<SInteger>(SInteger8::S8): return "S8";
    case static_cast<SInteger>(SInteger32::S32): return "S32";
    default: return std::format("SInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SInteger32 value) {
  switch (value) {
    case SInteger32::S32: return "S32";
    default: return std::format("SInteger32::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SInteger64 value) {
  switch (value) {
    case SInteger64::S64: return "S64";
    default: return std::format("SInteger64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SInteger8 value) {
  switch (value) {
    case SInteger8::S8: return "S8";
    default: return std::format("SInteger8::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SKEW value) {
  switch (value) {
    case SKEW::noSKEW: return "noSKEW";
    case SKEW::SKEW: return "SKEW";
    default: return std::format("SKEW::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SQInteger value) {
  switch (value) {
    case SQInteger::U8: return "U8";
    case SQInteger::_32: return "32";
    case SQInteger::_64: return "64";
    case SQInteger::F32: return "F32";
    case SQInteger::F16x2_FTZ_RN: return "F16x2.FTZ.RN";
    case SQInteger::S32: return "S32";
    case SQInteger::S64: return "S64";
    case SQInteger::INVALIDATOMICSIZE6: return "INVALIDATOMICSIZE6";
    default: return std::format("SQInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(STPMode value) {
  switch (value) {
    case STPMode::noWAIT: return "noWAIT";
    case STPMode::WAIT: return "WAIT";
    default: return std::format("STPMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Scale value) {
  switch (value) {
    case Scale::NONE: return "NONE";
    case Scale::D2: return "D2";
    case Scale::D4: return "D4";
    case Scale::D8: return "D8";
    case Scale::M8: return "M8";
    case Scale::M4: return "M4";
    case Scale::M2: return "M2";
    case Scale::INVALIDSCALE37: return "INVALIDSCALE37";
    default: return std::format("Scale::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Scoreboard value) {
  switch (value) {
    case Scoreboard::SB0: return "SB0";
    case Scoreboard::SB1: return "SB1";
    case Scoreboard::SB2: return "SB2";
    case Scoreboard::SB3: return "SB3";
    case Scoreboard::SB4: return "SB4";
    case Scoreboard::SB5: return "SB5";
    default: return std::format("Scoreboard::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Shflmd value) {
  switch (value) {
    case Shflmd::IDX: return "IDX";
    case Shflmd::UP: return "UP";
    case Shflmd::DOWN: return "DOWN";
    case Shflmd::BFLY: return "BFLY";
    default: return std::format("Shflmd::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(SpecialRegister value) {
  switch (value) {
    case SpecialRegister::SR0: return "SR0";
    case SpecialRegister::SR1: return "SR1";
    case SpecialRegister::SR2: return "SR2";
    case SpecialRegister::SR3: return "SR3";
    case SpecialRegister::SR4: return "SR4";
    case SpecialRegister::SR5: return "SR5";
    case SpecialRegister::SR6: return "SR6";
    case SpecialRegister::SR7: return "SR7";
    case SpecialRegister::SR8: return "SR8";
    case SpecialRegister::SR9: return "SR9";
    case SpecialRegister::SR10: return "SR10";
    case SpecialRegister::SR11: return "SR11";
    case SpecialRegister::SR12: return "SR12";
    case SpecialRegister::SR13: return "SR13";
    case SpecialRegister::SR14: return "SR14";
    case SpecialRegister::SR15: return "SR15";
    case SpecialRegister::SR16: return "SR16";
    case SpecialRegister::SR17: return "SR17";
    case SpecialRegister::SR18: return "SR18";
    case SpecialRegister::SR19: return "SR19";
    case SpecialRegister::SR20: return "SR20";
    case SpecialRegister::SR21: return "SR21";
    case SpecialRegister::SR22: return "SR22";
    case SpecialRegister::SR23: return "SR23";
    case SpecialRegister::SR24: return "SR24";
    case SpecialRegister::SR25: return "SR25";
    case SpecialRegister::SR26: return "SR26";
    case SpecialRegister::SR27: return "SR27";
    case SpecialRegister::SR28: return "SR28";
    case SpecialRegister::SR29: return "SR29";
    case SpecialRegister::SR30: return "SR30";
    case SpecialRegister::SR31: return "SR31";
    case SpecialRegister::SR32: return "SR32";
    case SpecialRegister::SR33: return "SR33";
    case SpecialRegister::SR34: return "SR34";
    case SpecialRegister::SR35: return "SR35";
    case SpecialRegister::SR36: return "SR36";
    case SpecialRegister::SR37: return "SR37";
    case SpecialRegister::SR38: return "SR38";
    case SpecialRegister::SR39: return "SR39";
    case SpecialRegister::SR40: return "SR40";
    case SpecialRegister::SR41: return "SR41";
    case SpecialRegister::SR42: return "SR42";
    case SpecialRegister::SR43: return "SR43";
    case SpecialRegister::SR44: return "SR44";
    case SpecialRegister::SR45: return "SR45";
    case SpecialRegister::SR46: return "SR46";
    case SpecialRegister::SR47: return "SR47";
    case SpecialRegister::SR48: return "SR48";
    case SpecialRegister::SR49: return "SR49";
    case SpecialRegister::SR50: return "SR50";
    case SpecialRegister::SR51: return "SR51";
    case SpecialRegister::SR52: return "SR52";
    case SpecialRegister::SR53: return "SR53";
    case SpecialRegister::SR54: return "SR54";
    case SpecialRegister::SR55: return "SR55";
    case SpecialRegister::SR56: return "SR56";
    case SpecialRegister::SR57: return "SR57";
    case SpecialRegister::SR58: return "SR58";
    case SpecialRegister::SR59: return "SR59";
    case SpecialRegister::SR60: return "SR60";
    case SpecialRegister::SR61: return "SR61";
    case SpecialRegister::SR62: return "SR62";
    case SpecialRegister::SR63: return "SR63";
    case SpecialRegister::SR64: return "SR64";
    case SpecialRegister::SR65: return "SR65";
    case SpecialRegister::SR66: return "SR66";
    case SpecialRegister::SR67: return "SR67";
    case SpecialRegister::SR68: return "SR68";
    case SpecialRegister::SR69: return "SR69";
    case SpecialRegister::SR70: return "SR70";
    case SpecialRegister::SR71: return "SR71";
    case SpecialRegister::SR72: return "SR72";
    case SpecialRegister::SR73: return "SR73";
    case SpecialRegister::SR74: return "SR74";
    case SpecialRegister::SR75: return "SR75";
    case SpecialRegister::SR76: return "SR76";
    case SpecialRegister::SR77: return "SR77";
    case SpecialRegister::SR78: return "SR78";
    case SpecialRegister::SR79: return "SR79";
    case SpecialRegister::SR80: return "SR80";
    case SpecialRegister::SR81: return "SR81";
    case SpecialRegister::SR82: return "SR82";
    case SpecialRegister::SR83: return "SR83";
    case SpecialRegister::SR84: return "SR84";
    case SpecialRegister::SR85: return "SR85";
    case SpecialRegister::SR86: return "SR86";
    case SpecialRegister::SR87: return "SR87";
    case SpecialRegister::SR88: return "SR88";
    case SpecialRegister::SR89: return "SR89";
    case SpecialRegister::SR90: return "SR90";
    case SpecialRegister::SR91: return "SR91";
    case SpecialRegister::SR92: return "SR92";
    case SpecialRegister::SR93: return "SR93";
    case SpecialRegister::SR94: return "SR94";
    case SpecialRegister::SR95: return "SR95";
    case SpecialRegister::SR96: return "SR96";
    case SpecialRegister::SR97: return "SR97";
    case SpecialRegister::SR98: return "SR98";
    case SpecialRegister::SR99: return "SR99";
    case SpecialRegister::SR100: return "SR100";
    case SpecialRegister::SR101: return "SR101";
    case SpecialRegister::SR102: return "SR102";
    case SpecialRegister::SR103: return "SR103";
    case SpecialRegister::SR104: return "SR104";
    case SpecialRegister::SR105: return "SR105";
    case SpecialRegister::SR106: return "SR106";
    case SpecialRegister::SR107: return "SR107";
    case SpecialRegister::SR108: return "SR108";
    case SpecialRegister::SR109: return "SR109";
    case SpecialRegister::SR110: return "SR110";
    case SpecialRegister::SR111: return "SR111";
    case SpecialRegister::SR112: return "SR112";
    case SpecialRegister::SR113: return "SR113";
    case SpecialRegister::SR114: return "SR114";
    case SpecialRegister::SR115: return "SR115";
    case SpecialRegister::SR116: return "SR116";
    case SpecialRegister::SR117: return "SR117";
    case SpecialRegister::SR118: return "SR118";
    case SpecialRegister::SR119: return "SR119";
    case SpecialRegister::SR120: return "SR120";
    case SpecialRegister::SR121: return "SR121";
    case SpecialRegister::SR122: return "SR122";
    case SpecialRegister::SR123: return "SR123";
    case SpecialRegister::SR124: return "SR124";
    case SpecialRegister::SR125: return "SR125";
    case SpecialRegister::SR126: return "SR126";
    case SpecialRegister::SR127: return "SR127";
    case SpecialRegister::SR128: return "SR128";
    case SpecialRegister::SR129: return "SR129";
    case SpecialRegister::SR130: return "SR130";
    case SpecialRegister::SR131: return "SR131";
    case SpecialRegister::SR132: return "SR132";
    case SpecialRegister::SR133: return "SR133";
    case SpecialRegister::SR134: return "SR134";
    case SpecialRegister::SR135: return "SR135";
    case SpecialRegister::SR136: return "SR136";
    case SpecialRegister::SR137: return "SR137";
    case SpecialRegister::SR138: return "SR138";
    case SpecialRegister::SR139: return "SR139";
    case SpecialRegister::SR140: return "SR140";
    case SpecialRegister::SR141: return "SR141";
    case SpecialRegister::SR142: return "SR142";
    case SpecialRegister::SR143: return "SR143";
    case SpecialRegister::SR144: return "SR144";
    case SpecialRegister::SR145: return "SR145";
    case SpecialRegister::SR146: return "SR146";
    case SpecialRegister::SR147: return "SR147";
    case SpecialRegister::SR148: return "SR148";
    case SpecialRegister::SR149: return "SR149";
    case SpecialRegister::SR150: return "SR150";
    case SpecialRegister::SR151: return "SR151";
    case SpecialRegister::SR152: return "SR152";
    case SpecialRegister::SR153: return "SR153";
    case SpecialRegister::SR154: return "SR154";
    case SpecialRegister::SR155: return "SR155";
    case SpecialRegister::SR156: return "SR156";
    case SpecialRegister::SR157: return "SR157";
    case SpecialRegister::SR158: return "SR158";
    case SpecialRegister::SR159: return "SR159";
    case SpecialRegister::SR160: return "SR160";
    case SpecialRegister::SR161: return "SR161";
    case SpecialRegister::SR162: return "SR162";
    case SpecialRegister::SR163: return "SR163";
    case SpecialRegister::SR164: return "SR164";
    case SpecialRegister::SR165: return "SR165";
    case SpecialRegister::SR166: return "SR166";
    case SpecialRegister::SR167: return "SR167";
    case SpecialRegister::SR168: return "SR168";
    case SpecialRegister::SR169: return "SR169";
    case SpecialRegister::SR170: return "SR170";
    case SpecialRegister::SR171: return "SR171";
    case SpecialRegister::SR172: return "SR172";
    case SpecialRegister::SR173: return "SR173";
    case SpecialRegister::SR174: return "SR174";
    case SpecialRegister::SR175: return "SR175";
    case SpecialRegister::SR176: return "SR176";
    case SpecialRegister::SR177: return "SR177";
    case SpecialRegister::SR178: return "SR178";
    case SpecialRegister::SR179: return "SR179";
    case SpecialRegister::SR180: return "SR180";
    case SpecialRegister::SR181: return "SR181";
    case SpecialRegister::SR182: return "SR182";
    case SpecialRegister::SR183: return "SR183";
    case SpecialRegister::SR184: return "SR184";
    case SpecialRegister::SR185: return "SR185";
    case SpecialRegister::SR186: return "SR186";
    case SpecialRegister::SR187: return "SR187";
    case SpecialRegister::SR188: return "SR188";
    case SpecialRegister::SR189: return "SR189";
    case SpecialRegister::SR190: return "SR190";
    case SpecialRegister::SR191: return "SR191";
    case SpecialRegister::SR192: return "SR192";
    case SpecialRegister::SR193: return "SR193";
    case SpecialRegister::SR194: return "SR194";
    case SpecialRegister::SR195: return "SR195";
    case SpecialRegister::SR196: return "SR196";
    case SpecialRegister::SR197: return "SR197";
    case SpecialRegister::SR198: return "SR198";
    case SpecialRegister::SR199: return "SR199";
    case SpecialRegister::SR200: return "SR200";
    case SpecialRegister::SR201: return "SR201";
    case SpecialRegister::SR202: return "SR202";
    case SpecialRegister::SR203: return "SR203";
    case SpecialRegister::SR204: return "SR204";
    case SpecialRegister::SR205: return "SR205";
    case SpecialRegister::SR206: return "SR206";
    case SpecialRegister::SR207: return "SR207";
    case SpecialRegister::SR208: return "SR208";
    case SpecialRegister::SR209: return "SR209";
    case SpecialRegister::SR210: return "SR210";
    case SpecialRegister::SR211: return "SR211";
    case SpecialRegister::SR212: return "SR212";
    case SpecialRegister::SR213: return "SR213";
    case SpecialRegister::SR214: return "SR214";
    case SpecialRegister::SR215: return "SR215";
    case SpecialRegister::SR216: return "SR216";
    case SpecialRegister::SR217: return "SR217";
    case SpecialRegister::SR218: return "SR218";
    case SpecialRegister::SR219: return "SR219";
    case SpecialRegister::SR220: return "SR220";
    case SpecialRegister::SR221: return "SR221";
    case SpecialRegister::SR222: return "SR222";
    case SpecialRegister::SR223: return "SR223";
    case SpecialRegister::SR224: return "SR224";
    case SpecialRegister::SR225: return "SR225";
    case SpecialRegister::SR226: return "SR226";
    case SpecialRegister::SR227: return "SR227";
    case SpecialRegister::SR228: return "SR228";
    case SpecialRegister::SR229: return "SR229";
    case SpecialRegister::SR230: return "SR230";
    case SpecialRegister::SR231: return "SR231";
    case SpecialRegister::SR232: return "SR232";
    case SpecialRegister::SR233: return "SR233";
    case SpecialRegister::SR234: return "SR234";
    case SpecialRegister::SR235: return "SR235";
    case SpecialRegister::SR236: return "SR236";
    case SpecialRegister::SR237: return "SR237";
    case SpecialRegister::SR238: return "SR238";
    case SpecialRegister::SR239: return "SR239";
    case SpecialRegister::SR240: return "SR240";
    case SpecialRegister::SR241: return "SR241";
    case SpecialRegister::SR242: return "SR242";
    case SpecialRegister::SR243: return "SR243";
    case SpecialRegister::SR244: return "SR244";
    case SpecialRegister::SR245: return "SR245";
    case SpecialRegister::SR246: return "SR246";
    case SpecialRegister::SR247: return "SR247";
    case SpecialRegister::SR248: return "SR248";
    case SpecialRegister::SR249: return "SR249";
    case SpecialRegister::SR250: return "SR250";
    case SpecialRegister::SR251: return "SR251";
    case SpecialRegister::SR252: return "SR252";
    case SpecialRegister::SR253: return "SR253";
    case SpecialRegister::SR254: return "SR254";
    case SpecialRegister::SR255: return "SR255";
    default: return std::format("SpecialRegister::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(StoreCacheOp value) {
  switch (value) {
    case StoreCacheOp::WB: return "WB";
    case StoreCacheOp::CG: return "CG";
    case StoreCacheOp::CS: return "CS";
    case StoreCacheOp::WT: return "WT";
    default: return std::format("StoreCacheOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(TEXWmsk2C value) {
  switch (value) {
    case TEXWmsk2C::R: return "R";
    case TEXWmsk2C::G: return "G";
    case TEXWmsk2C::B: return "B";
    case TEXWmsk2C::A: return "A";
    case TEXWmsk2C::RG: return "RG";
    case TEXWmsk2C::RA: return "RA";
    case TEXWmsk2C::GA: return "GA";
    case TEXWmsk2C::BA: return "BA";
    default: return std::format("TEXWmsk2C::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(TEXWmsk34C value) {
  switch (value) {
    case TEXWmsk34C::RGB: return "RGB";
    case TEXWmsk34C::RGA: return "RGA";
    case TEXWmsk34C::RBA: return "RBA";
    case TEXWmsk34C::GBA: return "GBA";
    case TEXWmsk34C::RGBA: return "RGBA";
    case TEXWmsk34C::INVALID5: return "INVALID5";
    case TEXWmsk34C::INVALID6: return "INVALID6";
    case TEXWmsk34C::INVALID7: return "INVALID7";
    default: return std::format("TEXWmsk34C::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(TOFF1 value) {
  switch (value) {
    case TOFF1::noTOFF: return "noTOFF";
    case TOFF1::AOFFI: return "AOFFI";
    default: return std::format("TOFF1::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(TOFF2 value) {
  switch (value) {
    case TOFF2::noTOFF: return "noTOFF";
    case TOFF2::AOFFI: return "AOFFI";
    case TOFF2::PTP: return "PTP";
    case TOFF2::INVALIDBTOFF03: return "INVALIDBTOFF03";
    default: return std::format("TOFF2::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(TPhase value) {
  switch (value) {
    case TPhase::noPhase: return "noPhase";
    case TPhase::T: return "T";
    case TPhase::P: return "P";
    case TPhase::INVALIDPHASE3: return "INVALIDPHASE3";
    default: return std::format("TPhase::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(TXQMode value) {
  switch (value) {
    case TXQMode::TEX_HEADER_DIMENSION: return "TEX_HEADER_DIMENSION";
    case TXQMode::TEX_HEADER_TEXTURE_TYPE: return "TEX_HEADER_TEXTURE_TYPE";
    case TXQMode::TEX_HEADER_SAMPLER_POS: return "TEX_HEADER_SAMPLER_POS";
    case TXQMode::_3: return "3";
    case TXQMode::_4: return "4";
    case TXQMode::_5: return "5";
    case TXQMode::_6: return "6";
    case TXQMode::_7: return "7";
    case TXQMode::TEX_SAMPLER_FILTER: return "TEX_SAMPLER_FILTER";
    case TXQMode::TEX_SAMPLER_LOD: return "TEX_SAMPLER_LOD";
    case TXQMode::TEX_SAMPLER_WRAP: return "TEX_SAMPLER_WRAP";
    case TXQMode::TEX_SAMPLER_BORDER_COLOR: return "TEX_SAMPLER_BORDER_COLOR";
    case TXQMode::_12: return "12";
    case TXQMode::_13: return "13";
    case TXQMode::_14: return "14";
    case TXQMode::_15: return "15";
    case TXQMode::_16: return "16";
    case TXQMode::_17: return "17";
    case TXQMode::_18: return "18";
    case TXQMode::_19: return "19";
    case TXQMode::_20: return "20";
    case TXQMode::_21: return "21";
    case TXQMode::_22: return "22";
    case TXQMode::_23: return "23";
    case TXQMode::_24: return "24";
    case TXQMode::_25: return "25";
    case TXQMode::_26: return "26";
    case TXQMode::_27: return "27";
    case TXQMode::_28: return "28";
    case TXQMode::_29: return "29";
    case TXQMode::_30: return "30";
    case TXQMode::_31: return "31";
    default: return std::format("TXQMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Test value) {
  switch (value) {
    case Test::FALSE: return "FALSE";
    case Test::ZFF: return "ZFF";
    case Test::LEG: return "LEG";
    case Test::U: return "U";
    case Test::ZFT: return "ZFT";
    case Test::TRUE: return "TRUE";
    case Test::NOT_OVERFLOW: return "NOT_OVERFLOW";
    case Test::CFF: return "CFF";
    case Test::ABOVE: return "ABOVE";
    case Test::SIGN: return "SIGN";
    case Test::SF1: return "SF1";
    case Test::CFT: return "CFT";
    case Test::OF1: return "OF1";
    case Test::NOT_SIGN: return "NOT_SIGN";
    case Test::BELOW_OR_EQUAL: return "BELOW_OR_EQUAL";
    case Test::NOT_CARRY: return "NOT_CARRY";
    case Test::_1F: return "1F";
    case Test::LT: return "LT";
    case Test::EQ: return "EQ";
    case Test::LE: return "LE";
    case Test::GT: return "GT";
    case Test::GE: return "GE";
    case Test::LTU: return "LTU";
    case Test::LEU: return "LEU";
    case Test::GTU: return "GTU";
    case Test::NEU: return "NEU";
    case Test::GEU: return "GEU";
    case Test::HI: return "HI";
    case Test::CSM_TA: return "CSM_TA";
    case Test::CSM_TR: return "CSM_TR";
    case Test::CSM_MX: return "CSM_MX";
    case Test::FCSM_TA: return "FCSM_TA";
    default: return std::format("Test::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(TexComp value) {
  switch (value) {
    case TexComp::R: return "R";
    case TexComp::G: return "G";
    case TexComp::B: return "B";
    case TexComp::A: return "A";
    default: return std::format("TexComp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(Trig value) {
  switch (value) {
    case Trig::TRIG: return "TRIG";
    default: return std::format("Trig::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(U value) {
  switch (value) {
    case U::noU: return "noU";
    case U::U: return "U";
    default: return std::format("U::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(U16 value) {
  switch (value) {
    case U16::U16: return "U16";
    default: return std::format("U16::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(U32 value) {
  switch (value) {
    case U32::U32: return "U32";
    case U32::INVALIDASEL7: return "INVALIDASEL7";
    default: return std::format("U32::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(U8 value) {
  switch (value) {
    case U8::U8: return "U8";
    default: return std::format("U8::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(UInteger value) {
  switch (value) {
    case static_cast<UInteger>(UInteger64::U64): return "U64";
    case static_cast<UInteger>(UInteger32::U32): return "U32";
    case static_cast<UInteger>(UInteger16::U16): return "U16";
    case static_cast<UInteger>(UInteger8::U8): return "U8";
    default: return std::format("UInteger::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(UInteger32 value) {
  switch (value) {
    case UInteger32::U32: return "U32";
    default: return std::format("UInteger32::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(UInteger64 value) {
  switch (value) {
    case UInteger64::U64: return "U64";
    default: return std::format("UInteger64::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(UInteger_old value) {
  switch (value) {
    case static_cast<UInteger_old>(U16::U16): return "U16";
    case static_cast<UInteger_old>(U8::U8): return "U8";
    case static_cast<UInteger_old>(U32::U32): return "U32";
    case static_cast<UInteger_old>(U32::INVALIDASEL7): return "INVALIDASEL7";
    default: return std::format("UInteger_old::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(USCHED_INFO value) {
  switch (value) {
    case USCHED_INFO::YIELD_SB: return "YIELD_SB";
    case USCHED_INFO::W1G: return "W1G";
    case USCHED_INFO::W2G: return "W2G";
    case USCHED_INFO::W3G: return "W3G";
    case USCHED_INFO::W4G: return "W4G";
    case USCHED_INFO::W5G: return "W5G";
    case USCHED_INFO::W6G: return "W6G";
    case USCHED_INFO::W7G: return "W7G";
    case USCHED_INFO::W8G: return "W8G";
    case USCHED_INFO::W9G: return "W9G";
    case USCHED_INFO::W10G: return "W10G";
    case USCHED_INFO::W11G: return "W11G";
    case USCHED_INFO::W12G: return "W12G";
    case USCHED_INFO::W13G: return "W13G";
    case USCHED_INFO::W14G: return "W14G";
    case USCHED_INFO::W15G: return "W15G";
    case USCHED_INFO::W1: return "W1";
    case USCHED_INFO::W2: return "W2";
    case USCHED_INFO::W3: return "W3";
    case USCHED_INFO::W4: return "W4";
    case USCHED_INFO::W5: return "W5";
    case USCHED_INFO::W6: return "W6";
    case USCHED_INFO::W7: return "W7";
    case USCHED_INFO::W8: return "W8";
    case USCHED_INFO::W9: return "W9";
    case USCHED_INFO::W10: return "W10";
    case USCHED_INFO::W11: return "W11";
    case USCHED_INFO::PIXBAR: return "PIXBAR";
    case USCHED_INFO::YLD: return "YLD";
    case USCHED_INFO::YLD8: return "YLD8";
    case USCHED_INFO::floxy2: return "floxy2";
    case USCHED_INFO::OFF_DECK: return "OFF_DECK";
    default: return std::format("USCHED_INFO::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(UnaryAbs value) {
  switch (value) {
    case UnaryAbs::noABS: return "noABS";
    case UnaryAbs::ABS: return "ABS";
    default: return std::format("UnaryAbs::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(UnaryInv value) {
  switch (value) {
    case UnaryInv::noINV: return "noINV";
    case UnaryInv::INV: return "INV";
    default: return std::format("UnaryInv::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(UnaryNeg value) {
  switch (value) {
    case UnaryNeg::noNEG: return "noNEG";
    case UnaryNeg::NEG: return "NEG";
    default: return std::format("UnaryNeg::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(VInteger32 value) {
  switch (value) {
    case VInteger32::U32: return "U32";
    case VInteger32::S32: return "S32";
    case VInteger32::INVALIDASEL7: return "INVALIDASEL7";
    case VInteger32::INVALIDASEL6: return "INVALIDASEL6";
    default: return std::format("VInteger32::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(VMadScale value) {
  switch (value) {
    case VMadScale::PASS: return "PASS";
    case VMadScale::SHR_7: return "SHR_7";
    case VMadScale::SHR_15: return "SHR_15";
    case VMadScale::INVALIDVMADSCALE3: return "INVALIDVMADSCALE3";
    default: return std::format("VMadScale::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(VOP value) {
  switch (value) {
    case VOP::MRG_16H: return "MRG_16H";
    case VOP::MRG_16L: return "MRG_16L";
    case VOP::MRG_8B0: return "MRG_8B0";
    case VOP::MRG_8B2: return "MRG_8B2";
    case VOP::ACC: return "ACC";
    case VOP::MIN: return "MIN";
    case VOP::MAX: return "MAX";
    case VOP::PASS: return "PASS";
    default: return std::format("VOP::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(VRed2 value) {
  switch (value) {
    case VRed2::SIMD_MRG: return "SIMD_MRG";
    case VRed2::ACC: return "ACC";
    case VRed2::INVALIDRED2: return "INVALIDRED2";
    case VRed2::INVALIDRED3: return "INVALIDRED3";
    default: return std::format("VRed2::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(VTG value) {
  switch (value) {
    case VTG::VTG: return "VTG";
    default: return std::format("VTG::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(VTGMode value) {
  switch (value) {
    case VTGMode::R: return "R";
    case VTGMode::A: return "A";
    case VTGMode::RA: return "RA";
    case VTGMode::INVALIDVTGMODE3: return "INVALIDVTGMODE3";
    default: return std::format("VTGMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(VoteOp value) {
  switch (value) {
    case VoteOp::ALL: return "ALL";
    case VoteOp::ANY: return "ANY";
    case VoteOp::EQ: return "EQ";
    case VoteOp::INVALIDVMODE3: return "INVALIDVMODE3";
    default: return std::format("VoteOp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(WR value) {
  switch (value) {
    case WR::wr: return "wr";
    default: return std::format("WR::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(X value) {
  switch (value) {
    case X::noX: return "noX";
    case X::X: return "X";
    default: return std::format("X::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(XMADcop value) {
  switch (value) {
    case XMADcop::C32: return "C32";
    case XMADcop::CLO: return "CLO";
    case XMADcop::CHI: return "CHI";
    case XMADcop::CSFU: return "CSFU";
    case XMADcop::CBCC: return "CBCC";
    default: return std::format("XMADcop::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(XMADcop2 value) {
  switch (value) {
    case XMADcop2::C32: return "C32";
    case XMADcop2::CLO: return "CLO";
    case XMADcop2::CHI: return "CHI";
    case XMADcop2::CSFU: return "CSFU";
    default: return std::format("XMADcop2::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(XMode value) {
  switch (value) {
    case XMode::noX: return "noX";
    case XMode::XLO: return "XLO";
    case XMode::XMED: return "XMED";
    case XMode::XHI: return "XHI";
    default: return std::format("XMode::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(XXHI value) {
  switch (value) {
    case XXHI::noX: return "noX";
    case XXHI::INVALIDSHRXMODE1: return "INVALIDSHRXMODE1";
    case XXHI::X: return "X";
    case XXHI::XHI: return "XHI";
    default: return std::format("XXHI::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(ZeroRegister value) {
  switch (value) {
    case ZeroRegister::RZ: return "RZ";
    default: return std::format("ZeroRegister::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(hadd2_32i__Ra value) {
  switch (value) {
    case hadd2_32i__Ra::R147: return "R147";
    case hadd2_32i__Ra::R146: return "R146";
    case hadd2_32i__Ra::R145: return "R145";
    case hadd2_32i__Ra::R144: return "R144";
    case hadd2_32i__Ra::R143: return "R143";
    case hadd2_32i__Ra::R142: return "R142";
    case hadd2_32i__Ra::R141: return "R141";
    case hadd2_32i__Ra::R140: return "R140";
    case hadd2_32i__Ra::R254: return "R254";
    case hadd2_32i__Ra::R253: return "R253";
    case hadd2_32i__Ra::R178: return "R178";
    case hadd2_32i__Ra::R149: return "R149";
    case hadd2_32i__Ra::R148: return "R148";
    case hadd2_32i__Ra::R231: return "R231";
    case hadd2_32i__Ra::R179: return "R179";
    case hadd2_32i__Ra::RZ: return "RZ";
    case hadd2_32i__Ra::R183: return "R183";
    case hadd2_32i__Ra::R38: return "R38";
    case hadd2_32i__Ra::R39: return "R39";
    case hadd2_32i__Ra::R34: return "R34";
    case hadd2_32i__Ra::R35: return "R35";
    case hadd2_32i__Ra::R36: return "R36";
    case hadd2_32i__Ra::R37: return "R37";
    case hadd2_32i__Ra::R30: return "R30";
    case hadd2_32i__Ra::R31: return "R31";
    case hadd2_32i__Ra::R32: return "R32";
    case hadd2_32i__Ra::R33: return "R33";
    case hadd2_32i__Ra::R4: return "R4";
    case hadd2_32i__Ra::R5: return "R5";
    case hadd2_32i__Ra::R6: return "R6";
    case hadd2_32i__Ra::R7: return "R7";
    case hadd2_32i__Ra::R0: return "R0";
    case hadd2_32i__Ra::R1: return "R1";
    case hadd2_32i__Ra::R2: return "R2";
    case hadd2_32i__Ra::R3: return "R3";
    case hadd2_32i__Ra::R8: return "R8";
    case hadd2_32i__Ra::R9: return "R9";
    case hadd2_32i__Ra::R182: return "R182";
    case hadd2_32i__Ra::R89: return "R89";
    case hadd2_32i__Ra::R88: return "R88";
    case hadd2_32i__Ra::R170: return "R170";
    case hadd2_32i__Ra::R171: return "R171";
    case hadd2_32i__Ra::R176: return "R176";
    case hadd2_32i__Ra::R177: return "R177";
    case hadd2_32i__Ra::R174: return "R174";
    case hadd2_32i__Ra::R175: return "R175";
    case hadd2_32i__Ra::R81: return "R81";
    case hadd2_32i__Ra::R80: return "R80";
    case hadd2_32i__Ra::R83: return "R83";
    case hadd2_32i__Ra::R82: return "R82";
    case hadd2_32i__Ra::R85: return "R85";
    case hadd2_32i__Ra::R84: return "R84";
    case hadd2_32i__Ra::R87: return "R87";
    case hadd2_32i__Ra::R86: return "R86";
    case hadd2_32i__Ra::R205: return "R205";
    case hadd2_32i__Ra::R248: return "R248";
    case hadd2_32i__Ra::R169: return "R169";
    case hadd2_32i__Ra::R168: return "R168";
    case hadd2_32i__Ra::R98: return "R98";
    case hadd2_32i__Ra::R99: return "R99";
    case hadd2_32i__Ra::R96: return "R96";
    case hadd2_32i__Ra::R97: return "R97";
    case hadd2_32i__Ra::R94: return "R94";
    case hadd2_32i__Ra::R95: return "R95";
    case hadd2_32i__Ra::R92: return "R92";
    case hadd2_32i__Ra::R93: return "R93";
    case hadd2_32i__Ra::R90: return "R90";
    case hadd2_32i__Ra::R91: return "R91";
    case hadd2_32i__Ra::R16: return "R16";
    case hadd2_32i__Ra::R17: return "R17";
    case hadd2_32i__Ra::R14: return "R14";
    case hadd2_32i__Ra::R15: return "R15";
    case hadd2_32i__Ra::R12: return "R12";
    case hadd2_32i__Ra::R13: return "R13";
    case hadd2_32i__Ra::R10: return "R10";
    case hadd2_32i__Ra::R11: return "R11";
    case hadd2_32i__Ra::R181: return "R181";
    case hadd2_32i__Ra::R18: return "R18";
    case hadd2_32i__Ra::R19: return "R19";
    case hadd2_32i__Ra::R180: return "R180";
    case hadd2_32i__Ra::R251: return "R251";
    case hadd2_32i__Ra::R187: return "R187";
    case hadd2_32i__Ra::R250: return "R250";
    case hadd2_32i__Ra::R186: return "R186";
    case hadd2_32i__Ra::R200: return "R200";
    case hadd2_32i__Ra::R201: return "R201";
    case hadd2_32i__Ra::R202: return "R202";
    case hadd2_32i__Ra::R203: return "R203";
    case hadd2_32i__Ra::R204: return "R204";
    case hadd2_32i__Ra::R185: return "R185";
    case hadd2_32i__Ra::R206: return "R206";
    case hadd2_32i__Ra::R207: return "R207";
    case hadd2_32i__Ra::R208: return "R208";
    case hadd2_32i__Ra::R209: return "R209";
    case hadd2_32i__Ra::R184: return "R184";
    case hadd2_32i__Ra::R118: return "R118";
    case hadd2_32i__Ra::R119: return "R119";
    case hadd2_32i__Ra::R110: return "R110";
    case hadd2_32i__Ra::R111: return "R111";
    case hadd2_32i__Ra::R112: return "R112";
    case hadd2_32i__Ra::R113: return "R113";
    case hadd2_32i__Ra::R114: return "R114";
    case hadd2_32i__Ra::R115: return "R115";
    case hadd2_32i__Ra::R116: return "R116";
    case hadd2_32i__Ra::R117: return "R117";
    case hadd2_32i__Ra::R63: return "R63";
    case hadd2_32i__Ra::R62: return "R62";
    case hadd2_32i__Ra::R61: return "R61";
    case hadd2_32i__Ra::R60: return "R60";
    case hadd2_32i__Ra::R67: return "R67";
    case hadd2_32i__Ra::R66: return "R66";
    case hadd2_32i__Ra::R65: return "R65";
    case hadd2_32i__Ra::R64: return "R64";
    case hadd2_32i__Ra::R193: return "R193";
    case hadd2_32i__Ra::R69: return "R69";
    case hadd2_32i__Ra::R68: return "R68";
    case hadd2_32i__Ra::R162: return "R162";
    case hadd2_32i__Ra::R249: return "R249";
    case hadd2_32i__Ra::R213: return "R213";
    case hadd2_32i__Ra::R212: return "R212";
    case hadd2_32i__Ra::R211: return "R211";
    case hadd2_32i__Ra::R210: return "R210";
    case hadd2_32i__Ra::R217: return "R217";
    case hadd2_32i__Ra::R216: return "R216";
    case hadd2_32i__Ra::R215: return "R215";
    case hadd2_32i__Ra::R214: return "R214";
    case hadd2_32i__Ra::R219: return "R219";
    case hadd2_32i__Ra::R218: return "R218";
    case hadd2_32i__Ra::R109: return "R109";
    case hadd2_32i__Ra::R108: return "R108";
    case hadd2_32i__Ra::R194: return "R194";
    case hadd2_32i__Ra::R103: return "R103";
    case hadd2_32i__Ra::R102: return "R102";
    case hadd2_32i__Ra::R101: return "R101";
    case hadd2_32i__Ra::R100: return "R100";
    case hadd2_32i__Ra::R107: return "R107";
    case hadd2_32i__Ra::R106: return "R106";
    case hadd2_32i__Ra::R105: return "R105";
    case hadd2_32i__Ra::R104: return "R104";
    case hadd2_32i__Ra::R190: return "R190";
    case hadd2_32i__Ra::R247: return "R247";
    case hadd2_32i__Ra::R220: return "R220";
    case hadd2_32i__Ra::R191: return "R191";
    case hadd2_32i__Ra::R240: return "R240";
    case hadd2_32i__Ra::R252: return "R252";
    case hadd2_32i__Ra::R192: return "R192";
    case hadd2_32i__Ra::R241: return "R241";
    case hadd2_32i__Ra::R70: return "R70";
    case hadd2_32i__Ra::R71: return "R71";
    case hadd2_32i__Ra::R72: return "R72";
    case hadd2_32i__Ra::R73: return "R73";
    case hadd2_32i__Ra::R74: return "R74";
    case hadd2_32i__Ra::R75: return "R75";
    case hadd2_32i__Ra::R76: return "R76";
    case hadd2_32i__Ra::R77: return "R77";
    case hadd2_32i__Ra::R78: return "R78";
    case hadd2_32i__Ra::R79: return "R79";
    case hadd2_32i__Ra::R195: return "R195";
    case hadd2_32i__Ra::R136: return "R136";
    case hadd2_32i__Ra::R137: return "R137";
    case hadd2_32i__Ra::R134: return "R134";
    case hadd2_32i__Ra::R135: return "R135";
    case hadd2_32i__Ra::R132: return "R132";
    case hadd2_32i__Ra::R133: return "R133";
    case hadd2_32i__Ra::R130: return "R130";
    case hadd2_32i__Ra::R131: return "R131";
    case hadd2_32i__Ra::R226: return "R226";
    case hadd2_32i__Ra::R227: return "R227";
    case hadd2_32i__Ra::R224: return "R224";
    case hadd2_32i__Ra::R197: return "R197";
    case hadd2_32i__Ra::R222: return "R222";
    case hadd2_32i__Ra::R223: return "R223";
    case hadd2_32i__Ra::R138: return "R138";
    case hadd2_32i__Ra::R139: return "R139";
    case hadd2_32i__Ra::R238: return "R238";
    case hadd2_32i__Ra::R198: return "R198";
    case hadd2_32i__Ra::R196: return "R196";
    case hadd2_32i__Ra::R199: return "R199";
    case hadd2_32i__Ra::R45: return "R45";
    case hadd2_32i__Ra::R44: return "R44";
    case hadd2_32i__Ra::R47: return "R47";
    case hadd2_32i__Ra::R46: return "R46";
    case hadd2_32i__Ra::R41: return "R41";
    case hadd2_32i__Ra::R40: return "R40";
    case hadd2_32i__Ra::R43: return "R43";
    case hadd2_32i__Ra::R42: return "R42";
    case hadd2_32i__Ra::R189: return "R189";
    case hadd2_32i__Ra::R188: return "R188";
    case hadd2_32i__Ra::R49: return "R49";
    case hadd2_32i__Ra::R48: return "R48";
    case hadd2_32i__Ra::R121: return "R121";
    case hadd2_32i__Ra::R120: return "R120";
    case hadd2_32i__Ra::R123: return "R123";
    case hadd2_32i__Ra::R122: return "R122";
    case hadd2_32i__Ra::R125: return "R125";
    case hadd2_32i__Ra::R124: return "R124";
    case hadd2_32i__Ra::R127: return "R127";
    case hadd2_32i__Ra::R126: return "R126";
    case hadd2_32i__Ra::R129: return "R129";
    case hadd2_32i__Ra::R128: return "R128";
    case hadd2_32i__Ra::R233: return "R233";
    case hadd2_32i__Ra::R232: return "R232";
    case hadd2_32i__Ra::R235: return "R235";
    case hadd2_32i__Ra::R234: return "R234";
    case hadd2_32i__Ra::R237: return "R237";
    case hadd2_32i__Ra::R236: return "R236";
    case hadd2_32i__Ra::R165: return "R165";
    case hadd2_32i__Ra::R164: return "R164";
    case hadd2_32i__Ra::R239: return "R239";
    case hadd2_32i__Ra::R167: return "R167";
    case hadd2_32i__Ra::R166: return "R166";
    case hadd2_32i__Ra::R228: return "R228";
    case hadd2_32i__Ra::R161: return "R161";
    case hadd2_32i__Ra::R229: return "R229";
    case hadd2_32i__Ra::R160: return "R160";
    case hadd2_32i__Ra::R58: return "R58";
    case hadd2_32i__Ra::R59: return "R59";
    case hadd2_32i__Ra::R163: return "R163";
    case hadd2_32i__Ra::R52: return "R52";
    case hadd2_32i__Ra::R53: return "R53";
    case hadd2_32i__Ra::R50: return "R50";
    case hadd2_32i__Ra::R51: return "R51";
    case hadd2_32i__Ra::R56: return "R56";
    case hadd2_32i__Ra::R57: return "R57";
    case hadd2_32i__Ra::R54: return "R54";
    case hadd2_32i__Ra::R55: return "R55";
    case hadd2_32i__Ra::R225: return "R225";
    case hadd2_32i__Ra::R154: return "R154";
    case hadd2_32i__Ra::R155: return "R155";
    case hadd2_32i__Ra::R156: return "R156";
    case hadd2_32i__Ra::R157: return "R157";
    case hadd2_32i__Ra::R150: return "R150";
    case hadd2_32i__Ra::R151: return "R151";
    case hadd2_32i__Ra::R152: return "R152";
    case hadd2_32i__Ra::R153: return "R153";
    case hadd2_32i__Ra::R244: return "R244";
    case hadd2_32i__Ra::R245: return "R245";
    case hadd2_32i__Ra::R246: return "R246";
    case hadd2_32i__Ra::R221: return "R221";
    case hadd2_32i__Ra::R158: return "R158";
    case hadd2_32i__Ra::R159: return "R159";
    case hadd2_32i__Ra::R242: return "R242";
    case hadd2_32i__Ra::R243: return "R243";
    case hadd2_32i__Ra::R172: return "R172";
    case hadd2_32i__Ra::R230: return "R230";
    case hadd2_32i__Ra::R173: return "R173";
    case hadd2_32i__Ra::R29: return "R29";
    case hadd2_32i__Ra::R28: return "R28";
    case hadd2_32i__Ra::R27: return "R27";
    case hadd2_32i__Ra::R26: return "R26";
    case hadd2_32i__Ra::R25: return "R25";
    case hadd2_32i__Ra::R24: return "R24";
    case hadd2_32i__Ra::R23: return "R23";
    case hadd2_32i__Ra::R22: return "R22";
    case hadd2_32i__Ra::R21: return "R21";
    case hadd2_32i__Ra::R20: return "R20";
    default: return std::format("hadd2_32i__Ra::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(hadd2_32i__ftz value) {
  switch (value) {
    case hadd2_32i__ftz::noftz: return "noftz";
    case hadd2_32i__ftz::FTZ: return "FTZ";
    default: return std::format("hadd2_32i__ftz::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(hadd2_32i__sat value) {
  switch (value) {
    case hadd2_32i__sat::nosat: return "nosat";
    case hadd2_32i__sat::SAT: return "SAT";
    default: return std::format("hadd2_32i__sat::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(hfma2__v0_fmz value) {
  switch (value) {
    case hfma2__v0_fmz::nofmz: return "nofmz";
    case hfma2__v0_fmz::FTZ: return "FTZ";
    case hfma2__v0_fmz::FMZ: return "FMZ";
    case hfma2__v0_fmz::INVALID: return "INVALID";
    default: return std::format("hfma2__v0_fmz::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(hset2__v0_bop value) {
  switch (value) {
    case hset2__v0_bop::AND: return "AND";
    case hset2__v0_bop::XOR: return "XOR";
    case hset2__v0_bop::OR: return "OR";
    default: return std::format("hset2__v0_bop::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(hset2__v0_cmp value) {
  switch (value) {
    case hset2__v0_cmp::LE: return "LE";
    case hset2__v0_cmp::GE: return "GE";
    case hset2__v0_cmp::GEU: return "GEU";
    case hset2__v0_cmp::LTU: return "LTU";
    case hset2__v0_cmp::F: return "F";
    case hset2__v0_cmp::EQU: return "EQU";
    case hset2__v0_cmp::NAN: return "NAN";
    case hset2__v0_cmp::NE: return "NE";
    case hset2__v0_cmp::T: return "T";
    case hset2__v0_cmp::LT: return "LT";
    case hset2__v0_cmp::GT: return "GT";
    case hset2__v0_cmp::LEU: return "LEU";
    case hset2__v0_cmp::NUM: return "NUM";
    case hset2__v0_cmp::NEU: return "NEU";
    case hset2__v0_cmp::EQ: return "EQ";
    case hset2__v0_cmp::GTU: return "GTU";
    default: return std::format("hset2__v0_cmp::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(maxShift value) {
  switch (value) {
    case maxShift::_32: return "32";
    case maxShift::INVALIDMAXSHIFT3: return "INVALIDMAXSHIFT3";
    case maxShift::U64: return "U64";
    case maxShift::S64: return "S64";
    default: return std::format("maxShift::{:#x}", static_cast<std::uint32_t>(value));
  }
}

const std::string_view ToString(optCC value) {
  switch (value) {
    case optCC::noCC: return "noCC";
    case optCC::CC: return "CC";
    default: return std::format("optCC::{:#x}", static_cast<std::uint32_t>(value));
  }
}

static std::string PrintInstruction([[maybe_unused]] const char* opcode, [[maybe_unused]] const Accessor<OpClass::NOP_DEFAULT>& accessor) {
  return "NOP;";
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FFMA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FFMA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FFMA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_FFMA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FFMA32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.fImm());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FFMA32I_2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.fImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FADD32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.fImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FCMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FCMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FCMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_FCMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FSWZADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.ndv());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.scale());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.scale());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.scale());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FMUL32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.fImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_FSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_FSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_FSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_FSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_FSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_FSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IPA_1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.idx());
  out += ".";
  out += ToString(accessor.ipaop());
  out += ".";
  out += ToString(accessor.msi());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ",";
  out += " ";
  if (accessor.Ps_not()) out += "!";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_IPA_1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ipaop());
  out += ".";
  out += ToString(accessor.msi());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ",";
  out += " ";
  if (accessor.Ps_not()) out += "!";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IPA_2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.idx());
  out += ".";
  out += ToString(accessor.ipaop());
  out += ".";
  out += ToString(accessor.msi());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Ps_not()) out += "!";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_IPA_2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ipaop());
  out += ".";
  out += ToString(accessor.msi());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Ps_not()) out += "!";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::RRO>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rroop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_RRO>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rroop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_RRO>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rroop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::MUFU>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.mufu());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FCHK>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.mode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FCHK>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.mode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FCHK>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.mode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DFMA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_DFMA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_DFMA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_DFMA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_DADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_DADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_DMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_DMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_DMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_DMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_DSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_DSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_DSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_DSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_DSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.fcomp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_DSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_DSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_DSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_DSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_DSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_IMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_IMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_IMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IMAD32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += ".";
  out += ToString(accessor.po());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IMADSP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.spa());
  out += ".";
  out += ToString(accessor.spb());
  out += ".";
  out += ToString(accessor.spc());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_IMADSP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.spa());
  out += ".";
  out += ToString(accessor.spb());
  out += ".";
  out += ToString(accessor.spc());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_IMADSP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.spa());
  out += ".";
  out += ToString(accessor.spb());
  out += ".";
  out += ToString(accessor.spc());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_IMADSP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.spa());
  out += ".";
  out += ToString(accessor.spb());
  out += ".";
  out += ToString(accessor.spc());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_IMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_IMUL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IMUL32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.us32b());
  out += ".";
  out += ToString(accessor.hib());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_IADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_IADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IADD3>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dir());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.csel());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BImm_IADD3>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm20());
  out += ".";
  out += ToString(accessor.jneg());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BConst_IADD3>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IADD32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ISCADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.po());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += std::format("{:#x}", accessor.shift());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_ISCADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.po());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ",";
  out += std::format("{:#x}", accessor.shift());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_ISCADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.po());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += std::format("{:#x}", accessor.shift());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ISCADD32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += std::format("{:#x}", accessor.shift());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_IMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_IMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BFE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.brev());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_BFE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.brev());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_BFE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.brev());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BFI>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_BFI>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_BFI>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_BFI>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.brev());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_SHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.brev());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_SHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.brev());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_SHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_SHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SHF_L_imm>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.shfl());
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.maxshift());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SHF_R_imm>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.shfr());
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.maxshift());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SHF_L_reg>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.shfl());
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.maxshift());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SHF_R_reg>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.shfr());
  out += ".";
  out += ToString(accessor.wmode());
  out += ".";
  out += ToString(accessor.maxshift());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LOP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lop());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.pop());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_invert()) out += "~";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_invert()) out += "~";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_LOP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lop());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.pop());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_invert()) out += "~";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jinv());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_LOP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lop());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.pop());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_invert()) out += "~";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_invert()) out += "~";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LOP32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lop());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_invert()) out += "~";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jinv());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LOP3_LUT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lut());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.pop());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += ",";
  out += std::format("{:#x}", accessor.Imm8());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LOP3_LUT_BImm>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lut());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += ",";
  out += std::format("{:#x}", accessor.Imm8());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LOP3_LUT_BConst>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lut());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += ",";
  out += std::format("{:#x}", accessor.Imm8());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LOP3>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lop());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.pop());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_invert()) out += "~";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_invert()) out += "~";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_invert()) out += "~";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LOP3_BImm>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lop());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_invert()) out += "~";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jinv());
  out += ",";
  out += " ";
  if (accessor.Rc_invert()) out += "~";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LOP3_Bconst>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lop());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_invert()) out += "~";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_invert()) out += "~";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Rc_invert()) out += "~";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::FLO>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.sh());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_invert()) out += "~";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_FLO>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.sh());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jinv());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_FLO>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.sh());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_invert()) out += "~";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ISET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_ISET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_ISET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_ISET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_ISET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_ISET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ISET_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_ISET_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_ISET_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_ISET_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_ISET_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_ISET_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ISETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_ISETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_ISETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_ISETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_ISETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_ISETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ISETP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_ISETP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_ISETP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_ISETP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_ISETP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_ISETP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ICMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_ICMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_ICMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_ICMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ICMP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_ICMP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_ICMP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_ICMP_U>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.us32());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::POPC>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Rb_invert()) out += "~";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_POPC>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jinv());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_POPC>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.srcConst_invert()) out += "~";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::XMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us16());
  out += ".";
  out += ToString(accessor.us16b());
  out += ".";
  out += ToString(accessor.psl());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.mrg());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ImmB_XMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us16());
  out += ".";
  out += ToString(accessor.us16b());
  out += ".";
  out += ToString(accessor.psl());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.mrg());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImmB_XMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us16());
  out += ".";
  out += ToString(accessor.us16b());
  out += ".";
  out += ToString(accessor.psl());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.mrg());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ConstB_XMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us16());
  out += ".";
  out += ToString(accessor.us16b());
  out += ".";
  out += ToString(accessor.psl());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.mrg());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.bsel());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ConstC_XMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.us16());
  out += ".";
  out += ToString(accessor.us16b());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VMAD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.vscale());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VADD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.po());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VABSDIFF>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VMNMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.mnmx());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VSETP_bop>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.icomp());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VSHL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b8_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b8_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b8_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b32_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_b32_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_b32_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_Imm_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a8_SImm_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_Imm_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::a32_SImm_VSHR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.wrap());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VABSDIFF4>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vred());
  out += ".";
  out += ToString(accessor.laneMsk());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.bsel());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_VABSDIFF4>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vred());
  out += ".";
  out += ToString(accessor.laneMsk());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SImm_VABSDIFF4>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dfmt());
  out += ".";
  out += ToString(accessor.safmt());
  out += ".";
  out += ToString(accessor.sbfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += ".";
  out += ToString(accessor.vred());
  out += ".";
  out += ToString(accessor.laneMsk());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.asel());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2F_1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2F_2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2F_2_64_32>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2F_1_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2F_2_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2F_2_64_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2F_1_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2F_2_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2F_1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2F_2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2F_2_64_32>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2F_1_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2F_2_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2F_2_64_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2F_1_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2F_2_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2F_1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2F_2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2F_2_64_32>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2F_1_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2F_2_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2F_2_64_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2F_1_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2F_2_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.fmts());
  out += ".";
  out += ToString(accessor.rnd());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2I_I64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2I_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::F2I_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2I_I64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2I_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_F2I_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2I_I64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2I_16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_F2I_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I2F>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I2F_F64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I2F64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I2F16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_I2F>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_I2F_F64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_I2F64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_I2F16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_I2F>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_I2F_F64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_I2F64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_I2F16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.rnd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I2I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I2I16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_I2I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_I2I16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ".";
  out += ToString(accessor.jneg());
  out += ".";
  out += ToString(accessor.jabs());
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_I2I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.bytesel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_I2I16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.dstfmt());
  out += ".";
  out += ToString(accessor.srcfmt());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ".";
  out += ToString(accessor.halfsel());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::MOV>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += std::format("{:#x}", accessor.quadMask());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_MOV>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += std::format("{:#x}", accessor.quadMask());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_MOV>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += std::format("{:#x}", accessor.quadMask());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::MOV32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += std::format("{:#x}", accessor.quadMask());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SEL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_SEL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_SEL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PRMT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.prmt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_PRMT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.prmt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_PRMT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.prmt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const1_PRMT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.prmt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SHFL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.shflmd());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::b_SHFL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.shflmd());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm5());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::c_b_SHFL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.shflmd());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm5());
  out += ",";
  out += std::format("{:#x}", accessor.uImm13());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::c_SHFL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.shflmd());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.uImm13());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::P2R>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.extract());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pr());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_P2R>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.extract());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pr());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_P2R>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.extract());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pr());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Simple_P2R>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.extract());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pr());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::R2P>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Pr());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.extract());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_R2P>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Pr());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.extract());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_R2P>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Pr());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.extract());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.dummyCC());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_CSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.CCTest());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  out += ToString(accessor.dummyCC());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.CCTest());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  out += ToString(accessor.inputCC());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_CSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.CCTest());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.inputCC());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.bop0());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Pc_not()) out += "!";
  out += ToString(accessor.Pc());
  out += ",";
  out += " ";
  if (accessor.Pb_not()) out += "!";
  out += ToString(accessor.Pb());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_PSET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.bop0());
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Pc_not()) out += "!";
  out += ToString(accessor.Pc());
  out += ",";
  out += " ";
  if (accessor.Pb_not()) out += "!";
  out += ToString(accessor.Pb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bop0());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Pc_not()) out += "!";
  out += ToString(accessor.Pc());
  out += ",";
  out += " ";
  if (accessor.Pb_not()) out += "!";
  out += ToString(accessor.Pb());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_PSETP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bop0());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Pc_not()) out += "!";
  out += ToString(accessor.Pc());
  out += ",";
  out += " ";
  if (accessor.Pb_not()) out += "!";
  out += ToString(accessor.Pb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::STP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.stpmode());
  out += ".";
  out += ToString(accessor.phase());
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TEX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.lc());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TEX_legacy_style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.lc());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TEX_B>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.lc());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TEX_B_legacy_style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.lc());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TEXS_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += " ";
  out += ToString(accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TEXS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += " ";
  out += ToString(accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TEXS_F16_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.f16());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += " ";
  out += ToString(accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TEXS_F16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.f16());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += " ";
  out += ToString(accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLDS_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ms());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += " ";
  out += ToString(accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLDS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ms());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += " ";
  out += ToString(accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLDS_F16_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.f16());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ms());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += " ";
  out += ToString(accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLDS_F16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.f16());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ms());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += " ";
  out += ToString(accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLD4S>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.tcomp());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLD4S_F16>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.f16());
  out += ".";
  out += ToString(accessor.tcomp());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd2());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ms());
  out += ".";
  out += ToString(accessor.clamp());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLD_B>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ms());
  out += ".";
  out += ToString(accessor.clamp());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLD4>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.tcomp());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLD4_B>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.tcomp());
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLD4_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.tcomp());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TLD4_B_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.tcomp());
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.dc());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TMML>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TMML_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TMML_B>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TMML_B_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.lod());
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lc());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXD_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lc());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXD_B>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.lc());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXD_B_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.lc());
  out += ".";
  out += ToString(accessor.toff());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += " ";
  out += ToString(accessor.paramA());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXQ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.query());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXQ_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.query());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXQ_Imm>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.query());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXQ_Imm_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.query());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXQ_B>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.query());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXQ_B_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.query());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXQ_B_Imm>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.query());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXQ_B_Imm_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.b());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.query());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::TXA_Legacy_Style>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ndv());
  out += ".";
  out += ToString(accessor.ndp());
  out += ".";
  out += ToString(accessor.phase());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.tid());
  out += ",";
  out += std::format("{:#x}", accessor.smp());
  out += ",";
  out += std::format("{:#x}", accessor.wmsk());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DEPBAR_LE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.le());
  out += " ";
  out += ToString(accessor.sbidx());
  out += ",";
  out += std::format("{:#x}", accessor.cnt());
  out += ",";
  out += std::format("{:#x}", accessor.dep_scbd());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DEPBAR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += std::format("{:#x}", accessor.dep_scbd());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::DEPBAR_ALL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.all());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::AL2P>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.io());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_AL2P>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.io());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ALD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.io());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ALD_PATCH>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.io());
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ALD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.io());
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ALD_PHYS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.io());
  out += ".";
  out += ToString(accessor.phys());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_AST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_AST_PATCH>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::AST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::AST_PHYS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.phys());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.srcAttr());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::OUT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.out());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_OUT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.out());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_OUT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.out());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PIXLD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.pixmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_PIXLD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.pixmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PIXLD_simple>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.pixmode());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pd());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LDC>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.ad());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_LDC>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.ad());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LDC_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.ad());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_LDC_64>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.ad());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_LD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LDG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_LDG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LDG_SPARSE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_LDG_SPARSE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LDL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_LDL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LDS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_LDS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LEA_LO_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.hilo());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += std::format("{:#x}", accessor.uImm5());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LEA_LO_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.hilo());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:#x}", accessor.uImm20());
  out += ",";
  out += std::format("{:#x}", accessor.uImm5());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LEA_LO_CONST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.hilo());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += std::format("{:#x}", accessor.uImm5());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LEA_HI_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.hi());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += ",";
  out += std::format("{:#x}", accessor.uImm5());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LEA_HI_CONST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.hi());
  out += ".";
  out += ToString(accessor.xmode());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ".";
  out += ToString(accessor.writeCC());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += ",";
  out += std::format("{:#x}", accessor.uImm5());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Plg());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Plg());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::STG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_STG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::STL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_STL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::STS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_STS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.atom());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.atom());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOM_CAS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOM_CAS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOM_CAS_Rb_and_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOM_CAS_Rb_and_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOM_CAS_RZ_and_Rc>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOM_CAS_RZ_and_Rc>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOM_SPARSE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.atom());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOM_CAS_SPARSE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOM_CAS_RZ_and_Rc_SPARSE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOM_CAS_Rb_and_RZ_SPARSE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOMS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.atom());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOMS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.atom());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOMS_CAS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOMS_CAS>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOMS_CAS_Rb_and_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOMS_CAS_Rb_and_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOMS_CAS_RZ_and_Rc>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOMS_CAS_RZ_and_Rc>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cas());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOMS_CAST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cast());
  out += ".";
  out += ToString(accessor.spin());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOMS_CAST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cast());
  out += ".";
  out += ToString(accessor.spin());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOMS_CAST_Rb_and_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cast());
  out += ".";
  out += ToString(accessor.spin());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOMS_CAST_Rb_and_RZ>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cast());
  out += ".";
  out += ToString(accessor.spin());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ATOMS_CAST_RZ_and_Rc>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cast());
  out += ".";
  out += ToString(accessor.spin());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_ATOMS_CAST_RZ_and_Rc>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cast());
  out += ".";
  out += ToString(accessor.spin());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::RED>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.redop());
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_RED>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.redop());
  out += ".";
  out += ToString(accessor.size());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.cctlop());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_CCTL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.cctlop());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTL_IVALL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.ivall());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTL_CI_IVALL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.ivall());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTL_QRY>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.op());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_CCTL_QRY>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.e());
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.op());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTLL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.cctllop());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::I_CCTLL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.cctllop());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.uImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTLL_IVALL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cctllop());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTLL_CRS_WBALL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cache());
  out += ".";
  out += ToString(accessor.cctllop());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTLT_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cctltop());
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTLT_IDX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cctltop());
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CCTLT_IVALL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.cctltop());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::MEMBAR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lvl());
  out += ".";
  out += ToString(accessor.ivall());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SULD_D_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SULD_D_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SULD_P_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.rgba());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SULD_P_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.rgba());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUST_D_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUST_D_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUST_P_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.rgba());
  out += ".";
  out += ToString(accessor.clamp());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUST_P_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.cop());
  out += ".";
  out += ToString(accessor.rgba());
  out += ".";
  out += ToString(accessor.clamp());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SURED_D_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.redop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SURED_D_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.redop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SURED_P_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.redop());
  out += ".";
  out += ToString(accessor.clamp());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SURED_P_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.redop());
  out += ".";
  out += ToString(accessor.clamp());
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_D_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_D_REG_SPARSE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_D_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_P_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_P_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_D_CAS_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_D_CAS_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.d());
  out += ".";
  out += ToString(accessor.ba());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.size());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_P_CAS_REG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  out += ToString(accessor.Rc());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SUATOM_P_CAS_IMM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.p());
  out += ".";
  out += ToString(accessor.dim());
  out += ".";
  out += ToString(accessor.suatomop());
  out += ".";
  out += ToString(accessor.clamp());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += std::format("{:#x}", accessor.suid());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BRA>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.uniform());
  out += ".";
  out += ToString(accessor.lmt());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BRA_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.uniform());
  out += ".";
  out += ToString(accessor.lmt());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BRX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lmt());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BRX_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lmt());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::JMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.uniform());
  out += ".";
  out += ToString(accessor.lmt());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ",";
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::JMP_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.uniform());
  out += ".";
  out += ToString(accessor.lmt());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::JMX>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lmt());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::JMX_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.lmt());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += ",";
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "+";
  out += std::format("{:#x}", accessor.sImm());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CAL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.inc());
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CAL_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.inc());
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PRET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.inc());
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PRET_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.inc());
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::JCAL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.inc());
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::JCAL_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.inc());
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SSY>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SSY_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PLONGJMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PLONGJMP_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PBK>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PBK_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PCNT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PCNT_c>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::RET>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LONGJMP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::KIL>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BRK>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CONT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::EXIT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.krc());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::PEXIT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SAM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::RAM>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BPT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bpt());
  out += std::format("{:#x}", accessor.sImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::RTT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.rttop());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IDE_EN>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.en());
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::IDE_DI>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.di());
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SYNC>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.CCTest());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NOP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NOP_trig>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.trig());
  out += " ";
  out += ToString(accessor.TestCC());
  out += ".";
  out += ToString(accessor.fcomp());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::S2R>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.SR());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::CS2R>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.SR());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::B2R_BAR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += std::format("{:#x}", accessor.barNum());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::B2R_RESULT>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmd());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pd());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::B2R_WARP>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmd());
  out += " ";
  out += ToString(accessor.Rd());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::R2B>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmd());
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::LEPC>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Sync>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Sync_b>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Sync_a_b>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += std::format("{:#x}", accessor.barNum());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Sync_a>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += std::format("{:#x}", accessor.barNum());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Arv>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Arv_a>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += std::format("{:#x}", accessor.barNum());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Arv_imm>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Arv_imm_a>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += std::format("{:#x}", accessor.barNum());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Red>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += ".";
  out += ToString(accessor.redmode());
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Red_b>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += ".";
  out += ToString(accessor.redmode());
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Red_a_b>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += ".";
  out += ToString(accessor.redmode());
  out += std::format("{:#x}", accessor.barNum());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Red_a>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += ".";
  out += ToString(accessor.redmode());
  out += std::format("{:#x}", accessor.barNum());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_syncall>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Scan>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_Scan_a>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += std::format("{:#x}", accessor.barNum());
  out += ",";
  out += " ";
  out += ToString(accessor.Rb());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_scan_imm>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += " ";
  out += ToString(accessor.Ra());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::BAR_scan_imm_a>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.barmode());
  out += std::format("{:#x}", accessor.barNum());
  out += ",";
  out += std::format("{:#x}", accessor.uImm());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VOTE_VTG>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.vtg());
  out += ".";
  out += ToString(accessor.vtgmode());
  out += std::format("{:#x}", accessor.uImm());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::VOTE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.voteop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SETCRSPTR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Ra());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::GETCRSPTR>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::SETLMEMBASE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Ra());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::GETLMEMBASE>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += " ";
  out += opcode;
  out += " ";
  out += ToString(accessor.Rd());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::ISBERD>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.io());
  out += ".";
  out += ToString(accessor.base());
  out += ".";
  out += ToString(accessor.skew());
  out += ".";
  out += ToString(accessor.size());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += "[";
  out += " ";
  out += ToString(accessor.Ra());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_bit_set());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hfma2__v2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.iswz_Rb_mod());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.iswz_Rc_reg_mod());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hfma2__v1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.Sb());
  out += ",";
  out += std::format("{:g}", accessor.Sb2());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.iswz_Rc_mod());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hfma2__v0>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Sb_negate()) out += "-";
  out += ToString(accessor.Sb());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.iswz_Rc_mod());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hset2__v2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.cmp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Rb_mod());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Ps_not()) out += "!";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hset2__v1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.cmp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.Sb());
  out += ",";
  out += std::format("{:g}", accessor.Sb2());
  out += ",";
  out += " ";
  if (accessor.Ps_not()) out += "!";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hset2__v0>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.cmp());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bop());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Sb_negate()) out += "-";
  out += ToString(accessor.Sb());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Ps_not()) out += "!";
  out += ToString(accessor.Ps());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hset2_bop__v1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.cmp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.Sb());
  out += ",";
  out += std::format("{:g}", accessor.Sb2());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hset2_bop__v0>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.cmp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Sb_negate()) out += "-";
  out += ToString(accessor.Sb());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hmul2_32i_>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.iswz_Ra_32i_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.imm());
  out += ",";
  out += std::format("{:g}", accessor.imm2());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hset2_bop__v2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.bval());
  out += ".";
  out += ToString(accessor.cmp());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Rb_mod());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hadd2__v0>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Sb_negate()) out += "-";
  if (accessor.Sb_absolute()) out += "|";
  out += ToString(accessor.Sb());
  if (accessor.Sb_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hadd2__v1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.Sb());
  out += ",";
  out += std::format("{:g}", accessor.Sb2());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hadd2__v2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Rb_mod());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hmul2__v2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Rb_mod());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hadd2_32i_>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.iswz_Ra_32i_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.imm());
  out += ",";
  out += std::format("{:g}", accessor.imm2());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hmul2__v1>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.Sb());
  out += ",";
  out += std::format("{:g}", accessor.Sb2());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::hmul2__v0>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra_mod());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Sb_negate()) out += "-";
  if (accessor.Sb_absolute()) out += "|";
  out += ToString(accessor.Sb());
  if (accessor.Sb_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::HSETP2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.h_and());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_HSETP2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.h_and());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  if (accessor.Rb_absolute()) out += "|";
  out += ToString(accessor.Rb());
  if (accessor.Rb_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Imm_HSETP2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.h_and());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ",";
  out += std::format("{:g}", accessor.uImmH0());
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Imm_HSETP2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.h_and());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.uImm());
  out += ",";
  out += std::format("{:g}", accessor.uImmH0());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::Const_HSETP2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.h_and());
  out += ".";
  out += ToString(accessor.ftz());
  out += ".";
  out += ToString(accessor.bopopt());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += ",";
  out += " ";
  if (accessor.Pa_not()) out += "!";
  out += ToString(accessor.Pa());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::NoBop_Const_HSETP2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fcomp());
  out += ".";
  out += ToString(accessor.h_and());
  out += ".";
  out += ToString(accessor.ftz());
  out += " ";
  out += ToString(accessor.Pd());
  out += ",";
  out += " ";
  out += ToString(accessor.nPd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  if (accessor.Ra_absolute()) out += "|";
  out += ToString(accessor.Ra());
  if (accessor.Ra_absolute()) out += "|";
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  if (accessor.srcConst_absolute()) out += "|";
  out += ToString(accessor.srcConst());
  if (accessor.srcConst_absolute()) out += "|";
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::HFMA2_32I>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.fImm());
  out += ",";
  out += std::format("{:g}", accessor.fImm1());
  out += ",";
  out += " ";
  if (accessor.Rc_negate()) out += "-";
  out += ToString(accessor.Rc());
  out += ".";
  out += ToString(accessor.reuse_src_c());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::HFMA2_32I_2>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.fmz());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += std::format("{:g}", accessor.fImm());
  out += ",";
  out += std::format("{:g}", accessor.fImm1());
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

static std::string PrintInstruction(const char* opcode, const Accessor<OpClass::HFMA2_CCST>& accessor) {
  std::string out;
  out.reserve(0x40);
  out += "@";
  out += " ";
  if (accessor.Pg_not()) out += "!";
  out += ToString(accessor.Pg());
  out += " ";
  out += opcode;
  out += ".";
  out += ToString(accessor.ofmt());
  out += ".";
  out += ToString(accessor.fmz());
  out += ".";
  out += ToString(accessor.sat());
  out += " ";
  out += ToString(accessor.Rd());
  out += ",";
  out += " ";
  if (accessor.Ra_negate()) out += "-";
  out += ToString(accessor.Ra());
  out += ".";
  out += ToString(accessor.iswz_Ra());
  out += ".";
  out += ToString(accessor.reuse_src_a());
  out += ",";
  out += " ";
  if (accessor.Rb_negate()) out += "-";
  out += ToString(accessor.Rb());
  out += ".";
  out += ToString(accessor.iswz_Rb());
  out += ".";
  out += ToString(accessor.reuse_src_b());
  out += ",";
  out += " ";
  if (accessor.srcConst_negate()) out += "-";
  out += ToString(accessor.srcConst());
  out += "[";
  out += std::format("{:#x}", accessor.constBank());
  out += "]";
  out += "[";
  out += std::format("{:#x}", accessor.immConstOffset());
  out += "]";
  out += " &";
  out += " ";
  out += ToString(accessor.req());
  out += "=";
  out += std::format("{:#x}", accessor.req_sb_bitset());
  out += " &";
  out += " ";
  out += ToString(accessor.rd());
  out += "=";
  out += std::format("{:#x}", accessor.src_rel_sb());
  out += " &";
  out += " ";
  out += ToString(accessor.wr());
  out += "=";
  out += std::format("{:#x}", accessor.dst_wr_sb());
  out += " ?";
  out += " ";
  out += ToString(accessor.usched_info());
  out += " ;";
  return out;
}

std::string Print(OpClass opclass, const char* opcode, std::uint64_t inst, std::uint64_t sched, std::uint64_t pc) {
  switch (opclass) {
    case OpClass::FFMA:
      return PrintInstruction(opcode, Accessor<OpClass::FFMA>(inst, sched, pc));
    case OpClass::Imm_FFMA:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FFMA>(inst, sched, pc));
    case OpClass::Const_FFMA:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FFMA>(inst, sched, pc));
    case OpClass::Const1_FFMA:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_FFMA>(inst, sched, pc));
    case OpClass::FFMA32I:
      return PrintInstruction(opcode, Accessor<OpClass::FFMA32I>(inst, sched, pc));
    case OpClass::FFMA32I_2:
      return PrintInstruction(opcode, Accessor<OpClass::FFMA32I_2>(inst, sched, pc));
    case OpClass::FADD:
      return PrintInstruction(opcode, Accessor<OpClass::FADD>(inst, sched, pc));
    case OpClass::Imm_FADD:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FADD>(inst, sched, pc));
    case OpClass::Const_FADD:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FADD>(inst, sched, pc));
    case OpClass::FADD32I:
      return PrintInstruction(opcode, Accessor<OpClass::FADD32I>(inst, sched, pc));
    case OpClass::FCMP:
      return PrintInstruction(opcode, Accessor<OpClass::FCMP>(inst, sched, pc));
    case OpClass::Imm_FCMP:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FCMP>(inst, sched, pc));
    case OpClass::Const_FCMP:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FCMP>(inst, sched, pc));
    case OpClass::Const1_FCMP:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_FCMP>(inst, sched, pc));
    case OpClass::FSWZADD:
      return PrintInstruction(opcode, Accessor<OpClass::FSWZADD>(inst, sched, pc));
    case OpClass::FMUL:
      return PrintInstruction(opcode, Accessor<OpClass::FMUL>(inst, sched, pc));
    case OpClass::Imm_FMUL:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FMUL>(inst, sched, pc));
    case OpClass::Const_FMUL:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FMUL>(inst, sched, pc));
    case OpClass::FMUL32I:
      return PrintInstruction(opcode, Accessor<OpClass::FMUL32I>(inst, sched, pc));
    case OpClass::FMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::FMNMX>(inst, sched, pc));
    case OpClass::Imm_FMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FMNMX>(inst, sched, pc));
    case OpClass::Const_FMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FMNMX>(inst, sched, pc));
    case OpClass::FSET:
      return PrintInstruction(opcode, Accessor<OpClass::FSET>(inst, sched, pc));
    case OpClass::NoBop_FSET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_FSET>(inst, sched, pc));
    case OpClass::Imm_FSET:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FSET>(inst, sched, pc));
    case OpClass::NoBop_Imm_FSET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_FSET>(inst, sched, pc));
    case OpClass::Const_FSET:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FSET>(inst, sched, pc));
    case OpClass::NoBop_Const_FSET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_FSET>(inst, sched, pc));
    case OpClass::FSETP:
      return PrintInstruction(opcode, Accessor<OpClass::FSETP>(inst, sched, pc));
    case OpClass::NoBop_FSETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_FSETP>(inst, sched, pc));
    case OpClass::Imm_FSETP:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FSETP>(inst, sched, pc));
    case OpClass::NoBop_Imm_FSETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_FSETP>(inst, sched, pc));
    case OpClass::Const_FSETP:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FSETP>(inst, sched, pc));
    case OpClass::NoBop_Const_FSETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_FSETP>(inst, sched, pc));
    case OpClass::IPA_1:
      return PrintInstruction(opcode, Accessor<OpClass::IPA_1>(inst, sched, pc));
    case OpClass::I_IPA_1:
      return PrintInstruction(opcode, Accessor<OpClass::I_IPA_1>(inst, sched, pc));
    case OpClass::IPA_2:
      return PrintInstruction(opcode, Accessor<OpClass::IPA_2>(inst, sched, pc));
    case OpClass::I_IPA_2:
      return PrintInstruction(opcode, Accessor<OpClass::I_IPA_2>(inst, sched, pc));
    case OpClass::RRO:
      return PrintInstruction(opcode, Accessor<OpClass::RRO>(inst, sched, pc));
    case OpClass::Imm_RRO:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_RRO>(inst, sched, pc));
    case OpClass::Const_RRO:
      return PrintInstruction(opcode, Accessor<OpClass::Const_RRO>(inst, sched, pc));
    case OpClass::MUFU:
      return PrintInstruction(opcode, Accessor<OpClass::MUFU>(inst, sched, pc));
    case OpClass::FCHK:
      return PrintInstruction(opcode, Accessor<OpClass::FCHK>(inst, sched, pc));
    case OpClass::Imm_FCHK:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FCHK>(inst, sched, pc));
    case OpClass::Const_FCHK:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FCHK>(inst, sched, pc));
    case OpClass::DFMA:
      return PrintInstruction(opcode, Accessor<OpClass::DFMA>(inst, sched, pc));
    case OpClass::Imm_DFMA:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_DFMA>(inst, sched, pc));
    case OpClass::Const_DFMA:
      return PrintInstruction(opcode, Accessor<OpClass::Const_DFMA>(inst, sched, pc));
    case OpClass::Const1_DFMA:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_DFMA>(inst, sched, pc));
    case OpClass::DADD:
      return PrintInstruction(opcode, Accessor<OpClass::DADD>(inst, sched, pc));
    case OpClass::Imm_DADD:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_DADD>(inst, sched, pc));
    case OpClass::Const_DADD:
      return PrintInstruction(opcode, Accessor<OpClass::Const_DADD>(inst, sched, pc));
    case OpClass::DMUL:
      return PrintInstruction(opcode, Accessor<OpClass::DMUL>(inst, sched, pc));
    case OpClass::Imm_DMUL:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_DMUL>(inst, sched, pc));
    case OpClass::Const_DMUL:
      return PrintInstruction(opcode, Accessor<OpClass::Const_DMUL>(inst, sched, pc));
    case OpClass::DMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::DMNMX>(inst, sched, pc));
    case OpClass::Imm_DMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_DMNMX>(inst, sched, pc));
    case OpClass::Const_DMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::Const_DMNMX>(inst, sched, pc));
    case OpClass::DSET:
      return PrintInstruction(opcode, Accessor<OpClass::DSET>(inst, sched, pc));
    case OpClass::NoBop_DSET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_DSET>(inst, sched, pc));
    case OpClass::Imm_DSET:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_DSET>(inst, sched, pc));
    case OpClass::NoBop_Imm_DSET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_DSET>(inst, sched, pc));
    case OpClass::Const_DSET:
      return PrintInstruction(opcode, Accessor<OpClass::Const_DSET>(inst, sched, pc));
    case OpClass::NoBop_Const_DSET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_DSET>(inst, sched, pc));
    case OpClass::DSETP:
      return PrintInstruction(opcode, Accessor<OpClass::DSETP>(inst, sched, pc));
    case OpClass::NoBop_DSETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_DSETP>(inst, sched, pc));
    case OpClass::Imm_DSETP:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_DSETP>(inst, sched, pc));
    case OpClass::NoBop_Imm_DSETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_DSETP>(inst, sched, pc));
    case OpClass::Const_DSETP:
      return PrintInstruction(opcode, Accessor<OpClass::Const_DSETP>(inst, sched, pc));
    case OpClass::NoBop_Const_DSETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_DSETP>(inst, sched, pc));
    case OpClass::IMAD:
      return PrintInstruction(opcode, Accessor<OpClass::IMAD>(inst, sched, pc));
    case OpClass::Imm_IMAD:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_IMAD>(inst, sched, pc));
    case OpClass::Const_IMAD:
      return PrintInstruction(opcode, Accessor<OpClass::Const_IMAD>(inst, sched, pc));
    case OpClass::Const1_IMAD:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_IMAD>(inst, sched, pc));
    case OpClass::IMAD32I:
      return PrintInstruction(opcode, Accessor<OpClass::IMAD32I>(inst, sched, pc));
    case OpClass::IMADSP:
      return PrintInstruction(opcode, Accessor<OpClass::IMADSP>(inst, sched, pc));
    case OpClass::Imm_IMADSP:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_IMADSP>(inst, sched, pc));
    case OpClass::Const_IMADSP:
      return PrintInstruction(opcode, Accessor<OpClass::Const_IMADSP>(inst, sched, pc));
    case OpClass::Const1_IMADSP:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_IMADSP>(inst, sched, pc));
    case OpClass::IMUL:
      return PrintInstruction(opcode, Accessor<OpClass::IMUL>(inst, sched, pc));
    case OpClass::Imm_IMUL:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_IMUL>(inst, sched, pc));
    case OpClass::Const_IMUL:
      return PrintInstruction(opcode, Accessor<OpClass::Const_IMUL>(inst, sched, pc));
    case OpClass::IMUL32I:
      return PrintInstruction(opcode, Accessor<OpClass::IMUL32I>(inst, sched, pc));
    case OpClass::IADD:
      return PrintInstruction(opcode, Accessor<OpClass::IADD>(inst, sched, pc));
    case OpClass::Imm_IADD:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_IADD>(inst, sched, pc));
    case OpClass::Const_IADD:
      return PrintInstruction(opcode, Accessor<OpClass::Const_IADD>(inst, sched, pc));
    case OpClass::IADD3:
      return PrintInstruction(opcode, Accessor<OpClass::IADD3>(inst, sched, pc));
    case OpClass::BImm_IADD3:
      return PrintInstruction(opcode, Accessor<OpClass::BImm_IADD3>(inst, sched, pc));
    case OpClass::BConst_IADD3:
      return PrintInstruction(opcode, Accessor<OpClass::BConst_IADD3>(inst, sched, pc));
    case OpClass::IADD32I:
      return PrintInstruction(opcode, Accessor<OpClass::IADD32I>(inst, sched, pc));
    case OpClass::ISCADD:
      return PrintInstruction(opcode, Accessor<OpClass::ISCADD>(inst, sched, pc));
    case OpClass::Imm_ISCADD:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_ISCADD>(inst, sched, pc));
    case OpClass::Const_ISCADD:
      return PrintInstruction(opcode, Accessor<OpClass::Const_ISCADD>(inst, sched, pc));
    case OpClass::ISCADD32I:
      return PrintInstruction(opcode, Accessor<OpClass::ISCADD32I>(inst, sched, pc));
    case OpClass::IMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::IMNMX>(inst, sched, pc));
    case OpClass::Imm_IMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_IMNMX>(inst, sched, pc));
    case OpClass::Const_IMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::Const_IMNMX>(inst, sched, pc));
    case OpClass::BFE:
      return PrintInstruction(opcode, Accessor<OpClass::BFE>(inst, sched, pc));
    case OpClass::Imm_BFE:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_BFE>(inst, sched, pc));
    case OpClass::Const_BFE:
      return PrintInstruction(opcode, Accessor<OpClass::Const_BFE>(inst, sched, pc));
    case OpClass::BFI:
      return PrintInstruction(opcode, Accessor<OpClass::BFI>(inst, sched, pc));
    case OpClass::Imm_BFI:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_BFI>(inst, sched, pc));
    case OpClass::Const_BFI:
      return PrintInstruction(opcode, Accessor<OpClass::Const_BFI>(inst, sched, pc));
    case OpClass::Const1_BFI:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_BFI>(inst, sched, pc));
    case OpClass::SHR:
      return PrintInstruction(opcode, Accessor<OpClass::SHR>(inst, sched, pc));
    case OpClass::Imm_SHR:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_SHR>(inst, sched, pc));
    case OpClass::Const_SHR:
      return PrintInstruction(opcode, Accessor<OpClass::Const_SHR>(inst, sched, pc));
    case OpClass::SHL:
      return PrintInstruction(opcode, Accessor<OpClass::SHL>(inst, sched, pc));
    case OpClass::Imm_SHL:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_SHL>(inst, sched, pc));
    case OpClass::Const_SHL:
      return PrintInstruction(opcode, Accessor<OpClass::Const_SHL>(inst, sched, pc));
    case OpClass::SHF_L_imm:
      return PrintInstruction(opcode, Accessor<OpClass::SHF_L_imm>(inst, sched, pc));
    case OpClass::SHF_R_imm:
      return PrintInstruction(opcode, Accessor<OpClass::SHF_R_imm>(inst, sched, pc));
    case OpClass::SHF_L_reg:
      return PrintInstruction(opcode, Accessor<OpClass::SHF_L_reg>(inst, sched, pc));
    case OpClass::SHF_R_reg:
      return PrintInstruction(opcode, Accessor<OpClass::SHF_R_reg>(inst, sched, pc));
    case OpClass::LOP:
      return PrintInstruction(opcode, Accessor<OpClass::LOP>(inst, sched, pc));
    case OpClass::Imm_LOP:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_LOP>(inst, sched, pc));
    case OpClass::Const_LOP:
      return PrintInstruction(opcode, Accessor<OpClass::Const_LOP>(inst, sched, pc));
    case OpClass::LOP32I:
      return PrintInstruction(opcode, Accessor<OpClass::LOP32I>(inst, sched, pc));
    case OpClass::LOP3_LUT:
      return PrintInstruction(opcode, Accessor<OpClass::LOP3_LUT>(inst, sched, pc));
    case OpClass::LOP3_LUT_BImm:
      return PrintInstruction(opcode, Accessor<OpClass::LOP3_LUT_BImm>(inst, sched, pc));
    case OpClass::LOP3_LUT_BConst:
      return PrintInstruction(opcode, Accessor<OpClass::LOP3_LUT_BConst>(inst, sched, pc));
    case OpClass::LOP3:
      return PrintInstruction(opcode, Accessor<OpClass::LOP3>(inst, sched, pc));
    case OpClass::LOP3_BImm:
      return PrintInstruction(opcode, Accessor<OpClass::LOP3_BImm>(inst, sched, pc));
    case OpClass::LOP3_Bconst:
      return PrintInstruction(opcode, Accessor<OpClass::LOP3_Bconst>(inst, sched, pc));
    case OpClass::FLO:
      return PrintInstruction(opcode, Accessor<OpClass::FLO>(inst, sched, pc));
    case OpClass::Imm_FLO:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_FLO>(inst, sched, pc));
    case OpClass::Const_FLO:
      return PrintInstruction(opcode, Accessor<OpClass::Const_FLO>(inst, sched, pc));
    case OpClass::ISET:
      return PrintInstruction(opcode, Accessor<OpClass::ISET>(inst, sched, pc));
    case OpClass::NoBop_ISET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_ISET>(inst, sched, pc));
    case OpClass::Imm_ISET:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_ISET>(inst, sched, pc));
    case OpClass::NoBop_Imm_ISET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_ISET>(inst, sched, pc));
    case OpClass::Const_ISET:
      return PrintInstruction(opcode, Accessor<OpClass::Const_ISET>(inst, sched, pc));
    case OpClass::NoBop_Const_ISET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_ISET>(inst, sched, pc));
    case OpClass::ISET_U:
      return PrintInstruction(opcode, Accessor<OpClass::ISET_U>(inst, sched, pc));
    case OpClass::NoBop_ISET_U:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_ISET_U>(inst, sched, pc));
    case OpClass::Imm_ISET_U:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_ISET_U>(inst, sched, pc));
    case OpClass::NoBop_Imm_ISET_U:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_ISET_U>(inst, sched, pc));
    case OpClass::Const_ISET_U:
      return PrintInstruction(opcode, Accessor<OpClass::Const_ISET_U>(inst, sched, pc));
    case OpClass::NoBop_Const_ISET_U:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_ISET_U>(inst, sched, pc));
    case OpClass::ISETP:
      return PrintInstruction(opcode, Accessor<OpClass::ISETP>(inst, sched, pc));
    case OpClass::NoBop_ISETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_ISETP>(inst, sched, pc));
    case OpClass::Imm_ISETP:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_ISETP>(inst, sched, pc));
    case OpClass::NoBop_Imm_ISETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_ISETP>(inst, sched, pc));
    case OpClass::Const_ISETP:
      return PrintInstruction(opcode, Accessor<OpClass::Const_ISETP>(inst, sched, pc));
    case OpClass::NoBop_Const_ISETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_ISETP>(inst, sched, pc));
    case OpClass::ISETP_U:
      return PrintInstruction(opcode, Accessor<OpClass::ISETP_U>(inst, sched, pc));
    case OpClass::NoBop_ISETP_U:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_ISETP_U>(inst, sched, pc));
    case OpClass::Imm_ISETP_U:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_ISETP_U>(inst, sched, pc));
    case OpClass::NoBop_Imm_ISETP_U:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_ISETP_U>(inst, sched, pc));
    case OpClass::Const_ISETP_U:
      return PrintInstruction(opcode, Accessor<OpClass::Const_ISETP_U>(inst, sched, pc));
    case OpClass::NoBop_Const_ISETP_U:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_ISETP_U>(inst, sched, pc));
    case OpClass::ICMP:
      return PrintInstruction(opcode, Accessor<OpClass::ICMP>(inst, sched, pc));
    case OpClass::Imm_ICMP:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_ICMP>(inst, sched, pc));
    case OpClass::Const_ICMP:
      return PrintInstruction(opcode, Accessor<OpClass::Const_ICMP>(inst, sched, pc));
    case OpClass::Const1_ICMP:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_ICMP>(inst, sched, pc));
    case OpClass::ICMP_U:
      return PrintInstruction(opcode, Accessor<OpClass::ICMP_U>(inst, sched, pc));
    case OpClass::Imm_ICMP_U:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_ICMP_U>(inst, sched, pc));
    case OpClass::Const_ICMP_U:
      return PrintInstruction(opcode, Accessor<OpClass::Const_ICMP_U>(inst, sched, pc));
    case OpClass::Const1_ICMP_U:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_ICMP_U>(inst, sched, pc));
    case OpClass::POPC:
      return PrintInstruction(opcode, Accessor<OpClass::POPC>(inst, sched, pc));
    case OpClass::Imm_POPC:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_POPC>(inst, sched, pc));
    case OpClass::Const_POPC:
      return PrintInstruction(opcode, Accessor<OpClass::Const_POPC>(inst, sched, pc));
    case OpClass::XMAD:
      return PrintInstruction(opcode, Accessor<OpClass::XMAD>(inst, sched, pc));
    case OpClass::ImmB_XMAD:
      return PrintInstruction(opcode, Accessor<OpClass::ImmB_XMAD>(inst, sched, pc));
    case OpClass::SImmB_XMAD:
      return PrintInstruction(opcode, Accessor<OpClass::SImmB_XMAD>(inst, sched, pc));
    case OpClass::ConstB_XMAD:
      return PrintInstruction(opcode, Accessor<OpClass::ConstB_XMAD>(inst, sched, pc));
    case OpClass::ConstC_XMAD:
      return PrintInstruction(opcode, Accessor<OpClass::ConstC_XMAD>(inst, sched, pc));
    case OpClass::VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::VMAD>(inst, sched, pc));
    case OpClass::a8_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VMAD>(inst, sched, pc));
    case OpClass::a32_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VMAD>(inst, sched, pc));
    case OpClass::b8_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VMAD>(inst, sched, pc));
    case OpClass::a8_b8_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VMAD>(inst, sched, pc));
    case OpClass::a32_b8_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VMAD>(inst, sched, pc));
    case OpClass::b32_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VMAD>(inst, sched, pc));
    case OpClass::a8_b32_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VMAD>(inst, sched, pc));
    case OpClass::a32_b32_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VMAD>(inst, sched, pc));
    case OpClass::Imm_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VMAD>(inst, sched, pc));
    case OpClass::SImm_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VMAD>(inst, sched, pc));
    case OpClass::a8_Imm_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VMAD>(inst, sched, pc));
    case OpClass::a8_SImm_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VMAD>(inst, sched, pc));
    case OpClass::a32_Imm_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VMAD>(inst, sched, pc));
    case OpClass::a32_SImm_VMAD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VMAD>(inst, sched, pc));
    case OpClass::VADD:
      return PrintInstruction(opcode, Accessor<OpClass::VADD>(inst, sched, pc));
    case OpClass::a8_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VADD>(inst, sched, pc));
    case OpClass::a32_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VADD>(inst, sched, pc));
    case OpClass::b8_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VADD>(inst, sched, pc));
    case OpClass::a8_b8_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VADD>(inst, sched, pc));
    case OpClass::a32_b8_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VADD>(inst, sched, pc));
    case OpClass::b32_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VADD>(inst, sched, pc));
    case OpClass::a8_b32_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VADD>(inst, sched, pc));
    case OpClass::a32_b32_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VADD>(inst, sched, pc));
    case OpClass::Imm_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VADD>(inst, sched, pc));
    case OpClass::SImm_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VADD>(inst, sched, pc));
    case OpClass::a8_Imm_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VADD>(inst, sched, pc));
    case OpClass::a8_SImm_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VADD>(inst, sched, pc));
    case OpClass::a32_Imm_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VADD>(inst, sched, pc));
    case OpClass::a32_SImm_VADD:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VADD>(inst, sched, pc));
    case OpClass::VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::VABSDIFF>(inst, sched, pc));
    case OpClass::a8_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VABSDIFF>(inst, sched, pc));
    case OpClass::a32_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VABSDIFF>(inst, sched, pc));
    case OpClass::b8_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VABSDIFF>(inst, sched, pc));
    case OpClass::a8_b8_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VABSDIFF>(inst, sched, pc));
    case OpClass::a32_b8_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VABSDIFF>(inst, sched, pc));
    case OpClass::b32_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VABSDIFF>(inst, sched, pc));
    case OpClass::a8_b32_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VABSDIFF>(inst, sched, pc));
    case OpClass::a32_b32_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VABSDIFF>(inst, sched, pc));
    case OpClass::Imm_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VABSDIFF>(inst, sched, pc));
    case OpClass::SImm_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VABSDIFF>(inst, sched, pc));
    case OpClass::a8_Imm_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VABSDIFF>(inst, sched, pc));
    case OpClass::a8_SImm_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VABSDIFF>(inst, sched, pc));
    case OpClass::a32_Imm_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VABSDIFF>(inst, sched, pc));
    case OpClass::a32_SImm_VABSDIFF:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VABSDIFF>(inst, sched, pc));
    case OpClass::VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::VMNMX>(inst, sched, pc));
    case OpClass::a8_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VMNMX>(inst, sched, pc));
    case OpClass::a32_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VMNMX>(inst, sched, pc));
    case OpClass::b8_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VMNMX>(inst, sched, pc));
    case OpClass::a8_b8_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VMNMX>(inst, sched, pc));
    case OpClass::a32_b8_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VMNMX>(inst, sched, pc));
    case OpClass::b32_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VMNMX>(inst, sched, pc));
    case OpClass::a8_b32_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VMNMX>(inst, sched, pc));
    case OpClass::a32_b32_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VMNMX>(inst, sched, pc));
    case OpClass::Imm_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VMNMX>(inst, sched, pc));
    case OpClass::SImm_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VMNMX>(inst, sched, pc));
    case OpClass::a8_Imm_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VMNMX>(inst, sched, pc));
    case OpClass::a8_SImm_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VMNMX>(inst, sched, pc));
    case OpClass::a32_Imm_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VMNMX>(inst, sched, pc));
    case OpClass::a32_SImm_VMNMX:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VMNMX>(inst, sched, pc));
    case OpClass::VSET:
      return PrintInstruction(opcode, Accessor<OpClass::VSET>(inst, sched, pc));
    case OpClass::a8_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VSET>(inst, sched, pc));
    case OpClass::a32_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VSET>(inst, sched, pc));
    case OpClass::b8_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VSET>(inst, sched, pc));
    case OpClass::a8_b8_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VSET>(inst, sched, pc));
    case OpClass::a32_b8_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VSET>(inst, sched, pc));
    case OpClass::b32_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VSET>(inst, sched, pc));
    case OpClass::a8_b32_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VSET>(inst, sched, pc));
    case OpClass::a32_b32_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VSET>(inst, sched, pc));
    case OpClass::Imm_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VSET>(inst, sched, pc));
    case OpClass::SImm_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VSET>(inst, sched, pc));
    case OpClass::a8_Imm_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VSET>(inst, sched, pc));
    case OpClass::a8_SImm_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VSET>(inst, sched, pc));
    case OpClass::a32_Imm_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VSET>(inst, sched, pc));
    case OpClass::a32_SImm_VSET:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VSET>(inst, sched, pc));
    case OpClass::VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::VSETP>(inst, sched, pc));
    case OpClass::a8_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VSETP>(inst, sched, pc));
    case OpClass::a32_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VSETP>(inst, sched, pc));
    case OpClass::b8_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VSETP>(inst, sched, pc));
    case OpClass::a8_b8_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VSETP>(inst, sched, pc));
    case OpClass::a32_b8_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VSETP>(inst, sched, pc));
    case OpClass::b32_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VSETP>(inst, sched, pc));
    case OpClass::a8_b32_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VSETP>(inst, sched, pc));
    case OpClass::a32_b32_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VSETP>(inst, sched, pc));
    case OpClass::Imm_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VSETP>(inst, sched, pc));
    case OpClass::SImm_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VSETP>(inst, sched, pc));
    case OpClass::a8_Imm_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VSETP>(inst, sched, pc));
    case OpClass::a8_SImm_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VSETP>(inst, sched, pc));
    case OpClass::a32_Imm_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VSETP>(inst, sched, pc));
    case OpClass::a32_SImm_VSETP:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VSETP>(inst, sched, pc));
    case OpClass::VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::VSETP_bop>(inst, sched, pc));
    case OpClass::a8_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VSETP_bop>(inst, sched, pc));
    case OpClass::a32_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VSETP_bop>(inst, sched, pc));
    case OpClass::b8_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VSETP_bop>(inst, sched, pc));
    case OpClass::a8_b8_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VSETP_bop>(inst, sched, pc));
    case OpClass::a32_b8_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VSETP_bop>(inst, sched, pc));
    case OpClass::b32_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VSETP_bop>(inst, sched, pc));
    case OpClass::a8_b32_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VSETP_bop>(inst, sched, pc));
    case OpClass::a32_b32_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VSETP_bop>(inst, sched, pc));
    case OpClass::Imm_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VSETP_bop>(inst, sched, pc));
    case OpClass::SImm_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VSETP_bop>(inst, sched, pc));
    case OpClass::a8_Imm_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VSETP_bop>(inst, sched, pc));
    case OpClass::a8_SImm_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VSETP_bop>(inst, sched, pc));
    case OpClass::a32_Imm_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VSETP_bop>(inst, sched, pc));
    case OpClass::a32_SImm_VSETP_bop:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VSETP_bop>(inst, sched, pc));
    case OpClass::VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::VSHL>(inst, sched, pc));
    case OpClass::a8_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VSHL>(inst, sched, pc));
    case OpClass::a32_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VSHL>(inst, sched, pc));
    case OpClass::b8_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VSHL>(inst, sched, pc));
    case OpClass::a8_b8_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VSHL>(inst, sched, pc));
    case OpClass::a32_b8_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VSHL>(inst, sched, pc));
    case OpClass::b32_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VSHL>(inst, sched, pc));
    case OpClass::a8_b32_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VSHL>(inst, sched, pc));
    case OpClass::a32_b32_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VSHL>(inst, sched, pc));
    case OpClass::Imm_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VSHL>(inst, sched, pc));
    case OpClass::SImm_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VSHL>(inst, sched, pc));
    case OpClass::a8_Imm_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VSHL>(inst, sched, pc));
    case OpClass::a8_SImm_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VSHL>(inst, sched, pc));
    case OpClass::a32_Imm_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VSHL>(inst, sched, pc));
    case OpClass::a32_SImm_VSHL:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VSHL>(inst, sched, pc));
    case OpClass::VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::VSHR>(inst, sched, pc));
    case OpClass::a8_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a8_VSHR>(inst, sched, pc));
    case OpClass::a32_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a32_VSHR>(inst, sched, pc));
    case OpClass::b8_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::b8_VSHR>(inst, sched, pc));
    case OpClass::a8_b8_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b8_VSHR>(inst, sched, pc));
    case OpClass::a32_b8_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b8_VSHR>(inst, sched, pc));
    case OpClass::b32_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::b32_VSHR>(inst, sched, pc));
    case OpClass::a8_b32_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a8_b32_VSHR>(inst, sched, pc));
    case OpClass::a32_b32_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a32_b32_VSHR>(inst, sched, pc));
    case OpClass::Imm_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VSHR>(inst, sched, pc));
    case OpClass::SImm_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VSHR>(inst, sched, pc));
    case OpClass::a8_Imm_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a8_Imm_VSHR>(inst, sched, pc));
    case OpClass::a8_SImm_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a8_SImm_VSHR>(inst, sched, pc));
    case OpClass::a32_Imm_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a32_Imm_VSHR>(inst, sched, pc));
    case OpClass::a32_SImm_VSHR:
      return PrintInstruction(opcode, Accessor<OpClass::a32_SImm_VSHR>(inst, sched, pc));
    case OpClass::VABSDIFF4:
      return PrintInstruction(opcode, Accessor<OpClass::VABSDIFF4>(inst, sched, pc));
    case OpClass::Imm_VABSDIFF4:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_VABSDIFF4>(inst, sched, pc));
    case OpClass::SImm_VABSDIFF4:
      return PrintInstruction(opcode, Accessor<OpClass::SImm_VABSDIFF4>(inst, sched, pc));
    case OpClass::F2F_1:
      return PrintInstruction(opcode, Accessor<OpClass::F2F_1>(inst, sched, pc));
    case OpClass::F2F_2:
      return PrintInstruction(opcode, Accessor<OpClass::F2F_2>(inst, sched, pc));
    case OpClass::F2F_2_64_32:
      return PrintInstruction(opcode, Accessor<OpClass::F2F_2_64_32>(inst, sched, pc));
    case OpClass::F2F_1_16:
      return PrintInstruction(opcode, Accessor<OpClass::F2F_1_16>(inst, sched, pc));
    case OpClass::F2F_2_16:
      return PrintInstruction(opcode, Accessor<OpClass::F2F_2_16>(inst, sched, pc));
    case OpClass::F2F_2_64_16:
      return PrintInstruction(opcode, Accessor<OpClass::F2F_2_64_16>(inst, sched, pc));
    case OpClass::F2F_1_64:
      return PrintInstruction(opcode, Accessor<OpClass::F2F_1_64>(inst, sched, pc));
    case OpClass::F2F_2_64:
      return PrintInstruction(opcode, Accessor<OpClass::F2F_2_64>(inst, sched, pc));
    case OpClass::Imm_F2F_1:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2F_1>(inst, sched, pc));
    case OpClass::Imm_F2F_2:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2F_2>(inst, sched, pc));
    case OpClass::Imm_F2F_2_64_32:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2F_2_64_32>(inst, sched, pc));
    case OpClass::Imm_F2F_1_16:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2F_1_16>(inst, sched, pc));
    case OpClass::Imm_F2F_2_16:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2F_2_16>(inst, sched, pc));
    case OpClass::Imm_F2F_2_64_16:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2F_2_64_16>(inst, sched, pc));
    case OpClass::Imm_F2F_1_64:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2F_1_64>(inst, sched, pc));
    case OpClass::Imm_F2F_2_64:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2F_2_64>(inst, sched, pc));
    case OpClass::Const_F2F_1:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2F_1>(inst, sched, pc));
    case OpClass::Const_F2F_2:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2F_2>(inst, sched, pc));
    case OpClass::Const_F2F_2_64_32:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2F_2_64_32>(inst, sched, pc));
    case OpClass::Const_F2F_1_16:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2F_1_16>(inst, sched, pc));
    case OpClass::Const_F2F_2_16:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2F_2_16>(inst, sched, pc));
    case OpClass::Const_F2F_2_64_16:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2F_2_64_16>(inst, sched, pc));
    case OpClass::Const_F2F_1_64:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2F_1_64>(inst, sched, pc));
    case OpClass::Const_F2F_2_64:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2F_2_64>(inst, sched, pc));
    case OpClass::F2I:
      return PrintInstruction(opcode, Accessor<OpClass::F2I>(inst, sched, pc));
    case OpClass::F2I_I64:
      return PrintInstruction(opcode, Accessor<OpClass::F2I_I64>(inst, sched, pc));
    case OpClass::F2I_16:
      return PrintInstruction(opcode, Accessor<OpClass::F2I_16>(inst, sched, pc));
    case OpClass::F2I_64:
      return PrintInstruction(opcode, Accessor<OpClass::F2I_64>(inst, sched, pc));
    case OpClass::Imm_F2I:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2I>(inst, sched, pc));
    case OpClass::Imm_F2I_I64:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2I_I64>(inst, sched, pc));
    case OpClass::Imm_F2I_16:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2I_16>(inst, sched, pc));
    case OpClass::Imm_F2I_64:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_F2I_64>(inst, sched, pc));
    case OpClass::Const_F2I:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2I>(inst, sched, pc));
    case OpClass::Const_F2I_I64:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2I_I64>(inst, sched, pc));
    case OpClass::Const_F2I_16:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2I_16>(inst, sched, pc));
    case OpClass::Const_F2I_64:
      return PrintInstruction(opcode, Accessor<OpClass::Const_F2I_64>(inst, sched, pc));
    case OpClass::I2F:
      return PrintInstruction(opcode, Accessor<OpClass::I2F>(inst, sched, pc));
    case OpClass::I2F_F64:
      return PrintInstruction(opcode, Accessor<OpClass::I2F_F64>(inst, sched, pc));
    case OpClass::I2F64:
      return PrintInstruction(opcode, Accessor<OpClass::I2F64>(inst, sched, pc));
    case OpClass::I2F16:
      return PrintInstruction(opcode, Accessor<OpClass::I2F16>(inst, sched, pc));
    case OpClass::Imm_I2F:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_I2F>(inst, sched, pc));
    case OpClass::Imm_I2F_F64:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_I2F_F64>(inst, sched, pc));
    case OpClass::Imm_I2F64:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_I2F64>(inst, sched, pc));
    case OpClass::Imm_I2F16:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_I2F16>(inst, sched, pc));
    case OpClass::Const_I2F:
      return PrintInstruction(opcode, Accessor<OpClass::Const_I2F>(inst, sched, pc));
    case OpClass::Const_I2F_F64:
      return PrintInstruction(opcode, Accessor<OpClass::Const_I2F_F64>(inst, sched, pc));
    case OpClass::Const_I2F64:
      return PrintInstruction(opcode, Accessor<OpClass::Const_I2F64>(inst, sched, pc));
    case OpClass::Const_I2F16:
      return PrintInstruction(opcode, Accessor<OpClass::Const_I2F16>(inst, sched, pc));
    case OpClass::I2I:
      return PrintInstruction(opcode, Accessor<OpClass::I2I>(inst, sched, pc));
    case OpClass::I2I16:
      return PrintInstruction(opcode, Accessor<OpClass::I2I16>(inst, sched, pc));
    case OpClass::Imm_I2I:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_I2I>(inst, sched, pc));
    case OpClass::Imm_I2I16:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_I2I16>(inst, sched, pc));
    case OpClass::Const_I2I:
      return PrintInstruction(opcode, Accessor<OpClass::Const_I2I>(inst, sched, pc));
    case OpClass::Const_I2I16:
      return PrintInstruction(opcode, Accessor<OpClass::Const_I2I16>(inst, sched, pc));
    case OpClass::MOV:
      return PrintInstruction(opcode, Accessor<OpClass::MOV>(inst, sched, pc));
    case OpClass::Imm_MOV:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_MOV>(inst, sched, pc));
    case OpClass::Const_MOV:
      return PrintInstruction(opcode, Accessor<OpClass::Const_MOV>(inst, sched, pc));
    case OpClass::MOV32I:
      return PrintInstruction(opcode, Accessor<OpClass::MOV32I>(inst, sched, pc));
    case OpClass::SEL:
      return PrintInstruction(opcode, Accessor<OpClass::SEL>(inst, sched, pc));
    case OpClass::Imm_SEL:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_SEL>(inst, sched, pc));
    case OpClass::Const_SEL:
      return PrintInstruction(opcode, Accessor<OpClass::Const_SEL>(inst, sched, pc));
    case OpClass::PRMT:
      return PrintInstruction(opcode, Accessor<OpClass::PRMT>(inst, sched, pc));
    case OpClass::Imm_PRMT:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_PRMT>(inst, sched, pc));
    case OpClass::Const_PRMT:
      return PrintInstruction(opcode, Accessor<OpClass::Const_PRMT>(inst, sched, pc));
    case OpClass::Const1_PRMT:
      return PrintInstruction(opcode, Accessor<OpClass::Const1_PRMT>(inst, sched, pc));
    case OpClass::SHFL:
      return PrintInstruction(opcode, Accessor<OpClass::SHFL>(inst, sched, pc));
    case OpClass::b_SHFL:
      return PrintInstruction(opcode, Accessor<OpClass::b_SHFL>(inst, sched, pc));
    case OpClass::c_b_SHFL:
      return PrintInstruction(opcode, Accessor<OpClass::c_b_SHFL>(inst, sched, pc));
    case OpClass::c_SHFL:
      return PrintInstruction(opcode, Accessor<OpClass::c_SHFL>(inst, sched, pc));
    case OpClass::P2R:
      return PrintInstruction(opcode, Accessor<OpClass::P2R>(inst, sched, pc));
    case OpClass::Imm_P2R:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_P2R>(inst, sched, pc));
    case OpClass::Const_P2R:
      return PrintInstruction(opcode, Accessor<OpClass::Const_P2R>(inst, sched, pc));
    case OpClass::Simple_P2R:
      return PrintInstruction(opcode, Accessor<OpClass::Simple_P2R>(inst, sched, pc));
    case OpClass::R2P:
      return PrintInstruction(opcode, Accessor<OpClass::R2P>(inst, sched, pc));
    case OpClass::Imm_R2P:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_R2P>(inst, sched, pc));
    case OpClass::Const_R2P:
      return PrintInstruction(opcode, Accessor<OpClass::Const_R2P>(inst, sched, pc));
    case OpClass::CSET:
      return PrintInstruction(opcode, Accessor<OpClass::CSET>(inst, sched, pc));
    case OpClass::NoBop_CSET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_CSET>(inst, sched, pc));
    case OpClass::CSETP:
      return PrintInstruction(opcode, Accessor<OpClass::CSETP>(inst, sched, pc));
    case OpClass::NoBop_CSETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_CSETP>(inst, sched, pc));
    case OpClass::PSET:
      return PrintInstruction(opcode, Accessor<OpClass::PSET>(inst, sched, pc));
    case OpClass::NoBop_PSET:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_PSET>(inst, sched, pc));
    case OpClass::PSETP:
      return PrintInstruction(opcode, Accessor<OpClass::PSETP>(inst, sched, pc));
    case OpClass::NoBop_PSETP:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_PSETP>(inst, sched, pc));
    case OpClass::STP:
      return PrintInstruction(opcode, Accessor<OpClass::STP>(inst, sched, pc));
    case OpClass::TEX:
      return PrintInstruction(opcode, Accessor<OpClass::TEX>(inst, sched, pc));
    case OpClass::TEX_legacy_style:
      return PrintInstruction(opcode, Accessor<OpClass::TEX_legacy_style>(inst, sched, pc));
    case OpClass::TEX_B:
      return PrintInstruction(opcode, Accessor<OpClass::TEX_B>(inst, sched, pc));
    case OpClass::TEX_B_legacy_style:
      return PrintInstruction(opcode, Accessor<OpClass::TEX_B_legacy_style>(inst, sched, pc));
    case OpClass::TEXS_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::TEXS_RZ>(inst, sched, pc));
    case OpClass::TEXS:
      return PrintInstruction(opcode, Accessor<OpClass::TEXS>(inst, sched, pc));
    case OpClass::TEXS_F16_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::TEXS_F16_RZ>(inst, sched, pc));
    case OpClass::TEXS_F16:
      return PrintInstruction(opcode, Accessor<OpClass::TEXS_F16>(inst, sched, pc));
    case OpClass::TLDS_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::TLDS_RZ>(inst, sched, pc));
    case OpClass::TLDS:
      return PrintInstruction(opcode, Accessor<OpClass::TLDS>(inst, sched, pc));
    case OpClass::TLDS_F16_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::TLDS_F16_RZ>(inst, sched, pc));
    case OpClass::TLDS_F16:
      return PrintInstruction(opcode, Accessor<OpClass::TLDS_F16>(inst, sched, pc));
    case OpClass::TLD4S:
      return PrintInstruction(opcode, Accessor<OpClass::TLD4S>(inst, sched, pc));
    case OpClass::TLD4S_F16:
      return PrintInstruction(opcode, Accessor<OpClass::TLD4S_F16>(inst, sched, pc));
    case OpClass::TLD:
      return PrintInstruction(opcode, Accessor<OpClass::TLD>(inst, sched, pc));
    case OpClass::TLD_B:
      return PrintInstruction(opcode, Accessor<OpClass::TLD_B>(inst, sched, pc));
    case OpClass::TLD4:
      return PrintInstruction(opcode, Accessor<OpClass::TLD4>(inst, sched, pc));
    case OpClass::TLD4_B:
      return PrintInstruction(opcode, Accessor<OpClass::TLD4_B>(inst, sched, pc));
    case OpClass::TLD4_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TLD4_Legacy_Style>(inst, sched, pc));
    case OpClass::TLD4_B_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TLD4_B_Legacy_Style>(inst, sched, pc));
    case OpClass::TMML:
      return PrintInstruction(opcode, Accessor<OpClass::TMML>(inst, sched, pc));
    case OpClass::TMML_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TMML_Legacy_Style>(inst, sched, pc));
    case OpClass::TMML_B:
      return PrintInstruction(opcode, Accessor<OpClass::TMML_B>(inst, sched, pc));
    case OpClass::TMML_B_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TMML_B_Legacy_Style>(inst, sched, pc));
    case OpClass::TXD:
      return PrintInstruction(opcode, Accessor<OpClass::TXD>(inst, sched, pc));
    case OpClass::TXD_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TXD_Legacy_Style>(inst, sched, pc));
    case OpClass::TXD_B:
      return PrintInstruction(opcode, Accessor<OpClass::TXD_B>(inst, sched, pc));
    case OpClass::TXD_B_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TXD_B_Legacy_Style>(inst, sched, pc));
    case OpClass::TXQ:
      return PrintInstruction(opcode, Accessor<OpClass::TXQ>(inst, sched, pc));
    case OpClass::TXQ_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TXQ_Legacy_Style>(inst, sched, pc));
    case OpClass::TXQ_Imm:
      return PrintInstruction(opcode, Accessor<OpClass::TXQ_Imm>(inst, sched, pc));
    case OpClass::TXQ_Imm_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TXQ_Imm_Legacy_Style>(inst, sched, pc));
    case OpClass::TXQ_B:
      return PrintInstruction(opcode, Accessor<OpClass::TXQ_B>(inst, sched, pc));
    case OpClass::TXQ_B_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TXQ_B_Legacy_Style>(inst, sched, pc));
    case OpClass::TXQ_B_Imm:
      return PrintInstruction(opcode, Accessor<OpClass::TXQ_B_Imm>(inst, sched, pc));
    case OpClass::TXQ_B_Imm_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TXQ_B_Imm_Legacy_Style>(inst, sched, pc));
    case OpClass::TXA:
      return PrintInstruction(opcode, Accessor<OpClass::TXA>(inst, sched, pc));
    case OpClass::TXA_Legacy_Style:
      return PrintInstruction(opcode, Accessor<OpClass::TXA_Legacy_Style>(inst, sched, pc));
    case OpClass::DEPBAR_LE:
      return PrintInstruction(opcode, Accessor<OpClass::DEPBAR_LE>(inst, sched, pc));
    case OpClass::DEPBAR:
      return PrintInstruction(opcode, Accessor<OpClass::DEPBAR>(inst, sched, pc));
    case OpClass::DEPBAR_ALL:
      return PrintInstruction(opcode, Accessor<OpClass::DEPBAR_ALL>(inst, sched, pc));
    case OpClass::AL2P:
      return PrintInstruction(opcode, Accessor<OpClass::AL2P>(inst, sched, pc));
    case OpClass::I_AL2P:
      return PrintInstruction(opcode, Accessor<OpClass::I_AL2P>(inst, sched, pc));
    case OpClass::I_ALD:
      return PrintInstruction(opcode, Accessor<OpClass::I_ALD>(inst, sched, pc));
    case OpClass::I_ALD_PATCH:
      return PrintInstruction(opcode, Accessor<OpClass::I_ALD_PATCH>(inst, sched, pc));
    case OpClass::ALD:
      return PrintInstruction(opcode, Accessor<OpClass::ALD>(inst, sched, pc));
    case OpClass::ALD_PHYS:
      return PrintInstruction(opcode, Accessor<OpClass::ALD_PHYS>(inst, sched, pc));
    case OpClass::I_AST:
      return PrintInstruction(opcode, Accessor<OpClass::I_AST>(inst, sched, pc));
    case OpClass::I_AST_PATCH:
      return PrintInstruction(opcode, Accessor<OpClass::I_AST_PATCH>(inst, sched, pc));
    case OpClass::AST:
      return PrintInstruction(opcode, Accessor<OpClass::AST>(inst, sched, pc));
    case OpClass::AST_PHYS:
      return PrintInstruction(opcode, Accessor<OpClass::AST_PHYS>(inst, sched, pc));
    case OpClass::OUT:
      return PrintInstruction(opcode, Accessor<OpClass::OUT>(inst, sched, pc));
    case OpClass::Imm_OUT:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_OUT>(inst, sched, pc));
    case OpClass::Const_OUT:
      return PrintInstruction(opcode, Accessor<OpClass::Const_OUT>(inst, sched, pc));
    case OpClass::PIXLD:
      return PrintInstruction(opcode, Accessor<OpClass::PIXLD>(inst, sched, pc));
    case OpClass::I_PIXLD:
      return PrintInstruction(opcode, Accessor<OpClass::I_PIXLD>(inst, sched, pc));
    case OpClass::PIXLD_simple:
      return PrintInstruction(opcode, Accessor<OpClass::PIXLD_simple>(inst, sched, pc));
    case OpClass::LDC:
      return PrintInstruction(opcode, Accessor<OpClass::LDC>(inst, sched, pc));
    case OpClass::I_LDC:
      return PrintInstruction(opcode, Accessor<OpClass::I_LDC>(inst, sched, pc));
    case OpClass::LDC_64:
      return PrintInstruction(opcode, Accessor<OpClass::LDC_64>(inst, sched, pc));
    case OpClass::I_LDC_64:
      return PrintInstruction(opcode, Accessor<OpClass::I_LDC_64>(inst, sched, pc));
    case OpClass::LD:
      return PrintInstruction(opcode, Accessor<OpClass::LD>(inst, sched, pc));
    case OpClass::I_LD:
      return PrintInstruction(opcode, Accessor<OpClass::I_LD>(inst, sched, pc));
    case OpClass::LDG:
      return PrintInstruction(opcode, Accessor<OpClass::LDG>(inst, sched, pc));
    case OpClass::I_LDG:
      return PrintInstruction(opcode, Accessor<OpClass::I_LDG>(inst, sched, pc));
    case OpClass::LDG_SPARSE:
      return PrintInstruction(opcode, Accessor<OpClass::LDG_SPARSE>(inst, sched, pc));
    case OpClass::I_LDG_SPARSE:
      return PrintInstruction(opcode, Accessor<OpClass::I_LDG_SPARSE>(inst, sched, pc));
    case OpClass::LDL:
      return PrintInstruction(opcode, Accessor<OpClass::LDL>(inst, sched, pc));
    case OpClass::I_LDL:
      return PrintInstruction(opcode, Accessor<OpClass::I_LDL>(inst, sched, pc));
    case OpClass::LDS:
      return PrintInstruction(opcode, Accessor<OpClass::LDS>(inst, sched, pc));
    case OpClass::I_LDS:
      return PrintInstruction(opcode, Accessor<OpClass::I_LDS>(inst, sched, pc));
    case OpClass::LEA_LO_REG:
      return PrintInstruction(opcode, Accessor<OpClass::LEA_LO_REG>(inst, sched, pc));
    case OpClass::LEA_LO_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::LEA_LO_IMM>(inst, sched, pc));
    case OpClass::LEA_LO_CONST:
      return PrintInstruction(opcode, Accessor<OpClass::LEA_LO_CONST>(inst, sched, pc));
    case OpClass::LEA_HI_REG:
      return PrintInstruction(opcode, Accessor<OpClass::LEA_HI_REG>(inst, sched, pc));
    case OpClass::LEA_HI_CONST:
      return PrintInstruction(opcode, Accessor<OpClass::LEA_HI_CONST>(inst, sched, pc));
    case OpClass::ST:
      return PrintInstruction(opcode, Accessor<OpClass::ST>(inst, sched, pc));
    case OpClass::I_ST:
      return PrintInstruction(opcode, Accessor<OpClass::I_ST>(inst, sched, pc));
    case OpClass::STG:
      return PrintInstruction(opcode, Accessor<OpClass::STG>(inst, sched, pc));
    case OpClass::I_STG:
      return PrintInstruction(opcode, Accessor<OpClass::I_STG>(inst, sched, pc));
    case OpClass::STL:
      return PrintInstruction(opcode, Accessor<OpClass::STL>(inst, sched, pc));
    case OpClass::I_STL:
      return PrintInstruction(opcode, Accessor<OpClass::I_STL>(inst, sched, pc));
    case OpClass::STS:
      return PrintInstruction(opcode, Accessor<OpClass::STS>(inst, sched, pc));
    case OpClass::I_STS:
      return PrintInstruction(opcode, Accessor<OpClass::I_STS>(inst, sched, pc));
    case OpClass::ATOM:
      return PrintInstruction(opcode, Accessor<OpClass::ATOM>(inst, sched, pc));
    case OpClass::I_ATOM:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOM>(inst, sched, pc));
    case OpClass::ATOM_CAS:
      return PrintInstruction(opcode, Accessor<OpClass::ATOM_CAS>(inst, sched, pc));
    case OpClass::I_ATOM_CAS:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOM_CAS>(inst, sched, pc));
    case OpClass::ATOM_CAS_Rb_and_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::ATOM_CAS_Rb_and_RZ>(inst, sched, pc));
    case OpClass::I_ATOM_CAS_Rb_and_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOM_CAS_Rb_and_RZ>(inst, sched, pc));
    case OpClass::ATOM_CAS_RZ_and_Rc:
      return PrintInstruction(opcode, Accessor<OpClass::ATOM_CAS_RZ_and_Rc>(inst, sched, pc));
    case OpClass::I_ATOM_CAS_RZ_and_Rc:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOM_CAS_RZ_and_Rc>(inst, sched, pc));
    case OpClass::ATOM_SPARSE:
      return PrintInstruction(opcode, Accessor<OpClass::ATOM_SPARSE>(inst, sched, pc));
    case OpClass::ATOM_CAS_SPARSE:
      return PrintInstruction(opcode, Accessor<OpClass::ATOM_CAS_SPARSE>(inst, sched, pc));
    case OpClass::ATOM_CAS_RZ_and_Rc_SPARSE:
      return PrintInstruction(opcode, Accessor<OpClass::ATOM_CAS_RZ_and_Rc_SPARSE>(inst, sched, pc));
    case OpClass::ATOM_CAS_Rb_and_RZ_SPARSE:
      return PrintInstruction(opcode, Accessor<OpClass::ATOM_CAS_Rb_and_RZ_SPARSE>(inst, sched, pc));
    case OpClass::ATOMS:
      return PrintInstruction(opcode, Accessor<OpClass::ATOMS>(inst, sched, pc));
    case OpClass::I_ATOMS:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOMS>(inst, sched, pc));
    case OpClass::ATOMS_CAS:
      return PrintInstruction(opcode, Accessor<OpClass::ATOMS_CAS>(inst, sched, pc));
    case OpClass::I_ATOMS_CAS:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOMS_CAS>(inst, sched, pc));
    case OpClass::ATOMS_CAS_Rb_and_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::ATOMS_CAS_Rb_and_RZ>(inst, sched, pc));
    case OpClass::I_ATOMS_CAS_Rb_and_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOMS_CAS_Rb_and_RZ>(inst, sched, pc));
    case OpClass::ATOMS_CAS_RZ_and_Rc:
      return PrintInstruction(opcode, Accessor<OpClass::ATOMS_CAS_RZ_and_Rc>(inst, sched, pc));
    case OpClass::I_ATOMS_CAS_RZ_and_Rc:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOMS_CAS_RZ_and_Rc>(inst, sched, pc));
    case OpClass::ATOMS_CAST:
      return PrintInstruction(opcode, Accessor<OpClass::ATOMS_CAST>(inst, sched, pc));
    case OpClass::I_ATOMS_CAST:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOMS_CAST>(inst, sched, pc));
    case OpClass::ATOMS_CAST_Rb_and_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::ATOMS_CAST_Rb_and_RZ>(inst, sched, pc));
    case OpClass::I_ATOMS_CAST_Rb_and_RZ:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOMS_CAST_Rb_and_RZ>(inst, sched, pc));
    case OpClass::ATOMS_CAST_RZ_and_Rc:
      return PrintInstruction(opcode, Accessor<OpClass::ATOMS_CAST_RZ_and_Rc>(inst, sched, pc));
    case OpClass::I_ATOMS_CAST_RZ_and_Rc:
      return PrintInstruction(opcode, Accessor<OpClass::I_ATOMS_CAST_RZ_and_Rc>(inst, sched, pc));
    case OpClass::RED:
      return PrintInstruction(opcode, Accessor<OpClass::RED>(inst, sched, pc));
    case OpClass::I_RED:
      return PrintInstruction(opcode, Accessor<OpClass::I_RED>(inst, sched, pc));
    case OpClass::CCTL:
      return PrintInstruction(opcode, Accessor<OpClass::CCTL>(inst, sched, pc));
    case OpClass::I_CCTL:
      return PrintInstruction(opcode, Accessor<OpClass::I_CCTL>(inst, sched, pc));
    case OpClass::CCTL_IVALL:
      return PrintInstruction(opcode, Accessor<OpClass::CCTL_IVALL>(inst, sched, pc));
    case OpClass::CCTL_CI_IVALL:
      return PrintInstruction(opcode, Accessor<OpClass::CCTL_CI_IVALL>(inst, sched, pc));
    case OpClass::CCTL_QRY:
      return PrintInstruction(opcode, Accessor<OpClass::CCTL_QRY>(inst, sched, pc));
    case OpClass::I_CCTL_QRY:
      return PrintInstruction(opcode, Accessor<OpClass::I_CCTL_QRY>(inst, sched, pc));
    case OpClass::CCTLL:
      return PrintInstruction(opcode, Accessor<OpClass::CCTLL>(inst, sched, pc));
    case OpClass::I_CCTLL:
      return PrintInstruction(opcode, Accessor<OpClass::I_CCTLL>(inst, sched, pc));
    case OpClass::CCTLL_IVALL:
      return PrintInstruction(opcode, Accessor<OpClass::CCTLL_IVALL>(inst, sched, pc));
    case OpClass::CCTLL_CRS_WBALL:
      return PrintInstruction(opcode, Accessor<OpClass::CCTLL_CRS_WBALL>(inst, sched, pc));
    case OpClass::CCTLT_REG:
      return PrintInstruction(opcode, Accessor<OpClass::CCTLT_REG>(inst, sched, pc));
    case OpClass::CCTLT_IDX:
      return PrintInstruction(opcode, Accessor<OpClass::CCTLT_IDX>(inst, sched, pc));
    case OpClass::CCTLT_IVALL:
      return PrintInstruction(opcode, Accessor<OpClass::CCTLT_IVALL>(inst, sched, pc));
    case OpClass::MEMBAR:
      return PrintInstruction(opcode, Accessor<OpClass::MEMBAR>(inst, sched, pc));
    case OpClass::SULD_D_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SULD_D_REG>(inst, sched, pc));
    case OpClass::SULD_D_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SULD_D_IMM>(inst, sched, pc));
    case OpClass::SULD_P_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SULD_P_REG>(inst, sched, pc));
    case OpClass::SULD_P_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SULD_P_IMM>(inst, sched, pc));
    case OpClass::SUST_D_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SUST_D_REG>(inst, sched, pc));
    case OpClass::SUST_D_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SUST_D_IMM>(inst, sched, pc));
    case OpClass::SUST_P_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SUST_P_REG>(inst, sched, pc));
    case OpClass::SUST_P_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SUST_P_IMM>(inst, sched, pc));
    case OpClass::SURED_D_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SURED_D_REG>(inst, sched, pc));
    case OpClass::SURED_D_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SURED_D_IMM>(inst, sched, pc));
    case OpClass::SURED_P_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SURED_P_REG>(inst, sched, pc));
    case OpClass::SURED_P_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SURED_P_IMM>(inst, sched, pc));
    case OpClass::SUATOM_D_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_D_REG>(inst, sched, pc));
    case OpClass::SUATOM_D_REG_SPARSE:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_D_REG_SPARSE>(inst, sched, pc));
    case OpClass::SUATOM_D_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_D_IMM>(inst, sched, pc));
    case OpClass::SUATOM_P_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_P_REG>(inst, sched, pc));
    case OpClass::SUATOM_P_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_P_IMM>(inst, sched, pc));
    case OpClass::SUATOM_D_CAS_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_D_CAS_REG>(inst, sched, pc));
    case OpClass::SUATOM_D_CAS_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_D_CAS_IMM>(inst, sched, pc));
    case OpClass::SUATOM_P_CAS_REG:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_P_CAS_REG>(inst, sched, pc));
    case OpClass::SUATOM_P_CAS_IMM:
      return PrintInstruction(opcode, Accessor<OpClass::SUATOM_P_CAS_IMM>(inst, sched, pc));
    case OpClass::BRA:
      return PrintInstruction(opcode, Accessor<OpClass::BRA>(inst, sched, pc));
    case OpClass::BRA_c:
      return PrintInstruction(opcode, Accessor<OpClass::BRA_c>(inst, sched, pc));
    case OpClass::BRX:
      return PrintInstruction(opcode, Accessor<OpClass::BRX>(inst, sched, pc));
    case OpClass::BRX_c:
      return PrintInstruction(opcode, Accessor<OpClass::BRX_c>(inst, sched, pc));
    case OpClass::JMP:
      return PrintInstruction(opcode, Accessor<OpClass::JMP>(inst, sched, pc));
    case OpClass::JMP_c:
      return PrintInstruction(opcode, Accessor<OpClass::JMP_c>(inst, sched, pc));
    case OpClass::JMX:
      return PrintInstruction(opcode, Accessor<OpClass::JMX>(inst, sched, pc));
    case OpClass::JMX_c:
      return PrintInstruction(opcode, Accessor<OpClass::JMX_c>(inst, sched, pc));
    case OpClass::CAL:
      return PrintInstruction(opcode, Accessor<OpClass::CAL>(inst, sched, pc));
    case OpClass::CAL_c:
      return PrintInstruction(opcode, Accessor<OpClass::CAL_c>(inst, sched, pc));
    case OpClass::PRET:
      return PrintInstruction(opcode, Accessor<OpClass::PRET>(inst, sched, pc));
    case OpClass::PRET_c:
      return PrintInstruction(opcode, Accessor<OpClass::PRET_c>(inst, sched, pc));
    case OpClass::JCAL:
      return PrintInstruction(opcode, Accessor<OpClass::JCAL>(inst, sched, pc));
    case OpClass::JCAL_c:
      return PrintInstruction(opcode, Accessor<OpClass::JCAL_c>(inst, sched, pc));
    case OpClass::SSY:
      return PrintInstruction(opcode, Accessor<OpClass::SSY>(inst, sched, pc));
    case OpClass::SSY_c:
      return PrintInstruction(opcode, Accessor<OpClass::SSY_c>(inst, sched, pc));
    case OpClass::PLONGJMP:
      return PrintInstruction(opcode, Accessor<OpClass::PLONGJMP>(inst, sched, pc));
    case OpClass::PLONGJMP_c:
      return PrintInstruction(opcode, Accessor<OpClass::PLONGJMP_c>(inst, sched, pc));
    case OpClass::PBK:
      return PrintInstruction(opcode, Accessor<OpClass::PBK>(inst, sched, pc));
    case OpClass::PBK_c:
      return PrintInstruction(opcode, Accessor<OpClass::PBK_c>(inst, sched, pc));
    case OpClass::PCNT:
      return PrintInstruction(opcode, Accessor<OpClass::PCNT>(inst, sched, pc));
    case OpClass::PCNT_c:
      return PrintInstruction(opcode, Accessor<OpClass::PCNT_c>(inst, sched, pc));
    case OpClass::RET:
      return PrintInstruction(opcode, Accessor<OpClass::RET>(inst, sched, pc));
    case OpClass::LONGJMP:
      return PrintInstruction(opcode, Accessor<OpClass::LONGJMP>(inst, sched, pc));
    case OpClass::KIL:
      return PrintInstruction(opcode, Accessor<OpClass::KIL>(inst, sched, pc));
    case OpClass::BRK:
      return PrintInstruction(opcode, Accessor<OpClass::BRK>(inst, sched, pc));
    case OpClass::CONT:
      return PrintInstruction(opcode, Accessor<OpClass::CONT>(inst, sched, pc));
    case OpClass::EXIT:
      return PrintInstruction(opcode, Accessor<OpClass::EXIT>(inst, sched, pc));
    case OpClass::PEXIT:
      return PrintInstruction(opcode, Accessor<OpClass::PEXIT>(inst, sched, pc));
    case OpClass::SAM:
      return PrintInstruction(opcode, Accessor<OpClass::SAM>(inst, sched, pc));
    case OpClass::RAM:
      return PrintInstruction(opcode, Accessor<OpClass::RAM>(inst, sched, pc));
    case OpClass::BPT:
      return PrintInstruction(opcode, Accessor<OpClass::BPT>(inst, sched, pc));
    case OpClass::RTT:
      return PrintInstruction(opcode, Accessor<OpClass::RTT>(inst, sched, pc));
    case OpClass::IDE_EN:
      return PrintInstruction(opcode, Accessor<OpClass::IDE_EN>(inst, sched, pc));
    case OpClass::IDE_DI:
      return PrintInstruction(opcode, Accessor<OpClass::IDE_DI>(inst, sched, pc));
    case OpClass::SYNC:
      return PrintInstruction(opcode, Accessor<OpClass::SYNC>(inst, sched, pc));
    case OpClass::NOP:
      return PrintInstruction(opcode, Accessor<OpClass::NOP>(inst, sched, pc));
    case OpClass::NOP_trig:
      return PrintInstruction(opcode, Accessor<OpClass::NOP_trig>(inst, sched, pc));
    case OpClass::S2R:
      return PrintInstruction(opcode, Accessor<OpClass::S2R>(inst, sched, pc));
    case OpClass::CS2R:
      return PrintInstruction(opcode, Accessor<OpClass::CS2R>(inst, sched, pc));
    case OpClass::B2R_BAR:
      return PrintInstruction(opcode, Accessor<OpClass::B2R_BAR>(inst, sched, pc));
    case OpClass::B2R_RESULT:
      return PrintInstruction(opcode, Accessor<OpClass::B2R_RESULT>(inst, sched, pc));
    case OpClass::B2R_WARP:
      return PrintInstruction(opcode, Accessor<OpClass::B2R_WARP>(inst, sched, pc));
    case OpClass::R2B:
      return PrintInstruction(opcode, Accessor<OpClass::R2B>(inst, sched, pc));
    case OpClass::LEPC:
      return PrintInstruction(opcode, Accessor<OpClass::LEPC>(inst, sched, pc));
    case OpClass::BAR_Sync:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Sync>(inst, sched, pc));
    case OpClass::BAR_Sync_b:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Sync_b>(inst, sched, pc));
    case OpClass::BAR_Sync_a_b:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Sync_a_b>(inst, sched, pc));
    case OpClass::BAR_Sync_a:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Sync_a>(inst, sched, pc));
    case OpClass::BAR_Arv:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Arv>(inst, sched, pc));
    case OpClass::BAR_Arv_a:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Arv_a>(inst, sched, pc));
    case OpClass::BAR_Arv_imm:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Arv_imm>(inst, sched, pc));
    case OpClass::BAR_Arv_imm_a:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Arv_imm_a>(inst, sched, pc));
    case OpClass::BAR_Red:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Red>(inst, sched, pc));
    case OpClass::BAR_Red_b:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Red_b>(inst, sched, pc));
    case OpClass::BAR_Red_a_b:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Red_a_b>(inst, sched, pc));
    case OpClass::BAR_Red_a:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Red_a>(inst, sched, pc));
    case OpClass::BAR_syncall:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_syncall>(inst, sched, pc));
    case OpClass::BAR_Scan:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Scan>(inst, sched, pc));
    case OpClass::BAR_Scan_a:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_Scan_a>(inst, sched, pc));
    case OpClass::BAR_scan_imm:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_scan_imm>(inst, sched, pc));
    case OpClass::BAR_scan_imm_a:
      return PrintInstruction(opcode, Accessor<OpClass::BAR_scan_imm_a>(inst, sched, pc));
    case OpClass::VOTE_VTG:
      return PrintInstruction(opcode, Accessor<OpClass::VOTE_VTG>(inst, sched, pc));
    case OpClass::VOTE:
      return PrintInstruction(opcode, Accessor<OpClass::VOTE>(inst, sched, pc));
    case OpClass::SETCRSPTR:
      return PrintInstruction(opcode, Accessor<OpClass::SETCRSPTR>(inst, sched, pc));
    case OpClass::GETCRSPTR:
      return PrintInstruction(opcode, Accessor<OpClass::GETCRSPTR>(inst, sched, pc));
    case OpClass::SETLMEMBASE:
      return PrintInstruction(opcode, Accessor<OpClass::SETLMEMBASE>(inst, sched, pc));
    case OpClass::GETLMEMBASE:
      return PrintInstruction(opcode, Accessor<OpClass::GETLMEMBASE>(inst, sched, pc));
    case OpClass::ISBERD:
      return PrintInstruction(opcode, Accessor<OpClass::ISBERD>(inst, sched, pc));
    case OpClass::hfma2__v2:
      return PrintInstruction(opcode, Accessor<OpClass::hfma2__v2>(inst, sched, pc));
    case OpClass::hfma2__v1:
      return PrintInstruction(opcode, Accessor<OpClass::hfma2__v1>(inst, sched, pc));
    case OpClass::hfma2__v0:
      return PrintInstruction(opcode, Accessor<OpClass::hfma2__v0>(inst, sched, pc));
    case OpClass::hset2__v2:
      return PrintInstruction(opcode, Accessor<OpClass::hset2__v2>(inst, sched, pc));
    case OpClass::hset2__v1:
      return PrintInstruction(opcode, Accessor<OpClass::hset2__v1>(inst, sched, pc));
    case OpClass::hset2__v0:
      return PrintInstruction(opcode, Accessor<OpClass::hset2__v0>(inst, sched, pc));
    case OpClass::hset2_bop__v1:
      return PrintInstruction(opcode, Accessor<OpClass::hset2_bop__v1>(inst, sched, pc));
    case OpClass::hset2_bop__v0:
      return PrintInstruction(opcode, Accessor<OpClass::hset2_bop__v0>(inst, sched, pc));
    case OpClass::hmul2_32i_:
      return PrintInstruction(opcode, Accessor<OpClass::hmul2_32i_>(inst, sched, pc));
    case OpClass::hset2_bop__v2:
      return PrintInstruction(opcode, Accessor<OpClass::hset2_bop__v2>(inst, sched, pc));
    case OpClass::hadd2__v0:
      return PrintInstruction(opcode, Accessor<OpClass::hadd2__v0>(inst, sched, pc));
    case OpClass::hadd2__v1:
      return PrintInstruction(opcode, Accessor<OpClass::hadd2__v1>(inst, sched, pc));
    case OpClass::hadd2__v2:
      return PrintInstruction(opcode, Accessor<OpClass::hadd2__v2>(inst, sched, pc));
    case OpClass::hmul2__v2:
      return PrintInstruction(opcode, Accessor<OpClass::hmul2__v2>(inst, sched, pc));
    case OpClass::hadd2_32i_:
      return PrintInstruction(opcode, Accessor<OpClass::hadd2_32i_>(inst, sched, pc));
    case OpClass::hmul2__v1:
      return PrintInstruction(opcode, Accessor<OpClass::hmul2__v1>(inst, sched, pc));
    case OpClass::hmul2__v0:
      return PrintInstruction(opcode, Accessor<OpClass::hmul2__v0>(inst, sched, pc));
    case OpClass::HSETP2:
      return PrintInstruction(opcode, Accessor<OpClass::HSETP2>(inst, sched, pc));
    case OpClass::NoBop_HSETP2:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_HSETP2>(inst, sched, pc));
    case OpClass::Imm_HSETP2:
      return PrintInstruction(opcode, Accessor<OpClass::Imm_HSETP2>(inst, sched, pc));
    case OpClass::NoBop_Imm_HSETP2:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Imm_HSETP2>(inst, sched, pc));
    case OpClass::Const_HSETP2:
      return PrintInstruction(opcode, Accessor<OpClass::Const_HSETP2>(inst, sched, pc));
    case OpClass::NoBop_Const_HSETP2:
      return PrintInstruction(opcode, Accessor<OpClass::NoBop_Const_HSETP2>(inst, sched, pc));
    case OpClass::HFMA2_32I:
      return PrintInstruction(opcode, Accessor<OpClass::HFMA2_32I>(inst, sched, pc));
    case OpClass::HFMA2_32I_2:
      return PrintInstruction(opcode, Accessor<OpClass::HFMA2_32I_2>(inst, sched, pc));
    case OpClass::HFMA2_CCST:
      return PrintInstruction(opcode, Accessor<OpClass::HFMA2_CCST>(inst, sched, pc));
    case OpClass::NOP_DEFAULT:
      return PrintInstruction(opcode, Accessor<OpClass::NOP_DEFAULT>(inst, sched, pc));
    default:
      UNREACHABLE_DEFAULT_CASE;
  }
}

} // maxwell