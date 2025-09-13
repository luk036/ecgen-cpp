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
