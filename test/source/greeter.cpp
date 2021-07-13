#include <doctest/doctest.h>
#include <ecgen/greeter.h>
#include <ecgen/version.h>

#include <string>

TEST_CASE("ECGenCpp") {
    using namespace ecgen;

    ECGenCpp ecgen("Tests");

    CHECK(ecgen.greet(LanguageCode::EN) == "Hello, Tests!");
    CHECK(ecgen.greet(LanguageCode::DE) == "Hallo Tests!");
    CHECK(ecgen.greet(LanguageCode::ES) == "¡Hola Tests!");
    CHECK(ecgen.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("ECGenCpp version") {
    static_assert(std::string_view(ECGENCPP_VERSION) == std::string_view("1.0"));
    CHECK(std::string(ECGENCPP_VERSION) == std::string("1.0"));
}
