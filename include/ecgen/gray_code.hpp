#pragma once

#include <cppcoro/recursive_generator.hpp>

namespace ecgen {
    /**
     * Generates a recursive Gray code sequence of length n.
     *
     * The recursive Gray code sequence is an ordering of all 2^n bitstrings of
     * length n, such that adjacent strings differ by only one bit flip.
     *
     * This generates the sequence efficiently using recursion and bit manipulation.
     *
     * @param[in] n - The length of the Gray code sequence to generate.
     * @returns A recursive generator that yields each value in the Gray code
     * sequence.
     */
    extern auto brgc_gen(int n) -> cppcoro::recursive_generator<int>;

    /**
     * Generates a Binary Reflexed Gray Code sequence of length n.
     *
     * The Binary Reflexed Gray Code is an ordering of all bitstrings of length n,
     * such that adjacent strings differ by only one bit flip.
     *
     * This implementation uses a for loop to iterate through the recursive
     * Gray Code generator, flipping bits at each step to generate the sequence.
     *
     * @tparam Container - The type of container to store the bitstrings.
     * @param[in] n - The length of the Gray code sequence to generate.
     * @return A generator that yields each value in the Gray code sequence.
     */
    template <typename Container> auto brgc(int n) -> cppcoro::generator<Container &> {
        auto lst = Container(n, 0);
        co_yield lst;
        for (const int i : brgc_gen(n)) {
            lst[i] = 1 - lst[i];  // flip
            co_yield lst;
        }
    }
}  // namespace ecgen
