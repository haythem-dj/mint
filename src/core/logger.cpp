#include <stdarg.h>

#include <iostream>

#include "mint/core/logger.hpp"

namespace mnt
{
logger::logger() {}

logger::~logger() {}

b8 logger::initialize(const std::string& name)
{
    if (m_is_initialized) return false;

    if (name == "") return false;

    m_name = name;

    m_is_initialized = true;
    return true;
}

void logger::shutdown() {}

void logger::log_message(log_level level, const char* msg, ...)
{
    const char* level_string[6] = {"FATAL", "ERROR", "WARN",
                                   "INFO",  "DEBUG", "TRACE"};
    char msg_out[32000];
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(msg_out, 32000, msg, arg_ptr);
    va_end(arg_ptr);

    char msg_out2[32000];
    sprintf(msg_out2, "[%s][%s]: %s\n", m_name.c_str(), level_string[level],
            msg_out);
    // std::cout << msg_out2;
    console_write(level, msg_out2);
}

void logger::log_message(log_level level, const std::string& message)
{
    log_message(level, message.c_str());
}
}  // namespace mnt
