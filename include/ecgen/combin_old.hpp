#pragma once

#include <cppcoro/recursive_generator.hpp> // for recursive_generator
#include <type_traits>                     // for integral_constant
#include <utility>                         // for pair

namespace ecgen {

/**
 * @brief EMK (GEN)
 *
 * @param[in] n
 * @param[in] k
 * @return cppcoro::recursive_generator<std::pair<size_t, size_t>>
 */
extern auto EMK_gen(size_t n, size_t k)
    -> cppcoro::recursive_generator<std::pair<size_t, size_t>>;

/**
 * @brief EMK (NEG)
 *
 * @param[in] n
 * @param[in] k
 * @return cppcoro::recursive_generator<std::pair<size_t, size_t>>
 */
extern auto EMK_neg(size_t n, size_t k)
    -> cppcoro::recursive_generator<std::pair<size_t, size_t>>;

} // namespace ecgen
