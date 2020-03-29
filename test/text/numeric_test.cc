//
// Copyright 2020 WebAssembly Community Group participants
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "wasp/text/numeric.h"

#include "gtest/gtest.h"

using namespace ::wasp;
using namespace ::wasp::text;

// Make SpanU8 from literal string.
inline SpanU8 operator"" _su8(const char* str, size_t N) {
  return SpanU8{reinterpret_cast<const u8*>(str),
                static_cast<SpanU8::index_type>(N)};
}

TEST(NumericTest, StrToNat_u8) {
  struct {
    SpanU8 span;
    LiteralKind kind;
    u8 value;
  } tests[] = {
      {"0"_su8, LiteralKind::Int, 0},
      {"1"_su8, LiteralKind::Int, 1},
      {"29"_su8, LiteralKind::Int, 29},
      {"38"_su8, LiteralKind::Int, 38},
      {"167"_su8, LiteralKind::Int, 167},
      {"245"_su8, LiteralKind::Int, 245},
      {"255"_su8, LiteralKind::Int, 255},
      {"0_1_2"_su8, LiteralKind::Int, 12},
      {"1_34"_su8, LiteralKind::Int, 134},
      {"24_8"_su8, LiteralKind::Int, 248},

      {"0x1"_su8, LiteralKind::HexInt, 0x01},
      {"0x23"_su8, LiteralKind::HexInt, 0x23},
      {"0x45"_su8, LiteralKind::HexInt, 0x45},
      {"0x67"_su8, LiteralKind::HexInt, 0x67},
      {"0x89"_su8, LiteralKind::HexInt, 0x89},
      {"0xAb"_su8, LiteralKind::HexInt, 0xab},
      {"0xcD"_su8, LiteralKind::HexInt, 0xcd},
      {"0xEf"_su8, LiteralKind::HexInt, 0xef},
      {"0xff"_su8, LiteralKind::HexInt, 0xff},
      {"0x0_0_0_0"_su8, LiteralKind::HexInt, 0},
      {"0x0_1_1"_su8, LiteralKind::HexInt, 17},
      {"0xf_f"_su8, LiteralKind::HexInt, 255},
  };
  for (auto test : tests) {
    EXPECT_EQ(test.value, StrToNat<u8>(test.kind, test.span));
  }
}

TEST(NumericTest, StrToNat_u16) {
  struct {
    SpanU8 span;
    LiteralKind kind;
    u16 value;
  } tests[] = {
      {"0"_su8, LiteralKind::Int, 0},
      {"1"_su8, LiteralKind::Int, 1},
      {"23"_su8, LiteralKind::Int, 23},
      {"345"_su8, LiteralKind::Int, 345},
      {"4567"_su8, LiteralKind::Int, 4567},
      {"56789"_su8, LiteralKind::Int, 56789},
      {"65535"_su8, LiteralKind::Int, 65535},
      {"0_0"_su8, LiteralKind::Int, 0},
      {"0_0_1"_su8, LiteralKind::Int, 1},
      {"2_3"_su8, LiteralKind::Int, 23},
      {"34_5"_su8, LiteralKind::Int, 345},
      {"4_5_6_7"_su8, LiteralKind::Int, 4567},
      {"5678_9"_su8, LiteralKind::Int, 56789},

      {"0x12"_su8, LiteralKind::HexInt, 0x12},
      {"0x345"_su8, LiteralKind::HexInt, 0x345},
      {"0x6789"_su8, LiteralKind::HexInt, 0x6789},
      {"0xAbcD"_su8, LiteralKind::HexInt, 0xabcd},
      {"0xEf01"_su8, LiteralKind::HexInt, 0xef01},
      {"0x0_1_2"_su8, LiteralKind::HexInt, 0x12},
      {"0x34_5"_su8, LiteralKind::HexInt, 0x345},
      {"0x6_78_9"_su8, LiteralKind::HexInt, 0x6789},
      {"0xaB_cD"_su8, LiteralKind::HexInt, 0xabcd},
      {"0xe_F_01"_su8, LiteralKind::HexInt, 0xef01},
  };
  for (auto test : tests) {
    EXPECT_EQ(test.value, StrToNat<u16>(test.kind, test.span));
  }
}

TEST(NumericTest, StrToNat_u32) {
  struct {
    SpanU8 span;
    LiteralKind kind;
    u32 value;
  } tests[] = {
      {"0"_su8, LiteralKind::Int, 0},
      {"12"_su8, LiteralKind::Int, 12},
      {"2345"_su8, LiteralKind::Int, 2345},
      {"345678"_su8, LiteralKind::Int, 345678},
      {"45678901"_su8, LiteralKind::Int, 45678901},
      {"3456789012"_su8, LiteralKind::Int, 3456789012},
      {"4294967295"_su8, LiteralKind::Int, 4294967295},
      {"1_2"_su8, LiteralKind::Int, 12},
      {"2_34_5"_su8, LiteralKind::Int, 2345},
      {"34_56_78"_su8, LiteralKind::Int, 345678},
      {"4567_8901"_su8, LiteralKind::Int, 45678901},
      {"345_6_789_012"_su8, LiteralKind::Int, 3456789012},
      {"4_294_967_295"_su8, LiteralKind::Int, 4294967295},

      {"0x123"_su8, LiteralKind::HexInt, 0x123},
      {"0x234567"_su8, LiteralKind::HexInt, 0x234567},
      {"0x3456789a"_su8, LiteralKind::HexInt, 0x3456789a},
      {"0x89abcdef"_su8, LiteralKind::HexInt, 0x89abcdef},
      {"0xffffffff"_su8, LiteralKind::HexInt, 0xffffffff},
      {"0x1_23"_su8, LiteralKind::HexInt, 0x123},
      {"0x23_45_67"_su8, LiteralKind::HexInt, 0x234567},
      {"0x345_678_9a"_su8, LiteralKind::HexInt, 0x3456789a},
      {"0x8_9ab_cdef"_su8, LiteralKind::HexInt, 0x89abcdef},
      {"0xff_ff_ff_ff"_su8, LiteralKind::HexInt, 0xffffffff},
  };
  for (auto test : tests) {
    EXPECT_EQ(test.value, StrToNat<u32>(test.kind, test.span));
  }
}

