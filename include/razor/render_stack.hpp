#pragma once

#include "razor/export.hpp"
#include "razor/renderer.hpp"
#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

namespace passionfruit::razor {

using renderer = std::function<int(int)>;

struct RAZOR_EXPORT render_stack {
    std::vector<renderer> stack;

    auto render(int target) {
        // std::invoke(Callable &&fn, Args &&args...)
        int x = target;
        for(auto& s: stack) {
            x = s(x);
        }
    }
};

} // namespace passionfruit::razor