#include <ecgen/perm_old.hpp>

namespace ecgen {

    auto sjt2(int n) -> py::Generator<std::vector<int>> {
        if (n == 2) {
            co_yield std::vector{0, 1};
            co_yield std::vector{1, 0};
            co_return;
        }

        auto gen = sjt2(n - 1);
        for (auto it = gen.begin(); it != gen.end(); ++it) {
            auto pi = *it;
            // downward: insert n-1 at positions n-1, n-2, ..., 0
            for (int i = n - 1; i >= 0; --i) {
                auto copy = pi;
                copy.insert(copy.begin() + i, n - 1);
                co_yield copy;
            }
            ++it;  // tricky part: advance to next parent permutation
            pi = *it;
            // upward: insert n-1 at positions 0, 1, ..., n-1
            for (int i = 0; i < n; ++i) {
                auto copy = pi;
                copy.insert(copy.begin() + i, n - 1);
                co_yield copy;
            }
        }
    }

}  // namespace ecgen
