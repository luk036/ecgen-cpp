#include <ecgen/version.h>

#include <iostream>

auto main() -> int {
    const auto ok = (ECGEN_VERSION_MAJOR >= 1);
    std::cout << "ecgen installed test: version " << ECGEN_VERSION << "\n";
    return ok ? 0 : 1;
}
