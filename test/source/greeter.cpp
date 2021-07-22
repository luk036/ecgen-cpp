#include <ecgen/greeter.h>
#include <ecgen/version.h>
#include <doctest/doctest.h>

#include <string>

TEST_CASE("undefined behavior") {
    int a = 125;
    int c = 32;
    [[maybe_unused]] int b = a >> c;  // see if your tool can catch the problem
    // std::cout << "125 >> 32 = " << b << "\n";
}

TEST_CASE("ECGen") {
    using namespace ecgen;

    ECGen ecgen("Tests");

    CHECK(ecgen.greet(LanguageCode::EN) == "Hello, Tests!");
    CHECK(ecgen.greet(LanguageCode::DE) == "Hallo Tests!");
    CHECK(ecgen.greet(LanguageCode::ES) == "¡Hola Tests!");
    CHECK(ecgen.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("ECGen version") {
    static_assert(std::string_view(ECGEN_VERSION) == std::string_view("1.0"));
    CHECK(std::string(ECGEN_VERSION) == std::string("1.0"));
}
