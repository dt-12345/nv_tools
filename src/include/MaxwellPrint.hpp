#pragma once

#include "MaxwellAccessor.hpp"

#include <optional>
#include <string>
#include <string_view>

namespace Maxwell {

std::string Print(OpClass opclass, const char* opcode, std::uint64_t inst, std::uint64_t sched, std::uint64_t pc);

} // Maxwell