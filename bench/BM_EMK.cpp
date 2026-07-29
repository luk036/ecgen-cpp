#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <ecgen/combin.hpp>
#include <ecgen/combin_old.hpp>

int main() {
    constexpr int N = 16;
    constexpr int K = 5;

    ankerl::nanobench::Bench bench;
    bench.title("EMK Combinations").unit("op").warmup(100).epochs(50);

    bench.run("emk_new", [&] {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(N, K)) {
            ++cnt;
        }
        ankerl::nanobench::doNotOptimizeAway(cnt);
    });

    bench.run("emk_old", [&] {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::emk_gen(N, K)) {
            ++cnt;
        }
        ankerl::nanobench::doNotOptimizeAway(cnt);
    });
}

/*
  |               ns/op |                op/s |    err% |          ins/op |          bra/op |   miss% |     total | benchmark
  |--------------------:|--------------------:|--------:|----------------:|----------------:|--------:|----------:|:----------
  |             131,235 |             7,619.5 |    1.2% |      30,755,982 |       1,554,724 |    0.1% |      0.01 | `emk_new`
  |             196,694 |             5,084.0 |    0.9% |      46,349,808 |       2,342,252 |    0.1% |      0.01 | `emk_old`
*/
