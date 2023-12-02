#include <algorithm> // for fill_n
#include <ecgen/combin.hpp>
#include <ecgen/combin_old.hpp>
#include <ecgen/gray_code.hpp>
#include <string>
#include <vector>

#include "benchmark/benchmark.h" // for BENCHMARK, State, BENCHMARK_...

/**
 * @brief
 *
 * @param[in,out] state
 */
static void EMK_new(benchmark::State &state) {
    constexpr size_t N = 16;
    constexpr size_t K = 5;
    while (state.KeepRunning()) {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::EMK_comb_gen(N, K)) {
            ++cnt;
        }
        benchmark::DoNotOptimize(cnt);
    }
}

// Register the function as a benchmark
BENCHMARK(EMK_new);

//~~~~~~~~~~~~~~~~

/**
 * @brief Define another benchmark
 *
 * @param[in,out] state
 */
static void EMK_old(benchmark::State &state) {
    constexpr size_t N = 16;
    constexpr size_t K = 5;
    while (state.KeepRunning()) {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::EMK_gen(N, K)) {
            ++cnt;
        }
        benchmark::DoNotOptimize(cnt);
    }
}
BENCHMARK(EMK_old);

BENCHMARK_MAIN();

/*
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
EMK_new         131235 ns       131245 ns         4447
EMK_old          196694 ns       196708 ns         3548
EMK_No_Trick     129743 ns       129750 ns         5357
*/
