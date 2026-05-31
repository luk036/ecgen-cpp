#include <ecgen/set_bipart.hpp>

namespace ecgen {
    static auto gen0_even(int n) -> py::RecursiveGenerator<int>;
    static auto gen1_even(int n) -> py::RecursiveGenerator<int>;
    static auto neg1_even(int n) -> py::RecursiveGenerator<int>;

    /**
     * @brief Set the bipartition gen object
     *
     * The `set_bipart_gen` function generates all bipartitions of a set of size
     * `n` into 2 non-empty subsets.
     *
     * @param[in] n The parameter `n` represents the number of elements in the
     * set.
     * @return py::RecursiveGenerator<int>
     */
    auto set_bipart_gen(int n) -> py::RecursiveGenerator<int> {
        if (n >= 3) {
            co_yield gen0_even(n);
        }
    }

    /**
     * @brief S(n, k, 0) even k (k=2)
     *
     * @param[in] n The parameter `n` represents the number of elements in the
     * set.
     * @return py::RecursiveGenerator<int>
     */
    static auto gen0_even(int n) -> py::RecursiveGenerator<int> {
        if (n < 3) {
            co_return;
        }
        co_yield n - 1;
        co_yield gen1_even(n - 1);  // S(n-1, k, 1).(k-1)
        co_yield n;
        co_yield neg1_even(n - 1);  // S'(n-1, k, 1).(k-2)
    }

    /**
     * @brief S(n, k, 1) even k (k=2)
     *
     * @param[in] n The parameter `n` represents the number of elements in the
     * set.
     * @return py::RecursiveGenerator<int>
     */
    static auto gen1_even(int n) -> py::RecursiveGenerator<int> {
        if (n < 3) {
            co_return;
        }
        co_yield 2;
        co_yield neg1_even(n - 1);
        co_yield n;
        co_yield gen1_even(n - 1);
    }

    /**
     * @brief S'(n, k, 1) even k (k=2)
     *
     * @param[in] n The parameter `n` represents the number of elements in the
     * set.
     * @return py::RecursiveGenerator<int>
     */
    static auto neg1_even(int n) -> py::RecursiveGenerator<int> {
        if (n < 3) {
            co_return;
        }
        co_yield neg1_even(n - 1);
        co_yield n;
        co_yield gen1_even(n - 1);
        co_yield 2;
    }
}  // namespace ecgen
