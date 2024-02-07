#include <snitch/snitch.hpp>
#include <passionfruit/razor.hpp>

TEST_CASE("Test case", "[greeting]") {
    REQUIRE(passionfruit::get_version() == 1);
}