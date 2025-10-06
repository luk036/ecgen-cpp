#include <doctest/doctest.h>

#include <ecgen/combin.hpp>
#include <vector>

TEST_CASE("Test emk: k=0") {
    auto V = std::vector<int>{1, 2, 3, 4};
    auto g = ecgen::emk(4, 0, V);
    size_t count = 0;
    for (const auto& combination : g) {
        CHECK(combination == std::vector<int>{1, 2, 3, 4});
        count++;
    }
    CHECK(count == ecgen::Combination<4, 0>());
}

TEST_CASE("Test emk: k>n") {
    auto V = std::vector<int>{1, 2, 3};
    auto g = ecgen::emk(3, 4, V);
    size_t count = 0;
    for (const auto& combination : g) {
        CHECK(combination == std::vector<int>{1, 2, 3});
        count++;
    }
    CHECK(count == ecgen::Combination<3, 4>());
}

TEST_CASE("Test emk: k=n") {
    auto V = std::vector<int>{1, 2, 3};
    auto g = ecgen::emk(3, 3, V);
    size_t count = 0;
    for (const auto& combination : g) {
        CHECK(combination == std::vector<int>{1, 2, 3});
        count++;
    }
    CHECK(count == ecgen::Combination<3, 3>());
}

TEST_CASE("Test emk: n=0, k=0") {
    auto V = std::vector<int>{};
    auto g = ecgen::emk(0, 0, V);
    size_t count = 0;
    for (const auto& combination : g) {
        CHECK(combination.empty());
        count++;
    }
    CHECK(count == ecgen::Combination<0, 0>());
}