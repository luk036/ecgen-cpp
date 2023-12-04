#pragma once

#include <cppcoro/recursive_generator.hpp> // for recursive_generator
#include <type_traits>                     // for integral_constant
#include <utility>                         // for pair

namespace ecgen {

/**
 * @brief emk (GEN)
 *
 * @param[in] n
 * @param[in] k
 * @return cppcoro::recursive_generator<std::pair<size_t, size_t>>
 */
extern auto emk_comb_gen(size_t n, size_t k)
    -> cppcoro::recursive_generator<std::pair<size_t, size_t>>;

// /**
//  * @brief emk (NEG)
//  *
//  * @param[in] n
//  * @param[in] k
//  * @return cppcoro::recursive_generator<std::pair<size_t, size_t>>
//  */
// extern auto emk_neg(size_t n, size_t k)
//     -> cppcoro::recursive_generator<std::pair<size_t, size_t>>;
//

/**
 * @brief Generate all combinations in reverse order by homogeneous
 * revolving-door
 *
 * @param[in] n
 * @param[in] k
 * @return recursive_generator<std::vector<size_t>>
 */
template <typename Container>
auto emk(size_t n, size_t k, Container &lst)
    -> cppcoro::generator<Container &> {
    // auto lst = Container(n, 0);
    // std::fill_n(lst.begin(), k, 1);
    co_yield lst;
    for (auto [x, y] : emk_comb_gen(n, k)) {
        auto temp = lst[x]; // swap
        lst[x] = lst[y];
        lst[y] = temp;
        co_yield lst;
    }
}

/**
 * @brief The number of combinations
 *
 * The `Combination()` function is a template function that calculates the
 * number of combinations of `K` elements from a set of `N` elements at
 * compile-time.
 *
 * @tparam N
 * @tparam K
 * @return constexpr auto
 */
template <size_t N, size_t K> constexpr auto Combination() {
    if constexpr (K >= N || K == 0) {
        return std::integral_constant<size_t, 1U>{};
    } else {
        return std::integral_constant<size_t, Combination<N - 1, K - 1>() +
                                                  Combination<N - 1, K>()>{};
    }
}

} // namespace ecgen
