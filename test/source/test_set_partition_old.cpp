#include <doctest/doctest.h>

#include <ecgen/set_partition.hpp>
#include <ecgen/set_partition_old.hpp>

TEST_CASE("set partition old odd odd") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen_old(5, 3)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd<5, 3>()());
}

TEST_CASE("set partition old even odd") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen_old(4, 3)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd<4, 3>()());
}

TEST_CASE("set partition old even k") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen_old(4, 2)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd<4, 2>()());

    size_t cnt2 = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen_old(6, 2)) {
        ++cnt2;
    }
    CHECK_EQ(cnt2, ecgen::Stirling2nd<6, 2>()());

    size_t cnt4 = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen_old(6, 4)) {
        ++cnt4;
    }
    CHECK_EQ(cnt4, ecgen::Stirling2nd<6, 4>()());
}

TEST_CASE("set partition old degenerate k") {
    // k >= n or k <= 0 produces no moves: only the initial partition remains
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen_old(4, 4)) {
        ++cnt;
    }
    CHECK_EQ(cnt, 1);
}
