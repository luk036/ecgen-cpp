#include <fmt/format.h>

#include <ecgen/combin.hpp>
#include <ecgen/gray_code.hpp>
#include <ecgen/perm.hpp>
#include <ecgen/set_bipart.hpp>
#include <ecgen/set_partition.hpp>
#include <string>

template <typename G> void dump(const char* name, G&& gen) {
    std::string sep;
    fmt::print("{}: [", name);
    int cnt = 0;
    for (auto&& val : gen) {
        fmt::print("{}", sep);
        if constexpr (std::is_same_v<std::decay_t<decltype(val)>, std::pair<int, int>>) {
            fmt::print("({}, {})", val.first, val.second);
        } else {
            fmt::print("{}", val);
        }
        sep = ", ";
        ++cnt;
    }
    fmt::print("] ({} items)\n", cnt);
}

int main() {
    fmt::print("=== EMK combinations ===\n");
    dump("emk_comb_gen(5,2)", ecgen::emk_comb_gen(5, 2));
    dump("emk_comb_gen(5,3)", ecgen::emk_comb_gen(5, 3));

    fmt::print("\n=== SJT permutations ===\n");
    dump("sjt_gen(3)", ecgen::sjt_gen(3));
    dump("sjt_gen(4)", ecgen::sjt_gen(4));

    fmt::print("\n=== Ehrlich permutations ===\n");
    dump("ehr_gen(3)", ecgen::ehr_gen(3));
    dump("ehr_gen(4)", ecgen::ehr_gen(4));

    fmt::print("\n=== BRGC ===\n");
    dump("brgc_gen(3)", ecgen::brgc_gen(3));

    fmt::print("\n=== Set partition ===\n");
    dump("set_partition_gen(5,2)", ecgen::set_partition_gen(5, 2));

    fmt::print("\n=== Set bipartition ===\n");
    dump("set_bipart_gen(5)", ecgen::set_bipart_gen(5));
}
