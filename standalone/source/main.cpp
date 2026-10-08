#include <ecgen/version.h>

#include <cxxopts.hpp>
#include <ecgen/combin.hpp>
#include <iostream>
#include <string>

auto main(int argc, char** argv) -> int {
    cxxopts::Options options("EcGen", "Combinatorial object generator demo");

    int n = 5;
    int k = 3;
    options.add_options()("h,help", "Print usage")("v,version", "Print version")(
        "size", "Size of the set", cxxopts::value(n))("comb-size", "Size of each combination",
                                                      cxxopts::value(k));

    const auto result = options.parse(argc, argv);
    if (result.count("help") > 0) {
        std::cout << options.help() << '\n';
        return 0;
    }
    if (result.count("version") > 0) {
        std::cout << "EcGen, version " << ECGEN_VERSION << '\n';
        return 0;
    }

    std::cout << "EcGen: " << k << "-combinations of " << n << " elements:\n";
    for (const auto& c : ecgen::emk_comb_gen(n, k)) {
        std::cout << "  (" << c.first << ", " << c.second << ")\n";
    }

    return 0;
}
