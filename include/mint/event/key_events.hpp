#pragma once

#include "mint/common/defines.hpp"

#include "mint/event/event.hpp"

#include "mint/input/key_codes.hpp"

namespace mnt
{
    class key_press : public event
    {
    public:
        key_press(input::key_code key_code) : m_key_code(key_code) {}

        EVENT_CLASS_TYPE(key_press);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "key press: " << (u32)m_key_code;
            return ss.str();
        }

        inline input::key_code get_key_code() const { return m_key_code; }

    private:
        input::key_code m_key_code = input::key_code::none;
    };

    class key_release : public event
    {
    public:
        key_release(input::key_code key_code) : m_key_code(key_code) {}

        EVENT_CLASS_TYPE(key_release);
        virtual std::string to_string() const override
        {
            std::stringstream ss;
            ss << "key release: " << (u32)m_key_code;
            return ss.str();
        }

        inline input::key_code get_key_code() const { return m_key_code; }

    private:
        input::key_code m_key_code = input::key_code::none;
    };
} // namespace mnt
