#include <cppcoro/coroutine.hpp>  // for cppcoro
#include <ecgen/gray_code.hpp>
#include <experimental/coroutine>  // for suspend_always, coroutine_handle

namespace ecgen {

    using namespace cppcoro;

    /**
     * @brief Binary Reflexed Gray Code Generator
     *
     * @param n
     * @return recursive_generator<int>
     */
    auto BRGC_gen(int n) -> recursive_generator<int> {
        if (n < 1) {
            co_return;
        }
        co_yield BRGC_gen(n - 1);
        co_yield n - 1;
        co_yield BRGC_gen(n - 1);
    }

    /**
     * @brief Binary Reflexed Gray Code (less efficiency)
     *
     * @param n
     * @return recursive_generator<std::vector<int>>
     */
    auto BRGC(int n) -> recursive_generator<std::vector<int>> {
        auto lst = std::vector(n, 0);
        co_yield lst;
        for (auto i : BRGC_gen(n)) {
            lst[i] = 1 - lst[i];  // flip
            co_yield lst;
        }
    }

}  // namespace ecgen
