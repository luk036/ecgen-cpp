#pragma once

#include <cppcoro/generator.hpp>
#include <type_traits>  // for integral_constant

namespace ecgen {
    /**
     * Generates integers from 0 to n-1 in an order that generates all
     * permutations of length n using the Steinhaus-Johnson-Trotter algorithm.
     *
     * Example visualization for n=3 (generating all permutations):
     * ```svgbob
     *    Start: 0 1 2
     *    Step 1: 0 2 1 (swap 1,2)
     *    Step 2: 2 0 1 (swap 0,2)
     *    Step 3: 2 1 0 (swap 0,1)
     *    Step 4: 1 2 0 (swap 1,2)
     *    Step 5: 1 0 2 (swap 0,2)
     * ```
     *
     * @param[in] n The permutation length
     * @return A cppcoro::generator that yields the permutation indices
     */
    extern auto sjt_gen(int n) -> cppcoro::generator<int>;

    /**
     * Generates integers from 0 to n-1 in an order that generates all
     * permutations of length n using the Eades-Hickey-Read (EHR) algorithm.
     *
     * Example visualization for n=3:
     * ```svgbob
     *    Start: 0 1 2
     *    Step 1: 1 0 2 (swap 0,1)
     *    Step 2: 2 0 1 (swap 1,2)
     *    Step 3: 0 2 1 (swap 0,1)
     *    Step 4: 1 2 0 (swap 0,1)
     *    Step 5: 2 1 0 (swap 1,2)
     * ```
     *
     * @param[in] n The permutation length
     * @return A cppcoro::generator that yields the permutation indices
     */
    extern auto ehr_gen(int n) -> cppcoro::generator<int>;

    /**
     * Computes the factorial of the input number N at compile time.
     *
     * This is used to calculate the total number of permutations of length N,
     * which is N!. It is implemented as a constexpr function template.
     *
     * Example calculation for N=4:
     * ```svgbob
     *    4! = 4 * 3 * 2 * 1 = 24
     *    So there are 24 permutations of 4 elements
     * ```
     *
     * @tparam N - The number to calculate the factorial of.
     * @return constexpr auto - The factorial of N as a std::integral_constant.
     */
    template <int N> constexpr auto Factorial() {
        if constexpr (N <= 1) {
            return std::integral_constant<size_t, 1U>{};
        } else {
            return std::integral_constant<size_t, N * Factorial<N - 1>()>{};
        }
    }

    /**
     * Generates a permutation by applying adjacent transpositions to the input
     * permutation container. This uses the Steinhaus-Johnson-Trotter algorithm.
     *
     * Example visualization for adjacent transpositions:
     * ```svgbob
     *    [a, b, c] -> [b, a, c] (swap positions 0,1)
     *    [b, a, c] -> [b, c, a] (swap positions 1,2)
     *    [b, c, a] -> [c, b, a] (swap positions 0,1)
     * ```
     *
     * @tparam Container
     * @param[in] perm
     * @return cppcoro::generator<Container&>
     */
    template <typename Container> inline auto sjt(Container &perm)
        -> cppcoro::generator<Container &> {
        const auto n = int(perm.size());
        for (const int idx : ecgen::sjt_gen(n)) {
            co_yield perm;
            auto temp = perm[static_cast<typename Container::size_type>(idx)];  // swap
            perm[static_cast<typename Container::size_type>(idx)] = perm[static_cast<typename Container::size_type>(idx + 1)];
            perm[static_cast<typename Container::size_type>(idx + 1)] = temp;
        }
    }

}  // namespace ecgen
