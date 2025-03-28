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
            for (int i = n - 1; i != 0; --i) {  // downward
                co_yield i - 1;
            }
            co_yield 1 + *it;
            for (int i = 0; i != n - 1; ++i) {  // upward
                co_yield i;
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
        auto c = std::vector<int>(n + 1, 0);  // c[0] is never used
        auto b = std::vector<int>(n);
        std::iota(b.begin(), b.end(), 0);  // 0, 1, ... n-1

        while (true) {
            int k = 1;
            do {
                if (c[k] == k) {
                    c[k] = 0;
                    k += 1;
                }
            } while (c[k] >= k);
            if (k == n) {
                break;
            }
            c[k] += 1;
            co_yield b[k];
            // for (int i = 1, j = k - 1; i < j; ++i, --j) {
            //     std::swap(b[i], b[j]);
            // }
            std::reverse(b.begin() + 1, b.begin() + k);
        }
    }
}  // namespace ecgen
