#pragma once

#include <echidna/echidna.hpp>
#include <nonstd/expected.hpp>
#include <seed/seed.hpp>

#include <razor/export.hpp>

namespace passionfruit::razor {

struct RAZOR_EXPORT context_creation_error {};

struct RAZOR_EXPORT render_context {
    echidna::instance instance;
    echidna::adapter adapter;
    echidna::device device;
    echidna::surface surface;
    echidna::queue queue;

    static auto create(const seed::window* window) -> nonstd::expected<render_context, context_creation_error>;
};

} // namespace passionfruit::razor