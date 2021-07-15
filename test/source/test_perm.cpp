#include <doctest/doctest.h>

#include <ecgen/perm.hpp>

TEST_CASE("Generate all permutations by SJT algorithm (odd)") {
    int cnt = 0;  // start from 0
    for ([[maybe_unused]] auto i : ecgen::SJT_gen(5)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by SJT algorithm (even)") {
    int cnt = 0;  // start from 0
    for ([[maybe_unused]] auto i : ecgen::SJT_gen(6)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<6>());
}

TEST_CASE("Generate all permutations by Ehr algorithm (odd)") {
    int cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::Ehr_gen(5)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by Ehr algorithm (even)") {
    int cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::Ehr_gen(6)) {
        ++cnt;
    }
    CHECK(cnt == ecgen::Factorial<6>());
}
