#include <ecgen/gray_code.hpp>

namespace ecgen {

    /**
     * @brief Binary Reflexed Gray Code Generator
     *
     * The function `brgc_gen` is a generator function that generates binary
     * reflexed gray code. It takes an input parameter `n` of type `int` and
     * returns a `py::RecursiveGenerator<int>`.
     *
     * @param[in] n The parameter `n` represents the number of bits in the binary
     * reflexed gray code sequence to be generated.
     * @return py::RecursiveGenerator<int>
     */
    auto brgc_gen(int n) -> py::RecursiveGenerator<int> {
        if (n < 1) {
            co_return;
        }
        co_yield brgc_gen(n - 1);
        co_yield n - 1;
        co_yield brgc_gen(n - 1);
    }

}  // namespace ecgen
