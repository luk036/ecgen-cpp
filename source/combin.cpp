#include <cppcoro/coroutine.hpp>  // for cppcoro, suspend_always, coroutine_handle
#include <ecgen/combin.hpp>
// #include <vector>  // for vector

namespace ecgen {

    using namespace cppcoro;

    using ret_t = std::tuple<int, int>;

    /**
     * @brief Generate all combinations by homogeneous revolving-door
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto EMK_gen(int n, int k) -> recursive_generator<ret_t> {
        if (n <= k || k == 0) {
            co_return;
        }
        if (k == 1) {
            for (auto i = 0; i != n - 1; ++i) {
                co_yield std::make_tuple(i, i + 1);
            }
        } else {
            co_yield EMK_gen(n - 1, k);
            co_yield std::make_tuple(n - 2, n - 1);
            co_yield EMK_neg(n - 2, k - 1);
            co_yield std::make_tuple(k - 2, n - 2);
            co_yield EMK_gen(n - 2, k - 2);
        }
    }

    /**
     * @brief Generate all combinations in reverse order by homogeneous
     * revolving-door
     *
     * @param n
     * @param k
     * @return recursive_generator<ret_t>
     */
    auto EMK_neg(int n, int k) -> recursive_generator<ret_t> {
        if (n <= k || k == 0) {
            co_return;
        }
        if (k == 1) {
            for (auto i = n - 1; i != 0; --i) {
                co_yield std::make_tuple(i, i - 1);
            }
        } else {
            co_yield EMK_neg(n - 2, k - 2);
            co_yield std::make_tuple(n - 2, k - 2);
            co_yield EMK_gen(n - 2, k - 1);
            co_yield std::make_tuple(n - 1, n - 2);
            co_yield EMK_neg(n - 1, k);
        }
    }

}  // namespace ecgen
