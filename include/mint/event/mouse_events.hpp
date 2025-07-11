#pragma once

#include "mint/common/defines.hpp"
#include "mint/event/event.hpp"

namespace mnt
{
    class mouse_press : public event
    {
    public:
        mouse_press(u32 button) : m_button(button) {}

        EVENT_CLASS_TYPE(mouse_press);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "mouse press: " << m_button;
            return ss.str();
        }

        inline u32 get_button() const { return m_button; }

    private:
        u32 m_button;
    };

    class mouse_release : public event
    {
    public:
        mouse_release(u32 button) : m_button(button) {}

        EVENT_CLASS_TYPE(mouse_release);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "mouse release: " << m_button;
            return ss.str();
        }

        inline u32 get_button() const { return m_button; }

    private:
        u32 m_button;
    };

    class mouse_move : public event
    {
    public:
        mouse_move(i32 x, i32 y) : m_x(x), m_y(y) {}

        EVENT_CLASS_TYPE(mouse_move);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "mouse move: " << m_x << ", " << m_y;
            return ss.str();
        }

        inline i32 get_x() const { return m_x; }
        inline i32 get_y() const { return m_y; }

    private:
        i32 m_x = 0;
        i32 m_y = 0;
    };

    class mouse_scroll : public event
    {
    public:
        mouse_scroll(i32 delta) : m_delta(delta) {}

        EVENT_CLASS_TYPE(mouse_scroll);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "mouse scroll: " << m_delta;
            return ss.str();
        }

        inline i32 get_delta() const { return m_delta; }

    private:
        i32 m_delta = 0;
    };
} // namespace mnt
