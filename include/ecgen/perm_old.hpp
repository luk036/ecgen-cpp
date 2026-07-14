/**
 * @file perm_old.hpp
 * @brief Legacy permutation generation (list-based SJT algorithm)
 */

#pragma once

#include <py2cpp/gen.hpp>
#include <vector>

namespace ecgen {

    /**
     * @brief Generate all permutations as lists using SJT algorithm
     *
     * Unlike sjt_gen which yields swap indices, sjt2 yields the actual
     * permutation vectors directly. The algorithm recursively generates
     * permutations by inserting the largest element at every possible
     * position, alternating between upward and downward directions.
     *
     * Example for n=3:
     * @verbatim
     *    [0, 1, 2]  [0, 2, 1]  [2, 0, 1]  [2, 1, 0]  [1, 2, 0]  [1, 0, 2]
     * @endverbatim
     *
     * @param[in] n The number of elements to permute
     * @return A generator that yields each permutation as a vector of ints
     */
    auto sjt2(int n) -> py::Generator<std::vector<int>>;

}  // namespace ecgen
