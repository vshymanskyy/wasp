//
// Copyright 2018 WebAssembly Community Group participants
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

#include "wasp/binary/instruction.h"

namespace wasp {
namespace binary {

Instruction::Instruction(Opcode opcode)
    : opcode(opcode), immediate(EmptyImmediate{}) {}

Instruction::Instruction(Opcode opcode, EmptyImmediate immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, BlockType immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, Index immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, CallIndirectImmediate immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, BrTableImmediate immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, u8 immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, MemArgImmediate immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, s32 immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, s64 immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, f32 immediate)
    : opcode(opcode), immediate(immediate) {}

Instruction::Instruction(Opcode opcode, f64 immediate)
    : opcode(opcode), immediate(immediate) {}

#define WASP_OPERATOR_EQ_NE_0(Name)                                  \
  bool operator==(const Name& lhs, const Name& rhs) { return true; } \
  bool operator!=(const Name& lhs, const Name& rhs) { return false; }

#define WASP_OPERATOR_EQ_NE_2(Name, f1, f2)           \
  bool operator==(const Name& lhs, const Name& rhs) { \
    return lhs.f1 == rhs.f1 && lhs.f2 == rhs.f2;      \
  }                                                   \
  bool operator!=(const Name& lhs, const Name& rhs) { return !(lhs == rhs); }

WASP_OPERATOR_EQ_NE_2(MemArgImmediate, align_log2, offset)
WASP_OPERATOR_EQ_NE_0(EmptyImmediate)
WASP_OPERATOR_EQ_NE_2(CallIndirectImmediate, index, reserved)
WASP_OPERATOR_EQ_NE_2(BrTableImmediate, targets, default_target)
WASP_OPERATOR_EQ_NE_2(Instruction, opcode, immediate)

#undef WASP_OPERATOR_EQ_NE_0
#undef WASP_OPERATOR_EQ_NE_2

}  // namespace binary
}  // namespace wasp
