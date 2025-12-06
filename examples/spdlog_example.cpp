#include <ecgen/perm.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

int main() {
    // Initialize spdlog
    auto console = spdlog::stdout_color_mt("console");
    console->set_level(spdlog::level::info);

    console->info("Starting spdlog example with ecgen-cpp");

    // Test permutation generation with logging
    console->info("Generating permutations of 3 elements:");

    int count = 0;
    for (auto perm : ecgen::sjt_gen(3)) {
        console->info("Permutation {}: {}", ++count, perm);
    }

    console->info("Generated {} permutations", count);

    // Test different log levels
    console->debug("This is a debug message");
    console->info("This is an info message");
    console->warn("This is a warning message");
    console->error("This is an error message");

    console->info("Example completed successfully");

    return 0;
}