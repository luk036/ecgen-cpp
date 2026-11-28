#include <doctest/doctest.h>

#include <ecgen/logging.hpp>
#include <string>

// These functions share one global "logger initialized" flag, so the ordering of
// the checks below matters: the first case must run while the flag is still clear.
TEST_CASE("logging: try_init_logger initializes exactly once") {
    CHECK_FALSE(ecgen::is_logger_initialized());

    CHECK(ecgen::try_init_logger_with_filter("debug"));
    CHECK(ecgen::is_logger_initialized());

    // already initialized: both variants are no-ops
    CHECK_FALSE(ecgen::try_init_logger_with_filter("warn"));
    CHECK_FALSE(ecgen::try_init_logger());
}

TEST_CASE("logging: init_logger always re-initializes") {
    ecgen::init_logger();
    CHECK(ecgen::is_logger_initialized());

    // every level string is accepted
    for (auto const& level : {std::string{"trace"}, std::string{"info"}, std::string{"error"}}) {
        ecgen::init_logger_with_filter(level);
        CHECK(ecgen::is_logger_initialized());
    }
}
