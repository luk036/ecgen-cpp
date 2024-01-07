#include <cppcoro/coroutine.hpp> // for cppcoro, suspend_always, coroutine_handle
#include <ecgen/combin.hpp>

namespace ecgen {

using namespace cppcoro;
using ret_t = std::pair<int, int>;

// Forward declare
static auto emk_gen_even(int n, int k) -> recursive_generator<ret_t>;
static auto emk_gen_odd(int n, int k) -> recursive_generator<ret_t>;
static auto emk_neg_even(int n, int k) -> recursive_generator<ret_t>;
static auto emk_neg_odd(int n, int k) -> recursive_generator<ret_t>;

/**
 * Generates all k-combinations from a set of n elements using the
 * homogeneous revolving door algorithm.
 *
 * This is an internal implementation function used by the combinatorics
 * library. It recursively generates combinations by pivoting elements
 * in and out of the combination.
 *
 * The algorithm pivots between adding successive elements, removing the
 * last element, and recursively generating the remaining combinations.
 *
 * @param[in] n The parameter `n` represents the total number of elements, and
 * `k` represents the size of each combination.
 * @param[in] k The parameter `k` represents the size of each combination. It
 * determines how many elements are selected from the total number of elements
 * `n` to form a combination.
 * @return recursive_generator<ret_t>
 */
static auto emk_gen_even(int n, int k) -> recursive_generator<ret_t> {
    if (k >= n - 1) {
        co_yield std::make_pair(n - 2, n - 1);
    } else {
        co_yield emk_gen_even(n - 1, k);
        co_yield std::make_pair(n - 2, n - 1);
        if (k == 2) {
            for (int i = n - 3; i != 0; --i) {
                co_yield std::make_pair(i, i - 1);
            }
        } else {
            co_yield emk_neg_odd(n - 2, k - 1);
        }
    }
    co_yield std::make_pair(k - 2, n - 2);
    if (k != 2) {
        co_yield emk_gen_even(n - 2, k - 2);
    }
}

/**
 * @brief Generate all combinations by homogeneous revolving-door
 *
 * `emk_gen` is a function that generates all combinations by using the
 * homogeneous revolving-door algorithm. It takes two parameters `n` and `k`,
 * where `n` is the total number of elements and `k` is the size of each
 * combination.
 *
 * @param[in] n The parameter `n` represents the total number of elements, and
 * `k` represents the size of each combination.
 * @param[in] k The parameter `k` represents the size of each combination. It
 * determines how many elements are selected from the total number of elements
 * `n` to form a combination.
 * @return recursive_generator<ret_t>
 */
static auto emk_gen_odd(int n, int k) -> recursive_generator<ret_t> {
    if (k < n - 1) {
        co_yield emk_gen_odd(n - 1, k);
        co_yield std::make_pair(n - 2, n - 1);
        co_yield emk_neg_even(n - 2, k - 1);
    } else {
        co_yield std::make_pair(n - 2, n - 1);
    }
    co_yield std::make_pair(k - 2, n - 2);
    if (k == 3) {
        for (int i = 0; i != n - 3; ++i) {
            co_yield std::make_pair(i, i + 1);
        }
    } else {
        co_yield emk_gen_odd(n - 2, k - 2);
    }
}

/**
 * @brief Generate all combinations in reverse order by homogeneous
 * revolving-door
 *
 * @param[in] n The parameter `n` represents the total number of elements, and
 * `k` represents the size of each combination.
 * @param[in] k The parameter `k` represents the size of each combination. It
 * determines how many elements are selected from the total number of elements
 * `n` to form a combination.
 * @return recursive_generator<ret_t>
 */
static auto emk_neg_even(int n, int k) -> recursive_generator<ret_t> {
    if (k != 2) {
        co_yield emk_neg_even(n - 2, k - 2);
    }
    co_yield std::make_pair(n - 2, k - 2);
    if (k < n - 1) {
        if (k != 2) {
            co_yield emk_gen_odd(n - 2, k - 1);
        } else {
            for (int i = 0; i != n - 3; ++i) {
                co_yield std::make_pair(i, i + 1);
            }
        }
        co_yield std::make_pair(n - 1, n - 2);
        co_yield emk_neg_even(n - 1, k);
    } else {
        co_yield std::make_pair(n - 1, n - 2);
    }
}

/**
 * @brief Generate all combinations in reverse order by homogeneous
 * revolving-door
 *
 * @param[in] n The parameter `n` represents the total number of elements, and
 * `k` represents the size of each combination.
 * @param[in] k The parameter `k` represents the size of each combination. It
 * determines how many elements are selected from the total number of elements
 * `n` to form a combination.
 * @return recursive_generator<ret_t>
 */
static auto emk_neg_odd(int n, int k) -> recursive_generator<ret_t> {
    if (k == 3) {
        for (int i = n - 3; i != 0; --i) {
            co_yield std::make_pair(i, i - 1);
        }
    } else {
        co_yield emk_neg_odd(n - 2, k - 2);
    }
    co_yield std::make_pair(n - 2, k - 2);
    if (k >= n - 1) {
        co_yield std::make_pair(n - 1, n - 2);
    } else {
        co_yield emk_gen_even(n - 2, k - 1);
        co_yield std::make_pair(n - 1, n - 2);
        co_yield emk_neg_odd(n - 1, k);
    }
}

/**
 * Generates all k-combinations from a set of n elements using the
 * homogeneous revolving door algorithm.
 *
 * This is an exported function that provides the main API for generating
 * combinations. It handles the high-level logic of calling helper functions
 * like emk_gen_even() and emk_gen_odd() based on the parity of k.
 *
 * @param[in] n The parameter `n` represents the total number of elements, and
 * `k` represents the size of each combination.
 * @param[in] k The parameter `k` represents the size of each combination. It
 * determines how many elements are selected from the total number of elements
 * `n` to form a combination.
 * @return recursive_generator<ret_t>
 */
auto emk_comb_gen(int n, int k) -> recursive_generator<ret_t> {
    if (n <= k || k == 0) {
        co_return;
    }
    if (k == 1) {
        for (int i = 0; i != n - 1; ++i) {
            co_yield std::make_pair(i, i + 1);
        }
    }
    if (k % 2 == 0) {
        co_yield emk_gen_even(n, k);
    } else {
        co_yield emk_gen_odd(n, k);
    }
}

} // namespace ecgen
