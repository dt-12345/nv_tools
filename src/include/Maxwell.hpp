#pragma once

#include "utility.hpp"

#include <cstdint>
#include <optional>
#include <tuple>
#include <type_traits>
#include <variant>

namespace Maxwell {

enum class OpClass : std::uint32_t {
  FFMA                      =   0x0, // FFMA
  Imm_FFMA                  =   0x1, // Imm_FFMA
  Const_FFMA                =   0x2, // Const_FFMA
  Const1_FFMA               =   0x3, // Const1_FFMA
  FFMA32I                   =   0x4, // FFMA32I
  FFMA32I_2                 =   0x5, // FFMA32I_2
  FADD                      =   0x6, // FADD
  Imm_FADD                  =   0x7, // Imm_FADD
  Const_FADD                =   0x8, // Const_FADD
  FADD32I                   =   0x9, // FADD32I
  FCMP                      =   0xa, // FCMP
  Imm_FCMP                  =   0xb, // Imm_FCMP
  Const_FCMP                =   0xc, // Const_FCMP
  Const1_FCMP               =   0xd, // Const1_FCMP
  FSWZADD                   =   0xe, // FSWZADD
  FMUL                      =   0xf, // FMUL
  Imm_FMUL                  =  0x10, // Imm_FMUL
  Const_FMUL                =  0x11, // Const_FMUL
  FMUL32I                   =  0x12, // FMUL32I
  FMNMX                     =  0x13, // FMNMX
  Imm_FMNMX                 =  0x14, // Imm_FMNMX
  Const_FMNMX               =  0x15, // Const_FMNMX
  FSET                      =  0x16, // FSET
  NoBop_FSET                =  0x17, // NoBop_FSET
  Imm_FSET                  =  0x18, // Imm_FSET
  NoBop_Imm_FSET            =  0x19, // NoBop_Imm_FSET
  Const_FSET                =  0x1a, // Const_FSET
  NoBop_Const_FSET          =  0x1b, // NoBop_Const_FSET
  FSETP                     =  0x1c, // FSETP
  NoBop_FSETP               =  0x1d, // NoBop_FSETP
  Imm_FSETP                 =  0x1e, // Imm_FSETP
  NoBop_Imm_FSETP           =  0x1f, // NoBop_Imm_FSETP
  Const_FSETP               =  0x20, // Const_FSETP
  NoBop_Const_FSETP         =  0x21, // NoBop_Const_FSETP
  IPA_1                     =  0x22, // IPA_1
  I_IPA_1                   =  0x23, // I_IPA_1
  IPA_2                     =  0x24, // IPA_2
  I_IPA_2                   =  0x25, // I_IPA_2
  RRO                       =  0x26, // RRO
  Imm_RRO                   =  0x27, // Imm_RRO
  Const_RRO                 =  0x28, // Const_RRO
  MUFU                      =  0x29, // MUFU
  FCHK                      =  0x2a, // FCHK
  Imm_FCHK                  =  0x2b, // Imm_FCHK
  Const_FCHK                =  0x2c, // Const_FCHK
  DFMA                      =  0x2d, // DFMA
  Imm_DFMA                  =  0x2e, // Imm_DFMA
  Const_DFMA                =  0x2f, // Const_DFMA
  Const1_DFMA               =  0x30, // Const1_DFMA
  DADD                      =  0x31, // DADD
  Imm_DADD                  =  0x32, // Imm_DADD
  Const_DADD                =  0x33, // Const_DADD
  DMUL                      =  0x34, // DMUL
  Imm_DMUL                  =  0x35, // Imm_DMUL
  Const_DMUL                =  0x36, // Const_DMUL
  DMNMX                     =  0x37, // DMNMX
  Imm_DMNMX                 =  0x38, // Imm_DMNMX
  Const_DMNMX               =  0x39, // Const_DMNMX
  DSET                      =  0x3a, // DSET
  NoBop_DSET                =  0x3b, // NoBop_DSET
  Imm_DSET                  =  0x3c, // Imm_DSET
  NoBop_Imm_DSET            =  0x3d, // NoBop_Imm_DSET
  Const_DSET                =  0x3e, // Const_DSET
  NoBop_Const_DSET          =  0x3f, // NoBop_Const_DSET
  DSETP                     =  0x40, // DSETP
  NoBop_DSETP               =  0x41, // NoBop_DSETP
  Imm_DSETP                 =  0x42, // Imm_DSETP
  NoBop_Imm_DSETP           =  0x43, // NoBop_Imm_DSETP
  Const_DSETP               =  0x44, // Const_DSETP
  NoBop_Const_DSETP         =  0x45, // NoBop_Const_DSETP
  IMAD                      =  0x46, // IMAD
  Imm_IMAD                  =  0x47, // Imm_IMAD
  Const_IMAD                =  0x48, // Const_IMAD
  Const1_IMAD               =  0x49, // Const1_IMAD
  IMAD32I                   =  0x4a, // IMAD32I
  IMADSP                    =  0x4b, // IMADSP
  Imm_IMADSP                =  0x4c, // Imm_IMADSP
  Const_IMADSP              =  0x4d, // Const_IMADSP
  Const1_IMADSP             =  0x4e, // Const1_IMADSP
  IMUL                      =  0x4f, // IMUL
  Imm_IMUL                  =  0x50, // Imm_IMUL
  Const_IMUL                =  0x51, // Const_IMUL
  IMUL32I                   =  0x52, // IMUL32I
  IADD                      =  0x53, // IADD
  Imm_IADD                  =  0x54, // Imm_IADD
  Const_IADD                =  0x55, // Const_IADD
  IADD3                     =  0x56, // IADD3
  BImm_IADD3                =  0x57, // BImm_IADD3
  BConst_IADD3              =  0x58, // BConst_IADD3
  IADD32I                   =  0x59, // IADD32I
  ISCADD                    =  0x5a, // ISCADD
  Imm_ISCADD                =  0x5b, // Imm_ISCADD
  Const_ISCADD              =  0x5c, // Const_ISCADD
  ISCADD32I                 =  0x5d, // ISCADD32I
  IMNMX                     =  0x5e, // IMNMX
  Imm_IMNMX                 =  0x5f, // Imm_IMNMX
  Const_IMNMX               =  0x60, // Const_IMNMX
  BFE                       =  0x61, // BFE
  Imm_BFE                   =  0x62, // Imm_BFE
  Const_BFE                 =  0x63, // Const_BFE
  BFI                       =  0x64, // BFI
  Imm_BFI                   =  0x65, // Imm_BFI
  Const_BFI                 =  0x66, // Const_BFI
  Const1_BFI                =  0x67, // Const1_BFI
  SHR                       =  0x68, // SHR
  Imm_SHR                   =  0x69, // Imm_SHR
  Const_SHR                 =  0x6a, // Const_SHR
  SHL                       =  0x6b, // SHL
  Imm_SHL                   =  0x6c, // Imm_SHL
  Const_SHL                 =  0x6d, // Const_SHL
  SHF_L_imm                 =  0x6e, // SHF_L_imm
  SHF_R_imm                 =  0x6f, // SHF_R_imm
  SHF_L_reg                 =  0x70, // SHF_L_reg
  SHF_R_reg                 =  0x71, // SHF_R_reg
  LOP                       =  0x72, // LOP
  Imm_LOP                   =  0x73, // Imm_LOP
  Const_LOP                 =  0x74, // Const_LOP
  LOP32I                    =  0x75, // LOP32I
  LOP3_LUT                  =  0x76, // LOP3_LUT
  LOP3_LUT_BImm             =  0x77, // LOP3_LUT_BImm
  LOP3_LUT_BConst           =  0x78, // LOP3_LUT_BConst
  LOP3                      =  0x79, // LOP3
  LOP3_BImm                 =  0x7a, // LOP3_BImm
  LOP3_Bconst               =  0x7b, // LOP3_Bconst
  FLO                       =  0x7c, // FLO
  Imm_FLO                   =  0x7d, // Imm_FLO
  Const_FLO                 =  0x7e, // Const_FLO
  ISET                      =  0x7f, // ISET
  NoBop_ISET                =  0x80, // NoBop_ISET
  Imm_ISET                  =  0x81, // Imm_ISET
  NoBop_Imm_ISET            =  0x82, // NoBop_Imm_ISET
  Const_ISET                =  0x83, // Const_ISET
  NoBop_Const_ISET          =  0x84, // NoBop_Const_ISET
  ISET_U                    =  0x85, // ISET_U
  NoBop_ISET_U              =  0x86, // NoBop_ISET_U
  Imm_ISET_U                =  0x87, // Imm_ISET_U
  NoBop_Imm_ISET_U          =  0x88, // NoBop_Imm_ISET_U
  Const_ISET_U              =  0x89, // Const_ISET_U
  NoBop_Const_ISET_U        =  0x8a, // NoBop_Const_ISET_U
  ISETP                     =  0x8b, // ISETP
  NoBop_ISETP               =  0x8c, // NoBop_ISETP
  Imm_ISETP                 =  0x8d, // Imm_ISETP
  NoBop_Imm_ISETP           =  0x8e, // NoBop_Imm_ISETP
  Const_ISETP               =  0x8f, // Const_ISETP
  NoBop_Const_ISETP         =  0x90, // NoBop_Const_ISETP
  ISETP_U                   =  0x91, // ISETP_U
  NoBop_ISETP_U             =  0x92, // NoBop_ISETP_U
  Imm_ISETP_U               =  0x93, // Imm_ISETP_U
  NoBop_Imm_ISETP_U         =  0x94, // NoBop_Imm_ISETP_U
  Const_ISETP_U             =  0x95, // Const_ISETP_U
  NoBop_Const_ISETP_U       =  0x96, // NoBop_Const_ISETP_U
  ICMP                      =  0x97, // ICMP
  Imm_ICMP                  =  0x98, // Imm_ICMP
  Const_ICMP                =  0x99, // Const_ICMP
  Const1_ICMP               =  0x9a, // Const1_ICMP
  ICMP_U                    =  0x9b, // ICMP_U
  Imm_ICMP_U                =  0x9c, // Imm_ICMP_U
  Const_ICMP_U              =  0x9d, // Const_ICMP_U
  Const1_ICMP_U             =  0x9e, // Const1_ICMP_U
  POPC                      =  0x9f, // POPC
  Imm_POPC                  =  0xa0, // Imm_POPC
  Const_POPC                =  0xa1, // Const_POPC
  XMAD                      =  0xa2, // XMAD
  ImmB_XMAD                 =  0xa3, // ImmB_XMAD
  SImmB_XMAD                =  0xa4, // SImmB_XMAD
  ConstB_XMAD               =  0xa5, // ConstB_XMAD
  ConstC_XMAD               =  0xa6, // ConstC_XMAD
  VMAD                      =  0xa7, // VMAD
  a8_VMAD                   =  0xa8, // a8_VMAD
  a32_VMAD                  =  0xa9, // a32_VMAD
  b8_VMAD                   =  0xaa, // b8_VMAD
  a8_b8_VMAD                =  0xab, // a8_b8_VMAD
  a32_b8_VMAD               =  0xac, // a32_b8_VMAD
  b32_VMAD                  =  0xad, // b32_VMAD
  a8_b32_VMAD               =  0xae, // a8_b32_VMAD
  a32_b32_VMAD              =  0xaf, // a32_b32_VMAD
  Imm_VMAD                  =  0xb0, // Imm_VMAD
  SImm_VMAD                 =  0xb1, // SImm_VMAD
  a8_Imm_VMAD               =  0xb2, // a8_Imm_VMAD
  a8_SImm_VMAD              =  0xb3, // a8_SImm_VMAD
  a32_Imm_VMAD              =  0xb4, // a32_Imm_VMAD
  a32_SImm_VMAD             =  0xb5, // a32_SImm_VMAD
  VADD                      =  0xb6, // VADD
  a8_VADD                   =  0xb7, // a8_VADD
  a32_VADD                  =  0xb8, // a32_VADD
  b8_VADD                   =  0xb9, // b8_VADD
  a8_b8_VADD                =  0xba, // a8_b8_VADD
  a32_b8_VADD               =  0xbb, // a32_b8_VADD
  b32_VADD                  =  0xbc, // b32_VADD
  a8_b32_VADD               =  0xbd, // a8_b32_VADD
  a32_b32_VADD              =  0xbe, // a32_b32_VADD
  Imm_VADD                  =  0xbf, // Imm_VADD
  SImm_VADD                 =  0xc0, // SImm_VADD
  a8_Imm_VADD               =  0xc1, // a8_Imm_VADD
  a8_SImm_VADD              =  0xc2, // a8_SImm_VADD
  a32_Imm_VADD              =  0xc3, // a32_Imm_VADD
  a32_SImm_VADD             =  0xc4, // a32_SImm_VADD
  VABSDIFF                  =  0xc5, // VABSDIFF
  a8_VABSDIFF               =  0xc6, // a8_VABSDIFF
  a32_VABSDIFF              =  0xc7, // a32_VABSDIFF
  b8_VABSDIFF               =  0xc8, // b8_VABSDIFF
  a8_b8_VABSDIFF            =  0xc9, // a8_b8_VABSDIFF
  a32_b8_VABSDIFF           =  0xca, // a32_b8_VABSDIFF
  b32_VABSDIFF              =  0xcb, // b32_VABSDIFF
  a8_b32_VABSDIFF           =  0xcc, // a8_b32_VABSDIFF
  a32_b32_VABSDIFF          =  0xcd, // a32_b32_VABSDIFF
  Imm_VABSDIFF              =  0xce, // Imm_VABSDIFF
  SImm_VABSDIFF             =  0xcf, // SImm_VABSDIFF
  a8_Imm_VABSDIFF           =  0xd0, // a8_Imm_VABSDIFF
  a8_SImm_VABSDIFF          =  0xd1, // a8_SImm_VABSDIFF
  a32_Imm_VABSDIFF          =  0xd2, // a32_Imm_VABSDIFF
  a32_SImm_VABSDIFF         =  0xd3, // a32_SImm_VABSDIFF
  VMNMX                     =  0xd4, // VMNMX
  a8_VMNMX                  =  0xd5, // a8_VMNMX
  a32_VMNMX                 =  0xd6, // a32_VMNMX
  b8_VMNMX                  =  0xd7, // b8_VMNMX
  a8_b8_VMNMX               =  0xd8, // a8_b8_VMNMX
  a32_b8_VMNMX              =  0xd9, // a32_b8_VMNMX
  b32_VMNMX                 =  0xda, // b32_VMNMX
  a8_b32_VMNMX              =  0xdb, // a8_b32_VMNMX
  a32_b32_VMNMX             =  0xdc, // a32_b32_VMNMX
  Imm_VMNMX                 =  0xdd, // Imm_VMNMX
  SImm_VMNMX                =  0xde, // SImm_VMNMX
  a8_Imm_VMNMX              =  0xdf, // a8_Imm_VMNMX
  a8_SImm_VMNMX             =  0xe0, // a8_SImm_VMNMX
  a32_Imm_VMNMX             =  0xe1, // a32_Imm_VMNMX
  a32_SImm_VMNMX            =  0xe2, // a32_SImm_VMNMX
  VSET                      =  0xe3, // VSET
  a8_VSET                   =  0xe4, // a8_VSET
  a32_VSET                  =  0xe5, // a32_VSET
  b8_VSET                   =  0xe6, // b8_VSET
  a8_b8_VSET                =  0xe7, // a8_b8_VSET
  a32_b8_VSET               =  0xe8, // a32_b8_VSET
  b32_VSET                  =  0xe9, // b32_VSET
  a8_b32_VSET               =  0xea, // a8_b32_VSET
  a32_b32_VSET              =  0xeb, // a32_b32_VSET
  Imm_VSET                  =  0xec, // Imm_VSET
  SImm_VSET                 =  0xed, // SImm_VSET
  a8_Imm_VSET               =  0xee, // a8_Imm_VSET
  a8_SImm_VSET              =  0xef, // a8_SImm_VSET
  a32_Imm_VSET              =  0xf0, // a32_Imm_VSET
  a32_SImm_VSET             =  0xf1, // a32_SImm_VSET
  VSETP                     =  0xf2, // VSETP
  a8_VSETP                  =  0xf3, // a8_VSETP
  a32_VSETP                 =  0xf4, // a32_VSETP
  b8_VSETP                  =  0xf5, // b8_VSETP
  a8_b8_VSETP               =  0xf6, // a8_b8_VSETP
  a32_b8_VSETP              =  0xf7, // a32_b8_VSETP
  b32_VSETP                 =  0xf8, // b32_VSETP
  a8_b32_VSETP              =  0xf9, // a8_b32_VSETP
  a32_b32_VSETP             =  0xfa, // a32_b32_VSETP
  Imm_VSETP                 =  0xfb, // Imm_VSETP
  SImm_VSETP                =  0xfc, // SImm_VSETP
  a8_Imm_VSETP              =  0xfd, // a8_Imm_VSETP
  a8_SImm_VSETP             =  0xfe, // a8_SImm_VSETP
  a32_Imm_VSETP             =  0xff, // a32_Imm_VSETP
  a32_SImm_VSETP            = 0x100, // a32_SImm_VSETP
  VSETP_bop                 = 0x101, // VSETP_bop
  a8_VSETP_bop              = 0x102, // a8_VSETP_bop
  a32_VSETP_bop             = 0x103, // a32_VSETP_bop
  b8_VSETP_bop              = 0x104, // b8_VSETP_bop
  a8_b8_VSETP_bop           = 0x105, // a8_b8_VSETP_bop
  a32_b8_VSETP_bop          = 0x106, // a32_b8_VSETP_bop
  b32_VSETP_bop             = 0x107, // b32_VSETP_bop
  a8_b32_VSETP_bop          = 0x108, // a8_b32_VSETP_bop
  a32_b32_VSETP_bop         = 0x109, // a32_b32_VSETP_bop
  Imm_VSETP_bop             = 0x10a, // Imm_VSETP_bop
  SImm_VSETP_bop            = 0x10b, // SImm_VSETP_bop
  a8_Imm_VSETP_bop          = 0x10c, // a8_Imm_VSETP_bop
  a8_SImm_VSETP_bop         = 0x10d, // a8_SImm_VSETP_bop
  a32_Imm_VSETP_bop         = 0x10e, // a32_Imm_VSETP_bop
  a32_SImm_VSETP_bop        = 0x10f, // a32_SImm_VSETP_bop
  VSHL                      = 0x110, // VSHL
  a8_VSHL                   = 0x111, // a8_VSHL
  a32_VSHL                  = 0x112, // a32_VSHL
  b8_VSHL                   = 0x113, // b8_VSHL
  a8_b8_VSHL                = 0x114, // a8_b8_VSHL
  a32_b8_VSHL               = 0x115, // a32_b8_VSHL
  b32_VSHL                  = 0x116, // b32_VSHL
  a8_b32_VSHL               = 0x117, // a8_b32_VSHL
  a32_b32_VSHL              = 0x118, // a32_b32_VSHL
  Imm_VSHL                  = 0x119, // Imm_VSHL
  SImm_VSHL                 = 0x11a, // SImm_VSHL
  a8_Imm_VSHL               = 0x11b, // a8_Imm_VSHL
  a8_SImm_VSHL              = 0x11c, // a8_SImm_VSHL
  a32_Imm_VSHL              = 0x11d, // a32_Imm_VSHL
  a32_SImm_VSHL             = 0x11e, // a32_SImm_VSHL
  VSHR                      = 0x11f, // VSHR
  a8_VSHR                   = 0x120, // a8_VSHR
  a32_VSHR                  = 0x121, // a32_VSHR
  b8_VSHR                   = 0x122, // b8_VSHR
  a8_b8_VSHR                = 0x123, // a8_b8_VSHR
  a32_b8_VSHR               = 0x124, // a32_b8_VSHR
  b32_VSHR                  = 0x125, // b32_VSHR
  a8_b32_VSHR               = 0x126, // a8_b32_VSHR
  a32_b32_VSHR              = 0x127, // a32_b32_VSHR
  Imm_VSHR                  = 0x128, // Imm_VSHR
  SImm_VSHR                 = 0x129, // SImm_VSHR
  a8_Imm_VSHR               = 0x12a, // a8_Imm_VSHR
  a8_SImm_VSHR              = 0x12b, // a8_SImm_VSHR
  a32_Imm_VSHR              = 0x12c, // a32_Imm_VSHR
  a32_SImm_VSHR             = 0x12d, // a32_SImm_VSHR
  VABSDIFF4                 = 0x12e, // VABSDIFF4
  Imm_VABSDIFF4             = 0x12f, // Imm_VABSDIFF4
  SImm_VABSDIFF4            = 0x130, // SImm_VABSDIFF4
  F2F_1                     = 0x131, // F2F_1
  F2F_2                     = 0x132, // F2F_2
  F2F_2_64_32               = 0x133, // F2F_2_64_32
  F2F_1_16                  = 0x134, // F2F_1_16
  F2F_2_16                  = 0x135, // F2F_2_16
  F2F_2_64_16               = 0x136, // F2F_2_64_16
  F2F_1_64                  = 0x137, // F2F_1_64
  F2F_2_64                  = 0x138, // F2F_2_64
  Imm_F2F_1                 = 0x139, // Imm_F2F_1
  Imm_F2F_2                 = 0x13a, // Imm_F2F_2
  Imm_F2F_2_64_32           = 0x13b, // Imm_F2F_2_64_32
  Imm_F2F_1_16              = 0x13c, // Imm_F2F_1_16
  Imm_F2F_2_16              = 0x13d, // Imm_F2F_2_16
  Imm_F2F_2_64_16           = 0x13e, // Imm_F2F_2_64_16
  Imm_F2F_1_64              = 0x13f, // Imm_F2F_1_64
  Imm_F2F_2_64              = 0x140, // Imm_F2F_2_64
  Const_F2F_1               = 0x141, // Const_F2F_1
  Const_F2F_2               = 0x142, // Const_F2F_2
  Const_F2F_2_64_32         = 0x143, // Const_F2F_2_64_32
  Const_F2F_1_16            = 0x144, // Const_F2F_1_16
  Const_F2F_2_16            = 0x145, // Const_F2F_2_16
  Const_F2F_2_64_16         = 0x146, // Const_F2F_2_64_16
  Const_F2F_1_64            = 0x147, // Const_F2F_1_64
  Const_F2F_2_64            = 0x148, // Const_F2F_2_64
  F2I                       = 0x149, // F2I
  F2I_I64                   = 0x14a, // F2I_I64
  F2I_16                    = 0x14b, // F2I_16
  F2I_64                    = 0x14c, // F2I_64
  Imm_F2I                   = 0x14d, // Imm_F2I
  Imm_F2I_I64               = 0x14e, // Imm_F2I_I64
  Imm_F2I_16                = 0x14f, // Imm_F2I_16
  Imm_F2I_64                = 0x150, // Imm_F2I_64
  Const_F2I                 = 0x151, // Const_F2I
  Const_F2I_I64             = 0x152, // Const_F2I_I64
  Const_F2I_16              = 0x153, // Const_F2I_16
  Const_F2I_64              = 0x154, // Const_F2I_64
  I2F                       = 0x155, // I2F
  I2F_F64                   = 0x156, // I2F_F64
  I2F64                     = 0x157, // I2F64
  I2F16                     = 0x158, // I2F16
  Imm_I2F                   = 0x159, // Imm_I2F
  Imm_I2F_F64               = 0x15a, // Imm_I2F_F64
  Imm_I2F64                 = 0x15b, // Imm_I2F64
  Imm_I2F16                 = 0x15c, // Imm_I2F16
  Const_I2F                 = 0x15d, // Const_I2F
  Const_I2F_F64             = 0x15e, // Const_I2F_F64
  Const_I2F64               = 0x15f, // Const_I2F64
  Const_I2F16               = 0x160, // Const_I2F16
  I2I                       = 0x161, // I2I
  I2I16                     = 0x162, // I2I16
  Imm_I2I                   = 0x163, // Imm_I2I
  Imm_I2I16                 = 0x164, // Imm_I2I16
  Const_I2I                 = 0x165, // Const_I2I
  Const_I2I16               = 0x166, // Const_I2I16
  MOV                       = 0x167, // MOV
  Imm_MOV                   = 0x168, // Imm_MOV
  Const_MOV                 = 0x169, // Const_MOV
  MOV32I                    = 0x16a, // MOV32I
  SEL                       = 0x16b, // SEL
  Imm_SEL                   = 0x16c, // Imm_SEL
  Const_SEL                 = 0x16d, // Const_SEL
  PRMT                      = 0x16e, // PRMT
  Imm_PRMT                  = 0x16f, // Imm_PRMT
  Const_PRMT                = 0x170, // Const_PRMT
  Const1_PRMT               = 0x171, // Const1_PRMT
  SHFL                      = 0x172, // SHFL
  b_SHFL                    = 0x173, // b_SHFL
  c_b_SHFL                  = 0x174, // c_b_SHFL
  c_SHFL                    = 0x175, // c_SHFL
  P2R                       = 0x176, // P2R
  Imm_P2R                   = 0x177, // Imm_P2R
  Const_P2R                 = 0x178, // Const_P2R
  Simple_P2R                = 0x179, // Simple_P2R
  R2P                       = 0x17a, // R2P
  Imm_R2P                   = 0x17b, // Imm_R2P
  Const_R2P                 = 0x17c, // Const_R2P
  CSET                      = 0x17d, // CSET
  NoBop_CSET                = 0x17e, // NoBop_CSET
  CSETP                     = 0x17f, // CSETP
  NoBop_CSETP               = 0x180, // NoBop_CSETP
  PSET                      = 0x181, // PSET
  NoBop_PSET                = 0x182, // NoBop_PSET
  PSETP                     = 0x183, // PSETP
  NoBop_PSETP               = 0x184, // NoBop_PSETP
  STP                       = 0x185, // STP
  TEX                       = 0x186, // TEX
  TEX_legacy_style          = 0x187, // TEX_legacy_style
  TEX_B                     = 0x188, // TEX_B
  TEX_B_legacy_style        = 0x189, // TEX_B_legacy_style
  TEXS_RZ                   = 0x18a, // TEXS_RZ
  TEXS                      = 0x18b, // TEXS
  TEXS_F16_RZ               = 0x18c, // TEXS_F16_RZ
  TEXS_F16                  = 0x18d, // TEXS_F16
  TLDS_RZ                   = 0x18e, // TLDS_RZ
  TLDS                      = 0x18f, // TLDS
  TLDS_F16_RZ               = 0x190, // TLDS_F16_RZ
  TLDS_F16                  = 0x191, // TLDS_F16
  TLD4S                     = 0x192, // TLD4S
  TLD4S_F16                 = 0x193, // TLD4S_F16
  TLD                       = 0x194, // TLD
  TLD_B                     = 0x195, // TLD_B
  TLD4                      = 0x196, // TLD4
  TLD4_B                    = 0x197, // TLD4_B
  TLD4_Legacy_Style         = 0x198, // TLD4_Legacy_Style
  TLD4_B_Legacy_Style       = 0x199, // TLD4_B_Legacy_Style
  TMML                      = 0x19a, // TMML
  TMML_Legacy_Style         = 0x19b, // TMML_Legacy_Style
  TMML_B                    = 0x19c, // TMML_B
  TMML_B_Legacy_Style       = 0x19d, // TMML_B_Legacy_Style
  TXD                       = 0x19e, // TXD
  TXD_Legacy_Style          = 0x19f, // TXD_Legacy_Style
  TXD_B                     = 0x1a0, // TXD.B
  TXD_B_Legacy_Style        = 0x1a1, // TXD_B_Legacy_Style
  TXQ                       = 0x1a2, // TXQ
  TXQ_Legacy_Style          = 0x1a3, // TXQ_Legacy_Style
  TXQ_Imm                   = 0x1a4, // TXQ_Imm
  TXQ_Imm_Legacy_Style      = 0x1a5, // TXQ_Imm_Legacy_Style
  TXQ_B                     = 0x1a6, // TXQ_B
  TXQ_B_Legacy_Style        = 0x1a7, // TXQ_B_Legacy_Style
  TXQ_B_Imm                 = 0x1a8, // TXQ_B_Imm
  TXQ_B_Imm_Legacy_Style    = 0x1a9, // TXQ_B_Imm_Legacy_Style
  TXA                       = 0x1aa, // TXA
  TXA_Legacy_Style          = 0x1ab, // TXA_Legacy_Style
  DEPBAR_LE                 = 0x1ac, // DEPBAR_LE
  DEPBAR                    = 0x1ad, // DEPBAR
  DEPBAR_ALL                = 0x1ae, // DEPBAR_ALL
  AL2P                      = 0x1af, // AL2P
  I_AL2P                    = 0x1b0, // I_AL2P
  I_ALD                     = 0x1b1, // I_ALD
  I_ALD_PATCH               = 0x1b2, // I_ALD_PATCH
  ALD                       = 0x1b3, // ALD
  ALD_PHYS                  = 0x1b4, // ALD_PHYS
  I_AST                     = 0x1b5, // I_AST
  I_AST_PATCH               = 0x1b6, // I_AST_PATCH
  AST                       = 0x1b7, // AST
  AST_PHYS                  = 0x1b8, // AST_PHYS
  OUT                       = 0x1b9, // OUT
  Imm_OUT                   = 0x1ba, // Imm_OUT
  Const_OUT                 = 0x1bb, // Const_OUT
  PIXLD                     = 0x1bc, // PIXLD
  I_PIXLD                   = 0x1bd, // I_PIXLD
  PIXLD_simple              = 0x1be, // PIXLD_simple
  LDC                       = 0x1bf, // LDC
  I_LDC                     = 0x1c0, // I_LDC
  LDC_64                    = 0x1c1, // LDC_64
  I_LDC_64                  = 0x1c2, // I_LDC_64
  LD                        = 0x1c3, // LD
  I_LD                      = 0x1c4, // I_LD
  LDG                       = 0x1c5, // LDG
  I_LDG                     = 0x1c6, // I_LDG
  LDG_SPARSE                = 0x1c7, // LDG_SPARSE
  I_LDG_SPARSE              = 0x1c8, // I_LDG_SPARSE
  LDL                       = 0x1c9, // LDL
  I_LDL                     = 0x1ca, // I_LDL
  LDS                       = 0x1cb, // LDS
  I_LDS                     = 0x1cc, // I_LDS
  LEA_LO_REG                = 0x1cd, // LEA_LO_REG
  LEA_LO_IMM                = 0x1ce, // LEA_LO_IMM
  LEA_LO_CONST              = 0x1cf, // LEA_LO_CONST
  LEA_HI_REG                = 0x1d0, // LEA_HI_REG
  LEA_HI_CONST              = 0x1d1, // LEA_HI_CONST
  ST                        = 0x1d2, // ST
  I_ST                      = 0x1d3, // I_ST
  STG                       = 0x1d4, // STG
  I_STG                     = 0x1d5, // I_STG
  STL                       = 0x1d6, // STL
  I_STL                     = 0x1d7, // I_STL
  STS                       = 0x1d8, // STS
  I_STS                     = 0x1d9, // I_STS
  ATOM                      = 0x1da, // ATOM
  I_ATOM                    = 0x1db, // I_ATOM
  ATOM_CAS                  = 0x1dc, // ATOM_CAS
  I_ATOM_CAS                = 0x1dd, // I_ATOM_CAS
  ATOM_CAS_Rb_and_RZ        = 0x1de, // ATOM_CAS_Rb_and_RZ
  I_ATOM_CAS_Rb_and_RZ      = 0x1df, // I_ATOM_CAS_Rb_and_RZ
  ATOM_CAS_RZ_and_Rc        = 0x1e0, // ATOM_CAS_RZ_and_Rc
  I_ATOM_CAS_RZ_and_Rc      = 0x1e1, // I_ATOM_CAS_RZ_and_Rc
  ATOM_SPARSE               = 0x1e2, // ATOM_SPARSE
  ATOM_CAS_SPARSE           = 0x1e3, // ATOM_CAS_SPARSE
  ATOM_CAS_RZ_and_Rc_SPARSE = 0x1e4, // ATOM_CAS_RZ_and_Rc_SPARSE
  ATOM_CAS_Rb_and_RZ_SPARSE = 0x1e5, // ATOM_CAS_Rb_and_RZ_SPARSE
  ATOMS                     = 0x1e6, // ATOMS
  I_ATOMS                   = 0x1e7, // I_ATOMS
  ATOMS_CAS                 = 0x1e8, // ATOMS_CAS
  I_ATOMS_CAS               = 0x1e9, // I_ATOMS_CAS
  ATOMS_CAS_Rb_and_RZ       = 0x1ea, // ATOMS_CAS_Rb_and_RZ
  I_ATOMS_CAS_Rb_and_RZ     = 0x1eb, // I_ATOMS_CAS_Rb_and_RZ
  ATOMS_CAS_RZ_and_Rc       = 0x1ec, // ATOMS_CAS_RZ_and_Rc
  I_ATOMS_CAS_RZ_and_Rc     = 0x1ed, // I_ATOMS_CAS_RZ_and_Rc
  ATOMS_CAST                = 0x1ee, // ATOMS_CAST
  I_ATOMS_CAST              = 0x1ef, // I_ATOMS_CAST
  ATOMS_CAST_Rb_and_RZ      = 0x1f0, // ATOMS_CAST_Rb_and_RZ
  I_ATOMS_CAST_Rb_and_RZ    = 0x1f1, // I_ATOMS_CAST_Rb_and_RZ
  ATOMS_CAST_RZ_and_Rc      = 0x1f2, // ATOMS_CAST_RZ_and_Rc
  I_ATOMS_CAST_RZ_and_Rc    = 0x1f3, // I_ATOMS_CAST_RZ_and_Rc
  RED                       = 0x1f4, // RED
  I_RED                     = 0x1f5, // I RED
  CCTL                      = 0x1f6, // CCTL
  I_CCTL                    = 0x1f7, // I_CCTL
  CCTL_IVALL                = 0x1f8, // CCTL_IVALL
  CCTL_CI_IVALL             = 0x1f9, // CCTL_CI_IVALL
  CCTL_QRY                  = 0x1fa, // CCTL_QRY
  I_CCTL_QRY                = 0x1fb, // I_CCTL_QRY
  CCTLL                     = 0x1fc, // CCTLL
  I_CCTLL                   = 0x1fd, // I_CCTLL
  CCTLL_IVALL               = 0x1fe, // CCTLL_IVALL
  CCTLL_CRS_WBALL           = 0x1ff, // CCTLL_CRS_WBALL
  CCTLT_REG                 = 0x200, // CCTLT_REG
  CCTLT_IDX                 = 0x201, // CCTLT_IDX
  CCTLT_IVALL               = 0x202, // CCTLT_IVALL
  MEMBAR                    = 0x203, // MEMBAR
  SULD_D_REG                = 0x204, // SULD_D_REG
  SULD_D_IMM                = 0x205, // SULD_D_IMM
  SULD_P_REG                = 0x206, // SULD_P_REG
  SULD_P_IMM                = 0x207, // SULD_P_IMM
  SUST_D_REG                = 0x208, // SUST_D_REG
  SUST_D_IMM                = 0x209, // SUST_D_IMM
  SUST_P_REG                = 0x20a, // SUST_P_REG
  SUST_P_IMM                = 0x20b, // SUST_P_IMM
  SURED_D_REG               = 0x20c, // SURED_D_REG
  SURED_D_IMM               = 0x20d, // SURED_D_IMM
  SURED_P_REG               = 0x20e, // SURED_P_REG
  SURED_P_IMM               = 0x20f, // SURED_P_IMM
  SUATOM_D_REG              = 0x210, // SUATOM_D_REG
  SUATOM_D_REG_SPARSE       = 0x211, // SUATOM_D_REG_SPARSE
  SUATOM_D_IMM              = 0x212, // SUATOM_D_IMM
  SUATOM_P_REG              = 0x213, // SUATOM_P_REG
  SUATOM_P_IMM              = 0x214, // SUATOM_P_IMM
  SUATOM_D_CAS_REG          = 0x215, // SUATOM_D_CAS_REG
  SUATOM_D_CAS_IMM          = 0x216, // SUATOM_D_CAS_IMM
  SUATOM_P_CAS_REG          = 0x217, // SUATOM_P_CAS_REG
  SUATOM_P_CAS_IMM          = 0x218, // SUATOM_P_CAS_IMM
  BRA                       = 0x219, // BRA
  BRA_c                     = 0x21a, // BRA_c
  BRX                       = 0x21b, // BRX
  BRX_c                     = 0x21c, // BRX_c
  JMP                       = 0x21d, // JMP
  JMP_c                     = 0x21e, // JMP_c
  JMX                       = 0x21f, // JMX
  JMX_c                     = 0x220, // JMX_c
  CAL                       = 0x221, // CAL
  CAL_c                     = 0x222, // CAL_c
  PRET                      = 0x223, // PRET
  PRET_c                    = 0x224, // PRET_c
  JCAL                      = 0x225, // JCAL
  JCAL_c                    = 0x226, // JCAL_c
  SSY                       = 0x227, // SSY
  SSY_c                     = 0x228, // SSY_c
  PLONGJMP                  = 0x229, // PLONGJMP
  PLONGJMP_c                = 0x22a, // PLONGJMP_c
  PBK                       = 0x22b, // PBK
  PBK_c                     = 0x22c, // PBK_c
  PCNT                      = 0x22d, // PCNT
  PCNT_c                    = 0x22e, // PCNT_c
  RET                       = 0x22f, // RET
  LONGJMP                   = 0x230, // LONGJMP
  KIL                       = 0x231, // KIL
  BRK                       = 0x232, // BRK
  CONT                      = 0x233, // CONT
  EXIT                      = 0x234, // EXIT
  PEXIT                     = 0x235, // PEXIT
  SAM                       = 0x236, // SAM
  RAM                       = 0x237, // RAM
  BPT                       = 0x238, // BPT
  RTT                       = 0x239, // RTT
  IDE_EN                    = 0x23a, // IDE_EN
  IDE_DI                    = 0x23b, // IDE_DI
  SYNC                      = 0x23c, // SYNC
  NOP                       = 0x23d, // NOP
  NOP_trig                  = 0x23e, // NOP_trig
  S2R                       = 0x23f, // S2R
  CS2R                      = 0x240, // CS2R
  B2R_BAR                   = 0x241, // B2R_BAR
  B2R_RESULT                = 0x242, // B2R_RESULT
  B2R_WARP                  = 0x243, // B2R_WARP
  R2B                       = 0x244, // R2B
  LEPC                      = 0x245, // LEPC
  BAR_Sync                  = 0x246, // BAR_Sync
  BAR_Sync_b                = 0x247, // BAR_Sync_b
  BAR_Sync_a_b              = 0x248, // BAR_Sync_a_b
  BAR_Sync_a                = 0x249, // BAR_Sync_a
  BAR_Arv                   = 0x24a, // BAR_Arv
  BAR_Arv_a                 = 0x24b, // BAR_Arv_a
  BAR_Arv_imm               = 0x24c, // BAR_Arv_imm
  BAR_Arv_imm_a             = 0x24d, // BAR_Arv_imm_a
  BAR_Red                   = 0x24e, // BAR_Red
  BAR_Red_b                 = 0x24f, // BAR_Red_b
  BAR_Red_a_b               = 0x250, // BAR_Red_a_b
  BAR_Red_a                 = 0x251, // BAR_Red_a
  BAR_syncall               = 0x252, // BAR_syncall
  BAR_Scan                  = 0x253, // BAR_Scan
  BAR_Scan_a                = 0x254, // BAR_Scan_a
  BAR_scan_imm              = 0x255, // BAR_scan_imm
  BAR_scan_imm_a            = 0x256, // BAR_scan_imm_a
  VOTE_VTG                  = 0x257, // VOTE.VTG
  VOTE                      = 0x258, // VOTE
  SETCRSPTR                 = 0x259, // SETCRSPTR
  GETCRSPTR                 = 0x25a, // GETCRSPTR
  SETLMEMBASE               = 0x25b, // SETLMEMBASE
  GETLMEMBASE               = 0x25c, // GETLMEMBASE
  ISBERD                    = 0x25d, // ISBERD
  hfma2__v2                 = 0x25e, // hfma2__v2
  hfma2__v1                 = 0x25f, // hfma2__v1
  hfma2__v0                 = 0x260, // hfma2__v0
  hset2__v2                 = 0x261, // hset2__v2
  hset2__v1                 = 0x262, // hset2__v1
  hset2__v0                 = 0x263, // hset2__v0
  hset2_bop__v1             = 0x264, // hset2_bop__v1
  hset2_bop__v0             = 0x265, // hset2_bop__v0
  hmul2_32i_                = 0x266, // hmul2_32i_
  hset2_bop__v2             = 0x267, // hset2_bop__v2
  hadd2__v0                 = 0x268, // hadd2__v0
  hadd2__v1                 = 0x269, // hadd2__v1
  hadd2__v2                 = 0x26a, // hadd2__v2
  hmul2__v2                 = 0x26b, // hmul2__v2
  hadd2_32i_                = 0x26c, // hadd2_32i_
  hmul2__v1                 = 0x26d, // hmul2__v1
  hmul2__v0                 = 0x26e, // hmul2__v0
  HSETP2                    = 0x26f, // HSETP2
  NoBop_HSETP2              = 0x270, // NoBop_HSETP2
  Imm_HSETP2                = 0x271, // Imm_HSETP2
  NoBop_Imm_HSETP2          = 0x272, // NoBop_Imm_HSETP2
  Const_HSETP2              = 0x273, // Const_HSETP2
  NoBop_Const_HSETP2        = 0x274, // NoBop_Const_HSETP2
  HFMA2_32I                 = 0x275, // HFMA2_32I
  HFMA2_32I_2               = 0x276, // HFMA2_32I_2
  HFMA2_CCST                = 0x277, // HFMA2_CCST
  NOP_DEFAULT               = 0x278, // NOP
};

struct DecodedInstruction {
  std::uint64_t inst;
  std::uint64_t sched;
  const char* opcode;
  OpClass opclass;
};

std::optional<const DecodedInstruction> Decode(std::uint64_t inst, std::uint64_t sched);

#define MAX_CONST_BANK 17

#define RELATIVE_ADDRESS_BASE 8ull

using AFix_BAREncoding = Encoding<BitRange<44, 1>>;
using AIOEncoding = Encoding<BitRange<32, 1>>;
using ALSizeEncoding = Encoding<BitRange<47, 2>>;
using AOFFIEncoding = Encoding<BitRange<54, 1>>;
using AOFFI2Encoding = Encoding<BitRange<51, 1>>;
using AOFFIBEncoding = Encoding<BitRange<36, 1>>;
using ASignedEncoding = Encoding<BitRange<40, 1>>;
using ASigned2Encoding = Encoding<BitRange<54, 1>>;
using ASigned3Encoding = Encoding<BitRange<48, 1>>;
using ASigned5Encoding = Encoding<BitRange<48, 1>>;
using AVGMode2Encoding = Encoding<BitRange<56, 2>>;
using AVGMode3Encoding = Encoding<BitRange<53, 2>>;
using AdModeEncoding = Encoding<BitRange<44, 2>>;
using ApartEncoding = Encoding<BitRange<35, 2>>;
using AtomEEncoding = Encoding<BitRange<48, 1>>;
using AtomOpEncoding = Encoding<BitRange<52, 4>>;
using AtomOp2Encoding = Encoding<BitRange<44, 4>>;
using AtomSizeEncoding = Encoding<BitRange<49, 3>>;
using AtomSize1Encoding = Encoding<BitRange<49, 1>>;
using AtomsSizeEncoding = Encoding<BitRange<28, 2>>;
using AtomsSize1Encoding = Encoding<BitRange<52, 1>>;
using BAEncoding = Encoding<BitRange<23, 1>>;
using BFix_BAREncoding = Encoding<BitRange<43, 1>>;
using BFix_SHFLEncoding = Encoding<BitRange<28, 1>>;
using BSignedEncoding = Encoding<BitRange<41, 1>>;
using BSigned2Encoding = Encoding<BitRange<55, 1>>;
using BSigned3Encoding = Encoding<BitRange<53, 1>>;
using BSigned4Encoding = Encoding<BitRange<57, 1>>;
using BSigned5Encoding = Encoding<BitRange<49, 1>>;
using BValEncoding = Encoding<BitRange<44, 1>>;
using BVal1Encoding = Encoding<BitRange<52, 1>>;
using BVideoEncoding = Encoding<BitRange<50, 1>>;
using BarNameEncoding = Encoding<BitRange<28, 4>>;
using BarOpEncoding = Encoding<BitRange<32, 3>>;
using BarRedOpEncoding = Encoding<BitRange<35, 2>>;
using BarmdEncoding = Encoding<BitRange<32, 2>>;
using BcaddrEncoding = Encoding<BitRange<20, 14>>;
using BcbankEncoding = Encoding<BitRange<34, 5>>;
using BconstEncoding = Encoding<BitRange<20, 19>, BitRange<56, 1>>;
using BimmH0Encoding = Encoding<BitRange<20, 10>>;
using BimmH1Encoding = Encoding<BitRange<30, 9>, BitRange<56, 1>>;
using BopEncoding = Encoding<BitRange<45, 2>>;
using Bop0Encoding = Encoding<BitRange<24, 2>>;
using BpartEncoding = Encoding<BitRange<33, 2>>;
using BptEncoding = Encoding<BitRange<6, 3>>;
using BrevEncoding = Encoding<BitRange<40, 1>>;
using ByEncoding = Encoding<BitRange<41, 2>>;
using ByteEncoding = Encoding<BitRange<41, 2>>;
using CAEncoding = Encoding<BitRange<5, 1>>;
using CBankEncoding = Encoding<BitRange<36, 5>>;
using CCC_1Encoding = Encoding<BitRange<0, 5>>;
using CCC_2Encoding = Encoding<BitRange<8, 5>>;
using CCPREncoding = Encoding<BitRange<40, 1>>;
using CCTLOpEncoding = Encoding<BitRange<0, 4>>;
using CCTLTOpEncoding = Encoding<BitRange<0, 2>>;
using CFix_SHFLEncoding = Encoding<BitRange<29, 1>>;
using CLEncoding = Encoding<BitRange<54, 1>>;
using COPEncoding = Encoding<BitRange<56, 2>>;
using COP2Encoding = Encoding<BitRange<44, 2>>;
using COP4Encoding = Encoding<BitRange<46, 2>>;
using COP5Encoding = Encoding<BitRange<24, 2>>;
using CacheEncoding = Encoding<BitRange<4, 2>>;
using Cache3Encoding = Encoding<BitRange<4, 3>>;
using ChkModeFEncoding = Encoding<BitRange<39, 6>>;
using Clamp4Encoding = Encoding<BitRange<49, 2>>;
using CpartEncoding = Encoding<BitRange<31, 2>>;
using DCEncoding = Encoding<BitRange<50, 1>>;
using DFormatEncoding = Encoding<BitRange<38, 1>>;
using DFormat2Encoding = Encoding<BitRange<54, 1>>;
using DIEncoding = Encoding<BitRange<5, 1>>;
using DestEncoding = Encoding<BitRange<0, 8>>;
using Dest2Encoding = Encoding<BitRange<28, 8>>;
using DstFmtEncoding = Encoding<BitRange<8, 2>>;
using DstPredEncoding = Encoding<BitRange<45, 3>>;
using DstPred1Encoding = Encoding<BitRange<44, 3>>;
using EEncoding = Encoding<BitRange<52, 1>>;
using E2Encoding = Encoding<BitRange<45, 1>>;
using FCompEncoding = Encoding<BitRange<48, 4>>;
using FComp2Encoding = Encoding<BitRange<35, 4>>;
using FComp3Encoding = Encoding<BitRange<49, 4>>;
using FMZEncoding = Encoding<BitRange<53, 2>>;
using FMZHighEncoding = Encoding<BitRange<53, 2>>;
using FMZLowEncoding = Encoding<BitRange<44, 2>>;
using FMZ_HEncoding = Encoding<BitRange<55, 2>>;
using FMZ_H2Encoding = Encoding<BitRange<57, 2>>;
using FTZEncoding = Encoding<BitRange<44, 1>>;
using FTZ2Encoding = Encoding<BitRange<47, 1>>;
using FTZ3Encoding = Encoding<BitRange<55, 1>>;
using FTZHEncoding = Encoding<BitRange<6, 1>>;
using FimmH0Encoding = Encoding<BitRange<20, 16>>;
using FimmH1Encoding = Encoding<BitRange<36, 16>>;
using HILOEncoding = Encoding<BitRange<39, 1>>;
using HILO2Encoding = Encoding<BitRange<53, 1>>;
using HILO3Encoding = Encoding<BitRange<54, 1>>;
using HILO4Encoding = Encoding<BitRange<35, 1>>;
using HILO5Encoding = Encoding<BitRange<52, 1>>;
using H_andEncoding = Encoding<BitRange<49, 1>>;
using H_and2Encoding = Encoding<BitRange<53, 1>>;
using IBaseEncoding = Encoding<BitRange<33, 2>>;
using ICompEncoding = Encoding<BitRange<49, 3>>;
using IDstFmtEncoding = Encoding<BitRange<8, 2>, BitRange<12, 1>>;
using INCEncoding = Encoding<BitRange<6, 1>>;
using IPAIDXEncoding = Encoding<BitRange<38, 1>>;
using IPAImm10Encoding = Encoding<BitRange<28, 10>>;
using IPAOpEncoding = Encoding<BitRange<54, 2>>;
using IRRndEncoding = Encoding<BitRange<39, 2>, BitRange<42, 1>>;
using ISrcFmtEncoding = Encoding<BitRange<10, 2>, BitRange<13, 1>>;
using Imm06_shfEncoding = Encoding<BitRange<20, 6>>;
using Imm10Encoding = Encoding<BitRange<20, 10>>;
using Imm11Encoding = Encoding<BitRange<20, 11>>;
using Imm12Encoding = Encoding<BitRange<20, 12>>;
using Imm13Encoding = Encoding<BitRange<34, 13>>;
using Imm16Encoding = Encoding<BitRange<20, 16>>;
using Imm20Encoding = Encoding<BitRange<20, 20>>;
using Imm20aEncoding = Encoding<BitRange<28, 20>>;
using Imm22aEncoding = Encoding<BitRange<22, 22>>;
using Imm22atomsEncoding = Encoding<BitRange<30, 22>>;
using Imm24Encoding = Encoding<BitRange<20, 24>>;
using Imm28Encoding = Encoding<BitRange<20, 28>>;
using Imm30aEncoding = Encoding<BitRange<22, 30>>;
using Imm32Encoding = Encoding<BitRange<20, 32>>;
using Imm5IEncoding = Encoding<BitRange<39, 5>>;
using Imm5IbEncoding = Encoding<BitRange<53, 5>>;
using Imm6Encoding = Encoding<BitRange<0, 6>>;
using Imm8Encoding = Encoding<BitRange<20, 8>>;
using ImmU5Encoding = Encoding<BitRange<39, 5>>;
using ImmU5_2Encoding = Encoding<BitRange<28, 5>>;
using ImmU5_3Encoding = Encoding<BitRange<51, 5>>;
using IvallEncoding = Encoding<BitRange<0, 2>>;
using KeepRefCntEncoding = Encoding<BitRange<5, 1>>;
using LCEncoding = Encoding<BitRange<58, 1>>;
using LCBEncoding = Encoding<BitRange<40, 1>>;
using LCDEncoding = Encoding<BitRange<50, 1>>;
using LDSSizeEncoding = Encoding<BitRange<44, 1>, BitRange<48, 3>>;
using LEEncoding = Encoding<BitRange<29, 1>>;
using LMTEncoding = Encoding<BitRange<6, 1>>;
using LODEncoding = Encoding<BitRange<55, 3>>;
using LOD1Encoding = Encoding<BitRange<55, 1>>;
using LODBEncoding = Encoding<BitRange<37, 3>>;
using LOPEncoding = Encoding<BitRange<41, 2>>;
using LOPImmEncoding = Encoding<BitRange<28, 8>>;
using LOPImm2Encoding = Encoding<BitRange<48, 8>>;
using LOP_IEncoding = Encoding<BitRange<53, 2>>;
using LRSEncoding = Encoding<BitRange<37, 2>>;
using LSSizeEncoding = Encoding<BitRange<53, 3>>;
using LSSize2Encoding = Encoding<BitRange<48, 3>>;
using LaneMask4Encoding = Encoding<BitRange<36, 2>, BitRange<51, 2>>;
using MEncoding = Encoding<BitRange<39, 1>>;
using MN2Encoding = Encoding<BitRange<56, 1>>;
using MRGEncoding = Encoding<BitRange<37, 1>>;
using MRG2Encoding = Encoding<BitRange<56, 1>>;
using MSEncoding = Encoding<BitRange<50, 1>>;
using MSIEncoding = Encoding<BitRange<52, 2>>;
using MVEncoding = Encoding<BitRange<49, 1>>;
using M_HEncoding = Encoding<BitRange<50, 1>>;
using MaxShiftEncoding = Encoding<BitRange<37, 2>>;
using MembarLEncoding = Encoding<BitRange<8, 2>>;
using MufuOpEncoding = Encoding<BitRange<20, 4>>;
using NDVEncoding = Encoding<BitRange<35, 1>>;
using NDV2Encoding = Encoding<BitRange<38, 1>>;
using NODEPEncoding = Encoding<BitRange<49, 1>>;
using OECoupledEncoding = Encoding<BitRange<20, 1>>;
using OEReuseAEncoding = Encoding<BitRange<17, 1>>;
using OEReuseBEncoding = Encoding<BitRange<18, 1>>;
using OEReuseCEncoding = Encoding<BitRange<19, 1>>;
using OETexPhaseEncoding = Encoding<BitRange<17, 2>>;
using OEUSchedInfoEncoding = Encoding<BitRange<0, 5>>;
using OEVarLatDestEncoding = Encoding<BitRange<5, 3>>;
using OEVarLatSrcEncoding = Encoding<BitRange<8, 3>>;
using OEWaitOnSbEncoding = Encoding<BitRange<11, 6>>;
using OfmtEncoding = Encoding<BitRange<49, 2>>;
using Opcode10Encoding = Encoding<BitRange<54, 10>>;
using Opcode11Encoding = Encoding<BitRange<53, 11>>;
using Opcode12Encoding = Encoding<BitRange<52, 12>>;
using Opcode13Encoding = Encoding<BitRange<51, 13>>;
using Opcode3Encoding = Encoding<BitRange<61, 3>>;
using Opcode5Encoding = Encoding<BitRange<59, 5>>;
using Opcode5b1Encoding = Encoding<BitRange<55, 1>, BitRange<59, 5>>;
using Opcode6Encoding = Encoding<BitRange<58, 6>>;
using Opcode7Encoding = Encoding<BitRange<57, 7>>;
using Opcode7b1Encoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using Opcode7b2Encoding = Encoding<BitRange<54, 2>, BitRange<57, 7>>;
using Opcode7b4Encoding = Encoding<BitRange<52, 4>, BitRange<57, 7>>;
using Opcode7b5Encoding = Encoding<BitRange<51, 5>, BitRange<57, 7>>;
using Opcode8Encoding = Encoding<BitRange<56, 8>>;
using Opcode9Encoding = Encoding<BitRange<55, 9>>;
using OutTypeEncoding = Encoding<BitRange<39, 2>>;
using PEncoding = Encoding<BitRange<31, 1>>;
using PDestEncoding = Encoding<BitRange<3, 3>>;
using PModeEncoding = Encoding<BitRange<48, 4>>;
using PNDestEncoding = Encoding<BitRange<0, 3>>;
using PNWordEncoding = Encoding<BitRange<28, 8>>;
using POPEncoding = Encoding<BitRange<44, 2>>;
using POP2Encoding = Encoding<BitRange<36, 2>>;
using PSLEncoding = Encoding<BitRange<36, 1>>;
using PSL2Encoding = Encoding<BitRange<55, 1>>;
using PSignEncoding = Encoding<BitRange<48, 2>>;
using PSign2Encoding = Encoding<BitRange<55, 2>>;
using PSign3Encoding = Encoding<BitRange<51, 2>>;
using ParamAEncoding = Encoding<BitRange<28, 3>>;
using PendCntEncoding = Encoding<BitRange<20, 6>>;
using PixModeEncoding = Encoding<BitRange<31, 3>>;
using PredEncoding = Encoding<BitRange<16, 3>>;
using PredDestEncoding = Encoding<BitRange<48, 3>>;
using PredDest2Encoding = Encoding<BitRange<30, 3>>;
using PredDest3Encoding = Encoding<BitRange<51, 3>>;
using PredDest4Encoding = Encoding<BitRange<41, 3>>;
using PredDstEncoding = Encoding<BitRange<51, 3>>;
using PredDstLopEncoding = Encoding<BitRange<48, 3>>;
using PredNotEncoding = Encoding<BitRange<19, 1>>;
using PredSrcEncoding = Encoding<BitRange<47, 3>>;
using PredSrcNotEncoding = Encoding<BitRange<50, 1>>;
using PredSrcldstEncoding = Encoding<BitRange<58, 3>>;
using QuadMaskEncoding = Encoding<BitRange<39, 4>>;
using QuadMask2Encoding = Encoding<BitRange<12, 4>>;
using RROOpEncoding = Encoding<BitRange<39, 1>>;
using RTTOpEncoding = Encoding<BitRange<0, 2>>;
using RedOpEncoding = Encoding<BitRange<23, 3>>;
using RedSizeEncoding = Encoding<BitRange<20, 3>>;
using RegAEncoding = Encoding<BitRange<8, 8>>;
using RegBEncoding = Encoding<BitRange<20, 8>>;
using RegBALDEncoding = Encoding<BitRange<39, 8>>;
using RegBASTEncoding = Encoding<BitRange<0, 8>>;
using RegCEncoding = Encoding<BitRange<39, 8>>;
using RndEncoding = Encoding<BitRange<51, 2>>;
using Rnd3Encoding = Encoding<BitRange<50, 2>>;
using RndLowEncoding = Encoding<BitRange<39, 2>>;
using Rnd_1Encoding = Encoding<BitRange<39, 2>>;
using SABCExtEncoding = Encoding<BitRange<48, 7>>;
using SBIDEncoding = Encoding<BitRange<26, 3>>;
using SHEncoding = Encoding<BitRange<41, 1>>;
using SRegEncoding = Encoding<BitRange<20, 8>>;
using STPModeEncoding = Encoding<BitRange<31, 1>>;
using SUDimEncoding = Encoding<BitRange<33, 3>>;
using SURGBAEncoding = Encoding<BitRange<20, 4>>;
using SURedOpEncoding = Encoding<BitRange<24, 3>>;
using SUSizeEncoding = Encoding<BitRange<20, 3>>;
using SatEncoding = Encoding<BitRange<50, 1>>;
using Sat2Encoding = Encoding<BitRange<54, 1>>;
using SatHighEncoding = Encoding<BitRange<55, 1>>;
using SatLowEncoding = Encoding<BitRange<51, 1>>;
using ScaleLowEncoding = Encoding<BitRange<41, 3>>;
using ShflmdEncoding = Encoding<BitRange<30, 2>>;
using SignedEncoding = Encoding<BitRange<48, 1>>;
using Size1RegBCEncoding = Encoding<BitRange<20, 8>, BitRange<49, 1>>;
using Src1NotEncoding = Encoding<BitRange<32, 1>>;
using Src1PredEncoding = Encoding<BitRange<29, 3>>;
using Src2NotEncoding = Encoding<BitRange<15, 1>>;
using Src2PredEncoding = Encoding<BitRange<12, 3>>;
using SrcDstFmtEncoding = Encoding<BitRange<8, 4>>;
using SrcFmtEncoding = Encoding<BitRange<10, 2>>;
using SrcFmt2Encoding = Encoding<BitRange<10, 2>, BitRange<13, 1>>;
using SrcNotEncoding = Encoding<BitRange<42, 1>>;
using SrcPredEncoding = Encoding<BitRange<39, 3>>;
using TOFF1Encoding = Encoding<BitRange<35, 1>>;
using TOFF2Encoding = Encoding<BitRange<54, 2>>;
using TOFF2BEncoding = Encoding<BitRange<36, 2>>;
using TexCompEncoding = Encoding<BitRange<56, 2>>;
using TexComp2Encoding = Encoding<BitRange<52, 2>>;
using TexCompBEncoding = Encoding<BitRange<38, 2>>;
using TexQueryEncoding = Encoding<BitRange<22, 6>>;
using TidBEncoding = Encoding<BitRange<36, 13>>;
using TidBSAMPEncoding = Encoding<BitRange<44, 5>>;
using TidBTEXEncoding = Encoding<BitRange<36, 8>>;
using TrigEncoding = Encoding<BitRange<13, 1>>;
using TsIdx13Encoding = Encoding<BitRange<36, 13>>;
using UEncoding = Encoding<BitRange<7, 1>>;
using VComp2Encoding = Encoding<BitRange<54, 3>>;
using VComp3Encoding = Encoding<BitRange<43, 2>, BitRange<47, 1>>;
using VModeEncoding = Encoding<BitRange<48, 2>>;
using VOPEncoding = Encoding<BitRange<51, 3>>;
using VPDestEncoding = Encoding<BitRange<45, 3>>;
using VRedEncoding = Encoding<BitRange<53, 2>>;
using VScaleEncoding = Encoding<BitRange<51, 2>>;
using WmskEncoding = Encoding<BitRange<31, 4>>;
using Wmsk3Encoding = Encoding<BitRange<50, 3>>;
using WriteCCEncoding = Encoding<BitRange<47, 1>>;
using WriteCCIEncoding = Encoding<BitRange<52, 1>>;
using XMADCopEncoding = Encoding<BitRange<50, 3>>;
using XMADCop2Encoding = Encoding<BitRange<50, 2>>;
using XModeEncoding = Encoding<BitRange<43, 2>>;
using XmEncoding = Encoding<BitRange<43, 1>>;
using Xm10Encoding = Encoding<BitRange<56, 1>>;
using Xm2Encoding = Encoding<BitRange<53, 1>>;
using Xm3Encoding = Encoding<BitRange<49, 1>>;
using Xm4Encoding = Encoding<BitRange<46, 1>>;
using Xm5Encoding = Encoding<BitRange<38, 1>>;
using Xm6Encoding = Encoding<BitRange<57, 1>>;
using Xm7Encoding = Encoding<BitRange<38, 1>>;
using Xm8Encoding = Encoding<BitRange<54, 1>>;
using Xm9Encoding = Encoding<BitRange<48, 1>>;
using Xm_IEncoding = Encoding<BitRange<57, 1>>;
using XmdSHFEncoding = Encoding<BitRange<48, 2>>;
using aA2Encoding = Encoding<BitRange<46, 1>>;
using aA3Encoding = Encoding<BitRange<54, 1>>;
using aA4Encoding = Encoding<BitRange<7, 1>>;
using aAHEncoding = Encoding<BitRange<44, 1>>;
using aBEncoding = Encoding<BitRange<49, 1>>;
using aB2Encoding = Encoding<BitRange<44, 1>>;
using aBHEncoding = Encoding<BitRange<30, 1>>;
using aBH2Encoding = Encoding<BitRange<54, 1>>;
using aSelectEncoding = Encoding<BitRange<36, 3>, BitRange<48, 1>>;
using asSize1RegBCEncoding = Encoding<BitRange<20, 8>, BitRange<52, 1>>;
using asel4Encoding = Encoding<BitRange<32, 4>>;
using atomsbcRZEncoding = Encoding<BitRange<28, 2>>;
using atomscSPINEncoding = Encoding<BitRange<53, 1>>;
using bSelectEncoding = Encoding<BitRange<28, 3>, BitRange<49, 1>>;
using bSelectUEncoding = Encoding<BitRange<28, 3>>;
using bcRZEncoding = Encoding<BitRange<50, 2>>;
using bsel4Encoding = Encoding<BitRange<28, 4>>;
using hadd2_32i__PgEncoding = Encoding<BitRange<16, 3>>;
using hadd2_32i__PgNotEncoding = Encoding<BitRange<19, 1>>;
using hadd2_32i__RaEncoding = Encoding<BitRange<8, 8>>;
using hadd2_32i__Ra_iswz_Ra_32i_modEncoding = Encoding<BitRange<53, 2>>;
using hadd2_32i__Ra_negateEncoding = Encoding<BitRange<56, 1>>;
using hadd2_32i__RdEncoding = Encoding<BitRange<0, 8>>;
using hadd2_32i__dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hadd2_32i__ftzEncoding = Encoding<BitRange<55, 1>>;
using hadd2_32i__immEncoding = Encoding<BitRange<36, 16>>;
using hadd2_32i__imm2Encoding = Encoding<BitRange<20, 16>>;
using hadd2_32i__opcodeEncoding = Encoding<BitRange<57, 7>>;
using hadd2_32i__req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hadd2_32i__satEncoding = Encoding<BitRange<52, 1>>;
using hadd2_32i__src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hadd2_32i__usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hadd2__v0_PgEncoding = Encoding<BitRange<16, 3>>;
using hadd2__v0_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hadd2__v0_RaEncoding = Encoding<BitRange<8, 8>>;
using hadd2__v0_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hadd2__v0_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hadd2__v0_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hadd2__v0_RdEncoding = Encoding<BitRange<0, 8>>;
using hadd2__v0_Sb_absoluteEncoding = Encoding<BitRange<54, 1>>;
using hadd2__v0_Sb_negateEncoding = Encoding<BitRange<56, 1>>;
using hadd2__v0_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hadd2__v0_ftzEncoding = Encoding<BitRange<39, 1>>;
using hadd2__v0_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hadd2__v0_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using hadd2__v0_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hadd2__v0_satEncoding = Encoding<BitRange<52, 1>>;
using hadd2__v0_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hadd2__v0_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hadd2__v1_PgEncoding = Encoding<BitRange<16, 3>>;
using hadd2__v1_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hadd2__v1_RaEncoding = Encoding<BitRange<8, 8>>;
using hadd2__v1_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hadd2__v1_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hadd2__v1_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hadd2__v1_RdEncoding = Encoding<BitRange<0, 8>>;
using hadd2__v1_SbEncoding = Encoding<BitRange<30, 9>, BitRange<56, 1>>;
using hadd2__v1_Sb2Encoding = Encoding<BitRange<20, 10>>;
using hadd2__v1_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hadd2__v1_ftzEncoding = Encoding<BitRange<39, 1>>;
using hadd2__v1_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hadd2__v1_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using hadd2__v1_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hadd2__v1_satEncoding = Encoding<BitRange<52, 1>>;
using hadd2__v1_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hadd2__v1_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hadd2__v2_PgEncoding = Encoding<BitRange<16, 3>>;
using hadd2__v2_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hadd2__v2_RaEncoding = Encoding<BitRange<8, 8>>;
using hadd2__v2_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hadd2__v2_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hadd2__v2_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hadd2__v2_RdEncoding = Encoding<BitRange<0, 8>>;
using hadd2__v2_SbEncoding = Encoding<BitRange<20, 8>>;
using hadd2__v2_Sb_absoluteEncoding = Encoding<BitRange<30, 1>>;
using hadd2__v2_Sb_iswz_Rb_modEncoding = Encoding<BitRange<28, 2>>;
using hadd2__v2_Sb_negateEncoding = Encoding<BitRange<31, 1>>;
using hadd2__v2_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hadd2__v2_ftzEncoding = Encoding<BitRange<39, 1>>;
using hadd2__v2_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hadd2__v2_opcodeEncoding = Encoding<BitRange<51, 13>>;
using hadd2__v2_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hadd2__v2_satEncoding = Encoding<BitRange<32, 1>>;
using hadd2__v2_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hadd2__v2_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hfma2__v0_PgEncoding = Encoding<BitRange<16, 3>>;
using hfma2__v0_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hfma2__v0_RaEncoding = Encoding<BitRange<8, 8>>;
using hfma2__v0_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hfma2__v0_RcEncoding = Encoding<BitRange<39, 8>>;
using hfma2__v0_Rc_iswz_Rc_modEncoding = Encoding<BitRange<53, 2>>;
using hfma2__v0_Rc_negateEncoding = Encoding<BitRange<51, 1>>;
using hfma2__v0_RdEncoding = Encoding<BitRange<0, 8>>;
using hfma2__v0_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hfma2__v0_fmzEncoding = Encoding<BitRange<57, 2>>;
using hfma2__v0_nABEncoding = Encoding<BitRange<56, 1>>;
using hfma2__v0_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hfma2__v0_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<59, 5>>;
using hfma2__v0_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hfma2__v0_satEncoding = Encoding<BitRange<52, 1>>;
using hfma2__v0_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hfma2__v0_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hfma2__v1_PgEncoding = Encoding<BitRange<16, 3>>;
using hfma2__v1_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hfma2__v1_RaEncoding = Encoding<BitRange<8, 8>>;
using hfma2__v1_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hfma2__v1_RcEncoding = Encoding<BitRange<39, 8>>;
using hfma2__v1_Rc_iswz_Rc_modEncoding = Encoding<BitRange<53, 2>>;
using hfma2__v1_Rc_negateEncoding = Encoding<BitRange<51, 1>>;
using hfma2__v1_RdEncoding = Encoding<BitRange<0, 8>>;
using hfma2__v1_SbEncoding = Encoding<BitRange<30, 9>, BitRange<56, 1>>;
using hfma2__v1_Sb2Encoding = Encoding<BitRange<20, 10>>;
using hfma2__v1_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hfma2__v1_fmzEncoding = Encoding<BitRange<57, 2>>;
using hfma2__v1_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hfma2__v1_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<59, 5>>;
using hfma2__v1_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hfma2__v1_satEncoding = Encoding<BitRange<52, 1>>;
using hfma2__v1_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hfma2__v1_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hfma2__v2_PgEncoding = Encoding<BitRange<16, 3>>;
using hfma2__v2_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hfma2__v2_RaEncoding = Encoding<BitRange<8, 8>>;
using hfma2__v2_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hfma2__v2_RcEncoding = Encoding<BitRange<39, 8>>;
using hfma2__v2_Rc_iswz_Rc_reg_modEncoding = Encoding<BitRange<35, 2>>;
using hfma2__v2_Rc_negateEncoding = Encoding<BitRange<30, 1>>;
using hfma2__v2_RdEncoding = Encoding<BitRange<0, 8>>;
using hfma2__v2_SbEncoding = Encoding<BitRange<20, 8>>;
using hfma2__v2_Sb_iswz_Rb_modEncoding = Encoding<BitRange<28, 2>>;
using hfma2__v2_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hfma2__v2_fmzEncoding = Encoding<BitRange<37, 2>>;
using hfma2__v2_nABEncoding = Encoding<BitRange<31, 1>>;
using hfma2__v2_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hfma2__v2_opcodeEncoding = Encoding<BitRange<51, 13>>;
using hfma2__v2_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hfma2__v2_satEncoding = Encoding<BitRange<32, 1>>;
using hfma2__v2_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hfma2__v2_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hmul2_32i__PgEncoding = Encoding<BitRange<16, 3>>;
using hmul2_32i__PgNotEncoding = Encoding<BitRange<19, 1>>;
using hmul2_32i__RaEncoding = Encoding<BitRange<8, 8>>;
using hmul2_32i__Ra_iswz_Ra_32i_modEncoding = Encoding<BitRange<53, 2>>;
using hmul2_32i__RdEncoding = Encoding<BitRange<0, 8>>;
using hmul2_32i__dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hmul2_32i__fmzEncoding = Encoding<BitRange<55, 2>>;
using hmul2_32i__immEncoding = Encoding<BitRange<36, 16>>;
using hmul2_32i__imm2Encoding = Encoding<BitRange<20, 16>>;
using hmul2_32i__opcodeEncoding = Encoding<BitRange<57, 7>>;
using hmul2_32i__req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hmul2_32i__satEncoding = Encoding<BitRange<52, 1>>;
using hmul2_32i__src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hmul2_32i__usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hmul2__v0_PgEncoding = Encoding<BitRange<16, 3>>;
using hmul2__v0_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hmul2__v0_RaEncoding = Encoding<BitRange<8, 8>>;
using hmul2__v0_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hmul2__v0_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hmul2__v0_RdEncoding = Encoding<BitRange<0, 8>>;
using hmul2__v0_Sb_absoluteEncoding = Encoding<BitRange<54, 1>>;
using hmul2__v0_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hmul2__v0_fmzEncoding = Encoding<BitRange<39, 2>>;
using hmul2__v0_nABEncoding = Encoding<BitRange<43, 1>>;
using hmul2__v0_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hmul2__v0_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using hmul2__v0_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hmul2__v0_satEncoding = Encoding<BitRange<52, 1>>;
using hmul2__v0_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hmul2__v0_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hmul2__v1_PgEncoding = Encoding<BitRange<16, 3>>;
using hmul2__v1_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hmul2__v1_RaEncoding = Encoding<BitRange<8, 8>>;
using hmul2__v1_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hmul2__v1_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hmul2__v1_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hmul2__v1_RdEncoding = Encoding<BitRange<0, 8>>;
using hmul2__v1_SbEncoding = Encoding<BitRange<30, 9>, BitRange<56, 1>>;
using hmul2__v1_Sb2Encoding = Encoding<BitRange<20, 10>>;
using hmul2__v1_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hmul2__v1_fmzEncoding = Encoding<BitRange<39, 2>>;
using hmul2__v1_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hmul2__v1_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using hmul2__v1_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hmul2__v1_satEncoding = Encoding<BitRange<52, 1>>;
using hmul2__v1_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hmul2__v1_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hmul2__v2_PgEncoding = Encoding<BitRange<16, 3>>;
using hmul2__v2_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hmul2__v2_RaEncoding = Encoding<BitRange<8, 8>>;
using hmul2__v2_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hmul2__v2_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hmul2__v2_RdEncoding = Encoding<BitRange<0, 8>>;
using hmul2__v2_SbEncoding = Encoding<BitRange<20, 8>>;
using hmul2__v2_Sb_absoluteEncoding = Encoding<BitRange<30, 1>>;
using hmul2__v2_Sb_iswz_Rb_modEncoding = Encoding<BitRange<28, 2>>;
using hmul2__v2_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hmul2__v2_fmzEncoding = Encoding<BitRange<39, 2>>;
using hmul2__v2_nABEncoding = Encoding<BitRange<31, 1>>;
using hmul2__v2_ofmtEncoding = Encoding<BitRange<49, 2>>;
using hmul2__v2_opcodeEncoding = Encoding<BitRange<51, 13>>;
using hmul2__v2_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hmul2__v2_satEncoding = Encoding<BitRange<32, 1>>;
using hmul2__v2_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hmul2__v2_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hset2__v0_PgEncoding = Encoding<BitRange<16, 3>>;
using hset2__v0_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hset2__v0_PsEncoding = Encoding<BitRange<39, 3>>;
using hset2__v0_PsNotEncoding = Encoding<BitRange<42, 1>>;
using hset2__v0_RaEncoding = Encoding<BitRange<8, 8>>;
using hset2__v0_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hset2__v0_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hset2__v0_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hset2__v0_RdEncoding = Encoding<BitRange<0, 8>>;
using hset2__v0_Sb_negateEncoding = Encoding<BitRange<56, 1>>;
using hset2__v0_bopEncoding = Encoding<BitRange<45, 2>>;
using hset2__v0_bvalEncoding = Encoding<BitRange<53, 1>>;
using hset2__v0_cmpEncoding = Encoding<BitRange<49, 4>>;
using hset2__v0_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hset2__v0_ftzEncoding = Encoding<BitRange<54, 1>>;
using hset2__v0_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using hset2__v0_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hset2__v0_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hset2__v0_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hset2__v1_PgEncoding = Encoding<BitRange<16, 3>>;
using hset2__v1_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hset2__v1_PsEncoding = Encoding<BitRange<39, 3>>;
using hset2__v1_PsNotEncoding = Encoding<BitRange<42, 1>>;
using hset2__v1_RaEncoding = Encoding<BitRange<8, 8>>;
using hset2__v1_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hset2__v1_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hset2__v1_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hset2__v1_RdEncoding = Encoding<BitRange<0, 8>>;
using hset2__v1_SbEncoding = Encoding<BitRange<30, 9>, BitRange<56, 1>>;
using hset2__v1_Sb2Encoding = Encoding<BitRange<20, 10>>;
using hset2__v1_bopEncoding = Encoding<BitRange<45, 2>>;
using hset2__v1_bvalEncoding = Encoding<BitRange<53, 1>>;
using hset2__v1_cmpEncoding = Encoding<BitRange<49, 4>>;
using hset2__v1_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hset2__v1_ftzEncoding = Encoding<BitRange<54, 1>>;
using hset2__v1_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using hset2__v1_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hset2__v1_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hset2__v1_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hset2__v2_PgEncoding = Encoding<BitRange<16, 3>>;
using hset2__v2_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hset2__v2_PsEncoding = Encoding<BitRange<39, 3>>;
using hset2__v2_PsNotEncoding = Encoding<BitRange<42, 1>>;
using hset2__v2_RaEncoding = Encoding<BitRange<8, 8>>;
using hset2__v2_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hset2__v2_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hset2__v2_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hset2__v2_RdEncoding = Encoding<BitRange<0, 8>>;
using hset2__v2_SbEncoding = Encoding<BitRange<20, 8>>;
using hset2__v2_Sb_absoluteEncoding = Encoding<BitRange<30, 1>>;
using hset2__v2_Sb_iswz_Rb_modEncoding = Encoding<BitRange<28, 2>>;
using hset2__v2_Sb_negateEncoding = Encoding<BitRange<31, 1>>;
using hset2__v2_bopEncoding = Encoding<BitRange<45, 2>>;
using hset2__v2_bvalEncoding = Encoding<BitRange<49, 1>>;
using hset2__v2_cmpEncoding = Encoding<BitRange<35, 4>>;
using hset2__v2_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hset2__v2_ftzEncoding = Encoding<BitRange<50, 1>>;
using hset2__v2_opcodeEncoding = Encoding<BitRange<51, 13>>;
using hset2__v2_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hset2__v2_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hset2__v2_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hset2_bop__v0_PgEncoding = Encoding<BitRange<16, 3>>;
using hset2_bop__v0_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hset2_bop__v0_PsEncoding = Encoding<BitRange<39, 3>>;
using hset2_bop__v0_PsNotEncoding = Encoding<BitRange<42, 1>>;
using hset2_bop__v0_RaEncoding = Encoding<BitRange<8, 8>>;
using hset2_bop__v0_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hset2_bop__v0_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hset2_bop__v0_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hset2_bop__v0_RdEncoding = Encoding<BitRange<0, 8>>;
using hset2_bop__v0_Sb_negateEncoding = Encoding<BitRange<56, 1>>;
using hset2_bop__v0_bopEncoding = Encoding<BitRange<45, 2>>;
using hset2_bop__v0_bvalEncoding = Encoding<BitRange<53, 1>>;
using hset2_bop__v0_cmpEncoding = Encoding<BitRange<49, 4>>;
using hset2_bop__v0_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hset2_bop__v0_ftzEncoding = Encoding<BitRange<54, 1>>;
using hset2_bop__v0_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using hset2_bop__v0_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hset2_bop__v0_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hset2_bop__v0_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hset2_bop__v1_PgEncoding = Encoding<BitRange<16, 3>>;
using hset2_bop__v1_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hset2_bop__v1_PsEncoding = Encoding<BitRange<39, 3>>;
using hset2_bop__v1_PsNotEncoding = Encoding<BitRange<42, 1>>;
using hset2_bop__v1_RaEncoding = Encoding<BitRange<8, 8>>;
using hset2_bop__v1_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hset2_bop__v1_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hset2_bop__v1_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hset2_bop__v1_RdEncoding = Encoding<BitRange<0, 8>>;
using hset2_bop__v1_SbEncoding = Encoding<BitRange<30, 9>, BitRange<56, 1>>;
using hset2_bop__v1_Sb2Encoding = Encoding<BitRange<20, 10>>;
using hset2_bop__v1_bopEncoding = Encoding<BitRange<45, 2>>;
using hset2_bop__v1_bvalEncoding = Encoding<BitRange<53, 1>>;
using hset2_bop__v1_cmpEncoding = Encoding<BitRange<49, 4>>;
using hset2_bop__v1_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hset2_bop__v1_ftzEncoding = Encoding<BitRange<54, 1>>;
using hset2_bop__v1_opcodeEncoding = Encoding<BitRange<55, 1>, BitRange<57, 7>>;
using hset2_bop__v1_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hset2_bop__v1_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hset2_bop__v1_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using hset2_bop__v2_PgEncoding = Encoding<BitRange<16, 3>>;
using hset2_bop__v2_PgNotEncoding = Encoding<BitRange<19, 1>>;
using hset2_bop__v2_PsEncoding = Encoding<BitRange<39, 3>>;
using hset2_bop__v2_PsNotEncoding = Encoding<BitRange<42, 1>>;
using hset2_bop__v2_RaEncoding = Encoding<BitRange<8, 8>>;
using hset2_bop__v2_Ra_absoluteEncoding = Encoding<BitRange<44, 1>>;
using hset2_bop__v2_Ra_iswz_Ra_modEncoding = Encoding<BitRange<47, 2>>;
using hset2_bop__v2_Ra_negateEncoding = Encoding<BitRange<43, 1>>;
using hset2_bop__v2_RdEncoding = Encoding<BitRange<0, 8>>;
using hset2_bop__v2_SbEncoding = Encoding<BitRange<20, 8>>;
using hset2_bop__v2_Sb_absoluteEncoding = Encoding<BitRange<30, 1>>;
using hset2_bop__v2_Sb_iswz_Rb_modEncoding = Encoding<BitRange<28, 2>>;
using hset2_bop__v2_Sb_negateEncoding = Encoding<BitRange<31, 1>>;
using hset2_bop__v2_bopEncoding = Encoding<BitRange<45, 2>>;
using hset2_bop__v2_bvalEncoding = Encoding<BitRange<49, 1>>;
using hset2_bop__v2_cmpEncoding = Encoding<BitRange<35, 4>>;
using hset2_bop__v2_dst_wr_sbEncoding = Encoding<BitRange<5, 3>>;
using hset2_bop__v2_ftzEncoding = Encoding<BitRange<50, 1>>;
using hset2_bop__v2_opcodeEncoding = Encoding<BitRange<51, 13>>;
using hset2_bop__v2_req_sb_bitsetEncoding = Encoding<BitRange<11, 6>>;
using hset2_bop__v2_src_rel_sbEncoding = Encoding<BitRange<8, 3>>;
using hset2_bop__v2_usched_infoEncoding = Encoding<BitRange<0, 5>>;
using nA1Encoding = Encoding<BitRange<48, 1>>;
using nA2Encoding = Encoding<BitRange<43, 1>>;
using nA3Encoding = Encoding<BitRange<43, 1>>;
using nA4Encoding = Encoding<BitRange<45, 1>>;
using nA5Encoding = Encoding<BitRange<37, 1>>;
using nA6Encoding = Encoding<BitRange<56, 1>>;
using nA7Encoding = Encoding<BitRange<51, 1>>;
using nABEncoding = Encoding<BitRange<48, 1>>;
using nAB2Encoding = Encoding<BitRange<56, 1>>;
using nAB_HEncoding = Encoding<BitRange<56, 1>>;
using nA_LEncoding = Encoding<BitRange<39, 1>>;
using nA_L2Encoding = Encoding<BitRange<55, 1>>;
using nBEncoding = Encoding<BitRange<45, 1>>;
using nB2Encoding = Encoding<BitRange<45, 1>>;
using nB3Encoding = Encoding<BitRange<53, 1>>;
using nB4Encoding = Encoding<BitRange<6, 1>>;
using nB7Encoding = Encoding<BitRange<50, 1>>;
using nBHEncoding = Encoding<BitRange<31, 1>>;
using nBH2Encoding = Encoding<BitRange<56, 1>>;
using nB_LEncoding = Encoding<BitRange<40, 1>>;
using nB_L2Encoding = Encoding<BitRange<56, 1>>;
using nCEncoding = Encoding<BitRange<49, 1>>;
using nC2Encoding = Encoding<BitRange<57, 1>>;
using nC7Encoding = Encoding<BitRange<49, 1>>;
using nC_HEncoding = Encoding<BitRange<52, 1>>;
using nC_H2Encoding = Encoding<BitRange<51, 1>>;
using safmtEncoding = Encoding<BitRange<48, 1>>;
using sat_HEncoding = Encoding<BitRange<52, 1>>;
using satmBAEncoding = Encoding<BitRange<28, 1>>;
using satmOpEncoding = Encoding<BitRange<29, 4>>;
using satmSize1Encoding = Encoding<BitRange<51, 3>>;
using satmSize2Encoding = Encoding<BitRange<36, 3>>;
using sbfmtEncoding = Encoding<BitRange<49, 1>>;
using shfl_imm5Encoding = Encoding<BitRange<20, 5>>;
using tex2d_4Encoding = Encoding<BitRange<53, 4>>;
using vAmuxEncoding = Encoding<BitRange<47, 2>>;
using vAmux_HEncoding = Encoding<BitRange<53, 2>>;
using vAmux_H2Encoding = Encoding<BitRange<47, 2>>;
using vBmuxEncoding = Encoding<BitRange<28, 2>>;
using vBmux_HEncoding = Encoding<BitRange<53, 2>>;

enum class A : std::uint32_t {
  A  = 0x0     , // A
  a  = 0x0     , // a
};
enum class AIO : std::uint32_t {
  I  = 0x0     , // I
  O  = 0x1     , // O
};
enum class AInteger : std::uint32_t {
  _32  = 0x0     , // 32
  _64  = 0x1     , // 64
  _96  = 0x2     , // 96
  _128 = 0x3     , // 128
};
enum class ALLOnly : std::uint32_t {
  ALL  = 0x0     , // ALL
};
enum class ASel4 : std::uint32_t {
  _0000          = 0x0     , // 0000
  _1111          = 0x1     , // 1111
  _2222          = 0x2     , // 2222
  _3333          = 0x3     , // 3333
  _3210          = 0x4     , // 3210
  _4321          = 0x5     , // 4321
  _5432          = 0x6     , // 5432
  _6543          = 0x7     , // 6543
  _3201          = 0x8     , // 3201
  _3012          = 0x9     , // 3012
  _0213          = 0xa     , // 0213
  _3120          = 0xb     , // 3120
  _1230          = 0xc     , // 1230
  _2310          = 0xd     , // 2310
  ASEL4E         = 0xe     , // ASEL4E
  INVALIDASEL4E  = 0xe     , // INVALIDASEL4E
  ASEL4F         = 0xf     , // ASEL4F
  INVALIDASEL4F  = 0xf     , // INVALIDASEL4F
};
enum class AdMode : std::uint32_t {
  IA   = 0x0     , // IA
  IL   = 0x1     , // IL
  IS   = 0x2     , // IS
  ISL  = 0x3     , // ISL
};
enum class AtomOp : std::uint32_t {
  ADD              = 0x0     , // ADD
  INVALIDATOMOP0   = 0x0     , // INVALIDATOMOP0
  INVALIDATOMOP1   = 0x1     , // INVALIDATOMOP1
  MIN              = 0x1     , // MIN
  INVALIDATOMOP2   = 0x2     , // INVALIDATOMOP2
  MAX              = 0x2     , // MAX
  INC              = 0x3     , // INC
  INVALIDATOMOP3   = 0x3     , // INVALIDATOMOP3
  DEC              = 0x4     , // DEC
  INVALIDATOMOP4   = 0x4     , // INVALIDATOMOP4
  AND              = 0x5     , // AND
  INVALIDATOMOP5   = 0x5     , // INVALIDATOMOP5
  INVALIDATOMOP6   = 0x6     , // INVALIDATOMOP6
  OR               = 0x6     , // OR
  INVALIDATOMOP7   = 0x7     , // INVALIDATOMOP7
  XOR              = 0x7     , // XOR
  EXCH             = 0x8     , // EXCH
  INVALIDATOMOP8   = 0x8     , // INVALIDATOMOP8
  INVALIDATOMOP9   = 0x9     , // INVALIDATOMOP9
  INVALIDATOMOP10  = 0xa     , // INVALIDATOMOP10
  SAFEADD          = 0xa     , // SAFEADD
  INVALIDATOMOP11  = 0xb     , // INVALIDATOMOP11
  INVALIDATOMOP12  = 0xc     , // INVALIDATOMOP12
  INVALIDATOMOP13  = 0xd     , // INVALIDATOMOP13
  INVALIDATOMOP14  = 0xe     , // INVALIDATOMOP14
  INVALIDATOMOP15  = 0xf     , // INVALIDATOMOP15
};
enum class AtomicInteger : std::uint32_t {
  _32           = 0x0     , // 32
  U32           = 0x0     , // U32
  S32           = 0x1     , // S32
  _64           = 0x2     , // 64
  U64           = 0x2     , // U64
  F32           = 0x3     , // F32
  F32_FTZ_RN    = 0x3     , // F32.FTZ.RN
  F16x2_FTZ_RN  = 0x4     , // F16x2.FTZ.RN
  S64           = 0x5     , // S64
  SD32          = 0x6     , // SD32
  SD64          = 0x7     , // SD64
};
enum class AtomsOp : std::uint32_t {
  ADD               = 0x0     , // ADD
  INVALIDATOMSOP0   = 0x0     , // INVALIDATOMSOP0
  INVALIDATOMSOP1   = 0x1     , // INVALIDATOMSOP1
  MIN               = 0x1     , // MIN
  INVALIDATOMSOP2   = 0x2     , // INVALIDATOMSOP2
  MAX               = 0x2     , // MAX
  INC               = 0x3     , // INC
  INVALIDATOMSOP3   = 0x3     , // INVALIDATOMSOP3
  DEC               = 0x4     , // DEC
  INVALIDATOMSOP4   = 0x4     , // INVALIDATOMSOP4
  AND               = 0x5     , // AND
  INVALIDATOMSOP5   = 0x5     , // INVALIDATOMSOP5
  INVALIDATOMSOP6   = 0x6     , // INVALIDATOMSOP6
  OR                = 0x6     , // OR
  INVALIDATOMSOP7   = 0x7     , // INVALIDATOMSOP7
  XOR               = 0x7     , // XOR
  EXCH              = 0x8     , // EXCH
  INVALIDATOMSOP8   = 0x8     , // INVALIDATOMSOP8
  INVALIDATOMSOP9   = 0x9     , // INVALIDATOMSOP9
  INVALIDATOMSOP10  = 0xa     , // INVALIDATOMSOP10
  INVALIDATOMSOP11  = 0xb     , // INVALIDATOMSOP11
  INVALIDATOMSOP12  = 0xc     , // INVALIDATOMSOP12
  INVALIDATOMSOP13  = 0xd     , // INVALIDATOMSOP13
  INVALIDATOMSOP14  = 0xe     , // INVALIDATOMSOP14
  INVALIDATOMSOP15  = 0xf     , // INVALIDATOMSOP15
};
enum class AtomsSPIN : std::uint32_t {
  noSPIN  = 0x0     , // noSPIN
  SPIN    = 0x1     , // SPIN
};
enum class AtomsSz : std::uint32_t {
  _32  = 0x0     , // 32
  U32  = 0x0     , // U32
  S32  = 0x1     , // S32
  _64  = 0x2     , // 64
  U64  = 0x2     , // U64
  S64  = 0x3     , // S64
};
enum class B1B0 : std::uint32_t {
  B0  = 0x0     , // B0
  H0  = 0x0     , // H0
  B1  = 0x1     , // B1
  B2  = 0x2     , // B2
  H1  = 0x2     , // H1
  B3  = 0x3     , // B3
};
enum class B3B0 : std::uint32_t {
  B0  = 0x0     , // B0
  B1  = 0x1     , // B1
  B2  = 0x2     , // B2
  B3  = 0x3     , // B3
};
enum class BA : std::uint32_t {
  noBA  = 0x0     , // noBA
  BA    = 0x1     , // BA
};
enum class BASE : std::uint32_t {
  MAP    = 0x0     , // MAP
  PATCH  = 0x1     , // PATCH
  PRIM   = 0x2     , // PRIM
  ATTR   = 0x3     , // ATTR
};
enum class BOnly : std::uint32_t {
  B  = 0x0     , // B
};
enum class BPTMode : std::uint32_t {
  DRAIN_ILLEGAL  = 0x0     , // DRAIN_ILLEGAL
  CAL            = 0x1     , // CAL
  PAUSE          = 0x2     , // PAUSE
  TRAP           = 0x3     , // TRAP
  INT            = 0x4     , // INT
  DRAIN          = 0x5     , // DRAIN
};
enum class BREV : std::uint32_t {
  noBREV  = 0x0     , // noBREV
  BREV    = 0x1     , // BREV
};
enum class BSel4 : std::uint32_t {
  _4444          = 0x0     , // 4444
  _5555          = 0x1     , // 5555
  _6666          = 0x2     , // 6666
  _7777          = 0x3     , // 7777
  _7654          = 0x4     , // 7654
  _6543          = 0x5     , // 6543
  _5432          = 0x6     , // 5432
  _4321          = 0x7     , // 4321
  _4567          = 0x8     , // 4567
  _6745          = 0x9     , // 6745
  _5476          = 0xa     , // 5476
  BSEL4B         = 0xb     , // BSEL4B
  INVALIDBSEL4B  = 0xb     , // INVALIDBSEL4B
  BSEL4C         = 0xc     , // BSEL4C
  INVALIDBSEL4C  = 0xc     , // INVALIDBSEL4C
  BSEL4D         = 0xd     , // BSEL4D
  INVALIDBSEL4D  = 0xd     , // INVALIDBSEL4D
  BSEL4E         = 0xe     , // BSEL4E
  INVALIDBSEL4E  = 0xe     , // INVALIDBSEL4E
};
enum class BVal : std::uint32_t {
  BM  = 0x0     , // BM
  BF  = 0x1     , // BF
};
enum class BarArv : std::uint32_t {
  ARV  = 0x1     , // ARV
};
enum class BarRED : std::uint32_t {
  RED  = 0x2     , // RED
};
enum class BarSCAN : std::uint32_t {
  SCAN  = 0x3     , // SCAN
};
enum class BarSYNCALL : std::uint32_t {
  SYNCALL  = 0x4     , // SYNCALL
};
enum class BarSync : std::uint32_t {
  SYNC  = 0x0     , // SYNC
};
enum class Barmd : std::uint32_t {
  BAR      = 0x0     , // BAR
  RESULT   = 0x1     , // RESULT
  WARP     = 0x2     , // WARP
  INVALID  = 0x3     , // INVALID
};
enum class BarmdBAR : std::uint32_t {
  BAR      = 0x0     , // BAR
  INVALID  = 0x3     , // INVALID
};
enum class BarmdRESULT : std::uint32_t {
  RESULT  = 0x1     , // RESULT
};
enum class BarmdWARP : std::uint32_t {
  WARP  = 0x2     , // WARP
};
enum class Bop : std::uint32_t {
  AND           = 0x0     , // AND
  OR            = 0x1     , // OR
  XOR           = 0x2     , // XOR
  INVALIDBOP03  = 0x3     , // INVALIDBOP03
  INVALIDBOP13  = 0x3     , // INVALIDBOP13
  INVALIDBOP3   = 0x3     , // INVALIDBOP3
};
enum class C : std::uint32_t {
  C  = 0x0     , // C
  c  = 0x0     , // c
};
enum class CAS : std::uint32_t {
  CAS  = 0x0     , // CAS
};
enum class CASInteger : std::uint32_t {
  _32  = 0x0     , // 32
  S32  = 0x0     , // S32
  U32  = 0x0     , // U32
  _64  = 0x1     , // 64
  S64  = 0x1     , // S64
  U64  = 0x1     , // U64
};
enum class CAST : std::uint32_t {
  CAST  = 0x0     , // CAST
};
enum class CC : std::uint32_t {
  CC  = 0x1     , // CC
};
enum class CCPR : std::uint32_t {
  PR  = 0x0     , // PR
  CC  = 0x1     , // CC
};
enum class CCTLLOp2 : std::uint32_t {
  IVALL  = 0x6     , // IVALL
};
enum class CCTLLOp3 : std::uint32_t {
  WBALL  = 0x8     , // WBALL
};
enum class CCTLOp : std::uint32_t {
  PF1              = 0x1     , // PF1
  PF1_5            = 0x2     , // PF1.5
  PF2              = 0x3     , // PF2
  WB               = 0x4     , // WB
  IV               = 0x5     , // IV
  RS               = 0x7     , // RS
  RSLB             = 0x9     , // RSLB
  INVALIDCCTLOP10  = 0xa     , // INVALIDCCTLOP10
  INVALIDCCTLOP11  = 0xb     , // INVALIDCCTLOP11
  INVALIDCCTLOP12  = 0xc     , // INVALIDCCTLOP12
  INVALIDCCTLOP13  = 0xd     , // INVALIDCCTLOP13
  INVALIDCCTLOP14  = 0xe     , // INVALIDCCTLOP14
  INVALIDCCTLOP15  = 0xf     , // INVALIDCCTLOP15
};
enum class CCTLTOp : std::uint32_t {
  IVTH             = 0x1     , // IVTH
  INVALIDCCTLTOP2  = 0x2     , // INVALIDCCTLTOP2
  INVALIDCCTLTOP3  = 0x3     , // INVALIDCCTLTOP3
};
enum class CCTLTOpIVALL : std::uint32_t {
  IVALL  = 0x0     , // IVALL
};
enum class CInteger : std::uint32_t {
  _8            = 0x0     , // 8
  SD            = 0x0     , // SD
  U8            = 0x0     , // U8
  S8            = 0x1     , // S8
  _16           = 0x2     , // 16
  U16           = 0x2     , // U16
  S16           = 0x3     , // S16
  _32           = 0x4     , // 32
  _64           = 0x5     , // 64
  _128          = 0x6     , // 128
  INVALIDSIZE7  = 0x7     , // INVALIDSIZE7
};
enum class CInteger_64 : std::uint32_t {
  _64 = 0x5     , // 64
};
enum class CInteger_n64_n128 : std::uint32_t {
  _8            = 0x0     , // 8
  SD            = 0x0     , // SD
  U8            = 0x0     , // U8
  S8            = 0x1     , // S8
  _16           = 0x2     , // 16
  U16           = 0x2     , // U16
  S16           = 0x3     , // S16
  _32           = 0x4     , // 32
  INVALIDSIZE6  = 0x6     , // INVALIDSIZE6
  INVALIDSIZE7  = 0x7     , // INVALIDSIZE7
};
enum class CL : std::uint32_t {
  noCL  = 0x0     , // noCL
  CL    = 0x1     , // CL
};
enum class CRSOnly : std::uint32_t {
  CRS  = 0x1     , // CRS
};
enum class CWMode : std::uint32_t {
  C  = 0x0     , // C
  W  = 0x1     , // W
};
enum class Cache3 : std::uint32_t {
  D                    = 0x0     , // D
  U                    = 0x1     , // U
  C                    = 0x2     , // C
  I                    = 0x3     , // I
  CRS                  = 0x4     , // CRS
  INVALIDCACHETYPE5    = 0x5     , // INVALIDCACHETYPE5
  INVALIDCCTLCACHEOP5  = 0x5     , // INVALIDCCTLCACHEOP5
  INVALIDCACHETYPE6    = 0x6     , // INVALIDCACHETYPE6
  INVALIDCCTLCACHEOP6  = 0x6     , // INVALIDCCTLCACHEOP6
  INVALIDCACHETYPE7    = 0x7     , // INVALIDCACHETYPE7
  INVALIDCCTLCACHEOP7  = 0x7     , // INVALIDCCTLCACHEOP7
};
enum class Cache3CI : std::uint32_t {
  C  = 0x2     , // C
  I  = 0x3     , // I
};
enum class Cache3NoCI : std::uint32_t {
  D                    = 0x0     , // D
  U                    = 0x1     , // U
  CRS                  = 0x4     , // CRS
  INVALIDCACHETYPE5    = 0x5     , // INVALIDCACHETYPE5
  INVALIDCCTLCACHEOP5  = 0x5     , // INVALIDCCTLCACHEOP5
  INVALIDCACHETYPE6    = 0x6     , // INVALIDCACHETYPE6
  INVALIDCCTLCACHEOP6  = 0x6     , // INVALIDCCTLCACHEOP6
  INVALIDCACHETYPE7    = 0x7     , // INVALIDCACHETYPE7
  INVALIDCCTLCACHEOP7  = 0x7     , // INVALIDCCTLCACHEOP7
};
enum class ChkMode : std::uint32_t {
  DIVIDE            = 0x0     , // DIVIDE
  INVALIDCHKMODE1   = 0x1     , // INVALIDCHKMODE1
  INVALIDCHKMODE2   = 0x2     , // INVALIDCHKMODE2
  INVALIDCHKMODE3   = 0x3     , // INVALIDCHKMODE3
  INVALIDCHKMODE4   = 0x4     , // INVALIDCHKMODE4
  INVALIDCHKMODE5   = 0x5     , // INVALIDCHKMODE5
  INVALIDCHKMODE6   = 0x6     , // INVALIDCHKMODE6
  INVALIDCHKMODE7   = 0x7     , // INVALIDCHKMODE7
  INVALIDCHKMODE8   = 0x8     , // INVALIDCHKMODE8
  INVALIDCHKMODE9   = 0x9     , // INVALIDCHKMODE9
  INVALIDCHKMODE10  = 0xa     , // INVALIDCHKMODE10
  INVALIDCHKMODE11  = 0xb     , // INVALIDCHKMODE11
  INVALIDCHKMODE12  = 0xc     , // INVALIDCHKMODE12
  INVALIDCHKMODE13  = 0xd     , // INVALIDCHKMODE13
  INVALIDCHKMODE14  = 0xe     , // INVALIDCHKMODE14
  INVALIDCHKMODE15  = 0xf     , // INVALIDCHKMODE15
  INVALIDCHKMODE16  = 0x10    , // INVALIDCHKMODE16
  INVALIDCHKMODE17  = 0x11    , // INVALIDCHKMODE17
  INVALIDCHKMODE18  = 0x12    , // INVALIDCHKMODE18
  INVALIDCHKMODE19  = 0x13    , // INVALIDCHKMODE19
  INVALIDCHKMODE20  = 0x14    , // INVALIDCHKMODE20
  INVALIDCHKMODE21  = 0x15    , // INVALIDCHKMODE21
  INVALIDCHKMODE22  = 0x16    , // INVALIDCHKMODE22
  INVALIDCHKMODE23  = 0x17    , // INVALIDCHKMODE23
  INVALIDCHKMODE24  = 0x18    , // INVALIDCHKMODE24
  INVALIDCHKMODE25  = 0x19    , // INVALIDCHKMODE25
  INVALIDCHKMODE26  = 0x1a    , // INVALIDCHKMODE26
  INVALIDCHKMODE27  = 0x1b    , // INVALIDCHKMODE27
  INVALIDCHKMODE28  = 0x1c    , // INVALIDCHKMODE28
  INVALIDCHKMODE29  = 0x1d    , // INVALIDCHKMODE29
  INVALIDCHKMODE30  = 0x1e    , // INVALIDCHKMODE30
  INVALIDCHKMODE31  = 0x1f    , // INVALIDCHKMODE31
  INVALIDCHKMODE32  = 0x20    , // INVALIDCHKMODE32
  INVALIDCHKMODE33  = 0x21    , // INVALIDCHKMODE33
  INVALIDCHKMODE34  = 0x22    , // INVALIDCHKMODE34
  INVALIDCHKMODE35  = 0x23    , // INVALIDCHKMODE35
  INVALIDCHKMODE36  = 0x24    , // INVALIDCHKMODE36
  INVALIDCHKMODE37  = 0x25    , // INVALIDCHKMODE37
  INVALIDCHKMODE38  = 0x26    , // INVALIDCHKMODE38
  INVALIDCHKMODE39  = 0x27    , // INVALIDCHKMODE39
  INVALIDCHKMODE40  = 0x28    , // INVALIDCHKMODE40
  INVALIDCHKMODE41  = 0x29    , // INVALIDCHKMODE41
  INVALIDCHKMODE42  = 0x2a    , // INVALIDCHKMODE42
  INVALIDCHKMODE43  = 0x2b    , // INVALIDCHKMODE43
  INVALIDCHKMODE44  = 0x2c    , // INVALIDCHKMODE44
  INVALIDCHKMODE45  = 0x2d    , // INVALIDCHKMODE45
  INVALIDCHKMODE46  = 0x2e    , // INVALIDCHKMODE46
  INVALIDCHKMODE47  = 0x2f    , // INVALIDCHKMODE47
  INVALIDCHKMODE48  = 0x30    , // INVALIDCHKMODE48
  INVALIDCHKMODE49  = 0x31    , // INVALIDCHKMODE49
  INVALIDCHKMODE50  = 0x32    , // INVALIDCHKMODE50
  INVALIDCHKMODE51  = 0x33    , // INVALIDCHKMODE51
  INVALIDCHKMODE52  = 0x34    , // INVALIDCHKMODE52
  INVALIDCHKMODE53  = 0x35    , // INVALIDCHKMODE53
  INVALIDCHKMODE54  = 0x36    , // INVALIDCHKMODE54
  INVALIDCHKMODE55  = 0x37    , // INVALIDCHKMODE55
  INVALIDCHKMODE56  = 0x38    , // INVALIDCHKMODE56
  INVALIDCHKMODE57  = 0x39    , // INVALIDCHKMODE57
  INVALIDCHKMODE58  = 0x3a    , // INVALIDCHKMODE58
  INVALIDCHKMODE59  = 0x3b    , // INVALIDCHKMODE59
  INVALIDCHKMODE60  = 0x3c    , // INVALIDCHKMODE60
  INVALIDCHKMODE61  = 0x3d    , // INVALIDCHKMODE61
  INVALIDCHKMODE62  = 0x3e    , // INVALIDCHKMODE62
  INVALIDCHKMODE63  = 0x3f    , // INVALIDCHKMODE63
};
enum class Clamp1 : std::uint32_t {
  IGN                   = 0x0     , // IGN
  NEAR                  = 0x1     , // NEAR
  TRAP                  = 0x2     , // TRAP
  INVALIDSURFACECLAMP3  = 0x3     , // INVALIDSURFACECLAMP3
};
enum class DC : std::uint32_t {
  noDC  = 0x0     , // noDC
  DC    = 0x1     , // DC
};
enum class DFormat : std::uint32_t {
  UD  = 0x0     , // UD
  SD  = 0x1     , // SD
};
enum class DIR : std::uint32_t {
  NS  = 0x0     , // NS
  RS  = 0x1     , // RS
  LS  = 0x2     , // LS
};
enum class DOnly : std::uint32_t {
  D  = 0x0     , // D
};
enum class Dim1 : std::uint32_t {
  _1D                 = 0x0     , // 1D
  _1D_BUFFER          = 0x1     , // 1D_BUFFER
  _1D_ARRAY           = 0x2     , // 1D_ARRAY
  _2D                 = 0x3     , // 2D
  _2D_ARRAY           = 0x4     , // 2D_ARRAY
  _3D                 = 0x5     , // 3D
  INVALIDSURFACEDIM6  = 0x6     , // INVALIDSURFACEDIM6
  INVALIDSURFACEDIM7  = 0x7     , // INVALIDSURFACEDIM7
};
enum class E : std::uint32_t {
  noE  = 0x0     , // noE
  E    = 0x1     , // E
};
enum class F2FRound1 : std::uint32_t {
  PASS   = 0x0     , // PASS
  RN     = 0x4     , // RN
  ROUND  = 0x4     , // ROUND
  FLOOR  = 0x5     , // FLOOR
  RM     = 0x5     , // RM
  CEIL   = 0x6     , // CEIL
  RP     = 0x6     , // RP
  RZ     = 0x7     , // RZ
  TRUNC  = 0x7     , // TRUNC
};
enum class F2FRound2 : std::uint32_t {
  PASS   = 0x0     , // PASS
  RN     = 0x0     , // RN
  ROUND  = 0x0     , // ROUND
  FLOOR  = 0x1     , // FLOOR
  RM     = 0x1     , // RM
  CEIL   = 0x2     , // CEIL
  RP     = 0x2     , // RP
  RZ     = 0x3     , // RZ
  TRUNC  = 0x3     , // TRUNC
};
enum class F2Ffmts1 : std::uint32_t {
  INVALIDFPDEST0_INVALIDFPSRC0  = 0x0     , // INVALIDFPDEST0.INVALIDFPSRC0
  F32_F32                       = 0xa     , // F32.F32
};
enum class F2Ffmts1_16 : std::uint32_t {
  F16_F16  = 0x5     , // F16.F16
};
enum class F2Ffmts1_64 : std::uint32_t {
  F64_F64  = 0xf     , // F64.F64
};
enum class F2Ffmts2 : std::uint32_t {
  F16_INVALIDFPSRC0   = 0x1     , // F16.INVALIDFPSRC0
  F32_INVALIDFPSRC0   = 0x2     , // F32.INVALIDFPSRC0
  F64_INVALIDFPSRC0   = 0x3     , // F64.INVALIDFPSRC0
  INVALIDFPDEST0_F32  = 0x8     , // INVALIDFPDEST0.F32
  F16_F32             = 0x9     , // F16.F32
};
enum class F2Ffmts2_16 : std::uint32_t {
  INVALIDFPDEST0_F16  = 0x4     , // INVALIDFPDEST0.F16
  F32_F16             = 0x6     , // F32.F16
};
enum class F2Ffmts2_64 : std::uint32_t {
  INVALIDFPDEST0_F64  = 0xc     , // INVALIDFPDEST0.F64
  F16_F64             = 0xd     , // F16.F64
  F32_F64             = 0xe     , // F32.F64
};
enum class F2Ffmts2_64_16 : std::uint32_t {
  F64_F16  = 0x7     , // F64.F16
};
enum class F2Ffmts2_64_32 : std::uint32_t {
  F64_F32  = 0xb     , // F64.F32
};
enum class FMZ : std::uint32_t {
  noFTZ        = 0x0     , // noFTZ
  FTZ          = 0x1     , // FTZ
  FMZ          = 0x2     , // FMZ
  INVALIDFMZ3  = 0x3     , // INVALIDFMZ3
};
enum class FTZ : std::uint32_t {
  noFTZ  = 0x0     , // noFTZ
  FTZ    = 0x1     , // FTZ
};
enum class Float : std::uint32_t {
  INVALIDFPDEST0  = 0x0     , // INVALIDFPDEST0
  INVALIDFPSRC0   = 0x0     , // INVALIDFPSRC0
  F16             = 0x1     , // F16
  F32             = 0x2     , // F32
  F64             = 0x3     , // F64
};
enum class Float16 : std::uint32_t {
  F16  = 0x1     , // F16
};
enum class Float32 : std::uint32_t {
  INVALIDFPDEST0  = 0x0     , // INVALIDFPDEST0
  INVALIDFPSRC0   = 0x0     , // INVALIDFPSRC0
  F32             = 0x2     , // F32
};
enum class Float64 : std::uint32_t {
  F64  = 0x3     , // F64
};
enum class FloatNo64 : std::uint32_t {
  INVALIDFPDEST0  = 0x0     , // INVALIDFPDEST0
  INVALIDFPSRC0   = 0x0     , // INVALIDFPSRC0
  F16             = 0x1     , // F16
  F32             = 0x2     , // F32
};
enum class H1H0 : std::uint32_t {
  H0  = 0x0     , // H0
  H1  = 0x1     , // H1
};
enum class HILO : std::uint32_t {
  LO  = 0x0     , // LO
  HI  = 0x1     , // HI
};
enum class HIOnly : std::uint32_t {
  HI  = 0x0     , // HI
};
enum class H_AND : std::uint32_t {
  noH_AND  = 0x0     , // noH_AND
  H_AND    = 0x1     , // H_AND
};
enum class I2XH : std::uint32_t {
  H0            = 0x0     , // H0
  INVALIDSIZE1  = 0x1     , // INVALIDSIZE1
  H1            = 0x2     , // H1
  INVALIDSIZE3  = 0x3     , // INVALIDSIZE3
};
enum class ICmpAll : std::uint32_t {
  F   = 0x0     , // F
  LT  = 0x1     , // LT
  EQ  = 0x2     , // EQ
  LE  = 0x3     , // LE
  GT  = 0x4     , // GT
  NE  = 0x5     , // NE
  GE  = 0x6     , // GE
  T   = 0x7     , // T
};
enum class ICmpU : std::uint32_t {
  LO  = 0x1     , // LO
  LS  = 0x3     , // LS
  HI  = 0x4     , // HI
  HS  = 0x6     , // HS
};
enum class IDEActionDIOnly : std::uint32_t {
  DI  = 0x1     , // DI
};
enum class IDEActionENOnly : std::uint32_t {
  EN  = 0x0     , // EN
};
enum class IDXOnly : std::uint32_t {
  IDX  = 0x0     , // IDX
};
enum class INC : std::uint32_t {
  NOINC  = 0x0     , // NOINC
  INC    = 0x1     , // INC
};
enum class IPAOp : std::uint32_t {
  PASS      = 0x0     , // PASS
  MUL       = 0x1     , // MUL
  CONSTANT  = 0x2     , // CONSTANT
  SC        = 0x3     , // SC
};
using ISBERDIO = AIO;
enum class ISBERDInteger : std::uint32_t {
  U8   = 0x0     , // U8
  U16  = 0x1     , // U16
  _32  = 0x2     , // 32
};
enum class ISWZ : std::uint32_t {
  H1_H0  = 0x0     , // H1_H0
  F32    = 0x1     , // F32
  H0_H0  = 0x2     , // H0_H0
  H1_H1  = 0x3     , // H1_H1
};
enum class Integer16 : std::uint32_t {
  U16  = 0x2     , // U16
  S16  = 0x3     , // S16
};
enum class Integer32 : std::uint32_t {
  U32  = 0x4     , // U32
  S32  = 0x5     , // S32
};
enum class Integer64 : std::uint32_t {
  U64  = 0x6     , // U64
  S64  = 0x7     , // S64
};
enum class Integer8 : std::uint32_t {
  U8  = 0x0     , // U8
  S8  = 0x1     , // S8
};
enum class IntegerSPA : std::uint32_t {
  U32    = 0x0     , // U32
  S32    = 0x1     , // S32
  U24    = 0x2     , // U24
  S24    = 0x3     , // S24
  U16H0  = 0x4     , // U16H0
  S16H0  = 0x5     , // S16H0
  U16H1  = 0x6     , // U16H1
  S16H1  = 0x7     , // S16H1
};
enum class IntegerSPB : std::uint32_t {
  U16H0  = 0x0     , // U16H0
  S16H0  = 0x1     , // S16H0
  U24    = 0x2     , // U24
  S24    = 0x3     , // S24
};
enum class IntegerSPC : std::uint32_t {
  U32    = 0x0     , // U32
  S32    = 0x1     , // S32
  U24    = 0x2     , // U24
  S24    = 0x3     , // S24
  U16H0  = 0x4     , // U16H0
  S16H0  = 0x5     , // S16H0
};
enum class Invalid64 : std::uint32_t {
  INVALID6  = 0x6     , // INVALID6
  INVALID7  = 0x7     , // INVALID7
};
enum class Invalid8 : std::uint32_t {
  INVALID0  = 0x0     , // INVALID0
  INVALID1  = 0x1     , // INVALID1
};
enum class KeepRefCount : std::uint32_t {
  noKEEPREFCOUNT  = 0x0     , // noKEEPREFCOUNT
  KEEPREFCOUNT    = 0x1     , // KEEPREFCOUNT
};
enum class LC : std::uint32_t {
  noLC  = 0x0     , // noLC
  LC    = 0x1     , // LC
};
enum class LCache : std::uint32_t {
  D                   = 0x0     , // D
  INVALIDLCACHETYPE2  = 0x2     , // INVALIDLCACHETYPE2
  INVALIDLCACHETYPE3  = 0x3     , // INVALIDLCACHETYPE3
};
enum class LDInteger : std::uint32_t {
  _8     = 0x0     , // 8
  U8     = 0x0     , // U8
  S8     = 0x1     , // S8
  _16    = 0x2     , // 16
  U16    = 0x2     , // U16
  S16    = 0x3     , // S16
  _32    = 0x4     , // 32
  _64    = 0x5     , // 64
  _128   = 0x6     , // 128
  U_128  = 0x7     , // U.128
};
enum class LDInteger_nU128 : std::uint32_t {
  _8            = 0x0     , // 8
  U8            = 0x0     , // U8
  S8            = 0x1     , // S8
  _16           = 0x2     , // 16
  U16           = 0x2     , // U16
  S16           = 0x3     , // S16
  _32           = 0x4     , // 32
  _64           = 0x5     , // 64
  _128          = 0x6     , // 128
  INVALIDSIZE7  = 0x7     , // INVALIDSIZE7
};
enum class LDSInteger : std::uint32_t {
  _8              = 0x0     , // 8
  U8              = 0x0     , // U8
  U_8             = 0x1     , // U.8
  U_U8            = 0x1     , // U.U8
  S8              = 0x2     , // S8
  U_S8            = 0x3     , // U.S8
  _16             = 0x4     , // 16
  U16             = 0x4     , // U16
  U_16            = 0x5     , // U.16
  U_U16           = 0x5     , // U.U16
  S16             = 0x6     , // S16
  U_S16           = 0x7     , // U.S16
  _32             = 0x8     , // 32
  U_32            = 0x9     , // U.32
  _64             = 0xa     , // 64
  U_64            = 0xb     , // U.64
  _128            = 0xc     , // 128
  U_128           = 0xd     , // U.128
  INVALIDSIZE7    = 0xe     , // INVALIDSIZE7
  U_INVALIDSIZE7  = 0xf     , // U.INVALIDSIZE7
};
enum class LEOnly : std::uint32_t {
  LE  = 0x0     , // LE
};
enum class LLoadCacheOp : std::uint32_t {
  CA  = 0x0     , // CA
  CS  = 0x0     , // CS
  LU  = 0x1     , // LU
  CI  = 0x2     , // CI
  CV  = 0x3     , // CV
};
enum class LMT : std::uint32_t {
  noLMT  = 0x0     , // noLMT
  LMT    = 0x1     , // LMT
};
enum class LOD : std::uint32_t {
  noLOD         = 0x0     , // noLOD
  LZ            = 0x1     , // LZ
  LB            = 0x2     , // LB
  LL            = 0x3     , // LL
  INVALIDBLOD4  = 0x4     , // INVALIDBLOD4
  INVALIDBLOD5  = 0x5     , // INVALIDBLOD5
  LBA           = 0x6     , // LBA
  LLA           = 0x7     , // LLA
};
enum class LOD1 : std::uint32_t {
  LZ  = 0x0     , // LZ
  LL  = 0x1     , // LL
};
enum class LOD2 : std::uint32_t {
  noLOD  = 0x0     , // noLOD
  LZ     = 0x1     , // LZ
  LL     = 0x2     , // LL
};
enum class LODOnly : std::uint32_t {
  LOD  = 0x0     , // LOD
};
enum class LOOnly : std::uint32_t {
  LO  = 0x0     , // LO
};
enum class LOP : std::uint32_t {
  AND     = 0x0     , // AND
  OR      = 0x1     , // OR
  XOR     = 0x2     , // XOR
  PASS_B  = 0x3     , // PASS_B
};
enum class LUTOnly : std::uint32_t {
  LUT  = 0x0     , // LUT
};
enum class LaneMask4 : std::uint32_t {
  Z     = 0x1     , // Z
  W     = 0x2     , // W
  ZW    = 0x3     , // ZW
  X     = 0x4     , // X
  XZ    = 0x5     , // XZ
  XW    = 0x6     , // XW
  XZW   = 0x7     , // XZW
  Y     = 0x8     , // Y
  YZ    = 0x9     , // YZ
  YW    = 0xa     , // YW
  YZW   = 0xb     , // YZW
  XY    = 0xc     , // XY
  XYZ   = 0xd     , // XYZ
  XYW   = 0xe     , // XYW
  XYZW  = 0xf     , // XYZW
};
enum class LoadCacheOp : std::uint32_t {
  CA  = 0x0     , // CA
  CS  = 0x0     , // CS
  CG  = 0x1     , // CG
  LU  = 0x1     , // LU
  CI  = 0x2     , // CI
  CV  = 0x3     , // CV
};
enum class MN : std::uint32_t {
  MN  = 0x0     , // MN
  MX  = 0x1     , // MX
};
enum class MRG : std::uint32_t {
  noMRG  = 0x0     , // noMRG
  MRG    = 0x1     , // MRG
};
enum class MS : std::uint32_t {
  noMS  = 0x0     , // noMS
  MS    = 0x1     , // MS
};
enum class MSI : std::uint32_t {
  C            = 0x0     , // C
  CENTER       = 0x0     , // CENTER
  CENTROID     = 0x1     , // CENTROID
  OFFSET       = 0x2     , // OFFSET
  INVALID      = 0x3     , // INVALID
  INVALIDMSI3  = 0x3     , // INVALIDMSI3
};
enum class MemBarIvall : std::uint32_t {
  NOIVALL  = 0x0     , // NOIVALL
  IVALLD   = 0x1     , // IVALLD
  IVALLT   = 0x2     , // IVALLT
  IVALLTD  = 0x3     , // IVALLTD
};
enum class MemBarLevel : std::uint32_t {
  CTA  = 0x0     , // CTA
  GL   = 0x1     , // GL
  SYS  = 0x2     , // SYS
  VC   = 0x3     , // VC
};
enum class MufuOp : std::uint32_t {
  COS                 = 0x0     , // COS
  SIN                 = 0x1     , // SIN
  EX2                 = 0x2     , // EX2
  LG2                 = 0x3     , // LG2
  RCP                 = 0x4     , // RCP
  RSQ                 = 0x5     , // RSQ
  RCP64H              = 0x6     , // RCP64H
  RSQ64H              = 0x7     , // RSQ64H
  SQRT                = 0x8     , // SQRT
  INVALIDMUFUOPCODE9  = 0x9     , // INVALIDMUFUOPCODE9
  INVALIDMUFUOPCODEA  = 0xa     , // INVALIDMUFUOPCODEA
  INVALIDMUFUOPCODEB  = 0xb     , // INVALIDMUFUOPCODEB
  INVALIDMUFUOPCODEC  = 0xc     , // INVALIDMUFUOPCODEC
  INVALIDMUFUOPCODED  = 0xd     , // INVALIDMUFUOPCODED
  INVALIDMUFUOPCODEE  = 0xe     , // INVALIDMUFUOPCODEE
  INVALIDMUFUOPCODEF  = 0xf     , // INVALIDMUFUOPCODEF
};
enum class NDV : std::uint32_t {
  noNDV  = 0x0     , // noNDV
  NDV    = 0x1     , // NDV
};
enum class NODEP : std::uint32_t {
  noNODEP  = 0x0     , // noNODEP
  NODEP    = 0x1     , // NODEP
};
enum class NonZeroRegister : std::uint32_t {
  R0    = 0x0     , // R0
  R00   = 0x0     , // R00
  R01   = 0x1     , // R01
  R1    = 0x1     , // R1
  R02   = 0x2     , // R02
  R2    = 0x2     , // R2
  R03   = 0x3     , // R03
  R3    = 0x3     , // R3
  R04   = 0x4     , // R04
  R4    = 0x4     , // R4
  R05   = 0x5     , // R05
  R5    = 0x5     , // R5
  R06   = 0x6     , // R06
  R6    = 0x6     , // R6
  R07   = 0x7     , // R07
  R7    = 0x7     , // R7
  R08   = 0x8     , // R08
  R8    = 0x8     , // R8
  R09   = 0x9     , // R09
  R9    = 0x9     , // R9
  R10   = 0xa     , // R10
  R11   = 0xb     , // R11
  R12   = 0xc     , // R12
  R13   = 0xd     , // R13
  R14   = 0xe     , // R14
  R15   = 0xf     , // R15
  R16   = 0x10    , // R16
  R17   = 0x11    , // R17
  R18   = 0x12    , // R18
  R19   = 0x13    , // R19
  R20   = 0x14    , // R20
  R21   = 0x15    , // R21
  R22   = 0x16    , // R22
  R23   = 0x17    , // R23
  R24   = 0x18    , // R24
  R25   = 0x19    , // R25
  R26   = 0x1a    , // R26
  R27   = 0x1b    , // R27
  R28   = 0x1c    , // R28
  R29   = 0x1d    , // R29
  R30   = 0x1e    , // R30
  R31   = 0x1f    , // R31
  R32   = 0x20    , // R32
  R33   = 0x21    , // R33
  R34   = 0x22    , // R34
  R35   = 0x23    , // R35
  R36   = 0x24    , // R36
  R37   = 0x25    , // R37
  R38   = 0x26    , // R38
  R39   = 0x27    , // R39
  R40   = 0x28    , // R40
  R41   = 0x29    , // R41
  R42   = 0x2a    , // R42
  R43   = 0x2b    , // R43
  R44   = 0x2c    , // R44
  R45   = 0x2d    , // R45
  R46   = 0x2e    , // R46
  R47   = 0x2f    , // R47
  R48   = 0x30    , // R48
  R49   = 0x31    , // R49
  R50   = 0x32    , // R50
  R51   = 0x33    , // R51
  R52   = 0x34    , // R52
  R53   = 0x35    , // R53
  R54   = 0x36    , // R54
  R55   = 0x37    , // R55
  R56   = 0x38    , // R56
  R57   = 0x39    , // R57
  R58   = 0x3a    , // R58
  R59   = 0x3b    , // R59
  R60   = 0x3c    , // R60
  R61   = 0x3d    , // R61
  R62   = 0x3e    , // R62
  R63   = 0x3f    , // R63
  R64   = 0x40    , // R64
  R65   = 0x41    , // R65
  R66   = 0x42    , // R66
  R67   = 0x43    , // R67
  R68   = 0x44    , // R68
  R69   = 0x45    , // R69
  R70   = 0x46    , // R70
  R71   = 0x47    , // R71
  R72   = 0x48    , // R72
  R73   = 0x49    , // R73
  R74   = 0x4a    , // R74
  R75   = 0x4b    , // R75
  R76   = 0x4c    , // R76
  R77   = 0x4d    , // R77
  R78   = 0x4e    , // R78
  R79   = 0x4f    , // R79
  R80   = 0x50    , // R80
  R81   = 0x51    , // R81
  R82   = 0x52    , // R82
  R83   = 0x53    , // R83
  R84   = 0x54    , // R84
  R85   = 0x55    , // R85
  R86   = 0x56    , // R86
  R87   = 0x57    , // R87
  R88   = 0x58    , // R88
  R89   = 0x59    , // R89
  R90   = 0x5a    , // R90
  R91   = 0x5b    , // R91
  R92   = 0x5c    , // R92
  R93   = 0x5d    , // R93
  R94   = 0x5e    , // R94
  R95   = 0x5f    , // R95
  R96   = 0x60    , // R96
  R97   = 0x61    , // R97
  R98   = 0x62    , // R98
  R99   = 0x63    , // R99
  R100  = 0x64    , // R100
  R101  = 0x65    , // R101
  R102  = 0x66    , // R102
  R103  = 0x67    , // R103
  R104  = 0x68    , // R104
  R105  = 0x69    , // R105
  R106  = 0x6a    , // R106
  R107  = 0x6b    , // R107
  R108  = 0x6c    , // R108
  R109  = 0x6d    , // R109
  R110  = 0x6e    , // R110
  R111  = 0x6f    , // R111
  R112  = 0x70    , // R112
  R113  = 0x71    , // R113
  R114  = 0x72    , // R114
  R115  = 0x73    , // R115
  R116  = 0x74    , // R116
  R117  = 0x75    , // R117
  R118  = 0x76    , // R118
  R119  = 0x77    , // R119
  R120  = 0x78    , // R120
  R121  = 0x79    , // R121
  R122  = 0x7a    , // R122
  R123  = 0x7b    , // R123
  R124  = 0x7c    , // R124
  R125  = 0x7d    , // R125
  R126  = 0x7e    , // R126
  R127  = 0x7f    , // R127
  R128  = 0x80    , // R128
  R129  = 0x81    , // R129
  R130  = 0x82    , // R130
  R131  = 0x83    , // R131
  R132  = 0x84    , // R132
  R133  = 0x85    , // R133
  R134  = 0x86    , // R134
  R135  = 0x87    , // R135
  R136  = 0x88    , // R136
  R137  = 0x89    , // R137
  R138  = 0x8a    , // R138
  R139  = 0x8b    , // R139
  R140  = 0x8c    , // R140
  R141  = 0x8d    , // R141
  R142  = 0x8e    , // R142
  R143  = 0x8f    , // R143
  R144  = 0x90    , // R144
  R145  = 0x91    , // R145
  R146  = 0x92    , // R146
  R147  = 0x93    , // R147
  R148  = 0x94    , // R148
  R149  = 0x95    , // R149
  R150  = 0x96    , // R150
  R151  = 0x97    , // R151
  R152  = 0x98    , // R152
  R153  = 0x99    , // R153
  R154  = 0x9a    , // R154
  R155  = 0x9b    , // R155
  R156  = 0x9c    , // R156
  R157  = 0x9d    , // R157
  R158  = 0x9e    , // R158
  R159  = 0x9f    , // R159
  R160  = 0xa0    , // R160
  R161  = 0xa1    , // R161
  R162  = 0xa2    , // R162
  R163  = 0xa3    , // R163
  R164  = 0xa4    , // R164
  R165  = 0xa5    , // R165
  R166  = 0xa6    , // R166
  R167  = 0xa7    , // R167
  R168  = 0xa8    , // R168
  R169  = 0xa9    , // R169
  R170  = 0xaa    , // R170
  R171  = 0xab    , // R171
  R172  = 0xac    , // R172
  R173  = 0xad    , // R173
  R174  = 0xae    , // R174
  R175  = 0xaf    , // R175
  R176  = 0xb0    , // R176
  R177  = 0xb1    , // R177
  R178  = 0xb2    , // R178
  R179  = 0xb3    , // R179
  R180  = 0xb4    , // R180
  R181  = 0xb5    , // R181
  R182  = 0xb6    , // R182
  R183  = 0xb7    , // R183
  R184  = 0xb8    , // R184
  R185  = 0xb9    , // R185
  R186  = 0xba    , // R186
  R187  = 0xbb    , // R187
  R188  = 0xbc    , // R188
  R189  = 0xbd    , // R189
  R190  = 0xbe    , // R190
  R191  = 0xbf    , // R191
  R192  = 0xc0    , // R192
  R193  = 0xc1    , // R193
  R194  = 0xc2    , // R194
  R195  = 0xc3    , // R195
  R196  = 0xc4    , // R196
  R197  = 0xc5    , // R197
  R198  = 0xc6    , // R198
  R199  = 0xc7    , // R199
  R200  = 0xc8    , // R200
  R201  = 0xc9    , // R201
  R202  = 0xca    , // R202
  R203  = 0xcb    , // R203
  R204  = 0xcc    , // R204
  R205  = 0xcd    , // R205
  R206  = 0xce    , // R206
  R207  = 0xcf    , // R207
  R208  = 0xd0    , // R208
  R209  = 0xd1    , // R209
  R210  = 0xd2    , // R210
  R211  = 0xd3    , // R211
  R212  = 0xd4    , // R212
  R213  = 0xd5    , // R213
  R214  = 0xd6    , // R214
  R215  = 0xd7    , // R215
  R216  = 0xd8    , // R216
  R217  = 0xd9    , // R217
  R218  = 0xda    , // R218
  R219  = 0xdb    , // R219
  R220  = 0xdc    , // R220
  R221  = 0xdd    , // R221
  R222  = 0xde    , // R222
  R223  = 0xdf    , // R223
  R224  = 0xe0    , // R224
  R225  = 0xe1    , // R225
  R226  = 0xe2    , // R226
  R227  = 0xe3    , // R227
  R228  = 0xe4    , // R228
  R229  = 0xe5    , // R229
  R230  = 0xe6    , // R230
  R231  = 0xe7    , // R231
  R232  = 0xe8    , // R232
  R233  = 0xe9    , // R233
  R234  = 0xea    , // R234
  R235  = 0xeb    , // R235
  R236  = 0xec    , // R236
  R237  = 0xed    , // R237
  R238  = 0xee    , // R238
  R239  = 0xef    , // R239
  R240  = 0xf0    , // R240
  R241  = 0xf1    , // R241
  R242  = 0xf2    , // R242
  R243  = 0xf3    , // R243
  R244  = 0xf4    , // R244
  R245  = 0xf5    , // R245
  R246  = 0xf6    , // R246
  R247  = 0xf7    , // R247
  R248  = 0xf8    , // R248
  R249  = 0xf9    , // R249
  R250  = 0xfa    , // R250
  R251  = 0xfb    , // R251
  R252  = 0xfc    , // R252
  R253  = 0xfd    , // R253
  R254  = 0xfe    , // R254
};
enum class Ofmt_FP16 : std::uint32_t {
  F16_V2  = 0x0     , // F16_V2
  F32     = 0x1     , // F32
  MRG_H0  = 0x2     , // MRG_H0
  MRG_H1  = 0x3     , // MRG_H1
};
using OnlyIvall = CCTLLOp2;
enum class OnlyQry : std::uint32_t {
  QRY1  = 0x0     , // QRY1
};
enum class OutType : std::uint32_t {
  INVALIDOUTSTYPE0  = 0x0     , // INVALIDOUTSTYPE0
  EMIT              = 0x1     , // EMIT
  CUT               = 0x2     , // CUT
  EMIT_THEN_CUT     = 0x3     , // EMIT_THEN_CUT
};
enum class PMode : std::uint32_t {
  IDX            = 0x0     , // IDX
  F4E            = 0x1     , // F4E
  B4E            = 0x2     , // B4E
  RC8            = 0x3     , // RC8
  ECL            = 0x4     , // ECL
  ECR            = 0x5     , // ECR
  RC16           = 0x6     , // RC16
  INVALIDPMODE7  = 0x7     , // INVALIDPMODE7
};
enum class PNWord : std::uint32_t {
  PPPPPPPP  = 0x0     , // PPPPPPPP
  PPPPPPNP  = 0x1     , // PPPPPPNP
  PPPPPPPN  = 0x2     , // PPPPPPPN
  PPPPPPZP  = 0x3     , // PPPPPPZP
  PPPPNPPP  = 0x4     , // PPPPNPPP
  PPPPNPNP  = 0x5     , // PPPPNPNP
  PPPPNPPN  = 0x6     , // PPPPNPPN
  PPPPNPZP  = 0x7     , // PPPPNPZP
  PPPPPNPP  = 0x8     , // PPPPPNPP
  PPPPPNNP  = 0x9     , // PPPPPNNP
  PPPPPNPN  = 0xa     , // PPPPPNPN
  PPPPPNZP  = 0xb     , // PPPPPNZP
  PPPPZPPP  = 0xc     , // PPPPZPPP
  PPPPZPNP  = 0xd     , // PPPPZPNP
  PPPPZPPN  = 0xe     , // PPPPZPPN
  PPPPZPZP  = 0xf     , // PPPPZPZP
  PPNPPPPP  = 0x10    , // PPNPPPPP
  PPNPPPNP  = 0x11    , // PPNPPPNP
  PPNPPPPN  = 0x12    , // PPNPPPPN
  PPNPPPZP  = 0x13    , // PPNPPPZP
  PPNPNPPP  = 0x14    , // PPNPNPPP
  PPNPNPNP  = 0x15    , // PPNPNPNP
  PPNPNPPN  = 0x16    , // PPNPNPPN
  PPNPNPZP  = 0x17    , // PPNPNPZP
  PPNPPNPP  = 0x18    , // PPNPPNPP
  PPNPPNNP  = 0x19    , // PPNPPNNP
  PPNPPNPN  = 0x1a    , // PPNPPNPN
  PPNPPNZP  = 0x1b    , // PPNPPNZP
  PPNPZPPP  = 0x1c    , // PPNPZPPP
  PPNPZPNP  = 0x1d    , // PPNPZPNP
  PPNPZPPN  = 0x1e    , // PPNPZPPN
  PPNPZPZP  = 0x1f    , // PPNPZPZP
  PPPNPPPP  = 0x20    , // PPPNPPPP
  PPPNPPNP  = 0x21    , // PPPNPPNP
  PPPNPPPN  = 0x22    , // PPPNPPPN
  PPPNPPZP  = 0x23    , // PPPNPPZP
  PPPNNPPP  = 0x24    , // PPPNNPPP
  PPPNNPNP  = 0x25    , // PPPNNPNP
  PPPNNPPN  = 0x26    , // PPPNNPPN
  PPPNNPZP  = 0x27    , // PPPNNPZP
  PPPNPNPP  = 0x28    , // PPPNPNPP
  PPPNPNNP  = 0x29    , // PPPNPNNP
  PPPNPNPN  = 0x2a    , // PPPNPNPN
  PPPNPNZP  = 0x2b    , // PPPNPNZP
  PPPNZPPP  = 0x2c    , // PPPNZPPP
  PPPNZPNP  = 0x2d    , // PPPNZPNP
  PPPNZPPN  = 0x2e    , // PPPNZPPN
  PPPNZPZP  = 0x2f    , // PPPNZPZP
  PPZPPPPP  = 0x30    , // PPZPPPPP
  PPZPPPNP  = 0x31    , // PPZPPPNP
  PPZPPPPN  = 0x32    , // PPZPPPPN
  PPZPPPZP  = 0x33    , // PPZPPPZP
  PPZPNPPP  = 0x34    , // PPZPNPPP
  PPZPNPNP  = 0x35    , // PPZPNPNP
  PPZPNPPN  = 0x36    , // PPZPNPPN
  PPZPNPZP  = 0x37    , // PPZPNPZP
  PPZPPNPP  = 0x38    , // PPZPPNPP
  PPZPPNNP  = 0x39    , // PPZPPNNP
  PPZPPNPN  = 0x3a    , // PPZPPNPN
  PPZPPNZP  = 0x3b    , // PPZPPNZP
  PPZPZPPP  = 0x3c    , // PPZPZPPP
  PPZPZPNP  = 0x3d    , // PPZPZPNP
  PPZPZPPN  = 0x3e    , // PPZPZPPN
  PPZPZPZP  = 0x3f    , // PPZPZPZP
  NPPPPPPP  = 0x40    , // NPPPPPPP
  NPPPPPNP  = 0x41    , // NPPPPPNP
  NPPPPPPN  = 0x42    , // NPPPPPPN
  NPPPPPZP  = 0x43    , // NPPPPPZP
  NPPPNPPP  = 0x44    , // NPPPNPPP
  NPPPNPNP  = 0x45    , // NPPPNPNP
  NPPPNPPN  = 0x46    , // NPPPNPPN
  NPPPNPZP  = 0x47    , // NPPPNPZP
  NPPPPNPP  = 0x48    , // NPPPPNPP
  NPPPPNNP  = 0x49    , // NPPPPNNP
  NPPPPNPN  = 0x4a    , // NPPPPNPN
  NPPPPNZP  = 0x4b    , // NPPPPNZP
  NPPPZPPP  = 0x4c    , // NPPPZPPP
  NPPPZPNP  = 0x4d    , // NPPPZPNP
  NPPPZPPN  = 0x4e    , // NPPPZPPN
  NPPPZPZP  = 0x4f    , // NPPPZPZP
  NPNPPPPP  = 0x50    , // NPNPPPPP
  NPNPPPNP  = 0x51    , // NPNPPPNP
  NPNPPPPN  = 0x52    , // NPNPPPPN
  NPNPPPZP  = 0x53    , // NPNPPPZP
  NPNPNPPP  = 0x54    , // NPNPNPPP
  NPNPNPNP  = 0x55    , // NPNPNPNP
  NPNPNPPN  = 0x56    , // NPNPNPPN
  NPNPNPZP  = 0x57    , // NPNPNPZP
  NPNPPNPP  = 0x58    , // NPNPPNPP
  NPNPPNNP  = 0x59    , // NPNPPNNP
  NPNPPNPN  = 0x5a    , // NPNPPNPN
  NPNPPNZP  = 0x5b    , // NPNPPNZP
  NPNPZPPP  = 0x5c    , // NPNPZPPP
  NPNPZPNP  = 0x5d    , // NPNPZPNP
  NPNPZPPN  = 0x5e    , // NPNPZPPN
  NPNPZPZP  = 0x5f    , // NPNPZPZP
  NPPNPPPP  = 0x60    , // NPPNPPPP
  NPPNPPNP  = 0x61    , // NPPNPPNP
  NPPNPPPN  = 0x62    , // NPPNPPPN
  NPPNPPZP  = 0x63    , // NPPNPPZP
  NPPNNPPP  = 0x64    , // NPPNNPPP
  NPPNNPNP  = 0x65    , // NPPNNPNP
  NPPNNPPN  = 0x66    , // NPPNNPPN
  NPPNNPZP  = 0x67    , // NPPNNPZP
  NPPNPNPP  = 0x68    , // NPPNPNPP
  NPPNPNNP  = 0x69    , // NPPNPNNP
  NPPNPNPN  = 0x6a    , // NPPNPNPN
  NPPNPNZP  = 0x6b    , // NPPNPNZP
  NPPNZPPP  = 0x6c    , // NPPNZPPP
  NPPNZPNP  = 0x6d    , // NPPNZPNP
  NPPNZPPN  = 0x6e    , // NPPNZPPN
  NPPNZPZP  = 0x6f    , // NPPNZPZP
  NPZPPPPP  = 0x70    , // NPZPPPPP
  NPZPPPNP  = 0x71    , // NPZPPPNP
  NPZPPPPN  = 0x72    , // NPZPPPPN
  NPZPPPZP  = 0x73    , // NPZPPPZP
  NPZPNPPP  = 0x74    , // NPZPNPPP
  NPZPNPNP  = 0x75    , // NPZPNPNP
  NPZPNPPN  = 0x76    , // NPZPNPPN
  NPZPNPZP  = 0x77    , // NPZPNPZP
  NPZPPNPP  = 0x78    , // NPZPPNPP
  NPZPPNNP  = 0x79    , // NPZPPNNP
  NPZPPNPN  = 0x7a    , // NPZPPNPN
  NPZPPNZP  = 0x7b    , // NPZPPNZP
  NPZPZPPP  = 0x7c    , // NPZPZPPP
  NPZPZPNP  = 0x7d    , // NPZPZPNP
  NPZPZPPN  = 0x7e    , // NPZPZPPN
  NPZPZPZP  = 0x7f    , // NPZPZPZP
  PNPPPPPP  = 0x80    , // PNPPPPPP
  PNPPPPNP  = 0x81    , // PNPPPPNP
  PNPPPPPN  = 0x82    , // PNPPPPPN
  PNPPPPZP  = 0x83    , // PNPPPPZP
  PNPPNPPP  = 0x84    , // PNPPNPPP
  PNPPNPNP  = 0x85    , // PNPPNPNP
  PNPPNPPN  = 0x86    , // PNPPNPPN
  PNPPNPZP  = 0x87    , // PNPPNPZP
  PNPPPNPP  = 0x88    , // PNPPPNPP
  PNPPPNNP  = 0x89    , // PNPPPNNP
  PNPPPNPN  = 0x8a    , // PNPPPNPN
  PNPPPNZP  = 0x8b    , // PNPPPNZP
  PNPPZPPP  = 0x8c    , // PNPPZPPP
  PNPPZPNP  = 0x8d    , // PNPPZPNP
  PNPPZPPN  = 0x8e    , // PNPPZPPN
  PNPPZPZP  = 0x8f    , // PNPPZPZP
  PNNPPPPP  = 0x90    , // PNNPPPPP
  PNNPPPNP  = 0x91    , // PNNPPPNP
  PNNPPPPN  = 0x92    , // PNNPPPPN
  PNNPPPZP  = 0x93    , // PNNPPPZP
  PNNPNPPP  = 0x94    , // PNNPNPPP
  PNNPNPNP  = 0x95    , // PNNPNPNP
  PNNPNPPN  = 0x96    , // PNNPNPPN
  PNNPNPZP  = 0x97    , // PNNPNPZP
  PNNPPNPP  = 0x98    , // PNNPPNPP
  PNNPPNNP  = 0x99    , // PNNPPNNP
  PNNPPNPN  = 0x9a    , // PNNPPNPN
  PNNPPNZP  = 0x9b    , // PNNPPNZP
  PNNPZPPP  = 0x9c    , // PNNPZPPP
  PNNPZPNP  = 0x9d    , // PNNPZPNP
  PNNPZPPN  = 0x9e    , // PNNPZPPN
  PNNPZPZP  = 0x9f    , // PNNPZPZP
  PNPNPPPP  = 0xa0    , // PNPNPPPP
  PNPNPPNP  = 0xa1    , // PNPNPPNP
  PNPNPPPN  = 0xa2    , // PNPNPPPN
  PNPNPPZP  = 0xa3    , // PNPNPPZP
  PNPNNPPP  = 0xa4    , // PNPNNPPP
  PNPNNPNP  = 0xa5    , // PNPNNPNP
  PNPNNPPN  = 0xa6    , // PNPNNPPN
  PNPNNPZP  = 0xa7    , // PNPNNPZP
  PNPNPNPP  = 0xa8    , // PNPNPNPP
  PNPNPNNP  = 0xa9    , // PNPNPNNP
  PNPNPNPN  = 0xaa    , // PNPNPNPN
  PNPNPNZP  = 0xab    , // PNPNPNZP
  PNPNZPPP  = 0xac    , // PNPNZPPP
  PNPNZPNP  = 0xad    , // PNPNZPNP
  PNPNZPPN  = 0xae    , // PNPNZPPN
  PNPNZPZP  = 0xaf    , // PNPNZPZP
  PNZPPPPP  = 0xb0    , // PNZPPPPP
  PNZPPPNP  = 0xb1    , // PNZPPPNP
  PNZPPPPN  = 0xb2    , // PNZPPPPN
  PNZPPPZP  = 0xb3    , // PNZPPPZP
  PNZPNPPP  = 0xb4    , // PNZPNPPP
  PNZPNPNP  = 0xb5    , // PNZPNPNP
  PNZPNPPN  = 0xb6    , // PNZPNPPN
  PNZPNPZP  = 0xb7    , // PNZPNPZP
  PNZPPNPP  = 0xb8    , // PNZPPNPP
  PNZPPNNP  = 0xb9    , // PNZPPNNP
  PNZPPNPN  = 0xba    , // PNZPPNPN
  PNZPPNZP  = 0xbb    , // PNZPPNZP
  PNZPZPPP  = 0xbc    , // PNZPZPPP
  PNZPZPNP  = 0xbd    , // PNZPZPNP
  PNZPZPPN  = 0xbe    , // PNZPZPPN
  PNZPZPZP  = 0xbf    , // PNZPZPZP
  ZPPPPPPP  = 0xc0    , // ZPPPPPPP
  ZPPPPPNP  = 0xc1    , // ZPPPPPNP
  ZPPPPPPN  = 0xc2    , // ZPPPPPPN
  ZPPPPPZP  = 0xc3    , // ZPPPPPZP
  ZPPPNPPP  = 0xc4    , // ZPPPNPPP
  ZPPPNPNP  = 0xc5    , // ZPPPNPNP
  ZPPPNPPN  = 0xc6    , // ZPPPNPPN
  ZPPPNPZP  = 0xc7    , // ZPPPNPZP
  ZPPPPNPP  = 0xc8    , // ZPPPPNPP
  ZPPPPNNP  = 0xc9    , // ZPPPPNNP
  ZPPPPNPN  = 0xca    , // ZPPPPNPN
  ZPPPPNZP  = 0xcb    , // ZPPPPNZP
  ZPPPZPPP  = 0xcc    , // ZPPPZPPP
  ZPPPZPNP  = 0xcd    , // ZPPPZPNP
  ZPPPZPPN  = 0xce    , // ZPPPZPPN
  ZPPPZPZP  = 0xcf    , // ZPPPZPZP
  ZPNPPPPP  = 0xd0    , // ZPNPPPPP
  ZPNPPPNP  = 0xd1    , // ZPNPPPNP
  ZPNPPPPN  = 0xd2    , // ZPNPPPPN
  ZPNPPPZP  = 0xd3    , // ZPNPPPZP
  ZPNPNPPP  = 0xd4    , // ZPNPNPPP
  ZPNPNPNP  = 0xd5    , // ZPNPNPNP
  ZPNPNPPN  = 0xd6    , // ZPNPNPPN
  ZPNPNPZP  = 0xd7    , // ZPNPNPZP
  ZPNPPNPP  = 0xd8    , // ZPNPPNPP
  ZPNPPNNP  = 0xd9    , // ZPNPPNNP
  ZPNPPNPN  = 0xda    , // ZPNPPNPN
  ZPNPPNZP  = 0xdb    , // ZPNPPNZP
  ZPNPZPPP  = 0xdc    , // ZPNPZPPP
  ZPNPZPNP  = 0xdd    , // ZPNPZPNP
  ZPNPZPPN  = 0xde    , // ZPNPZPPN
  ZPNPZPZP  = 0xdf    , // ZPNPZPZP
  ZPPNPPPP  = 0xe0    , // ZPPNPPPP
  ZPPNPPNP  = 0xe1    , // ZPPNPPNP
  ZPPNPPPN  = 0xe2    , // ZPPNPPPN
  ZPPNPPZP  = 0xe3    , // ZPPNPPZP
  ZPPNNPPP  = 0xe4    , // ZPPNNPPP
  ZPPNNPNP  = 0xe5    , // ZPPNNPNP
  ZPPNNPPN  = 0xe6    , // ZPPNNPPN
  ZPPNNPZP  = 0xe7    , // ZPPNNPZP
  ZPPNPNPP  = 0xe8    , // ZPPNPNPP
  ZPPNPNNP  = 0xe9    , // ZPPNPNNP
  ZPPNPNPN  = 0xea    , // ZPPNPNPN
  ZPPNPNZP  = 0xeb    , // ZPPNPNZP
  ZPPNZPPP  = 0xec    , // ZPPNZPPP
  ZPPNZPNP  = 0xed    , // ZPPNZPNP
  ZPPNZPPN  = 0xee    , // ZPPNZPPN
  ZPPNZPZP  = 0xef    , // ZPPNZPZP
  ZPZPPPPP  = 0xf0    , // ZPZPPPPP
  ZPZPPPNP  = 0xf1    , // ZPZPPPNP
  ZPZPPPPN  = 0xf2    , // ZPZPPPPN
  ZPZPPPZP  = 0xf3    , // ZPZPPPZP
  ZPZPNPPP  = 0xf4    , // ZPZPNPPP
  ZPZPNPNP  = 0xf5    , // ZPZPNPNP
  ZPZPNPPN  = 0xf6    , // ZPZPNPPN
  ZPZPNPZP  = 0xf7    , // ZPZPNPZP
  ZPZPPNPP  = 0xf8    , // ZPZPPNPP
  ZPZPPNNP  = 0xf9    , // ZPZPPNNP
  ZPZPPNPN  = 0xfa    , // ZPZPPNPN
  ZPZPPNZP  = 0xfb    , // ZPZPPNZP
  ZPZPZPPP  = 0xfc    , // ZPZPZPPP
  ZPZPZPNP  = 0xfd    , // ZPZPZPNP
  ZPZPZPPN  = 0xfe    , // ZPZPZPPN
  ZPZPZPZP  = 0xff    , // ZPZPZPZP
};
enum class PO : std::uint32_t {
  noPO  = 0x0     , // noPO
  PO    = 0x1     , // PO
};
enum class POP : std::uint32_t {
  F   = 0x0     , // F
  T   = 0x1     , // T
  Z   = 0x2     , // Z
  NZ  = 0x3     , // NZ
};
enum class POnly : std::uint32_t {
  P  = 0x0     , // P
};
enum class PSL : std::uint32_t {
  noPSL  = 0x0     , // noPSL
  PSL    = 0x1     , // PSL
};
enum class ParamA : std::uint32_t {
  _1D         = 0x0     , // _1D
  ARRAY_1D    = 0x1     , // ARRAY_1D
  RECT        = 0x2     , // RECT
  _2D         = 0x2     , // _2D
  ARRAY_2D    = 0x3     , // ARRAY_2D
  ARRAY_RECT  = 0x3     , // ARRAY_RECT
  _3D         = 0x4     , // _3D
  ARRAY_3D    = 0x5     , // ARRAY_3D
  CUBE        = 0x6     , // CUBE
  ARRAY_CUBE  = 0x7     , // ARRAY_CUBE
  CUBEARRAY   = 0x7     , // CUBEARRAY
};
enum class Partsel : std::uint32_t {
  _32 = 0x0     , // 32
  H0  = 0x1     , // H0
  H1  = 0x2     , // H1
};
enum class Phys : std::uint32_t {
  PHYS  = 0x0     , // PHYS
};
enum class PixMode : std::uint32_t {
  MSCOUNT          = 0x0     , // MSCOUNT
  COVMASK          = 0x1     , // COVMASK
  COVERED          = 0x2     , // COVERED
  OFFSET           = 0x3     , // OFFSET
  CENTROID_OFFSET  = 0x4     , // CENTROID_OFFSET
  MY_INDEX         = 0x5     , // MY_INDEX
  INVALID0         = 0x6     , // INVALID0
  INVALIDPIXMODE6  = 0x6     , // INVALIDPIXMODE6
  INVALID1         = 0x7     , // INVALID1
  INVALIDPIXMODE7  = 0x7     , // INVALIDPIXMODE7
};
enum class Predicate : std::uint32_t {
  P0  = 0x0     , // P0
  P1  = 0x1     , // P1
  P2  = 0x2     , // P2
  P3  = 0x3     , // P3
  P4  = 0x4     , // P4
  P5  = 0x5     , // P5
  P6  = 0x6     , // P6
  P7  = 0x7     , // P7
  PT  = 0x7     , // PT
};
enum class RD : std::uint32_t {
  rd  = 0x0     , // rd
};
enum class REQ : std::uint32_t {
  req  = 0x0     , // req
};
enum class REUSE : std::uint32_t {
  noreuse  = 0x0     , // noreuse
  reuse    = 0x1     , // reuse
};
enum class RGBA : std::uint32_t {
  INVALIDRGBAMASK1   = 0x1     , // INVALIDRGBAMASK1
  R                  = 0x1     , // R
  G                  = 0x2     , // G
  INVALIDRGBAMASK2   = 0x2     , // INVALIDRGBAMASK2
  INVALIDRGBAMASK3   = 0x3     , // INVALIDRGBAMASK3
  RG                 = 0x3     , // RG
  B                  = 0x4     , // B
  INVALIDRGBAMASK4   = 0x4     , // INVALIDRGBAMASK4
  INVALIDRGBAMASK5   = 0x5     , // INVALIDRGBAMASK5
  RB                 = 0x5     , // RB
  GB                 = 0x6     , // GB
  INVALIDRGBAMASK6   = 0x6     , // INVALIDRGBAMASK6
  INVALIDRGBAMASK7   = 0x7     , // INVALIDRGBAMASK7
  RGB                = 0x7     , // RGB
  A                  = 0x8     , // A
  INVALIDRGBAMASK8   = 0x8     , // INVALIDRGBAMASK8
  INVALIDRGBAMASK9   = 0x9     , // INVALIDRGBAMASK9
  RA                 = 0x9     , // RA
  GA                 = 0xa     , // GA
  INVALIDRGBAMASK10  = 0xa     , // INVALIDRGBAMASK10
  INVALIDRGBAMASK11  = 0xb     , // INVALIDRGBAMASK11
  RGA                = 0xb     , // RGA
  BA                 = 0xc     , // BA
  INVALIDRGBAMASK12  = 0xc     , // INVALIDRGBAMASK12
  INVALIDRGBAMASK13  = 0xd     , // INVALIDRGBAMASK13
  RBA                = 0xd     , // RBA
  GBA                = 0xe     , // GBA
  INVALIDRGBAMASK14  = 0xe     , // INVALIDRGBAMASK14
  INVALIDRGBAMASK15  = 0xf     , // INVALIDRGBAMASK15
  RGBA               = 0xf     , // RGBA
};
enum class RROOp : std::uint32_t {
  SINCOS  = 0x0     , // SINCOS
  EX2     = 0x1     , // EX2
};
enum class RTTOp : std::uint32_t {
  POPCRS       = 0x0     , // POPCRS
  TERMINATE    = 0x1     , // TERMINATE
  FALLTHROUGH  = 0x2     , // FALLTHROUGH
  PREEMPTED    = 0x3     , // PREEMPTED
};
enum class Red : std::uint32_t {
  POPC             = 0x0     , // POPC
  AND              = 0x1     , // AND
  OR               = 0x2     , // OR
  INVALIDBARMODE3  = 0x3     , // INVALIDBARMODE3
};
enum class RedOp : std::uint32_t {
  ADD             = 0x0     , // ADD
  INVALIDREDOP0   = 0x0     , // INVALIDREDOP0
  INVALIDREDOP1   = 0x1     , // INVALIDREDOP1
  MIN             = 0x1     , // MIN
  INVALIDREDOP2   = 0x2     , // INVALIDREDOP2
  MAX             = 0x2     , // MAX
  INC             = 0x3     , // INC
  INVALIDREDOP3   = 0x3     , // INVALIDREDOP3
  DEC             = 0x4     , // DEC
  INVALIDREDOP4   = 0x4     , // INVALIDREDOP4
  AND             = 0x5     , // AND
  INVALIDREDOP5   = 0x5     , // INVALIDREDOP5
  INVALIDREDOP6   = 0x6     , // INVALIDREDOP6
  OR              = 0x6     , // OR
  INVALIDREDOP7   = 0x7     , // INVALIDREDOP7
  XOR             = 0x7     , // XOR
  INVALIDREDOP8   = 0x8     , // INVALIDREDOP8
  INVALIDREDOP9   = 0x9     , // INVALIDREDOP9
  INVALIDREDOP10  = 0xa     , // INVALIDREDOP10
  INVALIDREDOP11  = 0xb     , // INVALIDREDOP11
  INVALIDREDOP12  = 0xc     , // INVALIDREDOP12
  INVALIDREDOP13  = 0xd     , // INVALIDREDOP13
  INVALIDREDOP14  = 0xe     , // INVALIDREDOP14
  INVALIDREDOP15  = 0xf     , // INVALIDREDOP15
};
enum class Round1 : std::uint32_t {
  RN  = 0x0     , // RN
  RM  = 0x1     , // RM
  RP  = 0x2     , // RP
  RZ  = 0x3     , // RZ
};
enum class Round3 : std::uint32_t {
  ROUND  = 0x0     , // ROUND
  FLOOR  = 0x1     , // FLOOR
  CEIL   = 0x2     , // CEIL
  TRUNC  = 0x3     , // TRUNC
};
enum class S16 : std::uint32_t {
  S16  = 0x3     , // S16
};
enum class SAT : std::uint32_t {
  noSAT  = 0x0     , // noSAT
  SAT    = 0x1     , // SAT
};
enum class SH : std::uint32_t {
  noSH  = 0x0     , // noSH
  SH    = 0x1     , // SH
};
enum class SHFXMode : std::uint32_t {
  NONE  = 0x0     , // NONE
  HI    = 0x1     , // HI
  X     = 0x2     , // X
  XHI   = 0x3     , // XHI
};
enum class SHF_L : std::uint32_t {
  L  = 0x0     , // L
};
enum class SHF_R : std::uint32_t {
  R  = 0x0     , // R
};
using SInteger16 = S16;
enum class SInteger32 : std::uint32_t {
  S32  = 0x5     , // S32
};
enum class SInteger64 : std::uint32_t {
  S64  = 0x7     , // S64
};
enum class SInteger8 : std::uint32_t {
  S8  = 0x1     , // S8
};
enum class SKEW : std::uint32_t {
  noSKEW  = 0x0     , // noSKEW
  SKEW    = 0x1     , // SKEW
};
enum class SQInteger : std::uint32_t {
  _32                  = 0x0     , // 32
  U32                  = 0x0     , // U32
  S32                  = 0x1     , // S32
  _64                  = 0x2     , // 64
  U64                  = 0x2     , // U64
  F32                  = 0x3     , // F32
  F32_FTZ_RN           = 0x3     , // F32.FTZ.RN
  F16x2_FTZ_RN         = 0x4     , // F16x2.FTZ.RN
  S64                  = 0x5     , // S64
  INVALIDATOMICSIZE6   = 0x6     , // INVALIDATOMICSIZE6
  F16                  = 0x7     , // F16
  F64                  = 0x7     , // F64
  INVALIDATOMICSIZE13  = 0x7     , // INVALIDATOMICSIZE13
  INVALIDATOMICSIZE14  = 0x7     , // INVALIDATOMICSIZE14
  INVALIDATOMICSIZE15  = 0x7     , // INVALIDATOMICSIZE15
  INVALIDATOMICSIZE7   = 0x7     , // INVALIDATOMICSIZE7
  S128                 = 0x7     , // S128
  S16                  = 0x7     , // S16
  S8                   = 0x7     , // S8
  U16                  = 0x7     , // U16
  U8                   = 0x7     , // U8
};
enum class STPMode : std::uint32_t {
  noWAIT  = 0x0     , // noWAIT
  WAIT    = 0x1     , // WAIT
};
enum class Scale : std::uint32_t {
  NONE            = 0x0     , // NONE
  D2              = 0x1     , // D2
  D4              = 0x2     , // D4
  D8              = 0x3     , // D8
  M8              = 0x4     , // M8
  M4              = 0x5     , // M4
  M2              = 0x6     , // M2
  INVALIDSCALE37  = 0x7     , // INVALIDSCALE37
};
enum class Scoreboard : std::uint32_t {
  SB0  = 0x0     , // SB0
  SB1  = 0x1     , // SB1
  SB2  = 0x2     , // SB2
  SB3  = 0x3     , // SB3
  SB4  = 0x4     , // SB4
  SB5  = 0x5     , // SB5
};
enum class Shflmd : std::uint32_t {
  IDX   = 0x0     , // IDX
  UP    = 0x1     , // UP
  DOWN  = 0x2     , // DOWN
  BFLY  = 0x3     , // BFLY
};
enum class SpecialRegister : std::uint32_t {
  SR0                               = 0x0     , // SR0
  SR_LANEID                         = 0x0     , // SR_LANEID
  SR1                               = 0x1     , // SR1
  SR_CLOCK                          = 0x1     , // SR_CLOCK
  SR2                               = 0x2     , // SR2
  SR_VIRTCFG                        = 0x2     , // SR_VIRTCFG
  SR3                               = 0x3     , // SR3
  SR_VIRTID                         = 0x3     , // SR_VIRTID
  SR4                               = 0x4     , // SR4
  SR_PM0                            = 0x4     , // SR_PM0
  SR5                               = 0x5     , // SR5
  SR_PM1                            = 0x5     , // SR_PM1
  SR6                               = 0x6     , // SR6
  SR_PM2                            = 0x6     , // SR_PM2
  SR7                               = 0x7     , // SR7
  SR_PM3                            = 0x7     , // SR_PM3
  SR8                               = 0x8     , // SR8
  SR_PM4                            = 0x8     , // SR_PM4
  SR9                               = 0x9     , // SR9
  SR_PM5                            = 0x9     , // SR_PM5
  SR10                              = 0xa     , // SR10
  SR_PM6                            = 0xa     , // SR_PM6
  SR11                              = 0xb     , // SR11
  SR_PM7                            = 0xb     , // SR_PM7
  SR12                              = 0xc     , // SR12
  SR13                              = 0xd     , // SR13
  SR14                              = 0xe     , // SR14
  SR15                              = 0xf     , // SR15
  SR_ORDERING_TICKET                = 0xf     , // SR_ORDERING_TICKET
  SR16                              = 0x10    , // SR16
  SR_PRIM_TYPE                      = 0x10    , // SR_PRIM_TYPE
  SR17                              = 0x11    , // SR17
  SR_INVOCATION_ID                  = 0x11    , // SR_INVOCATION_ID
  SR18                              = 0x12    , // SR18
  SR_Y_DIRECTION                    = 0x12    , // SR_Y_DIRECTION
  SR19                              = 0x13    , // SR19
  SR_THREAD_KILL                    = 0x13    , // SR_THREAD_KILL
  SM_SHADER_TYPE                    = 0x14    , // SM_SHADER_TYPE
  SR20                              = 0x14    , // SR20
  SR21                              = 0x15    , // SR21
  SR_DIRECTCBEWRITEADDRESSLOW       = 0x15    , // SR_DIRECTCBEWRITEADDRESSLOW
  SR22                              = 0x16    , // SR22
  SR_DIRECTCBEWRITEADDRESSHIGH      = 0x16    , // SR_DIRECTCBEWRITEADDRESSHIGH
  SR23                              = 0x17    , // SR23
  SR_DIRECTCBEWRITEENABLED          = 0x17    , // SR_DIRECTCBEWRITEENABLED
  SR24                              = 0x18    , // SR24
  SR_MACHINE_ID_0                   = 0x18    , // SR_MACHINE_ID_0
  SR25                              = 0x19    , // SR25
  SR_MACHINE_ID_1                   = 0x19    , // SR_MACHINE_ID_1
  SR26                              = 0x1a    , // SR26
  SR_MACHINE_ID_2                   = 0x1a    , // SR_MACHINE_ID_2
  SR27                              = 0x1b    , // SR27
  SR_MACHINE_ID_3                   = 0x1b    , // SR_MACHINE_ID_3
  SR28                              = 0x1c    , // SR28
  SR_AFFINITY                       = 0x1c    , // SR_AFFINITY
  SR29                              = 0x1d    , // SR29
  SR_INVOCATION_INFO                = 0x1d    , // SR_INVOCATION_INFO
  SR30                              = 0x1e    , // SR30
  SR_WSCALEFACTOR_XY                = 0x1e    , // SR_WSCALEFACTOR_XY
  SR31                              = 0x1f    , // SR31
  SR_WSCALEFACTOR_Z                 = 0x1f    , // SR_WSCALEFACTOR_Z
  SR32                              = 0x20    , // SR32
  SR_TID                            = 0x20    , // SR_TID
  SR33                              = 0x21    , // SR33
  SR_TID_X                          = 0x21    , // SR_TID.X
  SR34                              = 0x22    , // SR34
  SR_TID_Y                          = 0x22    , // SR_TID.Y
  SR35                              = 0x23    , // SR35
  SR_TID_Z                          = 0x23    , // SR_TID.Z
  SR36                              = 0x24    , // SR36
  SR_CTAPARAM                       = 0x24    , // SR_CTAPARAM
  SR_CTA_PARAM                      = 0x24    , // SR_CTA_PARAM
  SR37                              = 0x25    , // SR37
  SR_CTAID_X                        = 0x25    , // SR_CTAID.X
  SR38                              = 0x26    , // SR38
  SR_CTAID_Y                        = 0x26    , // SR_CTAID.Y
  SR39                              = 0x27    , // SR39
  SR_CTAID_Z                        = 0x27    , // SR_CTAID.Z
  SR40                              = 0x28    , // SR40
  SR_NTID                           = 0x28    , // SR_NTID
  SR41                              = 0x29    , // SR41
  SR_CirQueueIncrMinusOne           = 0x29    , // SR_CirQueueIncrMinusOne
  SR42                              = 0x2a    , // SR42
  SR_NLATC                          = 0x2a    , // SR_NLATC
  SR43                              = 0x2b    , // SR43
  SR44                              = 0x2c    , // SR44
  SR45                              = 0x2d    , // SR45
  SR46                              = 0x2e    , // SR46
  SR47                              = 0x2f    , // SR47
  SR48                              = 0x30    , // SR48
  SR_SWINLO                         = 0x30    , // SR_SWINLO
  SR49                              = 0x31    , // SR49
  SR_SWINSZ                         = 0x31    , // SR_SWINSZ
  SR50                              = 0x32    , // SR50
  SR_SMEMSZ                         = 0x32    , // SR_SMEMSZ
  SR51                              = 0x33    , // SR51
  SR_SMEMBANKS                      = 0x33    , // SR_SMEMBANKS
  SR52                              = 0x34    , // SR52
  SR_LWINLO                         = 0x34    , // SR_LWINLO
  SR53                              = 0x35    , // SR53
  SR_LWINSZ                         = 0x35    , // SR_LWINSZ
  SR54                              = 0x36    , // SR54
  SR_LMEMLOSZ                       = 0x36    , // SR_LMEMLOSZ
  SR55                              = 0x37    , // SR55
  SR_LMEMHIOFF                      = 0x37    , // SR_LMEMHIOFF
  SR56                              = 0x38    , // SR56
  SR_EQMASK                         = 0x38    , // SR_EQMASK
  SR57                              = 0x39    , // SR57
  SR_LTMASK                         = 0x39    , // SR_LTMASK
  SR58                              = 0x3a    , // SR58
  SR_LEMASK                         = 0x3a    , // SR_LEMASK
  SR59                              = 0x3b    , // SR59
  SR_GTMASK                         = 0x3b    , // SR_GTMASK
  SR60                              = 0x3c    , // SR60
  SR_GEMASK                         = 0x3c    , // SR_GEMASK
  SR61                              = 0x3d    , // SR61
  SR_REGALLOC                       = 0x3d    , // SR_REGALLOC
  SR62                              = 0x3e    , // SR62
  SR_CTXADDR                        = 0x3e    , // SR_CTXADDR
  SR63                              = 0x3f    , // SR63
  SR64                              = 0x40    , // SR64
  SR_GLOBALERRORSTATUS              = 0x40    , // SR_GLOBALERRORSTATUS
  SR65                              = 0x41    , // SR65
  SR66                              = 0x42    , // SR66
  SR_WARPERRORSTATUS                = 0x42    , // SR_WARPERRORSTATUS
  SR67                              = 0x43    , // SR67
  SR_WARPERRORSTATUSCLEAR           = 0x43    , // SR_WARPERRORSTATUSCLEAR
  SR68                              = 0x44    , // SR68
  SR69                              = 0x45    , // SR69
  SR70                              = 0x46    , // SR70
  SR71                              = 0x47    , // SR71
  SR72                              = 0x48    , // SR72
  SR_PM_HI0                         = 0x48    , // SR_PM_HI0
  SR73                              = 0x49    , // SR73
  SR_PM_HI1                         = 0x49    , // SR_PM_HI1
  SR74                              = 0x4a    , // SR74
  SR_PM_HI2                         = 0x4a    , // SR_PM_HI2
  SR75                              = 0x4b    , // SR75
  SR_PM_HI3                         = 0x4b    , // SR_PM_HI3
  SR76                              = 0x4c    , // SR76
  SR_PM_HI4                         = 0x4c    , // SR_PM_HI4
  SR77                              = 0x4d    , // SR77
  SR_PM_HI5                         = 0x4d    , // SR_PM_HI5
  SR78                              = 0x4e    , // SR78
  SR_PM_HI6                         = 0x4e    , // SR_PM_HI6
  SR79                              = 0x4f    , // SR79
  SR_PM_HI7                         = 0x4f    , // SR_PM_HI7
  SR80                              = 0x50    , // SR80
  SR_CLOCKLO                        = 0x50    , // SR_CLOCKLO
  SR81                              = 0x51    , // SR81
  SR_CLOCKHI                        = 0x51    , // SR_CLOCKHI
  SR82                              = 0x52    , // SR82
  SR_GLOBALTIMERLO                  = 0x52    , // SR_GLOBALTIMERLO
  SR83                              = 0x53    , // SR83
  SR_GLOBALTIMERHI                  = 0x53    , // SR_GLOBALTIMERHI
  SR84                              = 0x54    , // SR84
  SR85                              = 0x55    , // SR85
  SR86                              = 0x56    , // SR86
  SR87                              = 0x57    , // SR87
  SR88                              = 0x58    , // SR88
  SR89                              = 0x59    , // SR89
  SR90                              = 0x5a    , // SR90
  SR91                              = 0x5b    , // SR91
  SR92                              = 0x5c    , // SR92
  SR93                              = 0x5d    , // SR93
  SR94                              = 0x5e    , // SR94
  SR95                              = 0x5f    , // SR95
  SR96                              = 0x60    , // SR96
  SR_HWTASKID                       = 0x60    , // SR_HWTASKID
  SR97                              = 0x61    , // SR97
  SR_CIRCULARQUEUEENTRYINDEX        = 0x61    , // SR_CIRCULARQUEUEENTRYINDEX
  SR98                              = 0x62    , // SR98
  SR_CIRCULARQUEUEENTRYADDRESSLOW   = 0x62    , // SR_CIRCULARQUEUEENTRYADDRESSLOW
  SR99                              = 0x63    , // SR99
  SR_CIRCULARQUEUEENTRYADDRESSHIGH  = 0x63    , // SR_CIRCULARQUEUEENTRYADDRESSHIGH
  SR100                             = 0x64    , // SR100
  SR101                             = 0x65    , // SR101
  SR102                             = 0x66    , // SR102
  SR103                             = 0x67    , // SR103
  SR104                             = 0x68    , // SR104
  SR105                             = 0x69    , // SR105
  SR106                             = 0x6a    , // SR106
  SR107                             = 0x6b    , // SR107
  SR108                             = 0x6c    , // SR108
  SR109                             = 0x6d    , // SR109
  SR110                             = 0x6e    , // SR110
  SR111                             = 0x6f    , // SR111
  SR112                             = 0x70    , // SR112
  SR113                             = 0x71    , // SR113
  SR114                             = 0x72    , // SR114
  SR115                             = 0x73    , // SR115
  SR116                             = 0x74    , // SR116
  SR117                             = 0x75    , // SR117
  SR118                             = 0x76    , // SR118
  SR119                             = 0x77    , // SR119
  SR120                             = 0x78    , // SR120
  SR121                             = 0x79    , // SR121
  SR122                             = 0x7a    , // SR122
  SR123                             = 0x7b    , // SR123
  SR124                             = 0x7c    , // SR124
  SR125                             = 0x7d    , // SR125
  SR126                             = 0x7e    , // SR126
  SR127                             = 0x7f    , // SR127
  SR128                             = 0x80    , // SR128
  SR129                             = 0x81    , // SR129
  SR130                             = 0x82    , // SR130
  SR131                             = 0x83    , // SR131
  SR132                             = 0x84    , // SR132
  SR133                             = 0x85    , // SR133
  SR134                             = 0x86    , // SR134
  SR135                             = 0x87    , // SR135
  SR136                             = 0x88    , // SR136
  SR137                             = 0x89    , // SR137
  SR138                             = 0x8a    , // SR138
  SR139                             = 0x8b    , // SR139
  SR140                             = 0x8c    , // SR140
  SR141                             = 0x8d    , // SR141
  SR142                             = 0x8e    , // SR142
  SR143                             = 0x8f    , // SR143
  SR144                             = 0x90    , // SR144
  SR145                             = 0x91    , // SR145
  SR146                             = 0x92    , // SR146
  SR147                             = 0x93    , // SR147
  SR148                             = 0x94    , // SR148
  SR149                             = 0x95    , // SR149
  SR150                             = 0x96    , // SR150
  SR151                             = 0x97    , // SR151
  SR152                             = 0x98    , // SR152
  SR153                             = 0x99    , // SR153
  SR154                             = 0x9a    , // SR154
  SR155                             = 0x9b    , // SR155
  SR156                             = 0x9c    , // SR156
  SR157                             = 0x9d    , // SR157
  SR158                             = 0x9e    , // SR158
  SR159                             = 0x9f    , // SR159
  SR160                             = 0xa0    , // SR160
  SR161                             = 0xa1    , // SR161
  SR162                             = 0xa2    , // SR162
  SR163                             = 0xa3    , // SR163
  SR164                             = 0xa4    , // SR164
  SR165                             = 0xa5    , // SR165
  SR166                             = 0xa6    , // SR166
  SR167                             = 0xa7    , // SR167
  SR168                             = 0xa8    , // SR168
  SR169                             = 0xa9    , // SR169
  SR170                             = 0xaa    , // SR170
  SR171                             = 0xab    , // SR171
  SR172                             = 0xac    , // SR172
  SR173                             = 0xad    , // SR173
  SR174                             = 0xae    , // SR174
  SR175                             = 0xaf    , // SR175
  SR176                             = 0xb0    , // SR176
  SR177                             = 0xb1    , // SR177
  SR178                             = 0xb2    , // SR178
  SR179                             = 0xb3    , // SR179
  SR180                             = 0xb4    , // SR180
  SR181                             = 0xb5    , // SR181
  SR182                             = 0xb6    , // SR182
  SR183                             = 0xb7    , // SR183
  SR184                             = 0xb8    , // SR184
  SR185                             = 0xb9    , // SR185
  SR186                             = 0xba    , // SR186
  SR187                             = 0xbb    , // SR187
  SR188                             = 0xbc    , // SR188
  SR189                             = 0xbd    , // SR189
  SR190                             = 0xbe    , // SR190
  SR191                             = 0xbf    , // SR191
  SR192                             = 0xc0    , // SR192
  SR193                             = 0xc1    , // SR193
  SR194                             = 0xc2    , // SR194
  SR195                             = 0xc3    , // SR195
  SR196                             = 0xc4    , // SR196
  SR197                             = 0xc5    , // SR197
  SR198                             = 0xc6    , // SR198
  SR199                             = 0xc7    , // SR199
  SR200                             = 0xc8    , // SR200
  SR201                             = 0xc9    , // SR201
  SR202                             = 0xca    , // SR202
  SR203                             = 0xcb    , // SR203
  SR204                             = 0xcc    , // SR204
  SR205                             = 0xcd    , // SR205
  SR206                             = 0xce    , // SR206
  SR207                             = 0xcf    , // SR207
  SR208                             = 0xd0    , // SR208
  SR209                             = 0xd1    , // SR209
  SR210                             = 0xd2    , // SR210
  SR211                             = 0xd3    , // SR211
  SR212                             = 0xd4    , // SR212
  SR213                             = 0xd5    , // SR213
  SR214                             = 0xd6    , // SR214
  SR215                             = 0xd7    , // SR215
  SR216                             = 0xd8    , // SR216
  SR217                             = 0xd9    , // SR217
  SR218                             = 0xda    , // SR218
  SR219                             = 0xdb    , // SR219
  SR220                             = 0xdc    , // SR220
  SR221                             = 0xdd    , // SR221
  SR222                             = 0xde    , // SR222
  SR223                             = 0xdf    , // SR223
  SR224                             = 0xe0    , // SR224
  SR225                             = 0xe1    , // SR225
  SR226                             = 0xe2    , // SR226
  SR227                             = 0xe3    , // SR227
  SR228                             = 0xe4    , // SR228
  SR229                             = 0xe5    , // SR229
  SR230                             = 0xe6    , // SR230
  SR231                             = 0xe7    , // SR231
  SR232                             = 0xe8    , // SR232
  SR233                             = 0xe9    , // SR233
  SR234                             = 0xea    , // SR234
  SR235                             = 0xeb    , // SR235
  SR236                             = 0xec    , // SR236
  SR237                             = 0xed    , // SR237
  SR238                             = 0xee    , // SR238
  SR239                             = 0xef    , // SR239
  SR240                             = 0xf0    , // SR240
  SR241                             = 0xf1    , // SR241
  SR242                             = 0xf2    , // SR242
  SR243                             = 0xf3    , // SR243
  SR244                             = 0xf4    , // SR244
  SR245                             = 0xf5    , // SR245
  SR246                             = 0xf6    , // SR246
  SR247                             = 0xf7    , // SR247
  SR248                             = 0xf8    , // SR248
  SR249                             = 0xf9    , // SR249
  SR250                             = 0xfa    , // SR250
  SR251                             = 0xfb    , // SR251
  SR252                             = 0xfc    , // SR252
  SR253                             = 0xfd    , // SR253
  SR254                             = 0xfe    , // SR254
  SR255                             = 0xff    , // SR255
};
enum class StoreCacheOp : std::uint32_t {
  WB  = 0x0     , // WB
  CG  = 0x1     , // CG
  CS  = 0x2     , // CS
  WT  = 0x3     , // WT
};
enum class TEXWmsk2C : std::uint32_t {
  R   = 0x0     , // R
  G   = 0x1     , // G
  B   = 0x2     , // B
  A   = 0x3     , // A
  RG  = 0x4     , // RG
  RA  = 0x5     , // RA
  GA  = 0x6     , // GA
  BA  = 0x7     , // BA
};
enum class TEXWmsk34C : std::uint32_t {
  RGB       = 0x0     , // RGB
  RGA       = 0x1     , // RGA
  RBA       = 0x2     , // RBA
  GBA       = 0x3     , // GBA
  RGBA      = 0x4     , // RGBA
  INVALID5  = 0x5     , // INVALID5
  INVALID6  = 0x6     , // INVALID6
  INVALID7  = 0x7     , // INVALID7
};
enum class TOFF1 : std::uint32_t {
  noTOFF  = 0x0     , // noTOFF
  AOFFI   = 0x1     , // AOFFI
};
enum class TOFF2 : std::uint32_t {
  noTOFF          = 0x0     , // noTOFF
  AOFFI           = 0x1     , // AOFFI
  PTP             = 0x2     , // PTP
  INVALIDBTOFF03  = 0x3     , // INVALIDBTOFF03
};
enum class TPhase : std::uint32_t {
  noPhase        = 0x0     , // noPhase
  T              = 0x1     , // T
  P              = 0x2     , // P
  INVALIDPHASE3  = 0x3     , // INVALIDPHASE3
};
enum class TXQMode : std::uint32_t {
  TEX_HEADER_DIMENSION      = 0x0     , // TEX_HEADER_DIMENSION
  TEX_HEADER_TEXTURE_TYPE   = 0x1     , // TEX_HEADER_TEXTURE_TYPE
  TEX_HEADER_SAMPLER_POS    = 0x2     , // TEX_HEADER_SAMPLER_POS
  _3                        = 0x3     , // 3
  _4                        = 0x4     , // 4
  _5                        = 0x5     , // 5
  _6                        = 0x6     , // 6
  _7                        = 0x7     , // 7
  TEX_SAMPLER_FILTER        = 0x8     , // TEX_SAMPLER_FILTER
  TEX_SAMPLER_LOD           = 0x9     , // TEX_SAMPLER_LOD
  TEX_SAMPLER_WRAP          = 0xa     , // TEX_SAMPLER_WRAP
  TEX_SAMPLER_BORDER_COLOR  = 0xb     , // TEX_SAMPLER_BORDER_COLOR
  _12                       = 0xc     , // 12
  _13                       = 0xd     , // 13
  _14                       = 0xe     , // 14
  _15                       = 0xf     , // 15
  _16                       = 0x10    , // 16
  _17                       = 0x11    , // 17
  _18                       = 0x12    , // 18
  _19                       = 0x13    , // 19
  _20                       = 0x14    , // 20
  _21                       = 0x15    , // 21
  _22                       = 0x16    , // 22
  _23                       = 0x17    , // 23
  _24                       = 0x18    , // 24
  _25                       = 0x19    , // 25
  _26                       = 0x1a    , // 26
  _27                       = 0x1b    , // 27
  _28                       = 0x1c    , // 28
  _29                       = 0x1d    , // 29
  _30                       = 0x1e    , // 30
  _31                       = 0x1f    , // 31
};
enum class Test : std::uint32_t {
  F               = 0x0     , // F
  FALSE           = 0x0     , // FALSE
  LT              = 0x1     , // LT
  EQ              = 0x2     , // EQ
  LE              = 0x3     , // LE
  GT              = 0x4     , // GT
  NE              = 0x5     , // NE
  ZF0             = 0x5     , // ZF0
  ZFF             = 0x5     , // ZFF
  GE              = 0x6     , // GE
  LEG             = 0x7     , // LEG
  NUM             = 0x7     , // NUM
  NAN             = 0x8     , // NAN
  U               = 0x8     , // U
  LTU             = 0x9     , // LTU
  EQU             = 0xa     , // EQU
  ZF1             = 0xa     , // ZF1
  ZFT             = 0xa     , // ZFT
  LEU             = 0xb     , // LEU
  GTU             = 0xc     , // GTU
  NEU             = 0xd     , // NEU
  GEU             = 0xe     , // GEU
  T               = 0xf     , // T
  TRUE            = 0xf     , // TRUE
  _0FF            = 0x10    , // 0FF
  NOT_OVERFLOW    = 0x10    , // NOT_OVERFLOW
  OFF             = 0x10    , // OFF
  CARRY           = 0x11    , // CARRY
  CFF             = 0x11    , // CFF
  LO              = 0x11    , // LO
  ABOVE           = 0x12    , // ABOVE
  SF0             = 0x12    , // SF0
  SFF             = 0x12    , // SFF
  LS              = 0x13    , // LS
  SIGN            = 0x13    , // SIGN
  HI              = 0x14    , // HI
  SF1             = 0x15    , // SF1
  SFT             = 0x15    , // SFT
  CF1             = 0x16    , // CF1
  CFT             = 0x16    , // CFT
  HS              = 0x16    , // HS
  OF1             = 0x17    , // OF1
  OFT             = 0x17    , // OFT
  OVERFLOW        = 0x17    , // OVERFLOW
  CSM_TA          = 0x18    , // CSM_TA
  CSM_TR          = 0x19    , // CSM_TR
  CSM_MX          = 0x1a    , // CSM_MX
  FCSM_TA         = 0x1b    , // FCSM_TA
  FCSM_TR         = 0x1c    , // FCSM_TR
  NOT_SIGN        = 0x1c    , // NOT_SIGN
  BELOW_OR_EQUAL  = 0x1d    , // BELOW_OR_EQUAL
  FCSM_MX         = 0x1d    , // FCSM_MX
  _1E             = 0x1e    , // 1E
  NOT_CARRY       = 0x1e    , // NOT_CARRY
  RLE             = 0x1e    , // RLE
  _1F             = 0x1f    , // 1F
  RGT             = 0x1f    , // RGT
};
enum class TexComp : std::uint32_t {
  R  = 0x0     , // R
  G  = 0x1     , // G
  B  = 0x2     , // B
  A  = 0x3     , // A
};
enum class Trig : std::uint32_t {
  TRIG  = 0x1     , // TRIG
};
enum class U : std::uint32_t {
  noU  = 0x0     , // noU
  U    = 0x1     , // U
};
enum class U16 : std::uint32_t {
  U16  = 0x2     , // U16
};
enum class U32 : std::uint32_t {
  U32           = 0x4     , // U32
  INVALIDASEL7  = 0x6     , // INVALIDASEL7
  INVALIDBSEL7  = 0x6     , // INVALIDBSEL7
  INVALIDSEL7   = 0x6     , // INVALIDSEL7
};
enum class U8 : std::uint32_t {
  U8  = 0x0     , // U8
};
using UInteger16 = U16;
enum class UInteger32 : std::uint32_t {
  U32  = 0x4     , // U32
};
enum class UInteger64 : std::uint32_t {
  U64  = 0x6     , // U64
};
using UInteger8 = U8;
enum class USCHED_INFO : std::uint32_t {
  DRAIN                  = 0x0     , // DRAIN
  OFF_DECK_DRAIN         = 0x0     , // OFF_DECK_DRAIN
  OFF_DECK_YIELD_SB_ALL  = 0x0     , // OFF_DECK_YIELD_SB_ALL
  YIELD_SB               = 0x0     , // YIELD_SB
  W1G                    = 0x1     , // W1G
  WAIT1_END_GROUP        = 0x1     , // WAIT1_END_GROUP
  WAIT1_GROUP            = 0x1     , // WAIT1_GROUP
  W2G                    = 0x2     , // W2G
  WAIT2_END_GROUP        = 0x2     , // WAIT2_END_GROUP
  WAIT2_GROUP            = 0x2     , // WAIT2_GROUP
  W3G                    = 0x3     , // W3G
  WAIT3_END_GROUP        = 0x3     , // WAIT3_END_GROUP
  WAIT3_GROUP            = 0x3     , // WAIT3_GROUP
  W4G                    = 0x4     , // W4G
  WAIT4_END_GROUP        = 0x4     , // WAIT4_END_GROUP
  WAIT4_GROUP            = 0x4     , // WAIT4_GROUP
  W5G                    = 0x5     , // W5G
  WAIT5_END_GROUP        = 0x5     , // WAIT5_END_GROUP
  WAIT5_GROUP            = 0x5     , // WAIT5_GROUP
  W6G                    = 0x6     , // W6G
  WAIT6_END_GROUP        = 0x6     , // WAIT6_END_GROUP
  WAIT6_GROUP            = 0x6     , // WAIT6_GROUP
  W7G                    = 0x7     , // W7G
  WAIT7_END_GROUP        = 0x7     , // WAIT7_END_GROUP
  WAIT7_GROUP            = 0x7     , // WAIT7_GROUP
  W8G                    = 0x8     , // W8G
  WAIT8_END_GROUP        = 0x8     , // WAIT8_END_GROUP
  WAIT8_GROUP            = 0x8     , // WAIT8_GROUP
  W9G                    = 0x9     , // W9G
  WAIT9_END_GROUP        = 0x9     , // WAIT9_END_GROUP
  WAIT9_GROUP            = 0x9     , // WAIT9_GROUP
  W10G                   = 0xa     , // W10G
  WAIT10_END_GROUP       = 0xa     , // WAIT10_END_GROUP
  WAIT10_GROUP           = 0xa     , // WAIT10_GROUP
  W11G                   = 0xb     , // W11G
  WAIT11_END_GROUP       = 0xb     , // WAIT11_END_GROUP
  WAIT11_GROUP           = 0xb     , // WAIT11_GROUP
  W12G                   = 0xc     , // W12G
  WAIT12_END_GROUP       = 0xc     , // WAIT12_END_GROUP
  WAIT12_GROUP           = 0xc     , // WAIT12_GROUP
  W13G                   = 0xd     , // W13G
  WAIT13_END_GROUP       = 0xd     , // WAIT13_END_GROUP
  WAIT13_GROUP           = 0xd     , // WAIT13_GROUP
  W14G                   = 0xe     , // W14G
  WAIT14_END_GROUP       = 0xe     , // WAIT14_END_GROUP
  WAIT14_GROUP           = 0xe     , // WAIT14_GROUP
  W15G                   = 0xf     , // W15G
  WAIT15_END_GROUP       = 0xf     , // WAIT15_END_GROUP
  WAIT15_GROUP           = 0xf     , // WAIT15_GROUP
  floxy2                 = 0x10    , // floxy2
  W1                     = 0x11    , // W1
  W1B                    = 0x11    , // W1B
  WAIT1_BOOST            = 0x11    , // WAIT1_BOOST
  trans1                 = 0x11    , // trans1
  W2                     = 0x12    , // W2
  W2B                    = 0x12    , // W2B
  WAIT2_BOOST            = 0x12    , // WAIT2_BOOST
  trans2                 = 0x12    , // trans2
  W3                     = 0x13    , // W3
  W3B                    = 0x13    , // W3B
  WAIT3_BOOST            = 0x13    , // WAIT3_BOOST
  trans3                 = 0x13    , // trans3
  W4                     = 0x14    , // W4
  W4B                    = 0x14    , // W4B
  WAIT4_BOOST            = 0x14    , // WAIT4_BOOST
  trans4                 = 0x14    , // trans4
  W5                     = 0x15    , // W5
  W5B                    = 0x15    , // W5B
  WAIT5_BOOST            = 0x15    , // WAIT5_BOOST
  trans5                 = 0x15    , // trans5
  W6                     = 0x16    , // W6
  W6B                    = 0x16    , // W6B
  WAIT6_BOOST            = 0x16    , // WAIT6_BOOST
  trans6                 = 0x16    , // trans6
  W7                     = 0x17    , // W7
  W7B                    = 0x17    , // W7B
  WAIT7_BOOST            = 0x17    , // WAIT7_BOOST
  trans7                 = 0x17    , // trans7
  W8                     = 0x18    , // W8
  W8B                    = 0x18    , // W8B
  WAIT8_BOOST            = 0x18    , // WAIT8_BOOST
  trans8                 = 0x18    , // trans8
  W9                     = 0x19    , // W9
  W9B                    = 0x19    , // W9B
  WAIT9_BOOST            = 0x19    , // WAIT9_BOOST
  trans9                 = 0x19    , // trans9
  W10                    = 0x1a    , // W10
  W10B                   = 0x1a    , // W10B
  WAIT10_BOOST           = 0x1a    , // WAIT10_BOOST
  trans10                = 0x1a    , // trans10
  W11                    = 0x1b    , // W11
  W11B                   = 0x1b    , // W11B
  WAIT11_BOOST           = 0x1b    , // WAIT11_BOOST
  trans11                = 0x1b    , // trans11
  OFF_DECK_PIXBAR        = 0x1c    , // OFF_DECK_PIXBAR
  PIXBAR                 = 0x1c    , // PIXBAR
  OFF_DECK_YIELD         = 0x1d    , // OFF_DECK_YIELD
  OFF_DECK_YIELD6        = 0x1d    , // OFF_DECK_YIELD6
  YIELD                  = 0x1d    , // YIELD
  YIELD6                 = 0x1d    , // YIELD6
  YLD                    = 0x1d    , // YLD
  YLD6                   = 0x1d    , // YLD6
  OFF_DECK_YIELD8        = 0x1e    , // OFF_DECK_YIELD8
  YIELD8                 = 0x1e    , // YIELD8
  YLD8                   = 0x1e    , // YLD8
  OFF_DECK               = 0x1f    , // OFF_DECK
};
enum class UnaryAbs : std::uint32_t {
  noABS  = 0x0     , // noABS
  ABS    = 0x1     , // ABS
};
enum class UnaryInv : std::uint32_t {
  noINV  = 0x0     , // noINV
  INV    = 0x1     , // INV
};
enum class UnaryNeg : std::uint32_t {
  noNEG  = 0x0     , // noNEG
  NEG    = 0x1     , // NEG
};
enum class VInteger32 : std::uint32_t {
  U32           = 0x4     , // U32
  S32           = 0x5     , // S32
  INVALIDASEL6  = 0x6     , // INVALIDASEL6
  INVALIDBSEL6  = 0x6     , // INVALIDBSEL6
  INVALIDSEL6   = 0x6     , // INVALIDSEL6
  INVALIDASEL7  = 0x7     , // INVALIDASEL7
  INVALIDBSEL7  = 0x7     , // INVALIDBSEL7
  INVALIDSEL7   = 0x7     , // INVALIDSEL7
};
enum class VMadScale : std::uint32_t {
  PASS               = 0x0     , // PASS
  SHR_7              = 0x1     , // SHR_7
  SHR_15             = 0x2     , // SHR_15
  INVALIDVMADSCALE3  = 0x3     , // INVALIDVMADSCALE3
};
enum class VOP : std::uint32_t {
  MRG_16H  = 0x0     , // MRG_16H
  MRG_16L  = 0x1     , // MRG_16L
  MRG_8B0  = 0x2     , // MRG_8B0
  MRG_8B2  = 0x3     , // MRG_8B2
  ACC      = 0x4     , // ACC
  MIN      = 0x5     , // MIN
  MAX      = 0x6     , // MAX
  PASS     = 0x7     , // PASS
};
enum class VRed2 : std::uint32_t {
  SIMD_MRG     = 0x0     , // SIMD_MRG
  ACC          = 0x1     , // ACC
  INVALIDRED2  = 0x2     , // INVALIDRED2
  INVALIDRED3  = 0x3     , // INVALIDRED3
};
enum class VTG : std::uint32_t {
  VTG  = 0x0     , // VTG
};
enum class VTGMode : std::uint32_t {
  R                = 0x0     , // R
  A                = 0x1     , // A
  RA               = 0x2     , // RA
  INVALIDVTGMODE3  = 0x3     , // INVALIDVTGMODE3
};
enum class VoteOp : std::uint32_t {
  ALL            = 0x0     , // ALL
  ANY            = 0x1     , // ANY
  EQ             = 0x2     , // EQ
  INVALIDVMODE3  = 0x3     , // INVALIDVMODE3
};
enum class WR : std::uint32_t {
  wr  = 0x0     , // wr
};
enum class X : std::uint32_t {
  noX  = 0x0     , // noX
  X    = 0x1     , // X
};
enum class XMADcop : std::uint32_t {
  C32   = 0x0     , // C32
  CLO   = 0x1     , // CLO
  CHI   = 0x2     , // CHI
  CSFU  = 0x3     , // CSFU
  CBCC  = 0x4     , // CBCC
};
enum class XMADcop2 : std::uint32_t {
  C32   = 0x0     , // C32
  CLO   = 0x1     , // CLO
  CHI   = 0x2     , // CHI
  CSFU  = 0x3     , // CSFU
};
enum class XMode : std::uint32_t {
  noX   = 0x0     , // noX
  XLO   = 0x1     , // XLO
  XMED  = 0x2     , // XMED
  XHI   = 0x3     , // XHI
};
enum class XXHI : std::uint32_t {
  noX               = 0x0     , // noX
  INVALIDSHRXMODE1  = 0x1     , // INVALIDSHRXMODE1
  X                 = 0x2     , // X
  XHI               = 0x3     , // XHI
};
enum class ZeroRegister : std::uint32_t {
  RZ  = 0xff    , // RZ
};
enum class hadd2_32i__Ra : std::uint32_t {
  R0    = 0x0     , // R0
  R1    = 0x1     , // R1
  R2    = 0x2     , // R2
  R3    = 0x3     , // R3
  R4    = 0x4     , // R4
  R5    = 0x5     , // R5
  R6    = 0x6     , // R6
  R7    = 0x7     , // R7
  R8    = 0x8     , // R8
  R9    = 0x9     , // R9
  R10   = 0xa     , // R10
  R11   = 0xb     , // R11
  R12   = 0xc     , // R12
  R13   = 0xd     , // R13
  R14   = 0xe     , // R14
  R15   = 0xf     , // R15
  R16   = 0x10    , // R16
  R17   = 0x11    , // R17
  R18   = 0x12    , // R18
  R19   = 0x13    , // R19
  R20   = 0x14    , // R20
  R21   = 0x15    , // R21
  R22   = 0x16    , // R22
  R23   = 0x17    , // R23
  R24   = 0x18    , // R24
  R25   = 0x19    , // R25
  R26   = 0x1a    , // R26
  R27   = 0x1b    , // R27
  R28   = 0x1c    , // R28
  R29   = 0x1d    , // R29
  R30   = 0x1e    , // R30
  R31   = 0x1f    , // R31
  R32   = 0x20    , // R32
  R33   = 0x21    , // R33
  R34   = 0x22    , // R34
  R35   = 0x23    , // R35
  R36   = 0x24    , // R36
  R37   = 0x25    , // R37
  R38   = 0x26    , // R38
  R39   = 0x27    , // R39
  R40   = 0x28    , // R40
  R41   = 0x29    , // R41
  R42   = 0x2a    , // R42
  R43   = 0x2b    , // R43
  R44   = 0x2c    , // R44
  R45   = 0x2d    , // R45
  R46   = 0x2e    , // R46
  R47   = 0x2f    , // R47
  R48   = 0x30    , // R48
  R49   = 0x31    , // R49
  R50   = 0x32    , // R50
  R51   = 0x33    , // R51
  R52   = 0x34    , // R52
  R53   = 0x35    , // R53
  R54   = 0x36    , // R54
  R55   = 0x37    , // R55
  R56   = 0x38    , // R56
  R57   = 0x39    , // R57
  R58   = 0x3a    , // R58
  R59   = 0x3b    , // R59
  R60   = 0x3c    , // R60
  R61   = 0x3d    , // R61
  R62   = 0x3e    , // R62
  R63   = 0x3f    , // R63
  R64   = 0x40    , // R64
  R65   = 0x41    , // R65
  R66   = 0x42    , // R66
  R67   = 0x43    , // R67
  R68   = 0x44    , // R68
  R69   = 0x45    , // R69
  R70   = 0x46    , // R70
  R71   = 0x47    , // R71
  R72   = 0x48    , // R72
  R73   = 0x49    , // R73
  R74   = 0x4a    , // R74
  R75   = 0x4b    , // R75
  R76   = 0x4c    , // R76
  R77   = 0x4d    , // R77
  R78   = 0x4e    , // R78
  R79   = 0x4f    , // R79
  R80   = 0x50    , // R80
  R81   = 0x51    , // R81
  R82   = 0x52    , // R82
  R83   = 0x53    , // R83
  R84   = 0x54    , // R84
  R85   = 0x55    , // R85
  R86   = 0x56    , // R86
  R87   = 0x57    , // R87
  R88   = 0x58    , // R88
  R89   = 0x59    , // R89
  R90   = 0x5a    , // R90
  R91   = 0x5b    , // R91
  R92   = 0x5c    , // R92
  R93   = 0x5d    , // R93
  R94   = 0x5e    , // R94
  R95   = 0x5f    , // R95
  R96   = 0x60    , // R96
  R97   = 0x61    , // R97
  R98   = 0x62    , // R98
  R99   = 0x63    , // R99
  R100  = 0x64    , // R100
  R101  = 0x65    , // R101
  R102  = 0x66    , // R102
  R103  = 0x67    , // R103
  R104  = 0x68    , // R104
  R105  = 0x69    , // R105
  R106  = 0x6a    , // R106
  R107  = 0x6b    , // R107
  R108  = 0x6c    , // R108
  R109  = 0x6d    , // R109
  R110  = 0x6e    , // R110
  R111  = 0x6f    , // R111
  R112  = 0x70    , // R112
  R113  = 0x71    , // R113
  R114  = 0x72    , // R114
  R115  = 0x73    , // R115
  R116  = 0x74    , // R116
  R117  = 0x75    , // R117
  R118  = 0x76    , // R118
  R119  = 0x77    , // R119
  R120  = 0x78    , // R120
  R121  = 0x79    , // R121
  R122  = 0x7a    , // R122
  R123  = 0x7b    , // R123
  R124  = 0x7c    , // R124
  R125  = 0x7d    , // R125
  R126  = 0x7e    , // R126
  R127  = 0x7f    , // R127
  R128  = 0x80    , // R128
  R129  = 0x81    , // R129
  R130  = 0x82    , // R130
  R131  = 0x83    , // R131
  R132  = 0x84    , // R132
  R133  = 0x85    , // R133
  R134  = 0x86    , // R134
  R135  = 0x87    , // R135
  R136  = 0x88    , // R136
  R137  = 0x89    , // R137
  R138  = 0x8a    , // R138
  R139  = 0x8b    , // R139
  R140  = 0x8c    , // R140
  R141  = 0x8d    , // R141
  R142  = 0x8e    , // R142
  R143  = 0x8f    , // R143
  R144  = 0x90    , // R144
  R145  = 0x91    , // R145
  R146  = 0x92    , // R146
  R147  = 0x93    , // R147
  R148  = 0x94    , // R148
  R149  = 0x95    , // R149
  R150  = 0x96    , // R150
  R151  = 0x97    , // R151
  R152  = 0x98    , // R152
  R153  = 0x99    , // R153
  R154  = 0x9a    , // R154
  R155  = 0x9b    , // R155
  R156  = 0x9c    , // R156
  R157  = 0x9d    , // R157
  R158  = 0x9e    , // R158
  R159  = 0x9f    , // R159
  R160  = 0xa0    , // R160
  R161  = 0xa1    , // R161
  R162  = 0xa2    , // R162
  R163  = 0xa3    , // R163
  R164  = 0xa4    , // R164
  R165  = 0xa5    , // R165
  R166  = 0xa6    , // R166
  R167  = 0xa7    , // R167
  R168  = 0xa8    , // R168
  R169  = 0xa9    , // R169
  R170  = 0xaa    , // R170
  R171  = 0xab    , // R171
  R172  = 0xac    , // R172
  R173  = 0xad    , // R173
  R174  = 0xae    , // R174
  R175  = 0xaf    , // R175
  R176  = 0xb0    , // R176
  R177  = 0xb1    , // R177
  R178  = 0xb2    , // R178
  R179  = 0xb3    , // R179
  R180  = 0xb4    , // R180
  R181  = 0xb5    , // R181
  R182  = 0xb6    , // R182
  R183  = 0xb7    , // R183
  R184  = 0xb8    , // R184
  R185  = 0xb9    , // R185
  R186  = 0xba    , // R186
  R187  = 0xbb    , // R187
  R188  = 0xbc    , // R188
  R189  = 0xbd    , // R189
  R190  = 0xbe    , // R190
  R191  = 0xbf    , // R191
  R192  = 0xc0    , // R192
  R193  = 0xc1    , // R193
  R194  = 0xc2    , // R194
  R195  = 0xc3    , // R195
  R196  = 0xc4    , // R196
  R197  = 0xc5    , // R197
  R198  = 0xc6    , // R198
  R199  = 0xc7    , // R199
  R200  = 0xc8    , // R200
  R201  = 0xc9    , // R201
  R202  = 0xca    , // R202
  R203  = 0xcb    , // R203
  R204  = 0xcc    , // R204
  R205  = 0xcd    , // R205
  R206  = 0xce    , // R206
  R207  = 0xcf    , // R207
  R208  = 0xd0    , // R208
  R209  = 0xd1    , // R209
  R210  = 0xd2    , // R210
  R211  = 0xd3    , // R211
  R212  = 0xd4    , // R212
  R213  = 0xd5    , // R213
  R214  = 0xd6    , // R214
  R215  = 0xd7    , // R215
  R216  = 0xd8    , // R216
  R217  = 0xd9    , // R217
  R218  = 0xda    , // R218
  R219  = 0xdb    , // R219
  R220  = 0xdc    , // R220
  R221  = 0xdd    , // R221
  R222  = 0xde    , // R222
  R223  = 0xdf    , // R223
  R224  = 0xe0    , // R224
  R225  = 0xe1    , // R225
  R226  = 0xe2    , // R226
  R227  = 0xe3    , // R227
  R228  = 0xe4    , // R228
  R229  = 0xe5    , // R229
  R230  = 0xe6    , // R230
  R231  = 0xe7    , // R231
  R232  = 0xe8    , // R232
  R233  = 0xe9    , // R233
  R234  = 0xea    , // R234
  R235  = 0xeb    , // R235
  R236  = 0xec    , // R236
  R237  = 0xed    , // R237
  R238  = 0xee    , // R238
  R239  = 0xef    , // R239
  R240  = 0xf0    , // R240
  R241  = 0xf1    , // R241
  R242  = 0xf2    , // R242
  R243  = 0xf3    , // R243
  R244  = 0xf4    , // R244
  R245  = 0xf5    , // R245
  R246  = 0xf6    , // R246
  R247  = 0xf7    , // R247
  R248  = 0xf8    , // R248
  R249  = 0xf9    , // R249
  R250  = 0xfa    , // R250
  R251  = 0xfb    , // R251
  R252  = 0xfc    , // R252
  R253  = 0xfd    , // R253
  R254  = 0xfe    , // R254
  RZ    = 0xff    , // RZ
};
using hadd2_32i__Ra_iswz_Ra_32i_mod = ISWZ;
using hadd2_32i__Rd = hadd2_32i__Ra;
enum class hadd2_32i__ftz : std::uint32_t {
  noftz  = 0x0     , // noftz
  FTZ    = 0x1     , // FTZ
};
enum class hadd2_32i__sat : std::uint32_t {
  nosat  = 0x0     , // nosat
  SAT    = 0x1     , // SAT
};
using hadd2__v0_Ra = hadd2_32i__Ra;
using hadd2__v0_Ra_iswz_Ra_mod = ISWZ;
using hadd2__v0_Rd = hadd2_32i__Ra;
using hadd2__v0_ftz = hadd2_32i__ftz;
using hadd2__v0_ofmt = Ofmt_FP16;
using hadd2__v0_sat = hadd2_32i__sat;
using hadd2__v1_Ra = hadd2_32i__Ra;
using hadd2__v1_Ra_iswz_Ra_mod = ISWZ;
using hadd2__v1_Rd = hadd2_32i__Ra;
using hadd2__v1_ftz = hadd2_32i__ftz;
using hadd2__v1_ofmt = Ofmt_FP16;
using hadd2__v1_sat = hadd2_32i__sat;
using hadd2__v2_Ra = hadd2_32i__Ra;
using hadd2__v2_Ra_iswz_Ra_mod = ISWZ;
using hadd2__v2_Rb = hadd2_32i__Ra;
using hadd2__v2_Rd = hadd2_32i__Ra;
using hadd2__v2_Sb_iswz_Rb_mod = ISWZ;
using hadd2__v2_ftz = hadd2_32i__ftz;
using hadd2__v2_ofmt = Ofmt_FP16;
using hadd2__v2_sat = hadd2_32i__sat;
using hfma2__v0_Ra = hadd2_32i__Ra;
using hfma2__v0_Ra_iswz_Ra_mod = ISWZ;
using hfma2__v0_Rc = hadd2_32i__Ra;
using hfma2__v0_Rc_iswz_Rc_mod = ISWZ;
using hfma2__v0_Rd = hadd2_32i__Ra;
enum class hfma2__v0_fmz : std::uint32_t {
  nofmz    = 0x0     , // nofmz
  FTZ      = 0x1     , // FTZ
  FMZ      = 0x2     , // FMZ
  INVALID  = 0x3     , // INVALID
};
using hfma2__v0_ofmt = Ofmt_FP16;
using hfma2__v0_sat = hadd2_32i__sat;
using hfma2__v1_Ra = hadd2_32i__Ra;
using hfma2__v1_Ra_iswz_Ra_mod = ISWZ;
using hfma2__v1_Rc = hadd2_32i__Ra;
using hfma2__v1_Rc_iswz_Rc_mod = ISWZ;
using hfma2__v1_Rd = hadd2_32i__Ra;
using hfma2__v1_fmz = hfma2__v0_fmz;
using hfma2__v1_ofmt = Ofmt_FP16;
using hfma2__v1_sat = hadd2_32i__sat;
using hfma2__v2_Ra = hadd2_32i__Ra;
using hfma2__v2_Ra_iswz_Ra_mod = ISWZ;
using hfma2__v2_Rb = hadd2_32i__Ra;
using hfma2__v2_Rc = hadd2_32i__Ra;
using hfma2__v2_Rc_iswz_Rc_reg_mod = ISWZ;
using hfma2__v2_Rd = hadd2_32i__Ra;
using hfma2__v2_Sb_iswz_Rb_mod = ISWZ;
using hfma2__v2_fmz = hfma2__v0_fmz;
using hfma2__v2_ofmt = Ofmt_FP16;
using hfma2__v2_sat = hadd2_32i__sat;
using hmul2_32i__Ra = hadd2_32i__Ra;
using hmul2_32i__Ra_iswz_Ra_32i_mod = ISWZ;
using hmul2_32i__Rd = hadd2_32i__Ra;
using hmul2_32i__fmz = hfma2__v0_fmz;
using hmul2_32i__sat = hadd2_32i__sat;
using hmul2__v0_Ra = hadd2_32i__Ra;
using hmul2__v0_Ra_iswz_Ra_mod = ISWZ;
using hmul2__v0_Rd = hadd2_32i__Ra;
using hmul2__v0_fmz = hfma2__v0_fmz;
using hmul2__v0_ofmt = Ofmt_FP16;
using hmul2__v0_sat = hadd2_32i__sat;
using hmul2__v1_Ra = hadd2_32i__Ra;
using hmul2__v1_Ra_iswz_Ra_mod = ISWZ;
using hmul2__v1_Rd = hadd2_32i__Ra;
using hmul2__v1_fmz = hfma2__v0_fmz;
using hmul2__v1_ofmt = Ofmt_FP16;
using hmul2__v1_sat = hadd2_32i__sat;
using hmul2__v2_Ra = hadd2_32i__Ra;
using hmul2__v2_Ra_iswz_Ra_mod = ISWZ;
using hmul2__v2_Rb = hadd2_32i__Ra;
using hmul2__v2_Rd = hadd2_32i__Ra;
using hmul2__v2_Sb_iswz_Rb_mod = ISWZ;
using hmul2__v2_fmz = hfma2__v0_fmz;
using hmul2__v2_ofmt = Ofmt_FP16;
using hmul2__v2_sat = hadd2_32i__sat;
using hset2__v0_Ra = hadd2_32i__Ra;
using hset2__v0_Ra_iswz_Ra_mod = ISWZ;
using hset2__v0_Rd = hadd2_32i__Ra;
enum class hset2__v0_bop : std::uint32_t {
  AND  = 0x0     , // AND
  OR   = 0x1     , // OR
  XOR  = 0x2     , // XOR
};
using hset2__v0_bval = BVal;
enum class hset2__v0_cmp : std::uint32_t {
  F    = 0x0     , // F
  LT   = 0x1     , // LT
  EQ   = 0x2     , // EQ
  LE   = 0x3     , // LE
  GT   = 0x4     , // GT
  NE   = 0x5     , // NE
  GE   = 0x6     , // GE
  NUM  = 0x7     , // NUM
  NAN  = 0x8     , // NAN
  LTU  = 0x9     , // LTU
  EQU  = 0xa     , // EQU
  LEU  = 0xb     , // LEU
  GTU  = 0xc     , // GTU
  NEU  = 0xd     , // NEU
  GEU  = 0xe     , // GEU
  T    = 0xf     , // T
};
using hset2__v0_ftz = hadd2_32i__ftz;
using hset2__v1_Ra = hadd2_32i__Ra;
using hset2__v1_Ra_iswz_Ra_mod = ISWZ;
using hset2__v1_Rd = hadd2_32i__Ra;
using hset2__v1_bop = hset2__v0_bop;
using hset2__v1_bval = BVal;
using hset2__v1_cmp = hset2__v0_cmp;
using hset2__v1_ftz = hadd2_32i__ftz;
using hset2__v2_Ra = hadd2_32i__Ra;
using hset2__v2_Ra_iswz_Ra_mod = ISWZ;
using hset2__v2_Rb = hadd2_32i__Ra;
using hset2__v2_Rd = hadd2_32i__Ra;
using hset2__v2_Sb_iswz_Rb_mod = ISWZ;
using hset2__v2_bop = hset2__v0_bop;
using hset2__v2_bval = BVal;
using hset2__v2_cmp = hset2__v0_cmp;
using hset2__v2_ftz = hadd2_32i__ftz;
using hset2_bop__v0_Ra = hadd2_32i__Ra;
using hset2_bop__v0_Ra_iswz_Ra_mod = ISWZ;
using hset2_bop__v0_Rd = hadd2_32i__Ra;
using hset2_bop__v0_bval = BVal;
using hset2_bop__v0_cmp = hset2__v0_cmp;
using hset2_bop__v0_ftz = hadd2_32i__ftz;
using hset2_bop__v1_Ra = hadd2_32i__Ra;
using hset2_bop__v1_Ra_iswz_Ra_mod = ISWZ;
using hset2_bop__v1_Rd = hadd2_32i__Ra;
using hset2_bop__v1_bval = BVal;
using hset2_bop__v1_cmp = hset2__v0_cmp;
using hset2_bop__v1_ftz = hadd2_32i__ftz;
using hset2_bop__v2_Ra = hadd2_32i__Ra;
using hset2_bop__v2_Ra_iswz_Ra_mod = ISWZ;
using hset2_bop__v2_Rb = hadd2_32i__Ra;
using hset2_bop__v2_Rd = hadd2_32i__Ra;
using hset2_bop__v2_Sb_iswz_Rb_mod = ISWZ;
using hset2_bop__v2_bval = BVal;
using hset2_bop__v2_cmp = hset2__v0_cmp;
using hset2_bop__v2_ftz = hadd2_32i__ftz;
enum class maxShift : std::uint32_t {
  _32               = 0x0     , // 32
  INVALIDMAXSHIFT3  = 0x1     , // INVALIDMAXSHIFT3
  U64               = 0x2     , // U64
  S64               = 0x3     , // S64
};
enum class optCC : std::uint32_t {
  noCC  = 0x0     , // noCC
  CC    = 0x1     , // CC
};
struct Integer {
  std::uint32_t raw;
  constexpr Integer(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr Integer(Integer8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer8() const { return static_cast<Integer8>(raw); }
  constexpr Integer(Integer16 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer16() const { return static_cast<Integer16>(raw); }
  constexpr Integer(Integer32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer32() const { return static_cast<Integer32>(raw); }
  constexpr Integer(Integer64 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer64() const { return static_cast<Integer64>(raw); }
};
struct IntegerInv8No64 {
  std::uint32_t raw;
  constexpr IntegerInv8No64(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr IntegerInv8No64(Invalid8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Invalid8() const { return static_cast<Invalid8>(raw); }
  constexpr IntegerInv8No64(Integer16 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer16() const { return static_cast<Integer16>(raw); }
  constexpr IntegerInv8No64(Integer32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer32() const { return static_cast<Integer32>(raw); }
};
struct IntegerNo16Inv64 {
  std::uint32_t raw;
  constexpr IntegerNo16Inv64(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr IntegerNo16Inv64(Integer8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer8() const { return static_cast<Integer8>(raw); }
  constexpr IntegerNo16Inv64(Integer32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer32() const { return static_cast<Integer32>(raw); }
  constexpr IntegerNo16Inv64(Invalid64 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Invalid64() const { return static_cast<Invalid64>(raw); }
};
struct IntegerNo16No64 {
  std::uint32_t raw;
  constexpr IntegerNo16No64(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr IntegerNo16No64(Integer8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer8() const { return static_cast<Integer8>(raw); }
  constexpr IntegerNo16No64(Integer32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer32() const { return static_cast<Integer32>(raw); }
};
struct IntegerNo64 {
  std::uint32_t raw;
  constexpr IntegerNo64(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr IntegerNo64(Integer8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer8() const { return static_cast<Integer8>(raw); }
  constexpr IntegerNo64(Integer16 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer16() const { return static_cast<Integer16>(raw); }
  constexpr IntegerNo64(Integer32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer32() const { return static_cast<Integer32>(raw); }
};
struct IntegerNo8 {
  std::uint32_t raw;
  constexpr IntegerNo8(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr IntegerNo8(Invalid8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Invalid8() const { return static_cast<Invalid8>(raw); }
  constexpr IntegerNo8(Integer16 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer16() const { return static_cast<Integer16>(raw); }
  constexpr IntegerNo8(Integer32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer32() const { return static_cast<Integer32>(raw); }
  constexpr IntegerNo8(Integer64 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator Integer64() const { return static_cast<Integer64>(raw); }
};
using NonZeroRegisterFAU = NonZeroRegister;
struct Register {
  std::uint32_t raw;
  constexpr Register(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr Register(NonZeroRegister _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator NonZeroRegister() const { return static_cast<NonZeroRegister>(raw); }
  constexpr Register(ZeroRegister _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator ZeroRegister() const { return static_cast<ZeroRegister>(raw); }
};
using RegisterFAU = Register;
struct SInteger {
  std::uint32_t raw;
  constexpr SInteger(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr SInteger(SInteger8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator SInteger8() const { return static_cast<SInteger8>(raw); }
  constexpr SInteger(SInteger16 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator SInteger16() const { return static_cast<SInteger16>(raw); }
  constexpr SInteger(SInteger32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator SInteger32() const { return static_cast<SInteger32>(raw); }
  constexpr SInteger(SInteger64 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator SInteger64() const { return static_cast<SInteger64>(raw); }
};
struct UInteger {
  std::uint32_t raw;
  constexpr UInteger(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr UInteger(UInteger8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator UInteger8() const { return static_cast<UInteger8>(raw); }
  constexpr UInteger(UInteger16 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator UInteger16() const { return static_cast<UInteger16>(raw); }
  constexpr UInteger(UInteger32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator UInteger32() const { return static_cast<UInteger32>(raw); }
  constexpr UInteger(UInteger64 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator UInteger64() const { return static_cast<UInteger64>(raw); }
};
struct UInteger_old {
  std::uint32_t raw;
  constexpr UInteger_old(std::uint32_t _raw) noexcept : raw(_raw) {}
  constexpr operator std::uint32_t() const { return raw; }
  constexpr UInteger_old(U8 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator U8() const { return static_cast<U8>(raw); }
  constexpr UInteger_old(U16 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator U16() const { return static_cast<U16>(raw); }
  constexpr UInteger_old(U32 _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {}
  constexpr explicit operator U32() const { return static_cast<U32>(raw); }
};
std::optional<std::tuple<RegisterFAU, RegisterFAU, CASInteger>> ConsecutiveReg8(std::uint64_t value);
template<std::size_t BitSize>
std::optional<std::tuple<std::uint64_t, std::int64_t>> ConstBankAddress0(std::uint64_t value) {
  static_assert(BitSize <= sizeof(std::uint64_t) * CHAR_BIT, "Constant bank offset must fit within a 64-bit integer!");
  constexpr std::size_t nbits = BitSize - 1;
  constexpr std::uint64_t mask = (1ull << nbits) - 1;
  const std::uint64_t slot = value >> nbits;
  const std::int64_t offset = SEXT<nbits>(value & mask);
  return slot > MAX_CONST_BANK ? std::nullopt : std::make_optional<std::tuple<std::uint64_t, std::int64_t>>(slot, offset);
}
template<std::size_t BitSize>
std::optional<std::tuple<std::uint64_t, std::int64_t>> ConstBankAddress2(std::uint64_t value) {
  static_assert(BitSize <= sizeof(std::uint64_t) * CHAR_BIT, "Constant bank offset must fit within a 64-bit integer!");
  constexpr std::size_t nbits = BitSize - 1;
  constexpr std::uint64_t mask = (1ull << nbits) - 1;
  const std::uint64_t slot = value * 4 >> nbits;
  const std::int64_t offset = SEXT<nbits>(value * 4 & mask);
  return slot > MAX_CONST_BANK ? std::nullopt : std::make_optional<std::tuple<std::uint64_t, std::int64_t>>(slot, offset);
}
std::optional<std::tuple<Predicate>> DestPred(std::uint64_t value);
std::optional<std::tuple<IntegerSPC, IntegerSPA, IntegerSPB>> GetSPExtract(std::uint64_t value);
template<typename T>
std::optional<std::tuple<T, T>> IDENTICAL(std::uint64_t value) {
  static_assert(std::is_integral_v<T> || std::is_nothrow_convertible_v<std::uint64_t, T>, "T must be an integral type!");
  return std::make_optional<std::tuple<T, T>>(static_cast<T>(value), static_cast<T>(value));
}
std::optional<std::tuple<Integer>> IntSize(std::uint64_t value);
std::optional<std::tuple<Integer8>> Integer8Signed(std::uint64_t value);
std::optional<std::tuple<Integer>> IntegerSigned(std::uint64_t value);
std::optional<std::tuple<Integer32>> IsSigned(std::uint64_t value);
std::optional<std::tuple<Integer16>> IsSigned16(std::uint64_t value);
std::optional<std::tuple<LOP, std::uint64_t, std::uint64_t, std::uint64_t>> LutImm8(std::uint64_t value);
std::optional<std::tuple<PO, std::uint64_t, std::uint64_t>> PSign(std::uint64_t value);
std::optional<std::tuple<PO, std::uint64_t>> PSign32(std::uint64_t value);
std::optional<std::tuple<std::uint64_t, std::uint64_t>> PSignFFMA(std::uint64_t value);
std::optional<std::tuple<PO, std::uint64_t, std::uint64_t, std::uint64_t>> PSignMAD(std::uint64_t value);
std::optional<std::tuple<CWMode, UInteger_old>> SM5vshlCW(std::uint64_t value);
std::optional<std::tuple<TXQMode>> TXQModeDim(std::uint64_t value);
std::optional<std::tuple<ParamA, DC, LOD2>> Tex2D4(std::uint64_t value);
std::optional<std::tuple<ParamA, MS, LOD1, TOFF1>> Tld2D4(std::uint64_t value);
std::optional<std::tuple<Integer16, H1H0>> VFormat16(std::uint64_t value);
std::optional<std::tuple<VInteger32>> VFormat32(std::uint64_t value);
std::optional<std::tuple<Integer8, B1B0>> VFormat8(std::uint64_t value);
std::optional<std::tuple<U16, H1H0>> VFormatU16(std::uint64_t value);
std::optional<std::tuple<U32>> VFormatU32(std::uint64_t value);
std::optional<std::tuple<U8, B1B0>> VFormatU8(std::uint64_t value);
std::optional<std::tuple<std::uint64_t>> VarLatOperandEnc(std::uint64_t value);
std::optional<std::tuple<std::uint64_t, std::uint64_t>> hfma2__v0_nAB(std::uint64_t value);
std::optional<std::tuple<std::uint64_t, std::uint64_t>> hfma2__v2_nAB(std::uint64_t value);
std::optional<std::tuple<std::uint64_t, std::uint64_t>> hmul2__v0_nAB(std::uint64_t value);
std::optional<std::tuple<std::uint64_t, std::uint64_t>> hmul2__v2_nAB(std::uint64_t value);

} // namespace Maxwell