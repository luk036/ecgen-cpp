#pragma once

#include <cppcoro/recursive_generator.hpp>  // for recursive_generator
#include <tuple>                            // for tuple
#include <type_traits>                      // for integral_constant
// #include <vector>                           // for vector
// #include <type_traits>

namespace ecgen {

    /**
     * @brief EMK (GEN)
     *
     * @param n
     * @param k
     * @return cppcoro::recursive_generator<std::tuple<int, int>>
     */
    extern auto EMK_gen(int n, int k) -> cppcoro::recursive_generator<std::tuple<int, int>>;

    /**
     * @brief EMK (NEG)
     *
     * @param n
     * @param k
     * @return cppcoro::recursive_generator<std::tuple<int, int>>
     */
    extern auto EMK_neg(int n, int k) -> cppcoro::recursive_generator<std::tuple<int, int>>;

    /**
     * @brief EMK
     *
     * @param n
     * @param k
     * @return cppcoro::recursive_generator<std::vector<int>>
     */
    // extern auto EMK(int n, int k) -> cppcoro::recursive_generator<std::vector<int>>;

    /**
     * @brief The number of combinations
     *
     * @tparam N
     * @tparam K
     * @return constexpr auto
     */
    template <int N, int K> constexpr auto Combination() {
        if constexpr (K >= N || K == 0) {
            return std::integral_constant<int, 1U>{};
        } else {
            return std::integral_constant<int,
                                          Combination<N - 1, K - 1>() + Combination<N - 1, K>()>{};
        }
    }

}  // namespace ecgen