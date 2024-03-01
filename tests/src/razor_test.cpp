#include <razor/context.hpp>
#include <razor/razor.hpp>
#include <seed/seed.hpp>
#include <snitch/snitch.hpp>

using namespace passionfruit;

TEST_CASE("Create context", "[context]") {
    auto win_opt = seed::window_create_options{
        .title    = "Hello world",
        .width    = 1920,
        .height   = 1080,
        .flags    = seed::window_flags::hidden,
        .position = {seed::window_position::centered},
    };

    auto win = seed::window::create(win_opt);
    REQUIRE(win);

    auto ctx = razor::render_context::create(*win);

    CHECK(ctx);

    CHECK(ctx->instance);
    CHECK(ctx->surface);
    CHECK(ctx->adapter);
    CHECK(ctx->device);
    CHECK(ctx->queue);
}