#include "razor/context.hpp"

using nonstd::expected;
using nonstd::make_unexpected;

namespace passionfruit::razor {

auto render_context::create(const seed::window* window) -> expected<render_context, context_creation_error> {
    return make_unexpected(context_creation_error{});
}

} // namespace passionfruit::razor