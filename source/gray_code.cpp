#include <cppcoro/coroutine.hpp> // for cppcoro, suspend_always, coroutine_handle
#include <ecgen/gray_code.hpp>

namespace ecgen {

using namespace cppcoro;

/**
 * @brief Binary Reflexed Gray Code Generator
 *
 * The function `brgc_gen` is a generator function that generates binary
 * reflexed gray code. It takes an input parameter `n` of type `size_t` and
 * returns a `recursive_generator<size_t>`.
 *
 * @param n The parameter `n` represents the number of bits in the binary reflexed gray code sequence
 * to be generated.
 * @return recursive_generator<size_t>
 */
auto brgc_gen(size_t n) -> recursive_generator<size_t> {
    if (n < 1) {
        co_return;
    }
    co_yield brgc_gen(n - 1);
    co_yield n - 1;
    co_yield brgc_gen(n - 1);
}

} // namespace ecgen
