#include <doctest/doctest.h>

#include <algorithm> // for fill_n
#include <ecgen/combin.hpp>
#include <ecgen/gray_code.hpp>
#include <string>
#include <vector>

TEST_CASE("Generate Gray code by brgc_gen (odd)") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::brgc_gen(5)) {
        ++cnt;
    }
    CHECK_EQ(cnt, 32);
}

TEST_CASE("Generate Gray code by brgc_gen (even)") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::brgc_gen(6)) {
        ++cnt;
    }
    CHECK_EQ(cnt, 64);
}

TEST_CASE("Generate all combinations by emk_gen (odd, odd)") {
    constexpr int N = 15;
    constexpr int K = 5;
    size_t cnt = 1;
    for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(N, K)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<N, K>());
}

TEST_CASE("Generate all combinations by emk_gen (odd, even)") {
    constexpr int N = 15;
    constexpr int K = 6;
    size_t cnt = 1;
    for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(N, K)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<N, K>());
}

TEST_CASE("Generate all combinations by emk_gen (even, odd)") {
    constexpr int N = 16;
    constexpr int K = 5;
    size_t cnt = 1;
    for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(N, K)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<N, K>());
}

TEST_CASE("Generate all combinations by emk_gen (even, even)") {
    constexpr int N = 16;
    constexpr int K = 6;
    size_t cnt = 1;
    for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(N, K)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<N, K>());
}

TEST_CASE("Generate all combinations by emk_gen (special, even)") {
    constexpr int N = 6;
    constexpr int K = 6;
    size_t cnt = 1;
    for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(N, K)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<N, K>());
}

TEST_CASE("Generate all combinations by emk_gen (special, odd)") {
    constexpr int N = 5;
    constexpr int K = 5;
    size_t cnt = 1;
    for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(N, K)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<N, K>());
}

TEST_CASE("Generate Gray code (odd)") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto &l : ecgen::brgc<std::vector<bool>>(5)) {
        ++cnt;
    }
    CHECK_EQ(cnt, 32);
}

TEST_CASE("Generate Gray code (even)") {
    size_t cnt = 0;
    for ([[maybe_unused]] auto &l : ecgen::brgc<std::vector<int>>(6)) {
        ++cnt;
    }
    CHECK_EQ(cnt, 64);
}

TEST_CASE("Generate all combinations (odd)") {
    size_t cnt = 0;
    auto S = std::string("11100");
    for ([[maybe_unused]] auto &s : ecgen::emk(5, 3, S)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<5, 3>());
}

TEST_CASE("Generate all combinations (even)") {
    constexpr int N = 6;
    constexpr int K = 3;
    size_t cnt = 0;
    auto lst = std::vector<int>(N, 0);
    std::fill_n(lst.begin(), K, 1);
    for ([[maybe_unused]] auto &l : ecgen::emk(N, K, lst)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Combination<N, K>());
}
