#include <doctest/doctest.h>

#include <ecgen/combin.hpp>
#include <ecgen/perm.hpp>
#include <ecgen/gray_code.hpp>
#include <ecgen/set_partition.hpp>
#include <vector>
#include <numeric>

TEST_SUITE("stress tests") {
    TEST_CASE("combinations stress") {
        size_t count = 0;
        std::vector<int> dummy(20);
        for (auto&& c : ecgen::emk(20, 10, dummy)) {
            (void)c;
            count++;
        }
        CHECK(count == 184756);
    }

    TEST_CASE("permutations stress") {
        size_t count = 0;
        std::vector<int> p(10);
        std::iota(p.begin(), p.end(), 0);
        for (auto&& c : ecgen::sjt(p)) {
            (void)c;
            count++;
        }
        CHECK(count == 3628800);
    }

    TEST_CASE("gray code stress") {
        size_t count = 0;
        for (auto&& c : ecgen::brgc<std::vector<int>>(10)) {
            (void)c;
            count++;
        }
        CHECK(count == 1024);
    }

    TEST_CASE("set partition stress") {
        size_t count = 0;
        for (int k = 1; k <= 7; ++k) {
            size_t k_count = 0;
            for (auto&& c : ecgen::set_partition_gen(7, k)) {
                (void)c;
                k_count++;
            }
            count += k_count + 1;
        }
        CHECK(count == 877);
    }
}
