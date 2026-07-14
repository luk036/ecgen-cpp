/**
 * @file logging.hpp
 * @brief Logging utilities for ecgen-cpp
 */

#pragma once

#include <string>

namespace ecgen {

    /**
     * @brief Initialize the logger with default filter (info)
     *
     * Initializes spdlog with a stdout color sink at the info level.
     * Call once at program start.
     */
    void init_logger();

    /**
     * @brief Initialize the logger with a specific filter string
     *
     * @param filter Log level string (e.g. "info", "debug", "warn", "error")
     */
    void init_logger_with_filter(const std::string& filter);

    /**
     * @brief Try to initialize the logger with default filter (info)
     *
     * @return true if logger was successfully initialized, false if already initialized
     */
    bool try_init_logger();

    /**
     * @brief Try to initialize the logger with a specific filter string
     *
     * @param filter Log level string (e.g. "info", "debug", "warn", "error")
     * @return true if logger was successfully initialized, false if already initialized
     */
    bool try_init_logger_with_filter(const std::string& filter);

    /**
     * @brief Check if the logger has been initialized
     *
     * @return true if the logger has been initialized
     */
    bool is_logger_initialized();

}  // namespace ecgen
