#pragma once

#include <cppcoro/generator.hpp>
#include <type_traits> // for integral_constant

namespace ecgen {
/**
 * Generates integers from 0 to n-1 in an order that generates all
 * permutations of length n using the Steinhaus-Johnson-Trotter algorithm.
 *
 * @param[in] n The permutation length
 * @return A cppcoro::generator that yields the permutation indices
 */
extern auto sjt_gen(int n) -> cppcoro::generator<int>;

/**
 * Generates integers from 0 to n-1 in an order that generates all
 * permutations of length n using the Eades-Hickey-Read (EHR) algorithm.
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
 * @tparam Container
 * @param[in] perm
 * @return cppcoro::generator<Container&>
 */
template <typename Container>
inline auto sjt(Container &perm) -> cppcoro::generator<Container &> {
    const auto n = int(perm.size());
    for (int i : ecgen::sjt_gen(n)) {
        co_yield perm;
        auto temp = perm[i]; // swap
        perm[i] = perm[i + 1];
        perm[i + 1] = temp;
    }
}

/**
 * Generates a permutation by applying star transpositions to the input
 * permutation container. This uses the Eades-Hickey-Read (EHR) algorithm.
 *
 * @tparam Container - The type of the permutation container.
 * @param[in] perm - The permutation container to generate permutations for.
 * @return A cppcoro::generator that yields references to the permutation
 * container after each transposition.
 */
template <typename Container>
inline auto ehr(Container &perm) -> cppcoro::generator<Container &> {
    const auto n = int(perm.size());
    co_yield perm;
    for (int i : ecgen::ehr_gen(n)) {
        auto temp = perm[0]; // swap
        perm[0] = perm[i];
        perm[i] = temp;
        co_yield perm;
    }
}
} // namespace ecgen
