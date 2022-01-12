#pragma once

// #include <algorithm>                        // for fill_n
#include <cppcoro/recursive_generator.hpp>  // for recursive_generator
#include <tuple>                            // for tuple
#include <type_traits>                      // for integral_constant

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
     * @brief Generate all combinations in reverse order by homogeneous
     * revolving-door
     *
     * @param n
     * @param k
     * @return recursive_generator<std::vector<int>>
     */
    template <typename Container> auto EMK(int n, int k, Container& lst)
        -> cppcoro::generator<Container&> {
        // auto lst = Container(n, 0);
        // std::fill_n(lst.begin(), k, 1);
        co_yield lst;
        for (auto [x, y] : EMK_gen(n, k)) {
            auto temp = lst[x];  // swap
            lst[x] = lst[y];
            lst[y] = temp;
            co_yield lst;
        }
    }

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