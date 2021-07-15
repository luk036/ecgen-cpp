#pragma once

#include <cppcoro/generator.hpp>

namespace ecgen {

    /**
     * @brief SJT
     *
     * @param n
     * @return cppcoro::generator<int>
     */
    extern auto SJT_gen(int n) -> cppcoro::generator<int>;

    /**
     * @brief Ehr
     *
     * @param n
     * @return cppcoro::generator<int>
     */
    extern auto Ehr_gen(int n) -> cppcoro::generator<int>;

    /**
     * @brief Factorial, N!, the number of permutations
     *
     * @tparam N
     * @return constexpr auto
     */
    template <int N> constexpr auto Factorial() {
        if constexpr (N <= 1) {
            return std::integral_constant<int, 1U>{};
        } else {
            return std::integral_constant<int, N * Factorial<N - 1>()>{};
        }
    }

    /**
     * @brief SJT permutation by adjacent transposition
     *
     * @tparam Container
     * @param perm
     * @return cppcoro::generator<Container&>
     */
    template <typename Container> auto SJT(Container& perm) -> cppcoro::generator<Container&> {
        const auto n = int(perm.size());
        for (auto i : ecgen::SJT_gen(n)) {
            co_yield perm;
            std::swap(perm[i], perm[i + 1]);  // swap
        }
    }

}  // namespace ecgen
