#include <doctest/doctest.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <ecgen/gray_code.hpp>
#include <vector>

TEST_CASE("Test brgc: n=0") {
    auto g = ecgen::brgc<std::vector<int>>(0);
    auto it = g.begin();
    CHECK(it->empty());
    ++it;
    CHECK(it == g.end());
}

TEST_CASE("Test brgc: n=1") {
    auto g = ecgen::brgc<std::vector<int>>(1);
    std::vector<std::vector<int>> actual_sequence;
    for (const auto& v : g) {
        actual_sequence.push_back(v);
    }
    std::vector<std::vector<int>> expected_sequence = {
        {0}, {1}
    };
    CHECK(actual_sequence == expected_sequence);
}

TEST_CASE("Test brgc: n=3, check sequence") {
    auto g = ecgen::brgc<std::vector<int>>(3);
    std::vector<std::vector<int>> actual_sequence;
    for (const auto& v : g) {
        actual_sequence.push_back(v);
    }

    std::vector<std::vector<int>> expected_sequence = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
        {0, 1, 1}, {1, 1, 1}, {1, 0, 1}, {0, 0, 1}
    };

    INFO("Actual sequence: ", fmt::format("{}", fmt::join(actual_sequence, ", ")));
    INFO("Expected sequence: ", fmt::format("{}", fmt::join(expected_sequence, ", ")));
    CHECK(actual_sequence == expected_sequence);
}