#include <doctest/doctest.h>
#include <ecgen/combin.hpp>
#include <ecgen/gray_code.hpp>

TEST_CASE("Generate Gray code (odd)")
{
    int cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::BRGC_gen(5))
    {
        ++cnt;
    }
    CHECK(cnt == 32);
}

TEST_CASE("Generate Gray code (even)")
{
    int cnt = 1;
    for ([[maybe_unused]] auto i : ecgen::BRGC_gen(6))
    {
        ++cnt;
    }
    CHECK(cnt == 64);
}

TEST_CASE("Generate all combinations")
{
    int cnt = 1;
    for ([[maybe_unused]] auto [x, y] : ecgen::EMK_gen(5, 3))
    {
        ++cnt;
    }
    CHECK(cnt == ecgen::Combination<5, 3>());
}
