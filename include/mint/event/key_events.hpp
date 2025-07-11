#pragma once

#include "mint/common/defines.hpp"
#include "mint/event/event.hpp"

namespace mnt
{
    class key_press : public event
    {
    public:
        key_press(u32 key_code) : m_key_code(key_code) {}

        EVENT_CLASS_TYPE(key_press);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "key press: " << m_key_code;
        }

    private:
        u32 m_key_code = 0;
    };

    class key_release : public event
    {
    public:
        key_release(u32 key_code) : m_key_code(key_code) {}

        EVENT_CLASS_TYPE(key_release);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "key release: " << m_key_code;
            return ss.str();
        }

    private:
        u32 m_key_code = 0;
    };
} // namespace mnt
