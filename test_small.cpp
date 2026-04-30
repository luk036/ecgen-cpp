#include <ecgen/combin.hpp>
#include <ecgen/perm.hpp>
#include <iostream>

int main() {
    std::cout << "Testing small values...\n";

    // Test SJT with n=1
    std::cout << "Testing sjt_gen(1)...\n";
    try {
        int cnt = 0;
        for (auto idx : ecgen::sjt_gen(1)) {
            std::cout << "  idx: " << idx << '\n';
            cnt++;
            if (cnt > 100) break;
        }
        std::cout << "  Total: " << cnt << '\n';
    } catch (...) {
        std::cout << "  Exception!\n";
    }

    // Test SJT with n=2
    std::cout << "Testing sjt_gen(2)...\n";
    try {
        int cnt = 0;
        for (auto idx : ecgen::sjt_gen(2)) {
            std::cout << "  idx: " << idx << '\n';
            cnt++;
            if (cnt > 100) break;
        }
        std::cout << "  Total: " << cnt << '\n';
    } catch (...) {
        std::cout << "  Exception!\n";
    }

    // Test SJT with n=3
    std::cout << "Testing sjt_gen(3)...\n";
    try {
        int cnt = 0;
        for (auto idx : ecgen::sjt_gen(3)) {
            std::cout << "  idx: " << idx << '\n';
            cnt++;
            if (cnt > 100) break;
        }
        std::cout << "  Total: " << cnt << '\n';
    } catch (...) {
        std::cout << "  Exception!\n";
    }

    return 0;
}