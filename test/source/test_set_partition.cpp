#include <doctest/doctest.h>

#include <ecgen/set_partition.hpp>

TEST_CASE("set partition odd odd") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen(11, 5)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd<11, 5>());
}

TEST_CASE("set partition even odd") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen(10, 5)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd<10, 5>());
}

TEST_CASE("set partition odd even") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen(11, 6)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd<11, 6>());
}

TEST_CASE("set partition even even") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen(10, 6)) {
        ++cnt;
    }
    CHECK_EQ(cnt, ecgen::Stirling2nd<10, 6>());
}

TEST_CASE("set partition special") {
    size_t cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::set_partition_gen(6, 6)) {
        ++cnt;
    }
    CHECK_EQ(cnt, 1);

    for ([[maybe_unused]] auto i : ecgen::set_partition_gen(5, 5)) {
        ++cnt;
    }
    CHECK_EQ(cnt, 1);
}
