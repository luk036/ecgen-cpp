#include <fmt/format.h>

#include <ecgen/combin.hpp>
#include <ecgen/combin_old.hpp>
#include <ecgen/set_partition.hpp>
#include <ecgen/set_partition_old.hpp>

template <typename G1, typename G2> void check_count(const char* name, G1&& gen1, G2&& gen2) {
    size_t c1 = 0, c2 = 0;
    for ([[maybe_unused]] auto&& v : gen1) ++c1;
    for ([[maybe_unused]] auto&& v : gen2) ++c2;
    fmt::print("{}: {} ({} vs {})\n", name, c1 == c2 ? "MATCH" : "DIFFER", c1, c2);
}

int main() {
    check_count("EMK(5,2)", ecgen::emk_comb_gen(5, 2), ecgen::emk_gen(5, 2));
    check_count("EMK(5,3)", ecgen::emk_comb_gen(5, 3), ecgen::emk_gen(5, 3));
    check_count("EMK(16,5)", ecgen::emk_comb_gen(16, 5), ecgen::emk_gen(16, 5));
    check_count("SetPart(5,2)", ecgen::set_partition_gen(5, 2), ecgen::set_partition_gen_old(5, 2));
    check_count("SetPart(6,3)", ecgen::set_partition_gen(5, 3), ecgen::set_partition_gen_old(5, 3));
    check_count("SetPart(11,5)", ecgen::set_partition_gen(11, 5),
                ecgen::set_partition_gen_old(11, 5));
}
