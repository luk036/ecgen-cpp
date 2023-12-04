#include <cassert>
#include <cctype>
#include <cstdio>
#include <ecgen/set_partition_old.hpp>
#include <functional>
#include <utility>

namespace ecgen {
using namespace cppcoro;
using ret_t = std::pair<size_t, size_t>;

inline auto Move(size_t x, size_t y) -> recursive_generator<ret_t> {
    co_yield std::make_pair(x, y);
}

// The lists S(n,k,0) and S(n,k,1) satisfy the following properties.
// 1. Successive RG sequences differ in exactly one position.
// 2. first(S(n,k,0)) = first(S(n,k,1)) = 0^{n-k}0123...(k-1)
// 3. last(S(n,k,0)) = 0^{n-k}12...(k-1)0
// 4. last(S(n,k,1)) = 012...(k-1)0^{n-k}
// Note that first(S'(n,k,p)) = last(S(n,k,p))

static auto gen0_even(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto neg0_even(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto gen1_even(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto neg1_even(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto gen0_odd(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto neg0_odd(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto gen1_odd(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto neg1_odd(size_t n, size_t k) -> recursive_generator<ret_t>;

/**
 * @brief Set the partition gen object
 *
 * The `set_partition_gen` function is a generator function that generates all
 * possible set partitions of a set of size `n` into `k` non-empty subsets. It
 * takes two parameters `n` and `k`, which represent the size of the set and the
 * number of subsets, respectively.
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
auto set_partition_gen_old(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k % 2 == 0)
        co_yield gen0_even(n, k);
    else
        co_yield gen0_odd(n, k);
}

/**
 * @brief S(n,k,0) even k
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
static auto gen0_even(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k > 0 && k < n) {
        co_yield gen0_odd(n - 1, k - 1); // S(n-1, k-1, 0).(k-1)
        co_yield Move(n - 1, k - 1);
        co_yield gen1_even(n - 1, k); // S(n-1, k, 1).(k-1)
        co_yield Move(n, k - 2);
        co_yield neg1_even(n - 1, k); // S'(n-1, k, 1).(k-2)

        for (size_t i = k - 2; i > 1; i -= 2) {
            co_yield Move(n, i - 1);
            co_yield gen1_even(n - 1, k); // S(n-1, k, 1).i
            co_yield Move(n, i - 2);
            co_yield neg1_even(n - 1, k); // S'(n-1, k, 1).(i-1)
        }
    }
}

/**
 * @brief S'(n, k, 0) even k
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
static auto neg0_even(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k > 0 && k < n) {
        for (size_t i = 1; i < k - 2; i += 2) {
            co_yield gen1_even(n - 1, k); // S(n-1, k, 1).(i-1)
            co_yield Move(n, i);
            co_yield neg1_even(n - 1, k); // S'(n-1, k, 1).i
            co_yield Move(n, i + 1);
        }

        co_yield gen1_even(n - 1, k); // S(n-1, k, 1).(k-2)
        co_yield Move(n, k - 1);
        co_yield neg1_even(n - 1, k); // S(n-1, k, 1).(k-1)
        co_yield Move(n - 1, 0);
        co_yield neg0_odd(n - 1, k - 1); // S(n-1, k-1, 1).(k-1)
    }
}

/**
 * @brief S(n, k, 1) even k
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
static auto gen1_even(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k > 0 && k < n) {
        co_yield gen1_odd(n - 1, k - 1);
        co_yield Move(k, k - 1);
        co_yield neg1_even(n - 1, k);
        co_yield Move(n, k - 2);
        co_yield gen1_even(n - 1, k);

        for (size_t i = k - 2; i > 1; i -= 2) {
            co_yield Move(n, i - 1);
            co_yield neg1_even(n - 1, k);
            co_yield Move(n, i - 2);
            co_yield gen1_even(n - 1, k);
        }
    }
}

/**
 * @brief S'(n, k, 1) even k
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
static auto neg1_even(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k > 0 && k < n) {
        for (size_t i = 1; i < k - 2; i += 2) {
            co_yield neg1_even(n - 1, k);
            co_yield Move(n, i);
            co_yield gen1_even(n - 1, k);
            co_yield Move(n, i + 1);
        }

        co_yield neg1_even(n - 1, k);
        co_yield Move(n, k - 1);
        co_yield gen1_even(n - 1, k);
        co_yield Move(k, 0);
        co_yield neg1_odd(n - 1, k - 1);
    }
}

/**
 * @brief S(n, k, 0) odd k
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
static auto gen0_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k > 1 && k < n) {
        co_yield gen1_even(n - 1, k - 1);
        co_yield Move(k, k - 1);
        co_yield neg1_odd(n - 1, k);

        for (size_t i = k - 1; i > 1; i -= 2) {
            co_yield Move(n, i - 1);
            co_yield gen1_odd(n - 1, k);
            co_yield Move(n, i - 2);
            co_yield neg1_odd(n - 1, k);
        }
    }
}

/**
 * @brief S'(n, k, 0) odd k
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
static auto neg0_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k > 1 && k < n) {
        for (size_t i = 1; i < k - 1; i += 2) {
            co_yield gen1_odd(n - 1, k);
            co_yield Move(n, i);
            co_yield neg1_odd(n - 1, k);
            co_yield Move(n, i + 1);
        }

        co_yield gen1_odd(n - 1, k);
        co_yield Move(k, 0);
        co_yield neg1_even(n - 1, k - 1);
    }
}

/**
 * @brief S(n, k, 1) odd k
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
static auto gen1_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k > 1 && k < n) {
        co_yield gen0_even(n - 1, k - 1);
        co_yield Move(n - 1, k - 1);
        co_yield gen1_odd(n - 1, k);

        for (size_t i = k - 1; i > 1; i -= 2) {
            co_yield Move(n, i - 1);
            co_yield neg1_odd(n - 1, k);
            co_yield Move(n, i - 2);
            co_yield gen1_odd(n - 1, k);
        }
    }
}

/**
 * @brief S'(n, k, 1) odd k
 *
 * @param[in] n The parameter `n` represents the size of the set, i.e., the
 * number of elements in the set.
 * @param[in] k The parameter `k` represents the number of non-empty subsets
 * @return recursive_generator<ret_t>
 */
static auto neg1_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k > 1 && k < n) {
        for (size_t i = 1; i < k - 1; i += 2) {
            co_yield neg1_odd(n - 1, k);
            co_yield Move(n, i);
            co_yield gen1_odd(n - 1, k);
            co_yield Move(n, i + 1);
        }

        co_yield neg1_odd(n - 1, k);
        co_yield Move(n - 1, 0);
        co_yield neg0_even(n - 1, k - 1);
    }
}
} // namespace ecgen
