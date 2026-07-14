#include <doctest/doctest.h>

#include <ecgen/perm.hpp>
#include <ecgen/perm_old.hpp>

TEST_CASE("Generate all permutations by sjt2 (odd)") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto& p : ecgen::sjt2(5)) {
        CHECK_EQ(p.size(), 5);
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by sjt2 (even)") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto& p : ecgen::sjt2(6)) {
        CHECK_EQ(p.size(), 6);
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Factorial<6>());
}

TEST_CASE("sjt2 base case n=2") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto& p : ecgen::sjt2(2)) {
        ++cnt;
    }
    CHECK_EQ(cnt, 2);
}
