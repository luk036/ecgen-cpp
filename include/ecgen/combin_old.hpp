/**
 * @file combin_old.hpp
 * @brief Legacy combination generation (recursive, forward and reverse)
 */

#pragma once

#include <py2cpp/recursive_gen.hpp>
// #include <type_traits>                      // for integral_constant
#include <utility>  // for pair

namespace ecgen {

    /**
     * @brief Generate all k-combinations from n elements (recursive, forward order)
     *
     * This is a recursive generator function that yields all possible
     * k-combinations of integer indices ranging from 0 to n-1.
     *
     * @param[in] n - The size of the set to generate combinations from.
     * @param[in] k - The size of each generated combination.
     * @returns A recursive generator yielding all k-combinations as pairs of
     * indices.
     */
    extern auto emk_gen(int n, int k) -> py::RecursiveGenerator<std::pair<int, int>>;

    /**
     * @brief Generate all k-combinations from n elements (recursive, reverse order)
     *
     * This is the reverse variant of emk_gen, generating all possible
     * k-combinations of integer indices ranging from 0 to n-1 in
     * reverse lexicographic order.
     *
     * @param[in] n - The size of the set to generate combinations from.
     * @param[in] k - The size of each generated combination.
     * @returns A recursive generator yielding all k-combinations as pairs of
     * indices (in reverse order).
     */
    extern auto emk_neg(int n, int k) -> py::RecursiveGenerator<std::pair<int, int>>;

}  // namespace ecgen
