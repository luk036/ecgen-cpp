#include <ecgen/perm.hpp>
#include <numeric>  // import iota
#include <vector>

namespace ecgen {

    /**
     * @brief Generate all permutations by adjacent transposition
     *
     * @param n
     * @return cppcoro::generator<int>
     */
    auto SJT_gen(int n) -> cppcoro::generator<int> {
        /** Generate the swaps for the Steinhaus-Johnson-Trotter algorithm.*/
        if (n == 2) {
            co_yield 0;
            co_yield 0;  // tricky part: return to the original list
            co_return;
        }

        auto&& gen = SJT_gen(n - 1);
        for (auto it = gen.begin(); it != gen.end(); ++it) {
            for (auto i = n - 2; i != -1; --i) {  // downward
                co_yield i;
            }
            co_yield 1 + *it;
            for (auto i = 0; i != n - 1; ++i) {  // upward
                co_yield i;
            }
            co_yield *(++it);  // tricky part
        }
    }

    /**
     * @brief Binary Reflexed Gray Code (less efficiency)
     *
     * @param n
     * @return recursive_generator<std::vector<int>>
     * @todo benchmark with SJT_gen
     */
    auto SJT(int n) -> cppcoro::generator<std::vector<int>> {
        auto lst = std::vector(n, 0);
        std::iota(lst.begin(), lst.end(), 0);  // 0, 1, ... n-1
        for (auto i : SJT_gen(n)) {
            co_yield lst;
            std::swap(lst[i], lst[i + 1]);
        }
    }

    /**
     * @brief Generate all permutations by star transposition
     *
     * @param n
     * @return cppcoro::generator<int>
     */
    auto Ehr_gen(int n) -> cppcoro::generator<int> {
        auto c = std::vector(n + 1, 0);  // c[0] is never used
        auto b = std::vector(n, 0);
        std::iota(b.begin(), b.end(), 0);  // 0, 1, ... n-1

        while (true) {
            auto k = 1;
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
            for (auto i = 1, j = k - 1; i < j; ++i, --j) {
                std::swap(b[i], b[j]);
            }
        }
    }

}  // namespace ecgen