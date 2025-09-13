#include <doctest/doctest.h>

#include <ecgen/combin.hpp>
#include <ecgen/combin_old.hpp>
#include <string>
#include <vector>

TEST_CASE("Generate all combinations by emk_gen") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto i : ecgen::emk_gen(5, 3)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<5, 3>()() - 1);
}

TEST_CASE("Generate all combinations by emk_neg") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto i : ecgen::emk_neg(5, 3)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<5, 3>()() - 1);
}
