// #include <algorithm> // for fill_n
#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <ecgen/set_partition.hpp>
#include <ecgen/set_partition_old.hpp>

int main() {
    constexpr int N = 14;
    constexpr int K = 3;

    ankerl::nanobench::Bench bench;
    bench.title("Set Partition").unit("op").warmup(100).epochs(50);

    bench.run("set_partition_new", [&] {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::set_partition_gen(N, K)) {
            ++cnt;
        }
        ankerl::nanobench::doNotOptimizeAway(cnt);
    });

    bench.run("set_partition_old", [&] {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::set_partition_gen_old(N, K)) {
            ++cnt;
        }
        ankerl::nanobench::doNotOptimizeAway(cnt);
    });
}

/*
  |               ns/op |                op/s |    err% |          ins/op |          bra/op | miss%
  |     total | benchmark
  |--------------------:|--------------------:|--------:|----------------:|----------------:|--------:|----------:|:----------
  |             131,235 |             7,619.5 |    1.2% |      30,755,982 |       1,554,724 | 0.1% |
  0.01 | `set_partition_new` |             196,694 |             5,084.0 |    0.9% |      46,349,808
  |       2,342,252 |    0.1% |      0.01 | `set_partition_old`
*/
