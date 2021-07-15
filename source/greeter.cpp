#include <ecgen/greeter.h>
#include <fmt/format.h>

using namespace ecgen;

ECGen::ECGen(std::string _name) : name(std::move(_name)) {}

std::string ECGen::greet(LanguageCode lang) const {
    switch (lang) {
        default:
        case LanguageCode::EN:
            return fmt::format("Hello, {}!", name);
        case LanguageCode::DE:
            return fmt::format("Hallo {}!", name);
        case LanguageCode::ES:
            return fmt::format("¡Hola {}!", name);
        case LanguageCode::FR:
            return fmt::format("Bonjour {}!", name);
    }
}
