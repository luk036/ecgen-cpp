#include <cstdio>
#include <ecgen/combin.hpp>
#include <ecgen/gray_code.hpp>
#include <ecgen/perm.hpp>
#include <ecgen/set_bipart.hpp>
#include <ecgen/set_partition.hpp>
#include <string>

template <typename G> void dump(const char* name, G&& gen) {
    std::string sep;
    std::printf("%s: [", name);
    int cnt = 0;
    for (auto&& val : gen) {
        std::printf("%s", sep.c_str());
        if constexpr (std::is_same_v<std::decay_t<decltype(val)>, std::pair<int, int>>) {
            std::printf("(%d, %d)", val.first, val.second);
        } else {
            std::printf("%d", val);
        }
        sep = ", ";
        ++cnt;
    }
    std::printf("] (%d items)\n", cnt);
}

int main() {
    std::printf("=== EMK combinations ===\n");
    dump("emk_comb_gen(5,2)", ecgen::emk_comb_gen(5, 2));
    dump("emk_comb_gen(5,3)", ecgen::emk_comb_gen(5, 3));

    std::printf("\n=== SJT permutations ===\n");
    dump("sjt_gen(3)", ecgen::sjt_gen(3));
    dump("sjt_gen(4)", ecgen::sjt_gen(4));

    std::printf("\n=== Ehrlich permutations ===\n");
    dump("ehr_gen(3)", ecgen::ehr_gen(3));
    dump("ehr_gen(4)", ecgen::ehr_gen(4));

    std::printf("\n=== BRGC ===\n");
    dump("brgc_gen(3)", ecgen::brgc_gen(3));

    std::printf("\n=== Set partition ===\n");
    dump("set_partition_gen(5,2)", ecgen::set_partition_gen(5, 2));

    std::printf("\n=== Set bipartition ===\n");
    dump("set_bipart_gen(5)", ecgen::set_bipart_gen(5));
}
