#pragma once

#include <cppcoro/recursive_generator.hpp>

namespace ecgen {

    /**
     * @brief Generate reflexed Gray code
     *
     * @param n
     * @return cppcoro::recursive_generator<int>
     */
    extern auto BRGC_gen(int n) -> cppcoro::recursive_generator<int>;

    /**
     * @brief Binary Reflexed Gray Code (less efficiency)
     *
     * @tparam Container
     * @param n
     * @return cppcoro::generator<Container&>
     */
    template <typename Container> auto BRGC(int n) -> cppcoro::generator<Container&> {
        auto lst = Container(n, 0);
        co_yield lst;
        for (auto i : BRGC_gen(n)) {
            lst[i] = 1 - lst[i];  // flip
            co_yield lst;
        }
    }

}  // namespace ecgen