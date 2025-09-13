#include <doctest/doctest.h>

#include <ecgen/combin.hpp>
#include <string>
#include <vector>

TEST_CASE("Generate all combinations by emk_comb_gen") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto i : ecgen::emk_comb_gen(5, 3)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<5, 3>() - 1);
}

TEST_CASE("Generate all combinations by emk") {
    size_t cnt = 0;
    auto S = std::string("ABCDE");
    for ([[maybe_unused]] auto &s : ecgen::emk(5, 3, S)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<5, 3>());
}
