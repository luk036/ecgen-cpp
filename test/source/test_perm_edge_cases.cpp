#include <doctest/doctest.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <ecgen/perm.hpp>
#include <vector>

TEST_CASE("Test sjt: n=3, check sequence") {
    auto p = std::vector<int>{1, 2, 3};
    auto g = ecgen::sjt(p);
    std::vector<std::vector<int>> actual_sequence;
    for (const auto& v : g) {
        actual_sequence.push_back(v);
    }

    std::vector<std::vector<int>> expected_sequence = {
        {1, 2, 3}, {1, 3, 2}, {3, 1, 2},
        {3, 2, 1}, {2, 3, 1}, {2, 1, 3}
    };

    INFO("Actual sequence: ", fmt::format("{}", fmt::join(actual_sequence, ", ")));
    INFO("Expected sequence: ", fmt::format("{}", fmt::join(expected_sequence, ", ")));
    CHECK(actual_sequence == expected_sequence);
}