#include <doctest/doctest.h>

#include <ecgen/set_bipart.hpp>

TEST_CASE("set bipart odd") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto idx : ecgen::set_bipart_gen(11)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd2<11>());
}

TEST_CASE("set bipart even") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto idx : ecgen::set_bipart_gen(10)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd2<10>());
}

TEST_CASE("set bipart special") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto idx : ecgen::set_bipart_gen(2)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd2<2>());
}
