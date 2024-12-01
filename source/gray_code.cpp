#include <cppcoro/coroutine.hpp>  // for cppcoro, suspend_always, coroutine_handle
#include <ecgen/gray_code.hpp>

namespace ecgen {

    using namespace cppcoro;

    /**
     * @brief Binary Reflexed Gray Code Generator
     *
     * The function `brgc_gen` is a generator function that generates binary
     * reflexed gray code. It takes an input parameter `n` of type `int` and
     * returns a `recursive_generator<int>`.
     *
     * @param[in] n The parameter `n` represents the number of bits in the binary
     * reflexed gray code sequence to be generated.
     * @return recursive_generator<int>
     */
    auto brgc_gen(int n) -> recursive_generator<int> {
        if (n < 1) {
            co_return;
        }
        co_yield brgc_gen(n - 1);
        co_yield n - 1;
        co_yield brgc_gen(n - 1);
    }

}  // namespace ecgen
