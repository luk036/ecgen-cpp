#include <doctest/doctest.h>

#include <ecgen/perm.hpp>
#include <string>
#include <vector>

TEST_CASE("Generate all permutations by sjt_gen (odd)") {
    size_t cnt = 0;  // start from 0
    for ([[maybe_unused]] auto idx : ecgen::sjt_gen(5)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by sjt_gen (even)") {
    size_t cnt = 0;  // start from 0
    for ([[maybe_unused]] auto idx : ecgen::sjt_gen(6)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Factorial<6>());
}

TEST_CASE("Generate all permutations by ehr algorithm (odd)") {
    size_t cnt = 1;
    auto perm = std::vector{1, 3, 5, 7, 9};
    for (auto idx : ecgen::ehr_gen(5)) {
        ++cnt;
        std::swap(perm[0], perm[static_cast<std::vector<int>::size_type>(idx)]);
    }
    CHECK_EQ(cnt, ecgen::Factorial<5>());
    auto lst = std::vector{9, 7, 3, 5, 1};
    CHECK_EQ(perm, lst);
}

TEST_CASE("Generate all permutations by ehr algorithm (even)") {
    size_t cnt = 1;
    auto lst = std::vector{1, 3, 5, 7, 9, 11};
    auto perm = lst;
    for (auto idx : ecgen::ehr_gen(6)) {
        ++cnt;
        std::swap(perm[0], perm[static_cast<std::vector<int>::size_type>(idx)]);
    }
    std::swap(perm[0], perm[5]);
    CHECK_EQ(cnt, ecgen::Factorial<6>());
    CHECK_EQ(perm, lst);
}

TEST_CASE("Generate all permutations by sjt (odd)") {
    auto cnt = 0;  // start from 0
    auto L = std::vector{1, 3, 5, 7, 9};
    for ([[maybe_unused]] auto &l : ecgen::sjt(L)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Factorial<5>());
}

TEST_CASE("Generate all permutations by sjt (even)") {
    auto cnt = 0;  // start from 0
    auto S = std::string("ABCDEF");
    for ([[maybe_unused]] auto &s : ecgen::sjt(S)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Factorial<6>());
}

