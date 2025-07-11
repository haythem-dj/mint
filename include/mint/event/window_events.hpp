#pragma once

#include <sstream>

#include "mint/common/defines.hpp"
#include "mint/event/event.hpp"

namespace mnt
{
    class window_close : public event
    {
    public:
        window_close(i32 code) : m_code(code) {}

        EVENT_CLASS_TYPE(window_close);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "window close: " << m_code;
            return ss.str();
        }

        inline i32 get_code() const { return m_code; }

    private:
        i32 m_code = 0;
    };

    class window_resize : public event
    {
    public:
        window_resize(u32 width, u32 height) : m_width(width), m_height(height) {}

        EVENT_CLASS_TYPE(window_resize);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "window resize: " << m_width << ", " << m_height;
            return ss.str();
        }

        inline u32 get_width() const { return m_width; }
        inline u32 get_height() const { return m_height; }

    private:
        u32 m_width = 0;
        u32 m_height = 0;
    };
} // namespace mnt