TEST(NumericTest, StrToInt_s32) {
  struct {
    SpanU8 span;
    LiteralKind kind;
    s32 value;
  } tests[] = {
      {"0"_su8, LiteralKind::Int, 0},
      {"12"_su8, LiteralKind::Int, 12},
      {"2345"_su8, LiteralKind::Int, 2345},
      {"345678"_su8, LiteralKind::Int, 345678},
      {"45678901"_su8, LiteralKind::Int, 45678901},
      {"2147483647"_su8, LiteralKind::Int, 2147483647},
      {"1_2"_su8, LiteralKind::Int, 12},
      {"2_34_5"_su8, LiteralKind::Int, 2345},
      {"34_56_78"_su8, LiteralKind::Int, 345678},
      {"4567_8901"_su8, LiteralKind::Int, 45678901},
      {"2_147_483_647"_su8, LiteralKind::Int, 2147483647},

      {"+0"_su8, LiteralKind::Int, 0},
      {"+12"_su8, LiteralKind::Int, 12},
      {"+2345"_su8, LiteralKind::Int, 2345},
      {"+345678"_su8, LiteralKind::Int, 345678},
      {"+45678901"_su8, LiteralKind::Int, 45678901},
      {"+2147483647"_su8, LiteralKind::Int, 2147483647},
      {"+1_2"_su8, LiteralKind::Int, 12},
      {"+2_34_5"_su8, LiteralKind::Int, 2345},
      {"+34_56_78"_su8, LiteralKind::Int, 345678},
      {"+4567_8901"_su8, LiteralKind::Int, 45678901},
      {"+2_147_483_647"_su8, LiteralKind::Int, 2147483647},

      {"-0"_su8, LiteralKind::Int, 0},
      {"-12"_su8, LiteralKind::Int, -12},
      {"-2345"_su8, LiteralKind::Int, -2345},
      {"-345678"_su8, LiteralKind::Int, -345678},
      {"-45678901"_su8, LiteralKind::Int, -45678901},
      {"-2147483648"_su8, LiteralKind::Int, -2147483648},
      {"-1_2"_su8, LiteralKind::Int, -12},
      {"-2_34_5"_su8, LiteralKind::Int, -2345},
      {"-34_56_78"_su8, LiteralKind::Int, -345678},
      {"-4567_8901"_su8, LiteralKind::Int, -45678901},
      {"-2_147_483_648"_su8, LiteralKind::Int, -2147483648},

      {"0x123"_su8, LiteralKind::HexInt, 0x123},
      {"0x234567"_su8, LiteralKind::HexInt, 0x234567},
      {"0x3456789a"_su8, LiteralKind::HexInt, 0x3456789a},
      {"0x789abcde"_su8, LiteralKind::HexInt, 0x789abcde},
      {"0x7fffffff"_su8, LiteralKind::HexInt, 0x7fffffff},
      {"0x1_23"_su8, LiteralKind::HexInt, 0x123},
      {"0x23_45_67"_su8, LiteralKind::HexInt, 0x234567},
      {"0x345_678_9a"_su8, LiteralKind::HexInt, 0x3456789a},
      {"0x7_89a_bcde"_su8, LiteralKind::HexInt, 0x789abcde},
      {"0x7f_ff_ff_ff"_su8, LiteralKind::HexInt, 0x7fffffff},

      {"+0x123"_su8, LiteralKind::HexInt, 0x123},
      {"+0x234567"_su8, LiteralKind::HexInt, 0x234567},
      {"+0x3456789a"_su8, LiteralKind::HexInt, 0x3456789a},
      {"+0x789abcde"_su8, LiteralKind::HexInt, 0x789abcde},
      {"+0x7fffffff"_su8, LiteralKind::HexInt, 0x7fffffff},
      {"+0x1_23"_su8, LiteralKind::HexInt, 0x123},
      {"+0x23_45_67"_su8, LiteralKind::HexInt, 0x234567},
      {"+0x345_678_9a"_su8, LiteralKind::HexInt, 0x3456789a},
      {"+0x7_89a_bcde"_su8, LiteralKind::HexInt, 0x789abcde},
      {"+0x7f_ff_ff_ff"_su8, LiteralKind::HexInt, 0x7fffffff},

      {"-0x123"_su8, LiteralKind::HexInt, -0x123},
      {"-0x234567"_su8, LiteralKind::HexInt, -0x234567},
      {"-0x3456789a"_su8, LiteralKind::HexInt, -0x3456789a},
      {"-0x789abcde"_su8, LiteralKind::HexInt, -0x789abcde},
      {"-0x80000000"_su8, LiteralKind::HexInt, -0x80000000},
      {"-0x1_23"_su8, LiteralKind::HexInt, -0x123},
      {"-0x23_45_67"_su8, LiteralKind::HexInt, -0x234567},
      {"-0x345_678_9a"_su8, LiteralKind::HexInt, -0x3456789a},
      {"-0x7_89a_bcde"_su8, LiteralKind::HexInt, -0x789abcde},
      {"-0x80_00_00_00"_su8, LiteralKind::HexInt, -0x80000000},
  };
  for (auto test : tests) {
    EXPECT_EQ(test.value, StrToInt<s32>(test.kind, test.span));
  }
}
