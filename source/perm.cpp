#include <algorithm>
#include <ecgen/perm.hpp>
#include <numeric>  // for iota
#include <vector>

namespace ecgen {
    /**
     * @brief Generate all permutations by adjacent transposition
     *
     * The `sjt_gen` function is generating all permutations of size `n` using the
     * Steinhaus-Johnson-Trotter algorithm. It returns a
     * `cppcoro::generator<int>`, which is a coroutine-based generator that
     * yields values of type `int`.
     *
     * @param[in] n The parameter `n` represents the size of the permutations to be
     * generated. It determines the number of elements in each permutation.
     * @return cppcoro::generator<int>
     */
    auto sjt_gen(int n) -> cppcoro::generator<int> {
        /** Generate the swaps for the Steinhaus-Johnson-Trotter algorithm.*/
        if (n == 2) {
            co_yield 0;
            co_yield 0;  // tricky part: return to the original list
            co_return;
        }

        auto &&gen = sjt_gen(n - 1);
        for (auto it = gen.begin(); it != gen.end(); ++it) {
            for (int idx = n - 1; idx != 0; --idx) {  // downward
                co_yield idx - 1;
            }
            co_yield 1 + *it;
            for (int idx = 0; idx != n - 1; ++idx) {  // upward
                co_yield idx;
            }
            co_yield *(++it);  // tricky part
        }
    }

    /**
     * @brief Generate all permutations by star transposition
     *
     * The `ehr_gen` function is generating all permutations of size `n` using the
     * ehrlich-Straus algorithm. It returns a `cppcoro::generator<int>`, which is
     * a coroutine-based generator that yields values of type `int`.
     *
     * @param[in] n The parameter `n` represents the size of the permutations to be
     * generated. It determines the number of elements in each permutation.
     * @return cppcoro::generator<int>
     */
    auto ehr_gen(int n) -> cppcoro::generator<int> {
            auto counters = std::vector<int>(static_cast<size_t>(n + 1), 0);  // counters[0] is never used
            auto buffer = std::vector<int>(static_cast<size_t>(n));
            std::iota(buffer.begin(), buffer.end(), 0);  // 0, 1, ... n-1
    
            while (true) {
                int idx = 1;
                do {
                    if (counters[static_cast<size_t>(idx)] == idx) {
                        counters[static_cast<size_t>(idx)] = 0;
                        idx += 1;
                    }
                } while (counters[static_cast<size_t>(idx)] >= idx);
                if (idx == n) {
                    break;
                }
                counters[static_cast<size_t>(idx)] += 1;
                co_yield buffer[static_cast<size_t>(idx)];
                // for (int i = 1, j = idx - 1; i < j; ++i, --j) {
                //     std::swap(buffer[i], buffer[j]);
    
                // }
                std::reverse(buffer.begin() + 1, buffer.begin() + idx);
            }
        }
}  // namespace ecgen
