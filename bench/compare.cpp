#include <chrono>
#include <ecgen/combin.hpp>
#include <ecgen/gray_code.hpp>
#include <ecgen/perm.hpp>
#include <ecgen/set_bipart.hpp>
#include <ecgen/set_partition.hpp>
#include <fmt/format.h>

template <typename F> void bench(const char* name, F&& f) {
    auto start = std::chrono::steady_clock::now();
    auto result = f();
    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration<double, std::milli>(end - start).count();
    fmt::print("{:<30} {:10}  {:8.3f} ms\n", name, result, ms);
}

int main() {
    fmt::print("{:<30} {:10}  {:10}\n", "Operation", "Count", "Time");
    for (int i = 0; i < 70; ++i) fmt::print("-");
    fmt::print("\n");

    // EMK combinations
    bench("emk_comb_gen(16,5)", []() {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(16, 5)) ++cnt;
        return cnt;
    });
    bench("emk_comb_gen(10,5)", []() {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::emk_comb_gen(10, 5)) ++cnt;
        return cnt;
    });

    // SJT permutations
    bench("sjt_gen(8)", []() {
        size_t cnt = 0;
        for ([[maybe_unused]] auto idx : ecgen::sjt_gen(8)) ++cnt;
        return cnt;
    });
    bench("sjt_gen(7)", []() {
        size_t cnt = 0;
        for ([[maybe_unused]] auto idx : ecgen::sjt_gen(7)) ++cnt;
        return cnt;
    });
    bench("sjt_gen(5)", []() {
        size_t cnt = 0;
        for ([[maybe_unused]] auto idx : ecgen::sjt_gen(5)) ++cnt;
        return cnt;
    });

    // Ehrlich permutations
    bench("ehr_gen(8)", []() {
        size_t cnt = 1;
        for ([[maybe_unused]] auto idx : ecgen::ehr_gen(8)) ++cnt;
        return cnt;
    });

    // BRGC
    bench("brgc_gen(12)", []() {
        size_t cnt = 0;
        for ([[maybe_unused]] auto idx : ecgen::brgc_gen(12)) ++cnt;
        return cnt;
    });
    bench("brgc_gen(8)", []() {
        size_t cnt = 0;
        for ([[maybe_unused]] auto idx : ecgen::brgc_gen(8)) ++cnt;
        return cnt;
    });

    // Set partition
    bench("set_partition_gen(11,5)", []() {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::set_partition_gen(11, 5)) ++cnt;
        return cnt;
    });
    bench("set_partition_gen(8,4)", []() {
        size_t cnt = 1;
        for ([[maybe_unused]] auto [x, y] : ecgen::set_partition_gen(8, 4)) ++cnt;
        return cnt;
    });

    // Set bipartition
    bench("set_bipart_gen(15)", []() {
        size_t cnt = 1;
        for ([[maybe_unused]] auto x : ecgen::set_bipart_gen(15)) ++cnt;
        return cnt;
    });
    bench("set_bipart_gen(10)", []() {
        size_t cnt = 1;
        for ([[maybe_unused]] auto x : ecgen::set_bipart_gen(10)) ++cnt;
        return cnt;
    });
}
