#include <cppcoro/coroutine.hpp>  // for cppcoro, suspend_always, coroutine_handle
#include <ecgen/gray_code.hpp>
// #include <vector>

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

}  // namespace ecgen
