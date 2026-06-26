/**
 * @file combin.hpp
 * @brief Combination generation using the revolving door algorithm
 */

#pragma once

#include <py2cpp/gen.hpp>
#include <py2cpp/recursive_gen.hpp>
#include <type_traits>  // for integral_constant
#include <utility>      // for pair

namespace ecgen {

    /**
     * @brief Generate all k-combinations of n elements (revolving door algorithm)
     *
     * This is implemented as a recursive generator function that yields index pairs
     * representing the combinations using the revolving door algorithm.
     *
     * Example visualization of combinations (4 choose 2):
     * @verbatim
     *    0 1 2 3
     *    x x . .  -> indices 0,1
     *    x . x .  -> indices 0,2
     *    x . . x  -> indices 0,3
     *    . x x .  -> indices 1,2
     *    . x . x  -> indices 1,3
     *    . . x x  -> indices 2,3
     * @endverbatim
     *
     * @param[in] n - The number of elements in the full set.
     * @param[in] k - The number of elements to select in each combination.
     * @returns A recursive generator yielding index pairs for the k-combinations of
     * n elements.
     */
    extern auto emk_comb_gen(int n, int k) -> py::RecursiveGenerator<std::pair<int, int>>;

    /**
     * @brief Generate all k-combinations in reverse lexicographic order (revolving door)
     *
     * Example visualization of combinations (4 choose 2):
     * @verbatim
     *    0 1 2 3
     *    x x . .  -> indices 0,1
     *    x . x .  -> indices 0,2
     *    x . . x  -> indices 0,3
     *    . x x .  -> indices 1,2
     *    . x . x  -> indices 1,3
     *    . . x x  -> indices 2,3
     * @endverbatim
     *
     * @param[in] n - The number of elements in the set.
     * @param[in] k - The size of the combinations to generate.
     * @param[in] lst - The container holding the set elements.
     * @returns A generator that yields each k-combination of lst in reverse
     * lexicographic order.
     */
    template <typename Container> auto emk(int n, int k, Container lst)
        -> py::Generator<Container&> {
        co_yield lst;
        for (const auto& [pos_x, pos_y] : emk_comb_gen(n, k)) {
            auto temp = lst[static_cast<typename Container::size_type>(pos_x)];  // swap
            lst[static_cast<typename Container::size_type>(pos_x)]
                = lst[static_cast<typename Container::size_type>(pos_y)];
            lst[static_cast<typename Container::size_type>(pos_y)] = temp;
            co_yield lst;
        }
    }

    /**
     * @brief Calculate binomial coefficient C(N, K) at compile time
     *
     * This is a constexpr function that computes the result at compile-time
     * using Pascal's rule:
     *
     * @f[
     *     \binom{N}{K} = \binom{N-1}{K-1} + \binom{N-1}{K}
     * @f]
     *
     * Example calculation for C(4,2) = 6:
     * @verbatim
     *    C(4,2) = 4! / (2! * (4-2)!) = 24 / (2 * 2) = 6
     * @endverbatim
     *
     * @tparam N - The size of the set
     * @tparam K - The number of elements to select
     * @return The number of combinations, computed at compile-time.
     */
    template <int N, int K> constexpr auto Combination() {
        if constexpr (K >= N || K == 0) {
            return std::integral_constant<size_t, 1U>{};
        } else {
            return std::integral_constant<size_t,
                                          Combination<N - 1, K - 1>() + Combination<N - 1, K>()>{};
        }
    }

}  // namespace ecgen
