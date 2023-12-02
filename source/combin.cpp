#include <cppcoro/coroutine.hpp> // for cppcoro, suspend_always, coroutine_handle
#include <ecgen/combin.hpp>

namespace ecgen {

using namespace cppcoro;
using ret_t = std::pair<size_t, size_t>;

// Forward declare
static auto EMK_gen_even(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto EMK_gen_odd(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto EMK_neg_even(size_t n, size_t k) -> recursive_generator<ret_t>;
static auto EMK_neg_odd(size_t n, size_t k) -> recursive_generator<ret_t>;

/**
 * @brief Generate all combinations by homogeneous revolving-door
 *
 * `EMK_gen` is a function that generates all combinations by using the
 * homogeneous revolving-door algorithm. It takes two parameters `n` and `k`,
 * where `n` is the total number of elements and `k` is the size of each
 * combination.
 *
 * @param[in] n
 * @param[in] k
 * @return recursive_generator<ret_t>
 */
static auto EMK_gen_even(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k >= n - 1) {
        co_yield std::make_pair(n - 2, n - 1);
    } else {
        co_yield EMK_gen_even(n - 1, k);
        co_yield std::make_pair(n - 2, n - 1);
        if (k == 2) {
            for (size_t i = n - 3; i != 0; --i) {
                co_yield std::make_pair(i, i - 1);
            }
        } else {
            co_yield EMK_neg_odd(n - 2, k - 1);
        }
    }
    co_yield std::make_pair(k - 2, n - 2);
    if (k != 2) {
        co_yield EMK_gen_even(n - 2, k - 2);
    }
}

/**
 * @brief Generate all combinations by homogeneous revolving-door
 *
 * `EMK_gen` is a function that generates all combinations by using the
 * homogeneous revolving-door algorithm. It takes two parameters `n` and `k`,
 * where `n` is the total number of elements and `k` is the size of each
 * combination.
 *
 * @param[in] n
 * @param[in] k
 * @return recursive_generator<ret_t>
 */
static auto EMK_gen_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k < n - 1) {
        co_yield EMK_gen_odd(n - 1, k);
        co_yield std::make_pair(n - 2, n - 1);
        co_yield EMK_neg_even(n - 2, k - 1);
    } else {
        co_yield std::make_pair(n - 2, n - 1);
    }
    co_yield std::make_pair(k - 2, n - 2);
    if (k == 3) {
        for (size_t i = 0; i != n - 3; ++i) {
            co_yield std::make_pair(i, i + 1);
        }
    } else {
        co_yield EMK_gen_odd(n - 2, k - 2);
    }
}

/**
 * @brief Generate all combinations in reverse order by homogeneous
 * revolving-door
 *
 * @param[in] n
 * @param[in] k
 * @return recursive_generator<ret_t>
 */
static auto EMK_neg_even(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k != 2) {
        co_yield EMK_neg_even(n - 2, k - 2);
    }
    co_yield std::make_pair(n - 2, k - 2);
    if (k < n - 1) {
        if (k != 2) {
            co_yield EMK_gen_odd(n - 2, k - 1);
        } else {
            for (size_t i = 0; i != n - 3; ++i) {
                co_yield std::make_pair(i, i + 1);
            }
        }
        co_yield std::make_pair(n - 1, n - 2);
        co_yield EMK_neg_even(n - 1, k);
    } else {
        co_yield std::make_pair(n - 1, n - 2);
    }
}

/**
 * @brief Generate all combinations in reverse order by homogeneous
 * revolving-door
 *
 * @param[in] n
 * @param[in] k
 * @return recursive_generator<ret_t>
 */
static auto EMK_neg_odd(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (k == 3) {
        for (size_t i = n - 3; i != 0; --i) {
            co_yield std::make_pair(i, i - 1);
        }
    } else {
        co_yield EMK_neg_odd(n - 2, k - 2);
    }
    co_yield std::make_pair(n - 2, k - 2);
    if (k >= n - 1) {
        co_yield std::make_pair(n - 1, n - 2);
    } else {
        co_yield EMK_gen_even(n - 2, k - 1);
        co_yield std::make_pair(n - 1, n - 2);
        co_yield EMK_neg_odd(n - 1, k);
    }
}

/**
 * @brief Generate all combinations by homogeneous revolving-door
 *
 * `EMK_gen` is a function that generates all combinations by using the
 * homogeneous revolving-door algorithm. It takes two parameters `n` and `k`,
 * where `n` is the total number of elements and `k` is the size of each
 * combination.
 *
 * @param[in] n
 * @param[in] k
 * @return recursive_generator<ret_t>
 */
auto EMK_comb_gen(size_t n, size_t k) -> recursive_generator<ret_t> {
    if (n <= k || k == 0) {
        co_return;
    }
    if (k == 1) {
        for (size_t i = 0; i != n - 1; ++i) {
            co_yield std::make_pair(i, i + 1);
        }
    }
    if (k % 2 == 0) {
        co_yield EMK_gen_even(n, k);
    } else {
        co_yield EMK_gen_odd(n, k);
    }
}

} // namespace ecgen
