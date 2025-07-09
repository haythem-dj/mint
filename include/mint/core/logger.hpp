#pragma once

#include <string>

#include "mint/common/defines.hpp"

namespace mnt
{
enum log_level
{
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
};

class MINT_API logger
{
   public:
    logger();
    ~logger();

    b8 initialize(const std::string& name);
    void shutdown();

    void log_message(log_level level, const char* message, ...);
    void log_message(log_level level, const std::string& message);

   private:
    void console_write(log_level leve, const char* msg);

   private:
    b8 m_is_initialized = false;
    std::string m_name;
};
}  // namespace mnt

#define MINT_FATAL(...)                                                   \
    ::mnt::engine::get().get_logger().log_message(::mnt::LOG_LEVEL_FATAL, \
                                                  __VA_ARGS__)
#define MINT_ERROR(...)                                                   \
    ::mnt::engine::get().get_logger().log_message(::mnt::LOG_LEVEL_ERROR, \
                                                  __VA_ARGS__)
#define MINT_WARN(...)                                                   \
    ::mnt::engine::get().get_logger().log_message(::mnt::LOG_LEVEL_WARN, \
                                                  __VA_ARGS__)
#define MINT_INFO(...)                                                   \
    ::mnt::engine::get().get_logger().log_message(::mnt::LOG_LEVEL_INFO, \
                                                  __VA_ARGS__)
#define MINT_DEBUG(...)                                                   \
    ::mnt::engine::get().get_logger().log_message(::mnt::LOG_LEVEL_DEBUG, \
                                                  __VA_ARGS__)
#define MINT_TRACE(...)                                                   \
    ::mnt::engine::get().get_logger().log_message(::mnt::LOG_LEVEL_TRACE, \
                                                  __VA_ARGS__)

#define MINT_ASSERT(x, ...)                                               \
    do                                                                    \
    {                                                                     \
        if ((!x))                                                         \
        {                                                                 \
            MINT_FATAL("Assertion failed at %s, %d", __FILE__, __LINE__); \
            MINT_FATAL(__VA_ARGS__);                                      \
            MINT_DEBUGBREAK();                                            \
        }                                                                 \
    } while (false)
