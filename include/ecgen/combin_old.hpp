#pragma once

#include <cppcoro/recursive_generator.hpp> // for recursive_generator
#include <type_traits>                     // for integral_constant
#include <utility>                         // for pair

namespace ecgen {

/**
 * Generates all k-combinations from a set of n elements as pairs of indices.
 *
 * This is a recursive generator function that yields all possible
 * k-combinations of integer indices ranging from 0 to n-1.
 *
 * @param[in] n - The size of the set to generate combinations from.
 * @param[in] k - The size of each generated combination.
 * @returns A recursive generator yielding all k-combinations as pairs of
 * indices.
 */
extern auto emk_gen(int n,
                    int k) -> cppcoro::recursive_generator<std::pair<int, int>>;

/**
 * Generates all k-combinations from a set of n elements, without repetition.
 *
 * This is a recursive generator function that yields all possible
 * k-combinations of integer indices ranging from 0 to n-1, without repeating
 * indices.
 *
 * @param[in] n - The size of the set to generate combinations from.
 * @param[in] k - The size of each generated combination.
 * @returns A recursive generator yielding all k-combinations as pairs of
 * indices.
 */
extern auto emk_neg(int n,
                    int k) -> cppcoro::recursive_generator<std::pair<int, int>>;

} // namespace ecgen
