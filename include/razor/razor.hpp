#pragma once

#include <cstdint>
#include <echidna/echidna.hpp>

namespace passionfruit::razor {
auto get_version() -> std::uint64_t;
}