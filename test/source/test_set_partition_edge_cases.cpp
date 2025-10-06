#include <doctest/doctest.h>

#include <ecgen/set_partition.hpp>

TEST_CASE("Test set_partition_gen: k=1") {
    size_t count = 1;
    for ([[maybe_unused]] auto p : ecgen::set_partition_gen(5, 1)) {
        count++;
    }
    CHECK(count == ecgen::Stirling2nd<5, 1>());
}

TEST_CASE("Test set_partition_gen: k=n") {
    size_t count = 1;
    for ([[maybe_unused]] auto p : ecgen::set_partition_gen(5, 5)) {
        count++;
    }
    CHECK(count == ecgen::Stirling2nd<5, 5>());
}

TEST_CASE("Test set_partition_gen: k>n") {
    size_t count = 1;
    for ([[maybe_unused]] auto p : ecgen::set_partition_gen(5, 6)) {
        count++;
    }
    CHECK(count == ecgen::Stirling2nd<5, 6>());
}

TEST_CASE("Test set_partition_gen: n=0, k=0") {
    size_t count = 1;
    for ([[maybe_unused]] auto p : ecgen::set_partition_gen(0, 0)) {
        count++;
    }
    CHECK(count == ecgen::Stirling2nd<0, 0>());
}
