#pragma once

#include <echidna/echidna.hpp>
#include <nonstd/expected.hpp>
#include <seed/seed.hpp>

#include <razor/export.hpp>

namespace passionfruit::razor {

struct RAZOR_EXPORT context_creation_error {
    enum class type {
        create_instance_error,
        create_surface_error,
    };

    type type;
    std::string msg;
};

struct RAZOR_EXPORT render_context {
    echidna::instance instance;
    echidna::surface surface;
    echidna::adapter adapter;
    echidna::device device;
    echidna::queue queue;

    static auto create(const seed::window& window) -> nonstd::expected<render_context, context_creation_error>;
};

} // namespace passionfruit::razor