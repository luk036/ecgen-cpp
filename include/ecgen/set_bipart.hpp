/**
 * @file set_bipart.hpp
 * @brief Set bipartition (2-block partition) generation
 *
 * A bipartition of the set [n] = {1,2,3,...,n} into two nonempty blocks.
 * This is a specialized case of set partitions with exactly 2 blocks.
 *
 * The generator yields element indices that should be moved from one block
 * to the other, following a Gray code ordering where successive partitions
 * differ by moving only one element.
 *
 * Reference:
 * Frank Ruskey. Simple combinatorial Gray codes constructed by
 * reversing sublists. Lecture Notes in Computer Science, #762,
 * 201-208. Also downloadable from
 * http://webhome.cs.uvic.ca/~ruskey/Publications/SimpleGray/SimpleGray.html
 */

#pragma once

#include <py2cpp/recursive_gen.hpp>
#include <type_traits>  // for integral_constant

namespace ecgen {

    /**
     * @brief Compute Stirling numbers of the second kind S(N,2)
     *
     * Counts the number of ways to partition a set of N elements into 2 nonempty subsets.
     *
     * This is a specialized version for k=2, computed as 2^(N-1) - 1.
     *
     * Example:
     * @verbatim
     *    S(5,2) = 15  (2^4 - 1 = 15)
     *    S(4,2) = 7   (2^3 - 1 = 7)
     * @endverbatim
     *
     * @tparam N - The size of the set.
     * @return constexpr auto - The Stirling number S(N,2) as a
     * std::integral_constant.
     */
    template <int N> constexpr auto Stirling2nd2() {
        if constexpr (N <= 2) {
            return std::integral_constant<size_t, 1U>{};
        } else {
            return std::integral_constant<size_t, 1U + 2 * Stirling2nd2<N - 1>()>{};
        }
    }

    /**
     * Generates all bipartitions of a set of n elements into 2 blocks.
     *
     * The generator yields element indices that should be moved from one block
     * to the other, following a Gray code ordering where each step moves a
     * single element.
     *
     * Example for n=4 (bipartitions of {1,2,3,4} into 2 nonempty blocks):
     * @verbatim
     *    {1,2,3}{4} -> {1,2}{3,4} -> {1,3}{2,4} -> {1}{2,3,4} -> ...
     * @endverbatim
     *
     * @param[in] n - The number of elements to bipartition (n >= 3).
     * @return A recursive generator that yields element indices to move.
     */
    extern auto set_bipart_gen(int n) -> py::RecursiveGenerator<int>;

}  // namespace ecgen
