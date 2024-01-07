// #include <algorithm> // for fill_n
#include <ecgen/combin.hpp>
#include <ecgen/combin_old.hpp>

#include "benchmark/benchmark.h" // for BENCHMARK, State, BENCHMARK_...

/**
 * @brief
 *
 * @param[in,out] state
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
 * @brief Define another benchmark
 *
 * @param[in,out] state
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
