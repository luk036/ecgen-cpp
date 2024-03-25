#include <ecgen/combin.hpp>
#include <ecgen/combin_old.hpp>

#include "benchmark/benchmark.h" // for BENCHMARK, State, BENCHMARK_...

/**
 * The function `emk_new` generates combinations of size K from a set of size N
 * and measures its performance using Google Benchmark.
 *
 * @param state The `state` parameter in the `emk_new` function is of type
 * `benchmark::State &`. It is used to control the benchmark execution and
 * provide information about the benchmark state, such as the number of
 * iterations to run, the elapsed time, and other benchmark-related data.
 */
static void emk_new(benchmark::State &state) {
    constexpr int N = 16;
    constexpr int K = 5;
    while (state.KeepRunning()) {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(N, K)) {
            ++cnt;
        }
        benchmark::DoNotOptimize(cnt);
    }
}

// Register the function as a benchmark
BENCHMARK(emk_new);

//~~~~~~~~~~~~~~~~

/**
 * The function `emk_old` generates combinations of size K from a set of size N
 * and measures its performance using Google Benchmark.
 *
 * @param state The `state` parameter in the `emk_new` function is of type
 * `benchmark::State &`. It is used to control the benchmark execution and
 * provide information about the benchmark state, such as the number of
 * iterations to run, the elapsed time, and other benchmark-related data.
 */
static void emk_old(benchmark::State &state) {
    constexpr int N = 16;
    constexpr int K = 5;
    while (state.KeepRunning()) {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::emk_gen(N, K)) {
            ++cnt;
        }
        benchmark::DoNotOptimize(cnt);
    }
}
BENCHMARK(emk_old);

BENCHMARK_MAIN();

/*
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
emk_new         131235 ns       131245 ns         4447
emk_old          196694 ns       196708 ns         3548
emk_No_Trick     129743 ns       129750 ns         5357
*/
