#pragma once

#include <cppcoro/generator.hpp>
#include <type_traits> // for integral_constant

namespace ecgen {
/**
 * @brief sjt
 *
 * @param[in] n
 * @return cppcoro::generator<size_t>
 */
extern auto sjt_gen(size_t n) -> cppcoro::generator<size_t>;

/**
 * @brief ehr
 *
 * @param[in] n
 * @return cppcoro::generator<size_t>
 */
extern auto ehr_gen(size_t n) -> cppcoro::generator<size_t>;

/**
 * @brief Factorial, N!, the number of permutations
 *
 * The `Factorial()` function is a template function that calculates the
 * factorial of a given number `N` at compile-time.
 *
 * @tparam N
 * @return constexpr auto
 */
template <size_t N> constexpr auto Factorial() {
    if constexpr (N <= 1) {
        return std::integral_constant<size_t, 1U>{};
    } else {
        return std::integral_constant<size_t, N * Factorial<N - 1>()>{};
    }
}

/**
 * @brief sjt permutation by adjacent transposition (less efficiency)
 *
 * @tparam Container
 * @param[in] perm
 * @return cppcoro::generator<Container&>
 */
template <typename Container>
inline auto sjt(Container &perm) -> cppcoro::generator<Container &> {
    const auto n = perm.size();
    for (size_t i : ecgen::sjt_gen(n)) {
        co_yield perm;
        auto temp = perm[i]; // swap
        perm[i] = perm[i + 1];
        perm[i + 1] = temp;
    }
}

/**
 * @brief ehr permutation by star transposition (less efficiency)
 *
 * @tparam Container
 * @param[in] perm
 * @return cppcoro::generator<Container&>
 */
template <typename Container>
inline auto ehr(Container &perm) -> cppcoro::generator<Container &> {
    const auto n = perm.size();
    co_yield perm;
    for (size_t i : ecgen::ehr_gen(n)) {
        auto temp = perm[0]; // swap
        perm[0] = perm[i];
        perm[i] = temp;
        co_yield perm;
    }
}
} // namespace ecgen
