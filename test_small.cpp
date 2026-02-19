#include <iostream>
#include <ecgen/combin.hpp>
#include <ecgen/perm.hpp>

int main() {
    std::cout << "Testing small values..." << std::endl;

    // Test SJT with n=1
    std::cout << "Testing sjt_gen(1)..." << std::endl;
    try {
        int cnt = 0;
        for (auto idx : ecgen::sjt_gen(1)) {
            std::cout << "  idx: " << idx << std::endl;
            cnt++;
            if (cnt > 100) break;
        }
        std::cout << "  Total: " << cnt << std::endl;
    } catch (...) {
        std::cout << "  Exception!" << std::endl;
    }

    // Test SJT with n=2
    std::cout << "Testing sjt_gen(2)..." << std::endl;
    try {
        int cnt = 0;
        for (auto idx : ecgen::sjt_gen(2)) {
            std::cout << "  idx: " << idx << std::endl;
            cnt++;
            if (cnt > 100) break;
        }
        std::cout << "  Total: " << cnt << std::endl;
    } catch (...) {
        std::cout << "  Exception!" << std::endl;
    }

    // Test SJT with n=3
    std::cout << "Testing sjt_gen(3)..." << std::endl;
    try {
        int cnt = 0;
        for (auto idx : ecgen::sjt_gen(3)) {
            std::cout << "  idx: " << idx << std::endl;
            cnt++;
            if (cnt > 100) break;
        }
        std::cout << "  Total: " << cnt << std::endl;
    } catch (...) {
        std::cout << "  Exception!" << std::endl;
    }

    return 0;
}