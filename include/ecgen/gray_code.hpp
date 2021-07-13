#pragma once

#include <cppcoro/recursive_generator.hpp>
#include <vector>
// #include <type_traits>

namespace ecgen
{

/**
 * @brief Generate reflexed Gray code
 *
 * @param n
 * @return cppcoro::recursive_generator<int>
 */
extern auto BRGC_gen(int n) -> cppcoro::recursive_generator<int>;

/**
 * @brief BRGC
 *
 * @param n
 * @return cppcoro::recursive_generator<std::vector<int>>
 */
extern auto BRGC(int n) -> cppcoro::recursive_generator<std::vector<int>>;

} // namespace ecgen