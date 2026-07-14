#include <atomic>

#include <ecgen/logging.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace ecgen {

    namespace {
        std::atomic<bool>& get_logger_init_flag() {
            static std::atomic<bool> flag{false};
            return flag;
        }
    }  // namespace

    void init_logger() { init_logger_with_filter("info"); }

    void init_logger_with_filter(const std::string& filter) {
        auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto logger = std::make_shared<spdlog::logger>("ecgen", console);
        logger->set_level(spdlog::level::from_str(filter));
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        spdlog::set_default_logger(logger);
        get_logger_init_flag().store(true);
    }

    bool try_init_logger() { return try_init_logger_with_filter("info"); }

    bool try_init_logger_with_filter(const std::string& filter) {
        if (is_logger_initialized()) {
            return false;
        }
        try {
            auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto logger = std::make_shared<spdlog::logger>("ecgen", console);
            logger->set_level(spdlog::level::from_str(filter));
            logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
            spdlog::set_default_logger(logger);
            get_logger_init_flag().store(true);
            return true;
        } catch (const spdlog::spdlog_ex&) {
            return false;
        }
    }

    bool is_logger_initialized() { return get_logger_init_flag().load(); }

}  // namespace ecgen
