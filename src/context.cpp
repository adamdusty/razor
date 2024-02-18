#include "razor/context.hpp"

#include <bit>
#include <echidna/echidna.hpp>
#include <variant>
#include <webgpu.h>

using nonstd::expected;
using nonstd::make_unexpected;

namespace passionfruit::razor {

struct window_visitor {
    auto operator()(const seed::hwnd& win) -> WGPUSurfaceDescriptor {
        auto sd = echidna::surface_descriptor_from_windows_hwnd(win.hinstance, win.hwnd);
        return echidna::surface_descriptor(*std::bit_cast<WGPUChainedStruct*>(&sd), nullptr);
    }
    auto operator()(const auto& /* window */) -> WGPUSurfaceDescriptor { throw; }
};

auto render_context::create(const seed::window& window) -> expected<render_context, context_creation_error> {
    auto instance = echidna::instance{};
    auto surface  = echidna::surface{};
    auto adapter  = echidna::adapter{};
    auto device   = echidna::device{};
    auto queue    = echidna::queue{};

    // Create instance
    instance = echidna::instance::create();
    if(!instance) {
        return make_unexpected(context_creation_error{
            .type = context_creation_error::type::create_instance_error,
            .msg  = "Unable to create instance",
        });
    }

    // Create surface
    if(auto raw = window.platform_window()) {
        auto surf_desc = std::visit(window_visitor{}, *raw);
        surface        = instance.create_surface(surf_desc);
    } else {
        return nonstd::make_unexpected(
            context_creation_error{.type = context_creation_error::type::create_surface_error,
                                   .msg  = "Unable to create surface from instance."});
    }

    // Create adapter
    // TODO: Allow user to pass options for adapter
    auto adapter_options = echidna::adapter_options(surface);
    adapter              = instance.request_adapter(adapter_options);

    // Create device
    // TODO: Determine if caller needs to be able to specify device features
    auto device_descriptor = echidna::device_descriptor();
    device                 = adapter.request_device(device_descriptor);
    device.set_uncaptured_error_callback(echidna::device_error_stderr);

    // Create queue
    queue = device.get_queue();

    auto surface_config = echidna::surface_configuration(
        device, surface.preferred_format(adapter), window.size().first, window.size().second);
    surface.configure(surface_config);

    return render_context{
        .instance = std::move(instance),
        .surface  = std::move(surface),
        .adapter  = std::move(adapter),
        .device   = std::move(device),
        .queue    = std::move(queue),
    };
}

} // namespace passionfruit::razor