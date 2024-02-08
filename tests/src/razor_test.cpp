#include <razor/razor.hpp>
#include <snitch/snitch.hpp>

TEST_CASE("Test case", "[greeting]") {
    REQUIRE(passionfruit::razor::get_version() == 1);
}