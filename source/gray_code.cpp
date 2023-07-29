#include <cppcoro/coroutine.hpp> // for cppcoro, suspend_always, coroutine_handle
#include <ecgen/gray_code.hpp>

namespace ecgen {

using namespace cppcoro;

/**
 * @brief Binary Reflexed Gray Code Generator
 *
 * The function `BRGC_gen` is a generator function that generates binary
 * reflexed gray code. It takes an input parameter `n` of type `size_t` and
 * returns a `recursive_generator<size_t>`.
 *
 * @param[in] n
 * @return recursive_generator<size_t>
 */
auto BRGC_gen(size_t n) -> recursive_generator<size_t> {
    if (n < 1) {
        co_return;
    }
    co_yield BRGC_gen(n - 1);
    co_yield n - 1;
    co_yield BRGC_gen(n - 1);
}

} // namespace ecgen
