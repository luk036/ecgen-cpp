// #include <algorithm> // for fill_n
#include <ecgen/set_partition.hpp>
#include <ecgen/set_partition_old.hpp>

#include "benchmark/benchmark.h"  // for BENCHMARK, State, BENCHMARK_...

/**
 * @brief
 *
 * @param[in,out] state
 */
static void set_partition_new(benchmark::State &state) {
    constexpr int N = 14;
    constexpr int K = 3;
    while (state.KeepRunning()) {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::set_partition_gen(N, K)) {
            ++cnt;
        }
        benchmark::DoNotOptimize(cnt);
    }
}

// Register the function as a benchmark
BENCHMARK(set_partition_new);

//~~~~~~~~~~~~~~~~

/**
 * @brief Define another benchmark
 *
 * @param[in,out] state
 */
static void set_partition_old(benchmark::State &state) {
    constexpr size_t N = 14;
    constexpr size_t K = 3;
    while (state.KeepRunning()) {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::set_partition_gen_old(N, K)) {
            ++cnt;
        }
        benchmark::DoNotOptimize(cnt);
    }
}
BENCHMARK(set_partition_old);

BENCHMARK_MAIN();

/*
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
set_partition_new         131235 ns       131245 ns         4447
set_partition_old          196694 ns       196708 ns         3548
set_partition_No_Trick     129743 ns       129750 ns         5357
*/
