#include <iostream>
#include <ecgen/combin.hpp>

int main() {
    std::cout << "Testing emk_comb_gen(4, 2)..." << std::endl;
    size_t cnt = 0;
    try {
        for (auto idx : ecgen::emk_comb_gen(4, 2)) {
            std::cout << "Swap " << cnt << ": (" << idx.first << ", " << idx.second << ")" << std::endl;
            ++cnt;
        }
        std::cout << "Total swaps: " << cnt << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown exception" << std::endl;
        return 1;
    }
    return 0;
}