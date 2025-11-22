#pragma once

/**
 Set Partition

 A set partition of the set [n] = {1,2,3,...,n} is a collection B0,
 B1, ... Bj of disjoint subsets of [n] whose union is [n]. Each Bj
 is called a block. Below we show the partitions of [4]. The periods
 separtate the individual sets so that, for example, 1.23.4 is the
 partition {{1},{2,3},{4}}.
   1 block:  1234
   2 blocks: 123.4   124.3   134.2   1.234   12.34   13.24   14.23
   3 blocks: 1.2.34  1.24.3  14.2.3  13.2.4  12.3.4
   4 blocks: 1.2.3.4

 Each partition above has its blocks listed in increasing order of
 smallest element; thus block 0 contains element 1, block1 contains
 the smallest element not in block 0, and so on. A Restricted Growth
 string (or RG string) is a sring a[1..n] where a[i] is the block in
 whcih element i occurs. Restricted Growth strings are often called
 restricted growth functions. Here are the RG strings corresponding
 to the partitions shown above.

   1 block:  0000
   2 blocks: 0001, 0010, 0100, 0111, 0011, 0101, 0110
   3 blocks: 0122, 0121, 0112, 0120, 0102,

 ...more

 Reference:
 Frank Ruskey. Simple combinatorial Gray codes constructed by
 reversing sublists. Lecture Notes in Computer Science, #762,
 201-208. Also downloadable from
 http://webhome.cs.uvic.ca/~ruskey/Publications/SimpleGray/SimpleGray.html

**/

#include <cppcoro/recursive_generator.hpp>
#include <type_traits>
#include <utility>  // neccessary???

namespace ecgen {

    /**
     * Computes the Stirling number of the second kind, which counts the number of
     * ways to partition a set of N elements into K nonempty subsets. This is
     * implemented recursively using the recurrence relation for Stirling numbers.
     *
     * Example visualization for S(4,2) - partitions of 4 elements into 2 blocks:
     * ```svgbob
     *    {1,2}{3,4}  {1,3}{2,4}  {1,4}{2,3}  {1}{2,3,4}  {1,2,3}{4}  {1,3,4}{2}
     *      1 1 0 0     1 0 1 0     1 0 0 1     0 1 1 1     0 0 0 1     0 1 1 0
     * ```
     *
     * @tparam N
     * @tparam K
     * @return constexpr auto
     */
    template <int N, int K> constexpr auto Stirling2nd() {
        if constexpr (K >= N || K <= 1) {
            return std::integral_constant<size_t, 1U>{};
        } else {
            return std::integral_constant<size_t, Stirling2nd<N - 1, K - 1>()
                                                      + K * Stirling2nd<N - 1, K>()>{};
        }
    }

    /**
     * A recursive generator that produces all set partitions of {1, ..., n} into k
     * nonempty blocks.
     *
     * Example visualization for n=4, k=2 (partitions into 2 blocks):
     * ```svgbob
     *    Set {1,2,3,4} -> {{1,2},{3,4}}  {{1,3},{2,4}}  {{1,4},{2,3}}  {{1},{2,3,4}}  {{1,2,3},{4}}
     *                    Block 0  Block 1  Block 0  Block 1  Block 0  Block 1  Block 0  Block 1   Block 0   Block 1
     * ```
     *
     * @param[in] n - The size of the set to partition.
     * @param[in] k - The number of blocks in the partition.
     * @return A recursive generator that yields std::pair representing each
     * partition.
     */
    extern auto set_partition_gen(int n, int k)
        -> cppcoro::recursive_generator<std::pair<int, int>>;

}  // namespace ecgen
